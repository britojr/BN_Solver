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

void parentselection::SequentialSelection::calculateScores( int variable , FloatMap &cache ){
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
				boost::bind( &parentselection::SequentialSelection::calculateScores_internal ,
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

void parentselection::SequentialSelection::calculateScores_internal( int variable , FloatMap &pruned , FloatMap& cache ){
	// Perform sequential selection
	int prunedCount = 0 ;
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
		for(int i = 0 ; i < variableCount && !outOfTime ; i++){
			if( i == variable ) continue ;
			VARSET_SET( superset , i ) ;
			// Expand only if it is not already visited/calculated
			if( !cache.count( superset ) && !openCache.count( superset ) ){
				open.push( superset ) ;
				openCache[ superset ] = 0.0 ;
			}
			VARSET_CLEAR( superset , i ) ;
		}
	}

	io.stop() ;
//    t->cancel();
	io.reset() ;
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