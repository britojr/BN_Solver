/* 
 * File:   PermutationSet.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 05:22 PM
 */

#include <limits>

#include <boost/random.hpp>

#include "permutation_set.h"
#include "utils.h"

structureoptimizer::PermutationSet::PermutationSet(){
	// Do nothing
}

structureoptimizer::PermutationSet::PermutationSet( const structureoptimizer::PermutationSet &other ){
	permutation.clear() ;
	for(int i = 0 ; i < other.size() ; i++)
		permutation.push_back( other[ i ] ) ;
	this->bestScoreCalculator = other.getBestScoreCalculators() ;
	this->score = other.getScore() ;
}

structureoptimizer::PermutationSet::~PermutationSet(){
	// Do nothing
}

float structureoptimizer::PermutationSet::getScore() const {
	return score ;
}

void structureoptimizer::PermutationSet::setScore( float score ){
	this->score = score ;
}

void structureoptimizer::PermutationSet::setPermutation( std::vector<int> permutation ){
	this->permutation = permutation ;
	updateScore() ;
}

std::vector<int> structureoptimizer::PermutationSet::getPermutation(){
	return permutation ;
}

int structureoptimizer::PermutationSet::size() const {
	return permutation.size() ;
}

int structureoptimizer::PermutationSet::operator[]( int idx ) const {
	return permutation[ idx ] ;
}

bool structureoptimizer::PermutationSet::operator <( structureoptimizer::PermutationSet &other ) const {
	return compare( other.getScore() , score ) > 0 ;
}

bool structureoptimizer::PermutationSet::operator ==( structureoptimizer::PermutationSet &other ) const {
	return other.permutation == permutation ;
}

// Considering that minimizing is better
bool structureoptimizer::PermutationSet::isBetter( structureoptimizer::PermutationSet &other ){
	return (*this) < other ;
}

void structureoptimizer::PermutationSet::swap( int idx1 , int idx2 ){
	int aux = permutation[ idx1 ] ;
	permutation[ idx1 ] = permutation[ idx2 ] ;
	permutation[ idx2 ] = aux ;
	bool isAdjacentMove = abs( idx1 - idx2 ) == 1 ;
	isAdjacentMove ? updateScore( std::min( idx1 , idx2 ) ) : updateScore() ;
}

varset structureoptimizer::PermutationSet::getVarset( int index ){
	VARSET_NEW( vset , permutation.size() ) ;
	VARSET_CLEAR_ALL( vset ) ;
	for( int i = 0 ; i < index ; i++)
		VARSET_SET( vset , permutation[ i ] ) ;
	return vset ;
}

std::vector<bestscorecalculators::BestScoreCalculator*> structureoptimizer::PermutationSet::getBestScoreCalculators() const {
	return bestScoreCalculator ;
}
