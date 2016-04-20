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

void parentselection::IndependenceSelection::calculateScores( int variable , FloatMap &cache ){
	this->outOfTime = false ;

	io.reset() ;
	boost::asio::deadline_timer *t ;
	boost::asio::io_service io_t ;
	t = new boost::asio::deadline_timer( io_t ) ;
	
	FloatMap pruned ;
	init_map( pruned ) ;
	initialize( variable , pruned , cache ) ;
	if( runningTime > 0 ){
		printf( "I am using a timer in the calculation function.\n" ) ;
		t->expires_from_now( boost::posix_time::seconds( runningTime ) ) ;
		t->async_wait( boost::bind( &parentselection::ParentSetSelection::timeout, this, boost::asio::placeholders::error ) ) ;
		boost::thread workerThread ;

		workerThread = boost::thread( 
				boost::bind( &parentselection::IndependenceSelection::calculateScores_internal ,
							this , variable , boost::ref( pruned ) , boost::ref( cache )
				) 
		) ;
		io_t.run() ;
		workerThread.join() ;
		io_t.stop() ;
		t->cancel() ;
	}else{
		printf("I am executing without time limit\n" ) ;
		calculateScores_internal( variable , pruned , cache ) ;
	}
}

void parentselection::IndependenceSelection::calculateScores_internal( int variable , FloatMap &pruned , FloatMap& cache ){
	while( !open.empty() && !outOfTime ){
		// Get best approx score
		approxStruct best = open.top() ; open.pop() ;
		varset p1 = best.second.first ;
		varset p2 = best.second.second ;
		float approxValue = best.first ;

		// Get real score from approximation
		VARSET_NEW( parents , variableCount ) ;
		VARSET_OR( parents , p1 ) ;
		VARSET_OR( parents , p2 ) ;
		float score = scoringFunction->getFromApproximation( variable , p1 , p2 , approxValue , pruned , cache ) ;
		if( compare( score ) < 0 ){
			cache[ parents ] = score ;
		}

		if( cardinality( parents ) >= maxParents ) continue ;

		// Expand parent set
		VARSET_NEW( superset , variableCount ) ;
		superset = parents ;
		for(int i = 0 ; i < variableCount && !outOfTime ; i++){
			if( i == variable ) continue ;
			VARSET_SET( superset , i ) ;
			// Expand only if it is not already visited/calculated
			if( !cache.count( superset ) && !openCache.count( superset ) ){
				approxStruct approximation = scoringFunction->approximateScore( variable , superset , pruned , cache ) ;
				open.push( approximation ) ;
				openCache[ superset ] = 0.0 ;
			}
			VARSET_CLEAR( superset , i ) ;
		}
	}
	openCache.clear() ;
	io.stop();
//    t->cancel();
	io.reset();
}

void parentselection::IndependenceSelection::initialize( int variable , FloatMap &pruned , FloatMap &cache ){
	// Initialize closed
	VARSET_NEW( empty , variableCount ) ;
	VARSET_CLEAR_ALL( empty ) ;
	float score = scoringFunction->calculateScore( variable , empty , pruned , cache ) ;

	if( score < 1 ){
		cache[ empty ] = score ;
	}

	// Add parent set of size 1
	int prunedCount = 0 ;
	for(int i = 0 ; i < variableCount && !outOfTime ; i++){
		if( i == variable ) continue ;
		VARSET_NEW( parents , variableCount ) ;
		VARSET_SET( parents , i ) ;
		float score = scoringFunction->calculateScore( variable , parents , pruned , cache ) ;
		if( compare( score ) < 0 ){
			cache[ parents ] = score ;
		}else{
			prunedCount++ ;
		}
	}

	if( maxParents == 1 ) return ;

	// Initialize open
	std::priority_queue<approxStruct,std::vector<approxStruct>,compareIndependence> aux ;
	open = aux ;
	openCache.clear() ;
	for(int i = 0 ; i < variableCount - 1 && !outOfTime ; i++){
		if( i == variable ) continue ;
		VARSET_NEW( parents , variableCount ) ;
		VARSET_SET( parents , i ) ;
		for(int j = i+1 ; j < variableCount && !outOfTime ; j++){
			if( j == variable ) continue ;
			VARSET_SET( parents , j ) ;
			approxStruct approximation = scoringFunction->approximateScore( variable , parents , pruned , cache ) ;
			if( compare( approximation.first ) < 0 ){
				open.push( approximation ) ;
				openCache[ parents ] = 0.0 ;
			}
			VARSET_CLEAR( parents , j ) ;
		}
		VARSET_CLEAR( parents , i ) ;
	}
}