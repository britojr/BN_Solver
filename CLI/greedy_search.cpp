/* 
 * File:   GreedySearch.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 03:37 PM
 */

#include <cstdlib>

#include "greedy_search.h"
#include "utils.h"

structureoptimizer::GreedySearch::GreedySearch(){
	// Do nothing
}

structureoptimizer::GreedySearch::GreedySearch( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										int maxIterations ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->maxIterations = maxIterations ;
	this->numIterations = 0 ;
	this->variableCount = bestScoreCalculator.size() ;
	this->gen = boost::mt19937( time( NULL ) ) ;
}

structureoptimizer::GreedySearch::~GreedySearch(){
	// Do nothing
}

datastructures::BNStructure structureoptimizer::GreedySearch::search( int numSolutions ){
	structureoptimizer::PermutationSet best ;
	for(int k = 0 ; k < numSolutions ; k++){
		structureoptimizer::PermutationSet current = initializer->generate() ;
		printf( " ======== Greedy Search ======== \n" ) ;
		printf(" === Iteration %d ===\n" , 0 ) ;
		current.print() ;
		numIterations = 0 ;
		for(int i = 0 ; i < maxIterations ; i++){
			structureoptimizer::PermutationSet bestNeighbor = findBestNeighbor( current ) ;
			structureoptimizer::PermutationSet disturbedNeighbor = perturbSet( bestNeighbor ) ;
			if( disturbedNeighbor.isBetter( bestNeighbor ) ) bestNeighbor = disturbedNeighbor ;
			if( !bestNeighbor.isBetter( current ) ) break ;
			printf(" === Iteration %d ===\n" , i+1 ) ;
			current = bestNeighbor ;
			current.print() ;
			numIterations += 1 ;
		}
		if( best.size() == 0 || current.isBetter( best ) )
			best = current ;
	}
	printf(" === BEST === \n" ) ;
	printf( "Score = %.6f\n" , best.getScore() ) ;
	return datastructures::BNStructure( best , bestScoreCalculators ) ;
}

structureoptimizer::PermutationSet structureoptimizer::GreedySearch::findBestNeighbor( structureoptimizer::PermutationSet set ){
	structureoptimizer::PermutationSet bestN( set ) ;
	for(int i = 0 ; i < variableCount - 1 ; i++){
		structureoptimizer::PermutationSet neighbor = doSwap( set , i ) ;
		if( !neighbor.isBetter( bestN ) ) continue ;
		bestN = neighbor ;
	}
	return bestN ;
}

structureoptimizer::PermutationSet structureoptimizer::GreedySearch::perturbSet( structureoptimizer::PermutationSet set , int numSwaps ){
	structureoptimizer::PermutationSet newSet( set ) ;
	// Perform swaps
	for(int i = 0 ; i < numSwaps ; i++){
		int idx1 = random_generator( set.size() , this->gen ) ;
		int idx2 = random_generator( set.size() , this->gen ) ;
		newSet.swap( idx1 , idx2 ) ;
	}
	return newSet ;
}

structureoptimizer::PermutationSet structureoptimizer::GreedySearch::doSwap( structureoptimizer::PermutationSet set , int index ){
	structureoptimizer::PermutationSet newSet( set ) ;
	newSet.swap( index , index + 1 ) ;
	return newSet ;
}