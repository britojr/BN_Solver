/* 
 * File:   main.cpp
 * Author: nonwhite
 *
 * Created on 6 de diciembre de 2015, 10:32 AM
 */
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <stdexcept>
#include <vector>

#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include "parent_set_selection_main.h"
#include "structure_optimizer_main.h"

namespace po = boost::program_options ;

int main( int argc , char** argv ){
	std::string description = std::string( "Compute the scores for a csv file.  Example usage: " ) + argv[ 0 ] + " iris.csv iris.pss" ;
	po::options_description desc( description ) ;

	desc.add_options()
		( "dataset" , po::value<std::string> (&datasetFile)->required(), datasetFileString.c_str() )
//		( "bnetFile" , po::value<std::string> (&bnetFile)->required(), bnetFile.c_str() )
		( "delimiter,d" , po::value<char> (&delimiter)->required()->default_value( delimiterDefault ), delimiterString.c_str() )
		( "rMin,m" , po::value<int> (&rMin)->default_value( rMinDefault ), rMinString.c_str() )
		( "maxParents,p" , po::value<int> (&maxParents)->default_value( maxParentsDefault ) , maxParentsString.c_str() )
		( "threads,t" , po::value<int> (&threadCount)->default_value( threadCountDefault ) , threadString.c_str() )
		( "time,r" , po::value<int> (&runningTime)->default_value( runningTimeDefault ) , runningTimeString.c_str() )
		( "hasHeader,s" , hasHeaderString.c_str() )
		( "doNotPrune,o" , pruneString.c_str() )
		( "enableDeCamposPruning,c" , deCamposPruningString.c_str() )
		( "parentSelectionType,q" , po::value<std::string>(&selectionType)->default_value( selectionTypeDefault ) , parentselection::parentSetSelectionString.c_str() )
		( "bestScore,b" , po::value<std::string > (&bestScoreCalculator)->default_value( bestScoreCalculatorDefault ) , bestscorecalculators::bestScoreCalculatorString.c_str() )
		( "initializer,z" , po::value<std::string > (&initializerType)->default_value( initializerTypeDefault ) , initializers::initializerTypeString.c_str() )
		( "numSolutions,n" , po::value<int> (&numSolutions)->default_value( numSolutionsDefault ) , numSolutionsString.c_str() )
		( "maxIterations,k" , po::value<int> (&maxIterations)->default_value( maxIterationsDefault ) , maxIterationsString.c_str() )
		( "help,h" , "Show this help message." ) ;

	po::positional_options_description positionalOptions ;
	positionalOptions.add( "dataset" , 1 ) ;
//	positionalOptions.add( "output" , 1 ) ;

	po::variables_map vm ;
	po::store( po::command_line_parser( argc , argv )
				.options( desc )
				.positional( positionalOptions ).run() , vm ) ;

	if( vm.count( "help" ) || argc == 1 ){
		std::cout << desc ;
		return 0 ;
	}

	po::notify( vm ) ;

	hasHeader = vm.count( "hasHeader" ) ;
	prune = ( vm.count( "doNotPrune" ) == 0 ) ;
	enableDeCamposPruning = vm.count( "enableDeCamposPruning" ) ;

	if( threadCount < 1 ){
		threadCount = 1 ;
	}

	printf( "URLearning, Score Calculator\n" ) ;
	printf( "Dataset file: '%s'\n" , datasetFile.c_str() ) ;
//	printf( "Bnet file: '%s'\n" , bnetFile.c_str() ) ;
	printf( "Delimiter: '%c'\n" , delimiter ) ;
	printf( "r_min: '%d'\n" , rMin ) ;
	printf( "Scoring function: '%s'\n" , sf.c_str() ) ;
	printf( "Maximum parents: '%d'\n" , maxParents ) ;
	printf( "Threads: '%d'\n" , threadCount ) ;
	printf( "Running time (per variable): '%d'\n" , runningTime ) ;
	printf( "Has header: '%s'\n" , ( hasHeader ? "true" : "false" ) ) ;
	printf( "Enable end-of-scoring pruning: '%s'\n" , ( prune ? "true" : "false" ) ) ;
	printf( "Enable DeCampos pruning: '%s'\n" , ( enableDeCamposPruning ? "true" : "false" ) ) ;

	calculateScore() ;

	greedySearch() ;
}