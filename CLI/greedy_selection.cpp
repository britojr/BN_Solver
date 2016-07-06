/* 
 * File:   greedy_selection.cpp
 * Author: nonwhite
 * 
 * Created on 13 de marzo de 2016, 09:23 PM
 */
#include <boost/thread.hpp>

#include <queue>
#include <vector>

#include "greedy_selection.h"
#include "utils.h"
#include "typedefs.h"

parentselection::GreedySelection::GreedySelection( scoring::ScoringFunction *scoringFunction ,
													int maxParents , int variableCount ,
													int runningTime , scoring::Constraints *constraints ){
	this->scoringFunction = scoringFunction ;
	this->maxParents = maxParents ;
	this->variableCount = variableCount ;
	this->runningTime = runningTime ;
	this->constraints = constraints ;
}

void parentselection::GreedySelection::calculateScores_internal( int variable , FloatMap &pruned , FloatMap& cache ){
	int prunedCount = 0 ;
	std::vector<int> options = constraints->getPossibleParents( variable ) ;
	while( !open.empty() && !outOfTime ){
		pqelem node = open.top() ; open.pop() ;
		
		VARSET_NEW( best , variableCount ) ;
		best = node.first ;
		if( cardinality( best ) >= maxParents ) continue ;
		VARSET_NEW( superset , variableCount ) ;
		superset = best ;
		for(int i = 0 ; i < options.size() && !outOfTime ; i++){
			if( options[ i ] == variable ) continue ;
			VARSET_SET( superset , options[ i ] ) ;
			if( constraints->satisfiesConstraints( variable , superset ) ){
				if( !cache.count( superset ) && !openCache.count( superset ) ){
					float score = scoringFunction->calculateScore( variable , superset , pruned , cache ) ;
					if( score < 0 ){
						cache[ superset ] = score ;
						open.push( PAIR( superset , score ) ) ;
						openCache[ superset ] = 0.0 ;
					}else{
						prunedCount++ ;
					}
				}
			}
			VARSET_CLEAR( superset , options[ i ] ) ;
		}
	}
    t->cancel() ;
}

void parentselection::GreedySelection::initialize( int variable , FloatMap &pruned , FloatMap &cache ){
	// Initialize closed
	VARSET_NEW( empty , variableCount ) ;
	float score = scoringFunction->calculateScore( variable , empty , pruned , cache ) ;

	if( score < 1 ){
		cache[ empty ] = score ;
	}

	// Initialize open
	std::priority_queue<pqelem,std::vector<pqelem>,compareGreedy> aux ;
	open = aux ;
	openCache.clear() ;
	for(int i = 0 ; i < variableCount && !outOfTime ; i++){
		if( i == variable ) continue ;
		VARSET_NEW( parents , variableCount ) ;
		VARSET_SET( parents , i ) ;
		float score = scoringFunction->calculateScore( variable , parents , pruned , cache ) ;
		if( score < 0 ){
			cache[ parents ] = score ;
			open.push( PAIR( parents , score ) ) ;
			openCache[ parents ] = 0.0 ;
		}
	}	
}