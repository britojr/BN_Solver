/* 
 * File:   independence_selection.cpp
 * Author: nonwhite
 * 
 * Created on 13 de marzo de 2016, 09:23 PM
 */

#include <boost/thread.hpp>

#include <queue>
#include <vector>

#include "independence_selection.h"
#include "utils.h"
#include "typedefs.h"

parentselection::IndependenceSelection::IndependenceSelection( scoring::ScoringFunction *scoringFunction ,
														int maxParents , int variableCount ,
														int runningTime , scoring::Constraints *constraints ){
	this->scoringFunction = scoringFunction ;
	this->maxParents = maxParents ;
	this->variableCount = variableCount ;
	this->runningTime = runningTime ;
	this->constraints = constraints ;
}

void parentselection::IndependenceSelection::calculateScores_internal( int variable , FloatMap &pruned , FloatMap& cache ){
	// Get possible parents for variable based on constraints
	std::vector<int> options = constraints->getPossibleParents( variable ) ;
	
	while( !open.empty() && !outOfTime ){
		// Get best approx score
		approxStruct approximation = open.top() ; open.pop() ;
		varset p1 = approximation.second.first ;
		varset p2 = approximation.second.second ;
		float approxScore = approximation.first ;

		// Get real score from approximation
		VARSET_NEW( parents , variableCount ) ;
		VARSET_OR( parents , p1 ) ;
		VARSET_OR( parents , p2 ) ;
		float score = scoringFunction->getFromApproximation( variable , approximation , pruned , cache ) ;
		if( compare( score ) < 0 ){
			cache[ parents ] = score ;
		}

		if( cardinality( parents ) >= maxParents ) continue ;

		// Expand parent set
		VARSET_NEW( superset , variableCount ) ;
		superset = parents ;
		for(int i = 0 ; i < options.size() && !outOfTime ; i++){
			if( options[ i ] == variable ) continue ;
			VARSET_SET( superset , options[ i ] ) ;
			// Expand only if it is not already visited/calculated
			if( constraints->satisfiesConstraints( variable , parents ) ){
				if( !cache.count( superset ) && !openCache.count( superset ) ){
					approxStruct approximation = scoringFunction->approximateScore( variable , superset , pruned , cache ) ;
					open.push( approximation ) ;
					openCache[ superset ] = 0.0 ;
				}
			}
			VARSET_CLEAR( superset , options[ i ] ) ;
		}
	}
	openCache.clear() ;
    t->cancel() ;
}

void parentselection::IndependenceSelection::initialize( int variable , FloatMap &pruned , FloatMap &cache ){
	// Initialize closed
	VARSET_NEW( empty , variableCount ) ;
	VARSET_CLEAR_ALL( empty ) ;
	float score = scoringFunction->calculateScore( variable , empty , pruned , cache ) ;

	if( score < 1 ){
		cache[ empty ] = score ;
	}
	
	// Get possible parents based on constraints
	std::vector<int> options = constraints->getPossibleParents( variable ) ;

	// Add parent set of size 1
	int prunedCount = 0 ;
	for(int i = 0 ; i < options.size() && !outOfTime ; i++){
		if( options[ i ] == variable ) continue ;
		VARSET_NEW( parents , variableCount ) ;
		VARSET_SET( parents , options[ i ] ) ;
		if( constraints->satisfiesConstraints( variable , parents ) ){
			float score = scoringFunction->calculateScore( variable , parents , pruned , cache ) ;
			if( compare( score ) < 0 ){
				cache[ parents ] = score ;
			}else{
				prunedCount++ ;
			}
		}
	}

	if( maxParents == 1 ) return ;

	// Initialize open
	std::priority_queue<approxStruct,std::vector<approxStruct>,compareIndependence> aux ;
	open = aux ;
	openCache.clear() ;
	for(int i = 0 ; i < options.size() - 1 && !outOfTime ; i++){
		if( options[ i ] == variable ) continue ;
		VARSET_NEW( parents , variableCount ) ;
		VARSET_SET( parents , options[ i ] ) ;
		for(int j = i+1 ; j < options.size() && !outOfTime ; j++){
			if( options[ j ] == variable ) continue ;
			VARSET_SET( parents , options[ j ] ) ;
			if( constraints->satisfiesConstraints( variable , parents ) ){
				approxStruct approximation = scoringFunction->approximateScore( variable , parents , pruned , cache ) ;
				if( compare( approximation.first ) < 0 ){
					open.push( approximation ) ;
					openCache[ parents ] = 0.0 ;
				}
			}
			VARSET_CLEAR( parents , options[ j ] ) ;
		}
		VARSET_CLEAR( parents , options[ i ] ) ;
	}
}