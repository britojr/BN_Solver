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
	this->gen = boost::mt19937( time( NULL ) ) ;
	
	setParameters( parametersFile ) ;
}

structureoptimizer::BeamSearch::~BeamSearch(){
	// Do nothing
}

void structureoptimizer::BeamSearch::setDefaultParameters(){
	this->maxDepth = 10 ;
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
	printf( " ======== Greedy Search ======== \n" ) ;
	printf(" === Iteration %d ===\n" , 0 ) ;
	current.print( true ) ;
}

datastructures::BNStructure structureoptimizer::BeamSearch::search_internal(){
	boost::timer::auto_cpu_timer cpu( 6 , "CPU time = %w\n" ) ; // TODO: Rethink location of timer

	std::priority_queue<structureoptimizer::PermutationSet> q ;
	q.push( current ) ;
	
	structureoptimizer::PermutationSet best = current ;
	std::vector<structureoptimizer::PermutationSet> convergent ;
	for(int i = 0 ; i < maxDepth && !q.empty() && !outOfTime ; i++){
		printf("Depth #%d\n" , i+1 ) ;
		convergent = updateLayer( q ) ;
//		printf("Convergent = %d\n" , convergent.size() ) ;
		for(int j = 0 ; j < convergent.size() ; j++){
			if( convergent[ j ].isBetter( best ) ){
				best = convergent[ j ] ;
			}
		}
	}
	t->cancel() ;
	return datastructures::BNStructure( best , bestScoreCalculators ) ;
}

std::vector<structureoptimizer::PermutationSet> structureoptimizer::BeamSearch::updateLayer(
									std::priority_queue<structureoptimizer::PermutationSet> &q ){
	std::priority_queue<structureoptimizer::PermutationSet> beam ;
	std::vector<structureoptimizer::PermutationSet> convergent ;
	while( !q.empty() && !outOfTime ){
		structureoptimizer::PermutationSet best = q.top() ; q.pop() ;
		printf("\t" ) ; best.print() ;
		std::vector<structureoptimizer::PermutationSet> neighbours = getNeighbours( best ) ;
		printf("\tNeighbours = %d\n" , neighbours.size() ) ;
		if( neighbours.empty() ){
			convergent.push_back( best ) ;
		}else{
			for(int i = 0 ; i < neighbours.size() ; i++){
				printf ("\t\t" ) ; neighbours[ i ].print() ;
				beam.push( neighbours[ i ] ) ;
				if( beam.size() >= queueLength ) beam.pop() ;
			}
		}
	}
	q = beam ;
	return convergent ;
}

std::vector<structureoptimizer::PermutationSet> structureoptimizer::BeamSearch::getNeighbours(
									structureoptimizer::PermutationSet currentState ){
	std::vector<structureoptimizer::PermutationSet> neighbours ;
	// TODO: Improve to get only the 'queueLength' best ones
	for(int i = 0 ; i < variableCount - 1 ; i++){
		structureoptimizer::PermutationSet neighbour = doSwap( currentState , i ) ;
		if( !neighbour.isBetter( currentState ) ) continue ;
		neighbours.push_back( neighbour ) ;
	}
	return neighbours ;
}

structureoptimizer::PermutationSet structureoptimizer::BeamSearch::doSwap(
									structureoptimizer::PermutationSet set , int index ){
	structureoptimizer::PermutationSet newSet( set ) ;
	newSet.swap( index , index + 1 ) ;
	return newSet ;
}