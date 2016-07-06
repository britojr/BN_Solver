/* 
 * File:   SequentialSelection.cpp
 * Author: nonwhite
 * 
 * Created on 13 de marzo de 2016, 08:49 PM
 */
#include <boost/thread.hpp>

#include <queue>

#include "utils.h"
#include "sequential_selection.h"

parentselection::SequentialSelection::SequentialSelection( scoring::ScoringFunction *scoringFunction ,
														int maxParents , int variableCount ,
														int runningTime , scoring::Constraints *constraints ){
	this->scoringFunction = scoringFunction ;
	this->maxParents = maxParents ;
	this->variableCount = variableCount ;
	this->runningTime = runningTime ;
	this->constraints = constraints ;
}

void parentselection::SequentialSelection::calculateScores_internal( int variable , FloatMap &pruned , FloatMap& cache ){
	int prunedCount = 0 ;
	std::vector<int> options = constraints->getPossibleParents( variable ) ;
	while( !open.empty() && !outOfTime ){
		varset parents = open.front() ; open.pop() ;
		float score = scoringFunction->calculateScore( variable , parents , pruned , cache ) ;
		if( compare( score ) < 0 ){
			cache[ parents ] = score ;
		}else{
			prunedCount++ ;
		}
		
		if( cardinality( parents ) >= maxParents ) continue ;
		
		// Expand parent set
		VARSET_NEW( superset , variableCount ) ;
		superset = parents ;
		for(int i = 0 ; i < options.size() && !outOfTime ; i++){
			if( options[ i ] == variable ) continue ;
			VARSET_SET( superset , options[ i ] ) ;
			// Expand only if it is not already visited/calculated
			if( constraints->satisfiesConstraints( variable , superset ) ){
				if( !cache.count( superset ) && !openCache.count( superset ) ){
					open.push( superset ) ;
					openCache[ superset ] = 0.0 ;
				}
			}
			VARSET_CLEAR( superset , options[ i ] ) ;
		}
	}
    t->cancel() ;
}

void parentselection::SequentialSelection::initialize( int variable , FloatMap &pruned , FloatMap &cache ){
	// Initialize closed
	VARSET_NEW( empty , variableCount ) ;
	VARSET_CLEAR_ALL( empty ) ;
	float score = scoringFunction->calculateScore( variable , empty , pruned , cache ) ;
	if( score < 1 ){
		cache[ empty ] = score ;
	}

	// Initialize open
	std::queue<varset> aux ;
	open = aux ;
	open.push( empty ) ;
	openCache.clear() ;
}