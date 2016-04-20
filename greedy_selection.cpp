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

void parentselection::GreedySelection::calculateScores( int variable , FloatMap &cache ){
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
				boost::bind( &parentselection::GreedySelection::calculateScores_internal ,
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

void parentselection::GreedySelection::calculateScores_internal( int variable , FloatMap &pruned , FloatMap& cache ){
	int prunedCount ;
	while( !open.empty() && !outOfTime ){
		pqelem node = open.top() ; open.pop() ;
		
		VARSET_NEW( best , variableCount ) ;
		best = node.first ;
		if( cardinality( best ) >= maxParents ) continue ;
		VARSET_NEW( superset , variableCount ) ;
		superset = best ;
		for(int j = 0 ; j < variableCount && !outOfTime ; j++){
			if( j == variable ) continue ;
			VARSET_SET( superset , j ) ;
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
			VARSET_CLEAR( superset , j ) ;
		}
	}

	// TODO: Check this lines for time limit
	io.stop();
//    t->cancel();
	io.reset();
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