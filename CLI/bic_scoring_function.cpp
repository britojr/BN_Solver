/* 
 * File:   bic_scoring_function.cpp
 * Author: malone
 * Modified by: nonwhite
 * 
 * Created on November 23, 2012, 9:15 PM
 * Last Modified on July 21, 2016
 */

#include "typedefs.h"
#include "bic_scoring_function.h"
#include "log_likelihood_calculator.h"

scoring::BICScoringFunction::BICScoringFunction( datastructures::BayesianNetwork &network ,
												datastructures::RecordFile &recordFile ,
												LogLikelihoodCalculator *llc ,
												scoring::Constraints *constraints ,
												bool enableDeCamposPruning ){
	this->network = network ;
	this->baseComplexityPenalty = log( recordFile.size() ) / 2 ;
	this->recordFileSize = recordFile.size() ;
	this->constraints = constraints ;

	this->llc = llc ;
	this->enableDeCamposPruning = enableDeCamposPruning ;
}

scoring::BICScoringFunction::~BICScoringFunction(){
	// no pointers
}

float scoring::BICScoringFunction::t( int variable , varset parents ){
	float penalty = network.getCardinality(variable) - 1;

	for (int pa = 0; pa < network.size(); pa++) {
		if (VARSET_GET(parents, pa)) {
			penalty *= network.getCardinality(pa);
		}
	}

	return penalty;
}

float scoring::BICScoringFunction::calculateScore( int variable , varset parents ,
													FloatMap &pruned , FloatMap &cache) {
	// Check if it was already calculated
	auto s = cache.find( parents ) ;
	if( s != cache.end() ) return cache[ parents ] ;
	
	// Check if this violates the constraints
	if( constraints != NULL && !constraints->satisfiesConstraints( variable , parents ) ){
		invalidParents.insert( parents ) ;
		return 1 ;
	}

	// check for pruning
	float tVal = t( variable , parents ) ;

	if( enableDeCamposPruning ){
		auto s = pruned.find( parents ) ;
		// Check if it was already pruned
		if( s != pruned.end() ) return 0 ;
		for( int x = 0 ; x < network.size() ; x++){
			if( VARSET_GET( parents , x ) ){
				VARSET_CLEAR( parents , x ) ;
				// check the constraints
				if( invalidParents.size() > 0 && invalidParents.count( parents ) > 0 ){
					// we cannot say anything if we skipped this because of constraints
					VARSET_SET( parents , x ) ;
					continue ;
				}

				auto s = cache.find( parents ) ;

				if( s == cache.end() ){
					VARSET_SET( parents , x ) ;
					pruned[ parents ] = 0. ;
					return 0 ;
				}

				if( s->second + tVal > 0 ){
					VARSET_SET( parents , x ) ;
					pruned[ parents ] = 0. ;
					return 0 ;
				}

				VARSET_SET( parents , x ) ;
			}
		}
	}

	float score = llc->calculate( variable , parents ) ;
	// structure penalty
	score -= tVal * baseComplexityPenalty ;
	return score ;
}

approxStruct scoring::BICScoringFunction::approximateScore( int variable , varset parents ,
															FloatMap &pruned , FloatMap &cache ){
	
	// Find p1 and p2
	int variableCount = this->network.size() ;
	VARSET_NEW( p1 , variableCount ) ;
	VARSET_NEW( p2 , variableCount ) ;
	
	// Check if it was already pruned
	auto s = pruned.find( parents ) ;
	if( s != pruned.end() ) return PAIR( 1 , PAIR( p1 , p2 ) ) ;

	bool canApproximate = false ;

	for( auto node = cache.begin() ; node != cache.end() ; node++){
		VARSET_NEW( auxP , network.size() ) ;
		auxP = node->first ;
		if( !VARSET_IS_SUBSET_OF( auxP , parents ) ) continue ;
		VARSET_NEW( possibleP1 , variableCount ) ;
		possibleP1 = auxP ;
		if( cardinality( possibleP1 ) == 0 ) continue ; // Verify it is not empty
		VARSET_NEW( possibleP2 , variableCount ) ;
		possibleP2 = VARSET_AND( parents , VARSET_NOT( possibleP1 ) ) ;
		if( cardinality( possibleP2 ) == 0 ) continue ; // Verify it is not empty
		if( cache.count( possibleP2 ) > 0 ){
			p1 = possibleP1 ;
			p2 = possibleP2 ;
			canApproximate = true ;
			break ;
		}
	}

	if( !canApproximate ) return PAIR( 1 , PAIR( p1 , p2 ) ) ;

	// Get BIC( X , p1 ) and BIC( X , p2 )
	float b1 = cache[ p1 ] , b2 = cache[ p2 ] ;

	// inter( X , p1 , p2 ) = log( N ) / 2 ( |X| - 1 ) ( |p1| + |p2| - |p1||p2| - 1 ) - BIC( X , empty )
	float cardVar = network.getCardinality( variable ) ;
	float cardP1 = cardinality( p1 ) ;
	float cardP2 = cardinality( p2 ) ;
	VARSET_NEW( empty , variableCount ) ;
	VARSET_CLEAR_ALL( empty ) ;
	float inter = baseComplexityPenalty * ( cardVar - 1 ) * ( cardP1 + cardP2 - cardP1 * cardP2 - 1 ) - cache[ empty ] ;

	// BIC*( X , p1 , p2 ) = BIC( X , p1 ) + BIC( X , p2 ) + inter( X , p1 , p2 )
	float approxScore = b1 + b2 + inter ;
	return PAIR( approxScore , PAIR( p1 , p2 ) ) ;
}

float scoring::BICScoringFunction::getFromApproximation( int variable ,
														approxStruct &approximation ,
														FloatMap &pruned ,
														FloatMap &cache ){
	VARSET_NEW( parents , network.size() ) ;
	VARSET_OR( parents , approximation.second.first ) ;
	VARSET_OR( parents , approximation.second.second ) ;
	return calculateScore( variable , parents , pruned , cache ) ;
	// BIC( X , p1 U p2 ) = BIC*( X , p1 , p2 ) + N * ii( p1 , p2 , X )
//    float interInfo = llc->interactionInformation( p1 , p2 , variable ) ;
//    float N = recordFileSize ;
//    return approxValue + N * interInfo ;
}