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

#include "variable_neighborhood.h"
#include "utils.h"
#include "permutation_set_creator.h"

structureoptimizer::VariableNeighborhood::VariableNeighborhood(){
	// Do nothing
}

structureoptimizer::VariableNeighborhood::VariableNeighborhood( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										std::string parametersFile ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->variableCount = bestScoreCalculator.size() ;
	this->gen = boost::mt19937( time( NULL ) ) ;
	
	setParameters( parametersFile ) ;
}

structureoptimizer::VariableNeighborhood::~VariableNeighborhood(){
	// Do nothing
}

void structureoptimizer::VariableNeighborhood::setDefaultParameters(){
	this->maxIterations = 500 ;
}

void structureoptimizer::VariableNeighborhood::setFileParameters( std::map<std::string,std::string> params ){
	if( params.count( "max_iterations" ) )
		sscanf( params[ "max_iterations" ].c_str() , "%d" , &maxIterations ) ;
}

void structureoptimizer::VariableNeighborhood::printParameters(){
	printf( "Max number of iterations: %d\n" , maxIterations ) ;
}

void structureoptimizer::VariableNeighborhood::initialize(){
	current = initializer->generate() ;
	printf( " ======== Greedy Search ======== \n" ) ;
	printf(" === Iteration %d ===\n" , 0 ) ;
	current->print( true ) ;
}

datastructures::BNStructure structureoptimizer::VariableNeighborhood::search_internal(){
	boost::timer::auto_cpu_timer cpu( 6 , "CPU time = %w\n" ) ; // TODO: Rethink location of timer

	int numIterations = 0 ;
	int setType = 0 ;
	for(int i = 0 ; i < maxIterations && !outOfTime ; i++){
		structureoptimizer::PermutationSet* bestNeighbour = findBestNeighbour( current ) ;
		if( !bestNeighbour->isBetter( *current ) ){
			// TODO: Swap from acyclic_behavior to greedy_behavior or viceversa
			printf("<------------------------- Swap from %d to %d\n" , setType , 1 - setType ) ;
			setType = 1 - setType ;
			current = createSet( setType , variableCount , bestScoreCalculators ) ;
			i-- ;
		}
		printf(" === Iteration %d ===\n" , i+1 ) ;
		current = bestNeighbour->clone() ;
		current->print() ;
		numIterations += 1 ;
	}
	printf("Iterations = %d\n" , numIterations ) ;
	t->cancel() ;
	return *(current->getStructure()) ;
}

structureoptimizer::PermutationSet* structureoptimizer::VariableNeighborhood::findBestNeighbour( structureoptimizer::PermutationSet* set ){
	structureoptimizer::PermutationSet* bestN = set->clone() ;
	for(int i = 0 ; i < variableCount - 1 ; i++){
		structureoptimizer::PermutationSet* neighbour = doSwap( set , i ) ;
		if( !neighbour->isBetter( *bestN ) ) continue ;
		bestN = neighbour->clone() ;
	}
	return bestN ;
}

structureoptimizer::PermutationSet* structureoptimizer::VariableNeighborhood::doSwap( structureoptimizer::PermutationSet* set , int index ){
	structureoptimizer::PermutationSet* newSet = set->clone();
	newSet->swap( index , index + 1 ) ;
	return newSet ;
}