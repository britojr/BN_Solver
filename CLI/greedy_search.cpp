/* 
 * File:   GreedySearch.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 03:37 PM
 */

#include <cstdlib>

#include "greedy_search.h"

greedysearch::GreedySearch::GreedySearch(){
	// Do nothing
}

greedysearch::GreedySearch::GreedySearch( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										int maxIterations ){
	this->initializer = initializer ;
	this->bestScoreCalculator = bestScoreCalculator ;
	this->maxIterations = maxIterations ;
	this->numIterations = 0 ;
	this->variableCount = bestScoreCalculator.size() ;
}

greedysearch::GreedySearch::~GreedySearch(){
	// Do nothing
}

std::vector<greedysearch::Node*> greedysearch::GreedySearch::search( int numSolutions ){
	greedysearch::PermutationSet best ;
	for(int k = 0 ; k < numSolutions ; k++){
		greedysearch::PermutationSet current = initializer->generate() ;
		printf( " ======== Greedy Search ======== \n" ) ;
		printf(" === Iteration %d ===\n" , 0 ) ;
		current.print() ;
		numIterations = 0 ;
		for(int i = 0 ; i < maxIterations ; i++){
			greedysearch::PermutationSet bestNeighbor = findBestNeighbor( current ) ;
			greedysearch::PermutationSet disturbedNeighbor = disturbSet( bestNeighbor ) ;
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
	return reconstructSolution( best ) ;
}

greedysearch::PermutationSet greedysearch::GreedySearch::findBestNeighbor( greedysearch::PermutationSet set ){
	greedysearch::PermutationSet bestN = set ;
	for(int i = 0 ; i < variableCount - 1 ; i++){
		greedysearch::PermutationSet neighbor = doSwap( set , i ) ;
		if( !neighbor.isBetter( bestN ) ) continue ;
		bestN = neighbor ;
	}
	return bestN ;
}

greedysearch::PermutationSet greedysearch::GreedySearch::disturbSet( greedysearch::PermutationSet set , int numSwaps ){
	greedysearch::PermutationSet newSet = set ;
	// Perform swaps
	for(int i = 0 ; i < numSwaps ; i++){
		int idx1 = rand() % set.size() ;
		int idx2 = rand() % set.size() ;
		newSet.swap( idx1 , idx2 ) ;
	}
	// Update score
	float score = 0.0 ;
	for(int i = 0 ; i < variableCount ; i++){
		varset options = newSet.getVarset( i ) ;
		score += bestScoreCalculator[ i ]->getScore( options ) ;
	}
	newSet.setScore( score ) ;
	return newSet ;
}

greedysearch::PermutationSet greedysearch::GreedySearch::doSwap( greedysearch::PermutationSet set , int index ){
	greedysearch::PermutationSet newSet = set ;
	newSet.swap( index , index + 1 ) ;
	float newScore = set.getScore() ;

	// Remove previous scores
	varset previousOptions1 = set.getVarset( index ) ;
	newScore -= bestScoreCalculator[ index ]->getScore( previousOptions1 ) ;

	varset previousOptions2 = set.getVarset( index + 1 ) ;
	newScore -= bestScoreCalculator[ index + 1 ]->getScore( previousOptions2 ) ;

	// Add current scores
	varset currentOptions1 = newSet.getVarset( index ) ;
	newScore += bestScoreCalculator[ index ]->getScore( currentOptions1 ) ;

	varset currentOptions2 = newSet.getVarset( index + 1 ) ;
	newScore += bestScoreCalculator[ index + 1 ]->getScore( currentOptions2 ) ;

	newSet.setScore( newScore ) ;

	return newSet ;
}

std::vector<greedysearch::Node*> greedysearch::GreedySearch::reconstructSolution( greedysearch::PermutationSet set ){
	std::vector<Node*> nodes ;
	for(int i = 0 ; i < set.size() ; i++){
		Node* var = new Node( i , set.size() ) ;
		nodes.push_back( var ) ;
	}
	for(int i = 0 ; i < variableCount ; i++){
		varset options = set.getVarset( i ) ;
		float score = bestScoreCalculator[ i ]->getScore( options ) ; 
		nodes[ i ]->setScore( score ) ;
		varset parents = bestScoreCalculator[ i ]->getParents() ; 
		nodes[ i ]->setParents( parents ) ;
		for(int j = 0 ; j < variableCount ; j++){
			if( !VARSET_GET( parents , j ) ) continue ;
			nodes[ j ]->addChild( i ) ;
		}
	}
	return nodes ;
}