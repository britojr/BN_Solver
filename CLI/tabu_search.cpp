/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TabuSearch.cpp
 * Author: nonwhite
 * 
 * Created on September 5, 2016, 3:37 PM
 */
#include <boost/timer/timer.hpp>

#include "tabu_search.h"
#include "tabu_list.h"

structureoptimizer::TabuSearch::TabuSearch(){
	// Do nothing
}

structureoptimizer::TabuSearch::TabuSearch( initializers::Initializer* initializer ,
								std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
								std::string parametersFile ){
	this->variableCount = bestScoreCalculator.size() ;
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->gen = boost::mt19937( time( NULL ) ) ;

	setParameters( parametersFile ) ;
	
	this->tabuList = datastructures::TabuList( lengthTabuList , variableCount ) ;
}

structureoptimizer::TabuSearch::~TabuSearch(){
	// Do nothing
}

void structureoptimizer::TabuSearch::setDefaultParameters(){
	this->lengthTabuList = 0.2 * variableCount ;
	this->maxIterations = 500 ;
	this->useAspirationCriterion = false ;
}

void structureoptimizer::TabuSearch::setFileParameters( std::map<std::string, std::string> params ){
	if( params.count( "max_iterations" ) )
		sscanf( params[ "max_iterations" ].c_str() , "%d" , &maxIterations ) ;
	
	if( params.count( "length_tabu_list" ) )
		sscanf( params[ "length_tabu_list" ].c_str() , "%d" , &lengthTabuList ) ;
	
	if( params.count( "use_aspiration_criterion" ) ){
		int p ;
		sscanf( params[ "use_aspiration_criterion" ].c_str() , "%d" , &p ) ;
		useAspirationCriterion = ( p > 0 ) ;
	}
}

void structureoptimizer::TabuSearch::printParameters(){
	printf( "Max number of iterations: %d\n" , maxIterations ) ;
	printf( "Length of tabu list: %d\n" , lengthTabuList ) ;
	printf( "Use aspiration criterion: %s\n" , useAspirationCriterion ? "true" : "false" ) ;
}

void structureoptimizer::TabuSearch::initialize(){
	tabuList.clear() ;
	current = initializer->generate() ;
	printf( " ======== Tabu Search ======== \n" ) ;
	printf(" === Iteration %d ===\n" , 0 ) ;
	current->print( true ) ;
}

datastructures::BNStructure structureoptimizer::TabuSearch::search_internal(){
	boost::timer::auto_cpu_timer cpu( 6 , "CPU time = %w\n" ) ; // TODO: Rethink location of timer
	
	int numIterations = 0 ;
	for(int i = 0 ; i < maxIterations && !outOfTime ; i++,numIterations++){
		structureoptimizer::PermutationSet* bestNeighbour = findBestNeighbour( current ) ;
		if( !bestNeighbour->isBetter( *current ) ) break ;
		tabuList.add( (*current)[ bestSwap ] , (*current)[ bestSwap + 1 ] ) ;
		printf(" === Iteration %d ===\n" , i+1 ) ;
		current = bestNeighbour ;
		current->print() ;
	}
	printf("Iterations = %d\n" , numIterations ) ;
	t->cancel() ;
	return datastructures::BNStructure( current , bestScoreCalculators ) ;
}

structureoptimizer::PermutationSet* structureoptimizer::TabuSearch::findBestNeighbour(
														structureoptimizer::PermutationSet* currentState ){
	structureoptimizer::PermutationSet* bestN = currentState ;
//	int cont = 0 ;
	for(int i = 0 ; i < variableCount - 1 ; i++){
		if( !useAspirationCriterion && isTabuMove( currentState , i ) ){
//			cont++ ;
			continue ;
		}
		structureoptimizer::PermutationSet* neighbour( currentState ) ;
		neighbour->swap( i , i + 1 ) ;
		if( !neighbour->isBetter( *bestN ) ) continue ;
		bestN = neighbour ;
		bestSwap = i ;
	}
//	if( cont > 1 ) printf("Tabu moves: %d\n" , cont ) ; // TODO: Delete this
	return bestN ;
}

bool structureoptimizer::TabuSearch::isTabuMove( structureoptimizer::PermutationSet* currentState , int swapIndex ){
	int variable1 = (*currentState)[ swapIndex + 0 ] ;
	int variable2 = (*currentState)[ swapIndex + 1 ] ;
	return tabuList.has( variable1 , variable2 ) ;
}
