/*
 * File:   GreedySearch.cpp
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 03:37 PM
 */

#include <boost/timer/timer.hpp>
#include <cstdlib>
#include <cstdio>
#include <limits>

#include "greedy_search.h"
#include "utils.h"

structureoptimizer::GreedySearch::GreedySearch(){
	// Do nothing
}

structureoptimizer::GreedySearch::GreedySearch( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										std::string parametersFile ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->variableCount = bestScoreCalculator.size() ;
	this->gen = boost::mt19937( time( NULL ) ) ;

	setParameters( parametersFile ) ;
}

structureoptimizer::GreedySearch::~GreedySearch(){
	// Do nothing
}

void structureoptimizer::GreedySearch::setDefaultParameters(){
	this->performSolutionPerturbation = true ;
	this->numPerturbationSwaps = 3 ;
	this->maxIterations = 500 ;
}

void structureoptimizer::GreedySearch::setFileParameters( std::map<std::string,std::string> params ){
	if( params.count( "perturb_solution" ) ){
		int p ;
		sscanf( params[ "perturb_solution" ].c_str() , "%d" , &p ) ;
		performSolutionPerturbation = ( p > 0 ) ;
	}

	if( params.count( "num_swaps" ) )
		sscanf( params[ "num_swaps" ].c_str() , "%d" , &numPerturbationSwaps ) ;

	if( params.count( "max_iterations" ) ){
		sscanf( params[ "max_iterations" ].c_str() , "%d" , &maxIterations ) ;
		if ( maxIterations <= 0 )
			maxIterations = std::numeric_limits<int>::max() ;
	}
}

void structureoptimizer::GreedySearch::printParameters(){
	printf( "Max number of iterations: %d\n" , maxIterations ) ;
	printf( "Perturb solutions: %s\n" , performSolutionPerturbation ? "true" : "false" ) ;
	if( performSolutionPerturbation )
		printf( "Num. of perturbation swaps: %d\n" , numPerturbationSwaps ) ;
}

void structureoptimizer::GreedySearch::initialize(){
	current = initializer->generate() ;
	printf( " ======== Greedy Search ======== \n" ) ;
	printf(" === Iteration %d ===\n" , 0 ) ;
	current->print( true ) ;
}

datastructures::BNStructure structureoptimizer::GreedySearch::search_internal(){
	boost::timer::auto_cpu_timer cpu( 6 , "CPU time = %w\n" ) ; // TODO: Rethink location of timer

	int numIterations = 0 ;
	for(int i = 0 ; i < maxIterations && !outOfTime ; i++){
		structureoptimizer::PermutationSet* bestNeighbour = findBestNeighbour( current ) ;
		structureoptimizer::PermutationSet* disturbedNeighbour = perturbSet( bestNeighbour ) ;
		if( disturbedNeighbour->isBetter( *bestNeighbour ) ) bestNeighbour = disturbedNeighbour->clone() ;
		if( !bestNeighbour->isBetter( *current ) ) break ;
		printf(" === Iteration %d ===\n" , i+1 ) ;
		current = bestNeighbour->clone() ;
		current->print() ;
		numIterations += 1 ;
	}
	printf("Iterations = %d\n" , numIterations ) ;
	t->cancel() ;
	return *(current->getStructure()) ;
}

structureoptimizer::PermutationSet* structureoptimizer::GreedySearch::findBestNeighbour( structureoptimizer::PermutationSet* set ){
	structureoptimizer::PermutationSet* bestN = set->clone() ;
	for(int i = 0 ; i < variableCount - 1 ; i++){
		structureoptimizer::PermutationSet* neighbour = doSwap( set , i ) ;
		if( !neighbour->isBetter( *bestN ) ) continue ;
		bestN = neighbour->clone() ;
	}
	return bestN ;
}

structureoptimizer::PermutationSet* structureoptimizer::GreedySearch::perturbSet( structureoptimizer::PermutationSet* set ){
	structureoptimizer::PermutationSet* newSet = set->clone() ;
	if( performSolutionPerturbation ){
		// Perform swaps
		for(int i = 0 ; i < numPerturbationSwaps ; i++){
			int idx1 = random_generator( set->size() , gen ) ;
			int idx2 = random_generator( set->size() , gen ) ;
			newSet->swap( idx1 , idx2 ) ;
		}
	}
	return newSet ;
}

structureoptimizer::PermutationSet* structureoptimizer::GreedySearch::doSwap( structureoptimizer::PermutationSet* set , int index ){
	structureoptimizer::PermutationSet* newSet = set->clone();
	newSet->swap( index , index + 1 ) ;
	return newSet ;
}
