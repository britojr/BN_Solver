/* 
 * File:   DFSInitializer.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 05:00 PM
 */

#include <stack>
#include <algorithm>

#include "node.h"
#include "dfs_initializer.h"
#include "utils.h"

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
	// Initialize adjacent lists
	nodes.clear() ;
	for(int i = 0 ; i < variableCount ; i++){
		structureoptimizer::Node* var = new structureoptimizer::Node( i , variableCount ) ;
		nodes.push_back( var ) ;
	}

	printf("Getting best possible parents for every variable\n" ) ;
	VARSET_NEW( all , variableCount ) ;
	VARSET_SET_ALL( all , variableCount ) ;
	float totalScore = 0. , indegree = 0. ;
	for(int i = 0 ; i < variableCount ; i++){
		VARSET_CLEAR( all , i ) ;

		float score = bestScoreCalculators[ i ]->getScore( all ) ; 
		nodes[ i ]->setScore( score ) ;
		varset parents = bestScoreCalculators[ i ]->getParents() ;
		nodes[ i ]->setParents( parents ) ;
		indegree += cardinality( parents ) ;
		for(int j = 0 ; j < variableCount ; j++){
			if( !VARSET_GET( parents , j ) ) continue ;
			nodes[ j ]->addChild( i ) ;
		}
		totalScore += score ;

		VARSET_SET( all , i ) ;
	}
	printf("sc( H^* ) = %.3f\n" , -totalScore ) ;
	printf("m/n = %.2f\n" , indegree / variableCount ) ;
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

structureoptimizer::PermutationSet initializers::DFSInitializer::generate(){
	this->unvisitedVariables = varset( variableCount ) ;
	VARSET_SET_ALL( this->unvisitedVariables , variableCount ) ;

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
	structureoptimizer::PermutationSet set( variableCount ) ;
	set.setPermutation( order ) ;
	float score = 0.0 ;
	for(int i = 0 ; i < variableCount ; i++){
		varset options = set.getVarset( i ) ;
		score += bestScoreCalculators[ i ]->getScore( options ) ;
	}
	set.setScore( score ) ;

	return set ;
}

void initializers::DFSInitializer::updateNodeWeights(){
	unvisitedNodes.clear() ;
	std::vector<int> indegree( variableCount ) ;
	for(int i = 0 ; i < variableCount ; i++)
		indegree.push_back( getUnvisitedInDegree( i ) ) ;
	for(int i = 0 ; i < variableCount ; i++){
		if( VARSET_GET( unvisitedVariables , i ) ){
			std::vector<int> children = nodes[ i ]->getChildrenVector() ;
			int h = 1 ;
			for(int j = 0 ; j < children.size() ; j++){
				if( indegree[ children[ j ] ] == 0 ) continue ;
				h *= ( indegree[ children[ j ] ] - 1 ) ;
			}
			unvisitedNodes.push_back( PAIR( i , PAIR( indegree[ i ] , h ) ) ) ;
		}
	}
}

int initializers::DFSInitializer::getUnvisitedInDegree( int n ){
	varset currentParents = VARSET_AND( nodes[ n ]->getParents() , unvisitedVariables ) ;
	return cardinality( currentParents ) ;
}