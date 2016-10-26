/* 
 * File:   dfs_initializer.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 05:00 PM
 */

#include <stack>
#include <algorithm>

#include "node.h"
#include "dfs_initializer.h"
#include "utils.h"
#include "bn_structure.h"
#include "permutation_set_creator.h"

initializers::DFSInitializer::DFSInitializer(){
	// Do nothing
}

initializers::DFSInitializer::DFSInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ){
	this->variableCount = bestScoreCalculators.size() ;
	this->bestScoreCalculators = bestScoreCalculators ;
	this->gen = boost::mt19937( time( NULL ) ) ;
}

initializers::DFSInitializer::~DFSInitializer(){
	// Do nothing
}

void initializers::DFSInitializer::initialize(){
	// Get the cyclic graph H
	H = datastructures::BNStructure( bestScoreCalculators ) ;
	printf("sc( H^* ) = %.3f\n" , -H.getScore() ) ;
	printf("m/n = %.3f\n" , H.getMeanInDegree() ) ;
}

bool cmpNodes( hnode node1 , hnode node2 ){
	// Check in-degree
	if( node1.second.first != node2.second.first )
		return node1.second.first < node2.second.first ;
	// Check product of children's in-degre
	if( node1.second.second != node2.second.second )
		return node1.second.second < node2.second.second ;
	return node1.first < node2.first ;
}

structureoptimizer::PermutationSet* initializers::DFSInitializer::generate( int setType ){
	unvisitedVariables = varset( variableCount ) ;
	VARSET_SET_ALL( unvisitedVariables , variableCount ) ;

	// Traverse graph and obtain an order
	std::vector<int> order ;
	while( !unvisitedVariables.none() ){
		updateNodeWeights() ;
		std::sort( unvisitedNodes.begin() , unvisitedNodes.end() , cmpNodes ) ;
		std::vector<int> options ;
		hnode bestOption = unvisitedNodes[ 0 ] ;
		for(int i = 0 ; i < unvisitedNodes.size() ; i++)
			if( bestOption.second == unvisitedNodes[ i ].second )
				options.push_back( unvisitedNodes[ i ].first ) ;
		int rIndex = random_generator( options.size() , gen ) ;
		int rNode = options[ rIndex ] ;
		order.push_back( rNode ) ;
		VARSET_CLEAR( unvisitedVariables , rNode ) ;
	}
	
	// Build the permutation set
	structureoptimizer::PermutationSet* set = structureoptimizer::createSet( setType , variableCount , bestScoreCalculators ) ;
	set->setPermutation( order ) ;
	return set ;
}

void initializers::DFSInitializer::updateNodeWeights(){
	unvisitedNodes.clear() ;
	std::vector<int> indegree( variableCount ) ;
	for(int i = 0 ; i < variableCount ; i++)
		indegree[ i ] = getUnvisitedInDegree( i ) ;
	for(int i = 0 ; i < variableCount ; i++){
		if( VARSET_GET( unvisitedVariables , i ) ){
			std::vector<int> children = H[ i ]->getChildrenVector() ;
			int h = 1 ;
			for(int j = 0 ; j < children.size() ; j++){
				int ch = children[ j ] ;
				if( indegree[ ch ] == 0 ) continue ;
				h *= ( indegree[ ch ] - 1 ) ;
			}
			unvisitedNodes.push_back( PAIR( i , PAIR( indegree[ i ] , h ) ) ) ;
		}
	}
}

int initializers::DFSInitializer::getUnvisitedInDegree( int n ){
	varset currentParents = VARSET_AND( H[ n ]->getParents() , unvisitedVariables ) ;
	return cardinality( currentParents ) ;
}