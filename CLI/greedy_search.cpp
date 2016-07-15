/* 
 * File:   GreedySearch.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 03:37 PM
 */

#include <cstdlib>
#include <cstdio>

#include "greedy_search.h"
#include "utils.h"

structureoptimizer::GreedySearch::GreedySearch(){
	// Do nothing
}

structureoptimizer::GreedySearch::GreedySearch( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										std::string parametersFile ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->numIterations = 0 ;
	this->variableCount = bestScoreCalculator.size() ;
	this->gen = boost::mt19937( time( NULL ) ) ;
	
	setParameters( parametersFile ) ;
}

structureoptimizer::GreedySearch::~GreedySearch(){
	// Do nothing
}

void structureoptimizer::GreedySearch::setDefaultParameters(){
	this->performSolutionPerturbation = true ;
	this->numPerturbationSwaps = 3 ;
	this->maxIterations = 500 ;
}

void structureoptimizer::GreedySearch::setFileParameters( std::map<std::string,std::string> params ){
	if( params.count( "perturb_solution" ) ){
		int p ;
		sscanf( params[ "perturb_solution" ].c_str() , "%d" , &p ) ;
		performSolutionPerturbation = ( p > 0 ) ;
	}
	
	if( params.count( "num_swaps" ) )
		sscanf( params[ "num_swaps" ].c_str() , "%d" , &numPerturbationSwaps ) ;
	
	if( params.count( "max_iterations" ) )
		sscanf( params[ "max_iterations" ].c_str() , "%d" , &maxIterations ) ;
}

void structureoptimizer::GreedySearch::printParameters(){
	printf( "Max number of iterations: %d\n" , maxIterations ) ;
	printf( "Perturb solutions: %s\n" , performSolutionPerturbation ? "true" : "false" ) ;
	if( performSolutionPerturbation )
		printf( "Num. of perturbation swaps: %d\n" , numPerturbationSwaps ) ;
}

datastructures::BNStructure structureoptimizer::GreedySearch::search( int numSolutions ){
	structureoptimizer::PermutationSet best ;
	for(int k = 0 ; k < numSolutions ; k++){
		structureoptimizer::PermutationSet current = initializer->generate() ;
		printf( " ======== Greedy Search ======== \n" ) ;
		printf(" === Iteration %d ===\n" , 0 ) ;
		current.print( true ) ;
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

structureoptimizer::PermutationSet structureoptimizer::GreedySearch::perturbSet( structureoptimizer::PermutationSet set ){
	structureoptimizer::PermutationSet newSet( set ) ;
	if( performSolutionPerturbation ){
		// Perform swaps
		for(int i = 0 ; i < numPerturbationSwaps ; i++){
			int idx1 = random_generator( set.size() , gen ) ;
			int idx2 = random_generator( set.size() , gen ) ;
			newSet.swap( idx1 , idx2 ) ;
		}
	}
	return newSet ;
}

structureoptimizer::PermutationSet structureoptimizer::GreedySearch::doSwap( structureoptimizer::PermutationSet set , int index ){
	structureoptimizer::PermutationSet newSet( set ) ;
	newSet.swap( index , index + 1 ) ;
	return newSet ;
}