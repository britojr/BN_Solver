/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   beam_search.cpp
 * Author: nonwhite
 * 
 * Created on October 20, 2016, 3:52 PM
 */
#include <boost/timer/timer.hpp>

#include <queue>

#include "beam_list.h"
#include "beam_search.h"

structureoptimizer::BeamSearch::BeamSearch(){
	// Do nothing
}

structureoptimizer::BeamSearch::BeamSearch( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										std::string parametersFile ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->variableCount = bestScoreCalculator.size() ;
	
	setParameters( parametersFile ) ;
}

structureoptimizer::BeamSearch::~BeamSearch(){
	// Do nothing
}

void structureoptimizer::BeamSearch::setDefaultParameters(){
	this->maxDepth = 500 ;
	this->queueLength = log( variableCount ) ;
}

void structureoptimizer::BeamSearch::setFileParameters( std::map<std::string,std::string> params ){
	if( params.count( "max_depth" ) )
		sscanf( params[ "max_depth" ].c_str() , "%d" , &maxDepth ) ;
	
	if( params.count( "queue_length" ) )
		sscanf( params[ "queue_length" ].c_str() , "%d" , &queueLength ) ;
}

void structureoptimizer::BeamSearch::printParameters(){
	printf( "Max Depth: %d\n" , maxDepth ) ;
	printf( "Queue length: %d\n" , queueLength ) ;
}

void structureoptimizer::BeamSearch::initialize(){
	current = initializer->generate() ;
	printf( " ======== Beam Search ======== \n" ) ;
	printf(" === Iteration %d ===\n" , 0 ) ;
	current->print( true ) ;
}

datastructures::BNStructure structureoptimizer::BeamSearch::search_internal(){
	boost::timer::auto_cpu_timer cpu( 6 , "CPU time = %w\n" ) ; // TODO: Rethink location of timer

	datastructures::BeamList<> q( queueLength ) ;
	q.add( current ) ;

	structureoptimizer::PermutationSet* best = current ;
	std::vector<structureoptimizer::PermutationSet*> convergent ;
	int numIterations = 0 ;
	for(int k = 0 ; k < maxDepth && !q.empty() && !outOfTime ; k++,numIterations++){
		updateLayer( q ) ;
		if( !q.empty() && (*q.top()) < (*best) ){
			best = q.top()->clone() ;
			printf(" === Iteration %d ===\n" , k+1 ) ;
			best->print() ;
		}
	}
	printf("Iterations = %d\n" , numIterations ) ;
	t->cancel() ;
	return datastructures::BNStructure( best , bestScoreCalculators ) ;
}

void structureoptimizer::BeamSearch::updateLayer( datastructures::BeamList<> &q ){
	datastructures::BeamList<> beam( queueLength ) ;
	while( !q.empty() && !outOfTime ){
		structureoptimizer::PermutationSet* best = q.pop()->clone() ;
		datastructures::BeamList<> neighbours = getNeighbours( best ) ;
		if( !neighbours.empty() )
			beam.add( neighbours ) ;
	}
	q = beam ;
}

datastructures::BeamList<> structureoptimizer::BeamSearch::getNeighbours(
									structureoptimizer::PermutationSet* currentState ){
	datastructures::BeamList<> neighbours( queueLength ) ;
	for(int i = 0 ; i < variableCount - 1 ; i++){
		structureoptimizer::PermutationSet* neighbour = doSwap( currentState , i ) ;
		if( !neighbour->isBetter( *currentState ) ) continue ; // Prune worse solutions
		neighbours.add( neighbour->clone() ) ;
	}
	return neighbours ;
}

structureoptimizer::PermutationSet* structureoptimizer::BeamSearch::doSwap(
									structureoptimizer::PermutationSet* set , int index ){
	structureoptimizer::PermutationSet* newSet = set->clone() ;
	newSet->swap( index , index + 1 ) ;
	return newSet ;
}