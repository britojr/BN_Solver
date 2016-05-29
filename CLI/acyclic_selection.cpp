/* 
 * File:   acyclic_selection.cpp
 * Author: nonwhite
 * 
 * Created on 28 de mayo de 2016, 13:07
 */

#include "acyclic_selection.h"

structureoptimizer::AcyclicSelection::AcyclicSelection(){
	// Do nothing
}

structureoptimizer::AcyclicSelection::AcyclicSelection( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										int maxIterations ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->maxIterations = maxIterations ;
	this->numIterations = 0 ;
	this->variableCount = bestScoreCalculator.size() ;
}

structureoptimizer::AcyclicSelection::~AcyclicSelection(){
	// Do nothing
}

std::vector<structureoptimizer::Node*> structureoptimizer::AcyclicSelection::search( int numSolutions ){
//	structureoptimizer::PermutationSet best ;
//	for(int k = 0 ; k < numSolutions ; k++){
//		structureoptimizer::PermutationSet current = initializer->generate() ;
//		printf( " ======== Greedy Search ======== \n" ) ;
//		printf(" === Iteration %d ===\n" , 0 ) ;
//		current.print() ;
//		numIterations = 0 ;
//		for(int i = 0 ; i < maxIterations ; i++){
//			structureoptimizer::PermutationSet bestNeighbor = findBestNeighbor( current ) ;
//			structureoptimizer::PermutationSet disturbedNeighbor = disturbSet( bestNeighbor ) ;
//			if( disturbedNeighbor.isBetter( bestNeighbor ) ) bestNeighbor = disturbedNeighbor ;
//			if( !bestNeighbor.isBetter( current ) ) break ;
//			printf(" === Iteration %d ===\n" , i+1 ) ;
//			current = bestNeighbor ;
//			current.print() ;
//			numIterations += 1 ;
//		}
//		if( best.size() == 0 || current.isBetter( best ) )
//			best = current ;
//	}
//	return reconstructSolution( best ) ;
	return std::vector<structureoptimizer::Node*>() ;
}