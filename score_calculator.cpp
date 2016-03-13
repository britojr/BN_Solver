/* 
 * File:   score_calculator.cpp
 * Author: malone
 * 
 * Created on November 24, 2012, 5:46 PM
 */

#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#include <algorithm>
#include <math.h>
#include <stdexcept>
#include <queue>

#include <boost/dynamic_bitset.hpp>
#include <limits>

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>

#include "score_calculator.h"
#include "scoring_function.h"
#include "utils.h"

scoring::ScoreCalculator::ScoreCalculator( scoring::ScoringFunction *scoringFunction,
											int maxParents ,
											int variableCount ,
											int runningTime ,
											scoring::Constraints *constraints,
											std::string selectionType ){
	this->scoringFunction = scoringFunction;
	this->maxParents = maxParents;
	this->variableCount = variableCount;
	this->runningTime = runningTime;
	this->constraints = constraints ;
	boost::algorithm::to_lower( selectionType ) ;
	if( selectionType.compare( "sequential" ) == 0 ){
		this->parentSetSelectionType = 0 ;
	}else if( selectionType.compare( "greedy" ) == 0 ){
		this->parentSetSelectionType = 1 ;
	}else if( selectionType.compare( "independence" ) == 0 ){
		this->parentSetSelectionType = 2 ;
	}else{
		throw std::runtime_error( "Invalid selection type.  Options are: 'Sequential', 'Greedy' or 'Independence'." ) ;
	}
}

void scoring::ScoreCalculator::timeout(const boost::system::error_code& /*e*/) {
	printf("Out of time\n");
	outOfTime = true;
}

void scoring::ScoreCalculator::calculateScores(int variable, FloatMap &cache) {
	// TODO: Create an interface class for Parent Set Selection
	// TODO: Create SequentialSelection, GreedySelection, BestFirstSelection, IndependenceSelection classes
	this->outOfTime = false;

	io.reset() ;
	boost::asio::deadline_timer *t;
	boost::asio::io_service io_t;
	t = new boost::asio::deadline_timer(io_t);
	if (runningTime > 0) {
		printf("I am using a timer in the calculation function.\n");
		t->expires_from_now(boost::posix_time::seconds(runningTime));
		t->async_wait(boost::bind(&scoring::ScoreCalculator::timeout, this, boost::asio::placeholders::error));
		boost::thread workerThread ;
		switch( parentSetSelectionType ){
			case 0 :
				workerThread = boost::thread(boost::bind(&scoring::ScoreCalculator::calculateScores_sequential, this, variable, boost::ref(cache)));
				break ;
			case 1 :
				workerThread = boost::thread(boost::bind(&scoring::ScoreCalculator::calculateScores_greedy, this, variable, boost::ref(cache)));
				break ;
			case 2 :
				workerThread = boost::thread(boost::bind(&scoring::ScoreCalculator::calculateScores_independence, this, variable, boost::ref(cache)));
				break ;
		}

		io_t.run();
		workerThread.join();
		io_t.stop();
		t->cancel();
	} else {
		printf("I am executing without time limit\n" ) ;
		switch( parentSetSelectionType ){
			case 0 :
				calculateScores_sequential(variable, cache);
				break ;
			case 1 :
				calculateScores_greedy(variable, cache);
				break ;
			case 2 :
				calculateScores_independence(variable, cache);
				break ;
		}
	}
}

void scoring::ScoreCalculator::calculateScores_sequential(int variable, FloatMap &cache) {
	// calculate the initial score
	VARSET_NEW(empty, variableCount);
	float score = scoringFunction->calculateScore(variable, empty, cache);

	if (score < 1) {
		cache[empty] = score;
	}

	int prunedCount = 0;

	for (int layer = 1; layer <= maxParents && !outOfTime; layer++) {
		VARSET_NEW(variables, variableCount+1);
		for (int i = 0; i < layer; i++) {
			VARSET_SET(variables, i);
		}

		VARSET_NEW(max, variableCount+1);
		VARSET_SET(max, variableCount);

		while (VARSET_LESS_THAN(variables, max) && !outOfTime) {
			VARSET_RESIZE( variables , variableCount ) ;
			if (!VARSET_GET(variables, variable)) {

				score = scoringFunction->calculateScore(variable, variables, cache);

				// only store the score if it was not pruned
				if (score < 0) {
					cache[variables] = score;
				} else {
					prunedCount++;
				}

			}
			VARSET_RESIZE( variables , variableCount + 1 ) ;
			// find the next combination
			variables = nextPermutation(variables);
		}

		if (!outOfTime) highestCompletedLayer = layer;
	}

	io.stop();
//    t->cancel();
	io.reset();

}

