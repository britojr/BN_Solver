/* 
 * File:   structure_optimizer_main.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 1:23
 */

#ifndef STRUCTURE_OPTIMIZER_H
#define	STRUCTURE_OPTIMIZER_H

#include "learner_parameters.h"
#include "score_cache.h"
#include "structure_optimizer.h"
#include "structure_optimizer_creator.h"
#include "initializer.h"
#include "initializer_creator.h"
#include "best_score_calculator.h"
#include "best_score_creator.h"
#include "variable.h"

/* The algorithm for structure learning */
std::string structureOptimizerTypeDefault = "greedy_search" ;
std::string structureOptimizerType = structureOptimizerTypeDefault ;
std::string structureOptimizerTypeString = "Algorithm for order-based structure learning. Options: [ greedy_seach , acyclic_selection ]" ;
std::string structureOptimizerTypeShortCut = "algorithm" ;

/* The data structure to use to calculate best parent set scores */
std::string bestScoreCalculatorDefault = "bitwise" ;
std::string bestScoreCalculator = bestScoreCalculatorDefault ;
std::string bestScoreCalculatorShortCut = "bestScore,b" ;

/* The type of initializer to use */
std::string initializerTypeDefault = "random" ;
std::string initializerType = initializerTypeDefault ;
std::string initializerShortCut = "initializer,z" ;

/* Number of solutions to be generated with initializer */
int numSolutionsDefault = 1 ;
int numSolutions = numSolutionsDefault ;
std::string numSolutionsString = "Number of initial solutions to be generated." ;
std::string numSolutionsShortCut = "numSolutions,n" ;

/* Maximum time to obtain results for one initial solution */
int timePerSolutionDefault = 0 ; // Unlimited
int timePerSolution = timePerSolutionDefault ; // Unlimited
std::string timePerSolutionString = "Maximum time for processing each initial solution" ;
std::string timePerSolutionsShortCut = "timePerSolution,e" ;

/* Parameters file for structure learning algorithm */
std::string structureParametersFile ;
std::string structureParametersFileString = "Parameters file for structure learning algorithm" ;
std::string structureParametersFileShortCut = "stparams,j" ;

/* Scoring cache */
scoring::ScoreCache cache ;

void printSolution( datastructures::BNStructure solution ){
	for(int i = 0 ; i < solution.size() ; i++){
		varset vs = solution[ i ]->getParents() ;
		printf( "{" ) ;
		for( int j = 0 ; j < vs.size() ; j++){
			if( i == j && VARSET_GET( vs , j ) ) printf(" #%d# " , j ) ;
			printf("%d" , VARSET_GET( vs , j ) ) ;
		}
		printf( "}" ) ;
		printf("\n" ) ;
	}
}

inline void printSolution( std::string bnetFile , datastructures::BNStructure &solution ){
	if( bnetFile.size() == 0 ) return ;
	FILE *out = fopen( bnetFile.c_str() , "w" ) ;
	datastructures::BayesianNetwork* network = cache.getNetwork() ;
	
	for(int i = 0 ; i < solution.size() ; i++){
		fprintf( out , "%s:" , network->get( i )->getName().c_str() ) ;
		std::vector<int> children = solution[ i ]->getChildrenVector() ;
		for(int j = 0 ; j < children.size() ; j++)
			fprintf( out , " %s" , network->get( children[ j ] )->getName().c_str() ) ;
		fprintf( out , "\n" ) ;
	}

	fclose( out ) ;
}

void structureLearning(){
	printf( "========== STEP: STRUCTURE OPTIMIZATION ========== \n" ) ;
	printf( "Best score calculator: '%s'\n" , bestScoreCalculator.c_str() ) ;
	printf( "Initialization type: '%s'\n" , initializerType.c_str() ) ;
	printf( "Learning algorithm: '%s'\n" , structureOptimizerType.c_str() ) ;
	printf( "Max. time per solution (sec): %d\n" , timePerSolution ) ;

	printf( "Reading score cache.\n" ) ;
	cache.read( scoresFile ) ;
	if( scoresFile.compare( scoresFileDefault ) == 0 )
		remove( scoresFile.c_str() ) ;

	printf( "Creating Best score calculators.\n" ) ;
	std::vector<bestscorecalculators::BestScoreCalculator*> bestScCalc = bestscorecalculators::create( bestScoreCalculator , cache ) ;

	printf( "Creating Initialization heuristic.\n" ) ;
	initializers::Initializer* initializer = initializers::create( initializerType , bestScCalc ) ;

	printf( "Creating the order-based structure learning algorithm\n" ) ;
	structureoptimizer::StructureOptimizer* algorithm = structureoptimizer::create( structureOptimizerType , initializer , bestScCalc , structureParametersFile ) ;
	algorithm->printParameters() ;
	datastructures::BNStructure solution = algorithm->search( numSolutions , timePerSolution ) ;
	printSolution( bnetFile , solution ) ;
}

#endif	/* STRUCTURE_OPTIMIZER_H */