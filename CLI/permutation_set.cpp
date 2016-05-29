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

structureoptimizer::PermutationSet::PermutationSet( int size ){
	boost::mt19937 gen( time( NULL ) ) ;
	for(int i = 0 ; i < size ; i++)
		permutation.push_back( i ) ;
	permutation = shuffle( permutation , gen ) ;
	score = std::numeric_limits<float>::max() ;
}

structureoptimizer::PermutationSet::~PermutationSet(){
	// Do nothing
}

float structureoptimizer::PermutationSet::getScore(){
	return score ;
}

void structureoptimizer::PermutationSet::setScore( float score ){
	this->score = score ;
}

// Considering that minimizing is better
bool structureoptimizer::PermutationSet::isBetter( structureoptimizer::PermutationSet other ){
	return other.getScore() > score ;
}

void structureoptimizer::PermutationSet::setPermutation( std::vector<int> permutation ){
	this->permutation = permutation ;
}

std::vector<int> structureoptimizer::PermutationSet::getPermutation(){
	return permutation ;
}

int structureoptimizer::PermutationSet::size(){
	return permutation.size() ;
}

void structureoptimizer::PermutationSet::print(){
	for(int i = 0 ; i < permutation.size() ; i++){
		if( i ) printf(" " ) ;
		printf("%d" , permutation[ i ] ) ;
	}
	printf("\n" ) ;
	printf("Score = %.6f\n" , score ) ;
}

int structureoptimizer::PermutationSet::operator[]( int idx ){
	return permutation[ idx ] ;
}

void structureoptimizer::PermutationSet::swap( int idx1 , int idx2 ){
	int aux = permutation[ idx1 ] ;
	permutation[ idx1 ] = permutation[ idx2 ] ;
	permutation[ idx2 ] = aux ;
}

varset structureoptimizer::PermutationSet::getVarset( int index ){
	VARSET_NEW( set , permutation.size() ) ;
	for( int i = 0 ; i < index ; i++)
		VARSET_SET( set , permutation[ i ] ) ;
	return set ;
}