struct compareSecond {

	bool operator()(std::pair<varset, float> lhs, std::pair<varset, float> rhs) const {
		float val = lhs.second - rhs.second;

		if (fabs(val) > 2 * std::numeric_limits<float>::epsilon()) {
			return val > 0;
		}

		return lhs.first < rhs.first;
	}
} comparator;

void scoring::ScoreCalculator::calculateScores_greedy( int variable , FloatMap &cache ){
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
		std::sort( open.begin() , open.end() , comparator ) ;
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

void scoring::ScoreCalculator::calculateScores_independence( int variable , FloatMap &cache ){
	// calculate the initial score
	VARSET_NEW( empty , variableCount ) ;
	VARSET_CLEAR_ALL( empty ) ;
	float score = scoringFunction->calculateScore( variable , empty , cache ) ;

	if( score < 1 ){
		cache[ empty ] = score ;
	}

	// Add parent set of size 1
	int prunedCount = 0 ;
	for(int i = 0 ; i < variableCount && !outOfTime ; i++){
		if( i == variable ) continue ;
		VARSET_NEW( parents , variableCount ) ;
		VARSET_SET( parents , i ) ;
		float score = scoringFunction->calculateScore( variable , parents , cache ) ;
		if( compare( score ) < 0 ){
			cache[ parents ] = score ;
		}else{
			prunedCount++ ;
		}
	}

	if( maxParents == 1 ) return ;

	// Add parent sets of size 2 to open (with BIC* score)
	std::vector<approxStruct> open ;
	FloatMap openCache ;
	for(int i = 0 ; i < variableCount - 1 && !outOfTime ; i++){
		if( i == variable ) continue ;
		VARSET_NEW( parents , variableCount ) ;
		VARSET_SET( parents , i ) ;
		for(int j = i+1 ; j < variableCount && !outOfTime ; j++){
			if( j == variable ) continue ;
			VARSET_SET( parents , j ) ;
			approxStruct approximation = scoringFunction->approximateScore( variable , parents , cache ) ;
			if( compare( approximation.first ) < 0 ){
				open.push_back( approximation ) ;
				openCache[ parents ] = 0.0 ;
			}
			VARSET_CLEAR( parents , j ) ;
		}
		VARSET_CLEAR( parents , i ) ;
	}

	while( !open.empty() && !outOfTime ){
		sort( open.begin() , open.end() ) ;

		// Get best approx score
		approxStruct best = open.back() ;
		open.pop_back() ;
		varset p1 = best.second.first ;
		varset p2 = best.second.second ;
		float approxValue = best.first ;

		// Get real score from approximation
		VARSET_NEW( parents , variableCount ) ;
		VARSET_OR( parents , p1 ) ;
		VARSET_OR( parents , p2 ) ;
		float score = scoringFunction->getFromApproximation( variable , p1 , p2 , approxValue , cache ) ;
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
				approxStruct approximation = scoringFunction->approximateScore( variable , superset , cache ) ;
				open.push_back( approximation ) ;
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

void scoring::ScoreCalculator::prune(FloatMap &cache) {
	std::vector< std::pair<varset, float> > pairs;
	for (auto pair = cache.begin();
			pair != cache.end();
			pair++) {
		pairs.push_back(*pair);
	}

	std::sort(pairs.begin(), pairs.end(), comparator);

	// keep track of the ones that have been pruned
	boost::dynamic_bitset<> prunedSets(pairs.size());
	for (int i = 0; i < pairs.size(); i++) {
		if (prunedSets.test(i)) {
			continue;
		}

		varset pi = pairs[i].first;

		// make sure this variable set is not in an incomplete last layer
		if (cardinality(pi) > highestCompletedLayer) {
			prunedSets.set(i);
			continue;
		}

		for (int j = i + 1; j < pairs.size(); j++) {
			if (prunedSets.test(j)) {
				continue;
			}

			// check if parents[i] is a subset of parents[j]
			varset pj = pairs[j].first;

			if (VARSET_IS_SUBSET_OF(pi, pj)) {
				// then we can prune pj
				prunedSets.set(j);
				cache.erase(pj);
			}
		}
	}
}
