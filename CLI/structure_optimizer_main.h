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
#include "greedy_search.h"
#include "initializer.h"
#include "initializer_creator.h"
#include "best_score_calculator.h"
#include "best_score_creator.h"

/* The data structure to use to calculate best parent set scores */
std::string bestScoreCalculatorDefault = "bitwise" ;
std::string bestScoreCalculator = bestScoreCalculatorDefault ;

/* The type of initializer to use */
std::string initializerTypeDefault = "random" ;
std::string initializerType = initializerTypeDefault ;

/* Number of solutions to be generated with initializer */
int numSolutionsDefault = 1 ;
int numSolutions = numSolutionsDefault ;
std::string numSolutionsString = "Number of initial solutions to be generated." ;

/* Number of iterations for greedy search until stopping */
int maxIterationsDefault = 500 ;
int maxIterations = maxIterationsDefault ;
std::string maxIterationsString = "Max number of iterations in greedy search." ;

void greedySearch(){
	printf( "Scores file: '%s'\n" , scoresFile.c_str() ) ;
	//    printf("Net file: '%s'\n", netFile.c_str());
	printf( "Best score calculator: '%s'\n" , bestScoreCalculator.c_str() ) ;
	printf( "Initialization type: '%s'\n" , initializerType.c_str() ) ;

	printf( "Reading score cache.\n" ) ;
	scoring::ScoreCache cache ;
	cache.read( scoresFile ) ;
//	remove( scoresFile.c_str() ) ; // TODO: Check this

	printf( "Creating Best score calculators.\n" ) ;
	std::vector<bestscorecalculators::BestScoreCalculator*> bestScCalc = bestscorecalculators::create( bestScoreCalculator , cache ) ;

	printf( "Creating Initialization heuristic.\n" ) ;
	initializers::Initializer* initializer = initializers::create( initializerType , bestScCalc ) ;

	greedysearch::GreedySearch* algorithm = new greedysearch::GreedySearch( initializer , bestScCalc , maxIterations ) ;
	std::vector<greedysearch::Node*> solution = algorithm->search( numSolutions ) ;
}

#endif	/* STRUCTURE_OPTIMIZER_H */

