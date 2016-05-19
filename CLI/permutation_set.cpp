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

greedysearch::PermutationSet::PermutationSet(){
	// Do nothing
}

greedysearch::PermutationSet::PermutationSet( int size ){
	boost::mt19937 gen( time( NULL ) ) ;
	for(int i = 0 ; i < size ; i++)
		permutation.push_back( i ) ;
	permutation = shuffle( permutation , gen ) ;
	score = std::numeric_limits<float>::max() ;
}

greedysearch::PermutationSet::~PermutationSet(){
	// Do nothing
}

float greedysearch::PermutationSet::getScore(){
	return score ;
}

void greedysearch::PermutationSet::setScore( float score ){
	this->score = score ;
}

// Considering that minimizing is better
bool greedysearch::PermutationSet::isBetter( greedysearch::PermutationSet other ){
	return other.getScore() > score ;
}

void greedysearch::PermutationSet::setPermutation( std::vector<int> permutation ){
	this->permutation = permutation ;
}

std::vector<int> greedysearch::PermutationSet::getPermutation(){
	return permutation ;
}

int greedysearch::PermutationSet::size(){
	return permutation.size() ;
}

void greedysearch::PermutationSet::print(){
	for(int i = 0 ; i < permutation.size() ; i++){
		if( i ) printf(" " ) ;
		printf("%d" , permutation[ i ] ) ;
	}
	printf("\n" ) ;
	printf("Score = %.6f\n" , score ) ;
}

int greedysearch::PermutationSet::operator[]( int idx ){
	return permutation[ idx ] ;
}

void greedysearch::PermutationSet::swap( int idx1 , int idx2 ){
	int aux = permutation[ idx1 ] ;
	permutation[ idx1 ] = permutation[ idx2 ] ;
	permutation[ idx2 ] = aux ;
}

varset greedysearch::PermutationSet::getVarset( int index ){
	VARSET_NEW( set , permutation.size() ) ;
	for( int i = 0 ; i < index ; i++)
		VARSET_SET( set , permutation[ i ] ) ;
	return set ;
}
