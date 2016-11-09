/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   variable_neighborhood.cpp
 * Author: nonwhite
 * 
 * Created on November 1, 2016, 11:06 AM
 */

#include <boost/timer/timer.hpp>

#include "swap_search.h"
#include "utils.h"
#include "permutation_set_creator.h"

structureoptimizer::SwapSearch::SwapSearch(){
	// Do nothing
}

structureoptimizer::SwapSearch::SwapSearch( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										std::string parametersFile ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->variableCount = bestScoreCalculator.size() ;
	this->gen = boost::mt19937( time( NULL ) ) ;
	
	setParameters( parametersFile ) ;
}

structureoptimizer::SwapSearch::~SwapSearch(){
	// Do nothing
}

void structureoptimizer::SwapSearch::setDefaultParameters(){
	this->maxIterations = 500 ;
}

void structureoptimizer::SwapSearch::setFileParameters( std::map<std::string,std::string> params ){
	if( params.count( "max_iterations" ) )
		sscanf( params[ "max_iterations" ].c_str() , "%d" , &maxIterations ) ;
}

void structureoptimizer::SwapSearch::printParameters(){
	printf( "Max number of iterations: %d\n" , maxIterations ) ;
}

void structureoptimizer::SwapSearch::initialize(){
	current = initializer->generate( structureoptimizer::GREEDY_BEHAVIOR_SET ) ;
	printf( " ======== Swap Search ======== \n" ) ;
	printf(" === Iteration %d ===\n" , 0 ) ;
	current->print( true ) ;
}

datastructures::BNStructure structureoptimizer::SwapSearch::search_internal(){
	boost::timer::auto_cpu_timer cpu( 6 , "CPU time = %w\n" ) ; // TODO: Rethink location of timer

	int numIterations = 0 ;
	int setType = 0 ;
	structureoptimizer::PermutationSet* bestSol = NULL ;
	for(int i = 0 ; i < maxIterations && !outOfTime ; i++){
		structureoptimizer::PermutationSet* bestNeighbour = findBestNeighbour( current ) ;
		if( !bestNeighbour->isBetter( *current ) ){
			printf("Swap = %s\n" , setType == 0 ? "Greedy -> Acyclic" : "Acyclic -> Greedy" ) ;
			setType = 1 - setType ;
			current = createSet( setType , variableCount , bestScoreCalculators ) ;
		}else{
			current = bestNeighbour->clone() ;
		}
		printf(" === Iteration %d ===\n" , i+1 ) ;
		current->print() ;
		numIterations += 1 ;
		if( bestSol == NULL || current->isBetter( *bestSol ) )
			bestSol = current->clone() ;
	}
	printf("Iterations = %d\n" , numIterations ) ;
	t->cancel() ;
	return *(bestSol->getStructure()) ;
}

structureoptimizer::PermutationSet* structureoptimizer::SwapSearch::findBestNeighbour( structureoptimizer::PermutationSet* set ){
	structureoptimizer::PermutationSet* bestN = set->clone() ;
	for(int i = 0 ; i < variableCount - 1 ; i++){
		structureoptimizer::PermutationSet* neighbour = doSwap( set , i ) ;
		if( !neighbour->isBetter( *bestN ) ) continue ;
		bestN = neighbour->clone() ;
	}
	return bestN ;
}

structureoptimizer::PermutationSet* structureoptimizer::SwapSearch::doSwap( structureoptimizer::PermutationSet* set , int index ){
	structureoptimizer::PermutationSet* newSet = set->clone();
	newSet->swap( index , index + 1 ) ;
	return newSet ;
}