/*
 * File:   acyclic_selection.cpp
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 13:07
 */
#include <boost/timer/timer.hpp>
#include <limits>

#include "acyclic_selection.h"
#include "bn_structure.h"
#include "utils.h"
#include "permutation_set_creator.h"

structureoptimizer::AcyclicSelection::AcyclicSelection(){
	// Do nothing
}

structureoptimizer::AcyclicSelection::AcyclicSelection( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										std::string parametersFile ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->variableCount = bestScoreCalculator.size() ;
	setParameters( parametersFile ) ;
}

structureoptimizer::AcyclicSelection::~AcyclicSelection(){
	// Do nothing
}

void structureoptimizer::AcyclicSelection::setDefaultParameters(){
	this->maxIterations = 500 ;
}

void structureoptimizer::AcyclicSelection::setFileParameters( std::map<std::string,std::string> params ){
	if( params.count( "max_iterations" ) ){
		sscanf( params[ "max_iterations" ].c_str() , "%d" , &maxIterations ) ;
		if ( maxIterations <= 0 )
			maxIterations = std::numeric_limits<int>::max() ;
	}

	if( params.count( "topologic_sort" ) ){
		int t ;
		sscanf( params[ "topologic_sort" ].c_str() , "%d" , &t ) ;
		useTopologicalSort = ( t > 0 ) ;
	}
}

void structureoptimizer::AcyclicSelection::printParameters(){
	printf( "Max number of iterations: %d\n" , maxIterations ) ;
	printf( "Use topological sort as next neighbour: %s\n" , useTopologicalSort ? "true" : "false" ) ;
}

void structureoptimizer::AcyclicSelection::initialize(){
	printf( " ======== Acyclic Selection ======== \n" ) ;
	current = initializer->generate( structureoptimizer::ACYCLIC_BEHAVIOR_SET ) ;
	printf(" === Iteration %d ===\n" , 0 ) ;
	current->print( true ) ;
}

datastructures::BNStructure structureoptimizer::AcyclicSelection::search_internal(){
	boost::timer::auto_cpu_timer cpu( 6 , "CPU time = %w\n" ) ; // TODO: Rethink location of timer

	int numIterations = 0 ;
	for(int i = 0 ; i < maxIterations && !outOfTime ; i++,numIterations++){
		structureoptimizer::PermutationSet* bestNeighbour = chooseNeighbour( current ) ;
		if( !bestNeighbour->isBetter( *current ) ) break ;
		printf(" === Iteration %d ===\n" , i+1 ) ;
		current = bestNeighbour->clone() ;
		current->print() ;
	}
	printf("Iterations = %d\n" , numIterations ) ;
	t->cancel() ;
	return *(current->getStructure()) ;
}

structureoptimizer::PermutationSet* structureoptimizer::AcyclicSelection::findBestNeighbour( structureoptimizer::PermutationSet* set ){
	structureoptimizer::PermutationSet* bestN = set->clone() ;
	for(int i = 0 ; i < variableCount - 1 ; i++){
		structureoptimizer::PermutationSet* neighbour = doSwap( set , i ) ;
		if( !neighbour->isBetter( *bestN ) ) continue ;
		bestN = neighbour->clone() ;
	}
	return bestN ;
}

structureoptimizer::PermutationSet* structureoptimizer::AcyclicSelection::doSwap( structureoptimizer::PermutationSet* set , int index ){
	structureoptimizer::PermutationSet* newSet = set->clone();
	newSet->swap( index , index + 1 ) ;
	return newSet ;
}

structureoptimizer::PermutationSet* structureoptimizer::AcyclicSelection::chooseNeighbour( structureoptimizer::PermutationSet* set ){
	if(useTopologicalSort){
		structureoptimizer::PermutationSet* bestN = findBestNeighbour( set ) ;
		structureoptimizer::PermutationSet* topN = getTopologicNeighbour( set ) ;
		if ( topN->isBetter( *bestN ) ) {
			throw std::runtime_error("Topolical is better!") ;
			return topN ;
		}
		return bestN ;
	}
	return findBestNeighbour( set ) ;
}

structureoptimizer::PermutationSet* structureoptimizer::AcyclicSelection::getTopologicNeighbour( structureoptimizer::PermutationSet* set ){
	structureoptimizer::PermutationSet* topN = set->clone() ;
	topN->setPermutation( set->getStructure()->getTopologic() ) ;
	return topN ;
}
