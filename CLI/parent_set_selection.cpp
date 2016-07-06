/* 
 * File:   WPathInitializer.cpp
 * Author: nonwhite
 * 
 * Created on 20 de febrero de 2016, 10:08 AM
 */
#include <algorithm>
#include <boost/thread.hpp>

#include "parent_set_selection.h"

struct compareSecond {
	bool operator()(std::pair<varset, float> lhs, std::pair<varset, float> rhs) const {
		float val = lhs.second - rhs.second;

		if (fabs(val) > 2 * std::numeric_limits<float>::epsilon()) {
			return val > 0;
		}

		return lhs.first < rhs.first;
	}
} comparatorPrune ;

void parentselection::ParentSetSelection::prune( FloatMap &cache ){
	std::vector< std::pair<varset, float> > pairs ;
	for( auto pair = cache.begin() ; pair != cache.end() ; pair++)
		pairs.push_back( *pair ) ;

	std::sort( pairs.begin() , pairs.end() , comparatorPrune ) ;

	// keep track of the ones that have been pruned
	boost::dynamic_bitset<> prunedSets( pairs.size() ) ;
	for( int i = 0; i < pairs.size(); i++){
		if( prunedSets.test( i ) ) continue ;

		varset pi = pairs[ i ].first ;

		// make sure this variable set is not in an incomplete last layer
		if( cardinality( pi ) > highestCompletedLayer ){
			prunedSets.set( i ) ;
			continue ;
		}

		for( int j = i + 1 ; j < pairs.size() ; j++){
			if( prunedSets.test( j ) ) continue ;

			// check if parents[i] is a subset of parents[j]
			varset pj = pairs[ j ].first ;

			if( VARSET_IS_SUBSET_OF( pi , pj ) ){
				// then we can prune pj
				prunedSets.set( j ) ;
				cache.erase( pj ) ;
			}
		}
	}
}

void parentselection::ParentSetSelection::timeout( const boost::system::error_code& /*e*/ ){
	printf( "Out of time\n" ) ;
	outOfTime = true ;
}

void parentselection::ParentSetSelection::calculateScores( int variable , FloatMap &cache ){
	outOfTime = false ;

	boost::asio::io_service io_t ;
	t = new boost::asio::deadline_timer( io_t ) ;
	
	FloatMap pruned ;
	init_map( pruned ) ;
	initialize( variable , pruned , cache ) ;
	if( runningTime > 0 ){
		printf( "I am using a timer in the calculation function.\n" ) ;
		t->expires_from_now( boost::posix_time::seconds( runningTime ) ) ;
		t->async_wait( boost::bind( &parentselection::ParentSetSelection::timeout, this, boost::asio::placeholders::error ) ) ;
		boost::thread workerThread(
				boost::bind( &parentselection::ParentSetSelection::calculateScores_internal ,
							this , variable , boost::ref( pruned ) , boost::ref( cache )
				)
		) ;
		io_t.run() ;
		workerThread.join() ;
		io_t.stop() ;
	}else{
		printf("I am executing without time limit\n" ) ;
		calculateScores_internal( variable , pruned , cache ) ;
	}
}