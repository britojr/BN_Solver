/* 
 * File:   SequentialSelection.cpp
 * Author: nonwhite
 * 
 * Created on 13 de marzo de 2016, 08:49 PM
 */
#include <boost/thread.hpp>

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
	if( runningTime > 0 ){
		printf( "I am using a timer in the calculation function.\n" ) ;
		t->expires_from_now( boost::posix_time::seconds( runningTime ) ) ;
		t->async_wait( boost::bind( &parentselection::ParentSetSelection::timeout, this, boost::asio::placeholders::error ) ) ;
		boost::thread workerThread ;

		FloatMap pruned ;
		init_map( pruned ) ;
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
		FloatMap pruned ;
		init_map( pruned ) ;
		calculateScores_internal( variable , pruned , cache ) ;
	}
}

void parentselection::SequentialSelection::calculateScores_internal( int variable , FloatMap &pruned , FloatMap& cache ){
	// calculate the initial score
	VARSET_NEW( empty , variableCount ) ;
	float score = scoringFunction->calculateScore( variable , empty , pruned , cache ) ;

	if(score < 1 ){
		cache[ empty ] = score ;
	}

	int prunedCount = 0 ;

	for( int layer = 1 ; layer <= maxParents && !outOfTime ; layer++){
		VARSET_NEW( variables , variableCount+1 ) ;
		for( int i = 0 ; i < layer ; i++){
			VARSET_SET( variables , i ) ;
		}

		VARSET_NEW( max , variableCount + 1 ) ;
		VARSET_SET( max , variableCount ) ;

		while( VARSET_LESS_THAN( variables , max ) && !outOfTime ){
			VARSET_RESIZE( variables , variableCount ) ;
			if( !VARSET_GET( variables , variable ) ){
				score = scoringFunction->calculateScore( variable , variables , pruned , cache ) ;

				// only store the score if it was not pruned
				if( score < 0 ){
					cache[ variables ] = score ;
				}else{
					prunedCount++ ;
				}
			}
			VARSET_RESIZE( variables , variableCount + 1 ) ;
			// find the next combination
			variables = nextPermutation( variables ) ;
		}

		if( !outOfTime ) highestCompletedLayer = layer ;
	}

	io.stop() ;
//    t->cancel();
	io.reset() ;
}
