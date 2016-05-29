/* 
 * File:   parent_set_selection_main.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 1:23
 */

#ifndef SCORER_H
#define	SCORER_H

#include <cstdlib>
#include <ctime>
#include <math.h>
#include <stdexcept>
#include <vector>

#include <boost/thread.hpp>

#include "utils_main.h"
#include "record_file.h"
#include "bayesian_network.h"
#include "ad_tree.h"
#include "score_cache.h"
#include "scoring_function.h"
#include "scoring_function_creator.h"
#include "parent_set_selection.h"
#include "parent_set_selection_creator.h"
#include "node.h"
#include "utils.h"
#include "files.h"

namespace po = boost::program_options ;

/* The delimiter in each line of data file */
char delimiterDefault = ',' ;
char delimiter = delimiterDefault ;
std::string delimiterString = "The delimiter of the input file." ;
std::string delimiterShortCut = "delimiter,d" ;

/* The minimum number of records in the AD-tree */
int rMinDefault = 5 ;
int rMin = rMinDefault ;
std::string rMinString = "The minimum number of records in the AD-tree nodes." ;
std::string rMinShortCut = "rMin,m" ;

/* A hard limit on the size of parent sets */
int maxParentsDefault = 0 ;
int maxParents = maxParentsDefault ;
std::string maxParentsString = "The maximum number of parents for any variable. A value less than 1 means no limit." ;
std::string maxParentsShortCut = "maxParents,p" ;

/* The number of threads to use */
int threadCountDefault = 1 ;
int threadCount = threadCountDefault ;
std::string threadString = "The number of separate threads to use for score calculations." ;
std::string threadCountShortCut = "threads,t" ;

/* The maximum amount of time to use for each variable */
int runningTimeDefault = 0 ;
int runningTime = runningTimeDefault ;
std::string runningTimeString = "The maximum amount of time to use for each variable. A value less than 1 means no limit." ;
std::string runningTimeShortCut = "time,r" ;

/* Whether the data file has variable names in the first row */
bool hasHeader = false ;
std::string hasHeaderString = "Add this flag if the first line of the input file gives the variable names." ;
std::string hasHeaderShortCut = "hasHeader,s" ;

/* Whether to prune the scores before printing */
bool prune = true ;
std::string pruneString = "Add this flag if the scores should NOT be pruned at the end of the search." ;
std::string pruneShortCut = "doNotPrune,o" ;

/* Whether to use deCampos-style pruning */
bool enableDeCamposPruning = true ;
std::string deCamposPruningString = "Add this flag if the scores should be pruned while calculating." ;
std::string deCamposPruningShortCut = "enableDeCamposPruning,c" ;

/* Method to select parent sets */
std::string selectionTypeDefault = "sequential" ;
std::string selectionType = selectionTypeDefault ;
std::string selectionTypeShortCut = "parentSelectionType,q" ;

/* File specifying constraints on the scores */
std::string constraintsFile ;

/* The scoring function to use */
std::string sfDefault = "BIC" ;
std::string sf = sfDefault ;
std::string sfShortCut = "scoreFunction,f" ;
std::string sfString = "Scoring function used. Options: 'bic'" ;

/* A reference to the scoring function object */
scoring::ScoringFunction *scoringFunction ;

/* The network information */
datastructures::BayesianNetwork network ;

/* The constraints information */
scoring::Constraints *constraints ;

void scoringThread( int thread ){
	parentselection::ParentSetSelection* pss = 
			parentselection::create( selectionType , scoringFunction ,
									maxParents , network.size() ,
									runningTime , constraints ) ;
	for( int variable = 0 ; variable < network.size() ; variable++ ){
		if( variable % threadCount != thread ){
			continue ;
		}

		std::string varFilename = scoresFile + "." + TO_STRING( variable ) ;
		if( file_exists( varFilename ) ) continue ;

		printf( "Thread: %d , Variable: %d , Time: %s\n" , thread , variable , getTime().c_str() ) ;

		FloatMap sc ;
		init_map( sc ) ;
		pss->calculateScores( variable , sc ) ;

		int size = sc.size() ;
		printf( "Thread: %d , Variable: %d , Size before pruning: %d , Time: %s\n" , thread , variable , size , getTime().c_str() ) ;

		if( prune ){
			pss->prune( sc ) ;
			int prunedSize = sc.size() ;
			printf( "Thread: %d , Variable: %d , Size after pruning: %d , Time: %s\n" , thread , variable , prunedSize , getTime().c_str() ) ;
		}

		createVariableScoreFile( varFilename , network , variable , sc ) ;
		
		sc.clear() ;
	}
}

void calculateScore(){
	printf( "Parsing input file.\n" ) ;
	datastructures::RecordFile recordFile( datasetFile , delimiter , hasHeader ) ;
	recordFile.read() ;

	printf( "Initializing data specifications.\n" ) ;
	network.initialize( recordFile ) ;

	printf( "Creating AD-tree.\n" ) ;
	scoring::ADTree *adTree = new scoring::ADTree( rMin ) ;
	adTree->initialize( network , recordFile ) ;
	adTree->createTree() ;

	constraints = NULL ;
	if( constraintsFile.length() > 0 )
		constraints = scoring::parseConstraints( constraintsFile , network ) ;

	printf( "Creating the score function calculator\n" ) ;
	scoringFunction = scoring::create( sf , adTree , network , recordFile , constraints , enableDeCamposPruning ) ;
	maxParents = scoring::parentsize( sf, maxParents , network , recordFile ) ;
	
	std::vector<boost::thread*> threads ;
	for( int thread = 0 ; thread < threadCount ; thread++){
		boost::thread *workerThread = new boost::thread( scoringThread , thread ) ;
		threads.push_back( workerThread ) ;
	}

	for( auto it = threads.begin() ; it != threads.end() ; it++)
		( *it )->join() ;

	// concatenate all of the files together
	std::map<std::string,std::string> metadata ;
	metadata[ "datasetFile" ] = datasetFile ;
	metadata[ "variableCount" ] = TO_STRING( network.size() ) ;
	metadata[ "numRecords" ] = TO_STRING( recordFile.size() ) ;
	metadata[ "maxParents" ] = TO_STRING( maxParents ) ;
	metadata[ "scoringFunction" ] = sf ;
	metadata[ "parentSelection" ] = selectionType ;
	concatenateScoreFiles( scoresFile , metadata ) ;
}

#endif	/* SCORER_H */