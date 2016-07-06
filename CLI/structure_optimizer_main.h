/* 
 * File:   structure_optimizer_main.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 1:23
 */

#ifndef STRUCTURE_OPTIMIZER_H
#define	STRUCTURE_OPTIMIZER_H

#include "utils_main.h"
#include "score_cache.h"
#include "structure_optimizer.h"
#include "structure_optimizer_creator.h"
#include "initializer.h"
#include "initializer_creator.h"
#include "best_score_calculator.h"
#include "best_score_creator.h"

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

/* Number of iterations for greedy search until stopping */
int maxIterationsDefault = 500 ;
int maxIterations = maxIterationsDefault ;
std::string maxIterationsString = "Max number of iterations in order-based structure learning." ;
std::string maxIterationsShortCut = "maxIterations,k" ;

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

void structureLearning(){
	printf( "========== STEP: STRUCTURE OPTIMIZATION ========== \n" ) ;
	printf( "Best score calculator: '%s'\n" , bestScoreCalculator.c_str() ) ;
	printf( "Initialization type: '%s'\n" , initializerType.c_str() ) ;
	printf( "Learning algorithm: '%s'\n" , structureOptimizerType.c_str() ) ;

	printf( "Reading score cache.\n" ) ;
	scoring::ScoreCache cache ;
	cache.read( scoresFile ) ;
	if( scoresFile.compare( scoresFileDefault ) == 0 )
		remove( scoresFile.c_str() ) ;

	printf( "Creating Best score calculators.\n" ) ;
	std::vector<bestscorecalculators::BestScoreCalculator*> bestScCalc = bestscorecalculators::create( bestScoreCalculator , cache ) ;

	printf( "Creating Initialization heuristic.\n" ) ;
	initializers::Initializer* initializer = initializers::create( initializerType , bestScCalc ) ;

	printf( "Creating the order-based structure learning algorithm\n" ) ;
	structureoptimizer::StructureOptimizer* algorithm = structureoptimizer::create( structureOptimizerType , initializer , bestScCalc , maxIterations ) ;
	datastructures::BNStructure solution = algorithm->search( numSolutions ) ;
	printSolution( solution ) ;
}

#endif	/* STRUCTURE_OPTIMIZER_H */