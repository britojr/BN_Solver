/* 
 * File:   greedy_selection.cpp
 * Author: nonwhite
 * 
 * Created on 13 de marzo de 2016, 09:23 PM
 */
#include <boost/thread.hpp>

#include "greedy_selection.h"

struct compareSecond {

	bool operator()(std::pair<varset, float> lhs, std::pair<varset, float> rhs) const {
		float val = lhs.second - rhs.second;

		if (fabs(val) > 2 * std::numeric_limits<float>::epsilon()) {
			return val > 0;
		}

		return lhs.first < rhs.first;
	}
} comparatorGreedy ;

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
	if( runningTime > 0 ){
		printf( "I am using a timer in the calculation function.\n" ) ;
		t->expires_from_now( boost::posix_time::seconds( runningTime ) ) ;
		t->async_wait( boost::bind( &parentselection::ParentSetSelection::timeout, this, boost::asio::placeholders::error ) ) ;
		boost::thread workerThread ;

		workerThread = boost::thread( 
				boost::bind( &parentselection::GreedySelection::calculateScores_internal ,
							this , variable , boost::ref( cache )
				) 
		) ;
		io_t.run() ;
		workerThread.join() ;
		io_t.stop() ;
		t->cancel() ;
	}else{
		printf("I am executing without time limit\n" ) ;
		calculateScores_internal( variable , cache ) ;
	}
}

void parentselection::GreedySelection::calculateScores_internal( int variable , FloatMap& cache ){
	// calculate the initial score
	VARSET_NEW( empty , variableCount ) ;
	float score = scoringFunction->calculateScore( variable , empty , cache ) ;

	if( score < 1 ){
		cache[ empty ] = score ;
	}

	// Add parent set of size 1
	int prunedCount = 0 ;
	std::vector<std::pair<varset,float> > open ;
	for(int i = 0 ; i < variableCount && !outOfTime ; i++){
		if( i == variable ) continue ;
		VARSET_NEW( parents , variableCount ) ;
		VARSET_SET( parents , i ) ;
		float score = scoringFunction->calculateScore( variable , parents , cache ) ;
		if( score < 0 ){
			cache[ parents ] = score ;
			open.push_back( PAIR( parents , score ) ) ;
		}else{
			prunedCount++ ;
		}
	}

	while( !open.empty() && !outOfTime ){
		std::sort( open.begin() , open.end() , comparatorGreedy ) ;
		std::pair<varset,float> node = open[ 0 ] ;
		open.erase( open.begin() ) ;
		VARSET_NEW( best , variableCount ) ;
		best = node.first ;
		if( cardinality( best ) >= maxParents ) break ;
		VARSET_NEW( superset , variableCount ) ;
		superset = best ;
		for(int j = 0 ; j < variableCount && !outOfTime ; j++){
			if( j == variable ) continue ;
			VARSET_SET( superset , j ) ;
			float score = scoringFunction->calculateScore( variable , superset , cache ) ;
			if( score < 0 ){
				cache[ superset ] = score ;
				open.push_back( PAIR( superset , score ) ) ;
			}else{
				prunedCount++ ;
			}
			VARSET_CLEAR( superset , j ) ;
		}
	}

	// Set in cache all other scores not explored
	for(int i = 0 ; i < open.size() ; i++){
		std::pair<varset,float> node = open[ i ] ;
		cache[ node.first ] = node.second ;
	}
	// TODO: Check this lines for time limit
	io.stop();
//    t->cancel();
	io.reset();
}