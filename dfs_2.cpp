/* 
 * File:   WPathInitializer.cpp
 * Author: nonwhite
 * 
 * Created on 20 de febrero de 2016, 10:08 AM
 */

#include "dfs_2.h"
#include "utils.h"

initializers::DFS2Initializer::DFS2Initializer(){
	// Do nothing
}

initializers::DFS2Initializer::DFS2Initializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ){
	this->bestScoreCalculators = bestScoreCalculators ;
	this->variableCount = bestScoreCalculators.size() ;
	this->nodeWeights = std::vector<float>( variableCount ) ;
	this->gen = boost::mt19937( time( NULL ) ) ;
}

initializers::DFS2Initializer::~DFS2Initializer(){
	// Do nothing
}

void initializers::DFS2Initializer::initialize(){
	// Initialize adjacent lists
	nodes.clear() ;
	for(int i = 0 ; i < variableCount ; i++){
		greedysearch::Node* var = new greedysearch::Node( i , variableCount ) ;
		nodes.push_back( var ) ;
	}

	printf("Getting best possible parents for every variable\n" ) ;
	// Get best possible parents for every variable
	VARSET_NEW( all , variableCount ) ;
	VARSET_SET_ALL( all , variableCount ) ;
	for(int i = 0 ; i < variableCount ; i++){
		VARSET_CLEAR( all , i ) ;

		float score = bestScoreCalculators[ i ]->getScore( all ) ;
		nodes[ i ]->setScore( score ) ;
		varset parents = bestScoreCalculators[ i ]->getParents() ;
		nodes[ i ]->setParents( parents ) ;
		for(int j = 0 ; j < variableCount ; j++){
			if( !VARSET_GET( parents , j ) ) continue ;
			VARSET_CLEAR( parents , j ) ;
			float weight = score - bestScoreCalculators[ i ]->getScore( parents ) ;
			nodes[ j ]->addChild( i , weight ) ;
			VARSET_SET( parents , j ) ;
		}

		VARSET_SET( all , i ) ;
	}
}

/*
 * Choose unvisited node based on the in-degree
 * Choose next node uniformly
 */
greedysearch::PermutationSet initializers::DFS2Initializer::generate(){
	this->unvisitedVariables = varset( variableCount ) ;
	VARSET_SET_ALL( this->unvisitedVariables , variableCount ) ;

	// Distribution to take random nodes
	for(int i = 0 ; i < variableCount ; i++)
		nodeWeights[ i ] = 1. / ( nodes[ i ]->getInGrade() + 1 ) ;

	// Traverse graph and obtain an order
	std::vector<int> order ;
	while( !unvisitedVariables.none() ){
		std::vector<int> unvisited ;
		std::vector<float> weights ;
		for(int i = 0 ; i < variableCount ; i++)
			if( VARSET_GET( unvisitedVariables , i ) ){
				weights.push_back( nodeWeights[ i ] ) ;
				unvisited.push_back( i ) ;
			}
		int rIndex = random_generator( weights , gen ) ;
		std::vector<int> visited = traverse( unvisited[ rIndex ] ) ;
		for(int i = 0 ; i < visited.size() ; i++)
			order.push_back( visited[ i ] ) ;
	}

	// Build the permutation set
	greedysearch::PermutationSet set( variableCount ) ;
	set.setPermutation( order ) ;
	float score = 0.0 ;
	for(int i = 0 ; i < variableCount ; i++){
		varset options = set.getVarset( i ) ;
		score += bestScoreCalculators[ i ]->getScore( options ) ;
	}
	set.setScore( score ) ;

	return set ;
}

std::vector<int> initializers::DFS2Initializer::traverse( int index ){
	std::vector<int> visited ;
	visited.push_back( index ) ;
	VARSET_CLEAR( unvisitedVariables , index ) ;
	std::vector<int> children = shuffle( nodes[ index ]->getChildrenVector() , gen ) ;
	for(int i = 0 ; i < children.size() ; i++){
		if( !VARSET_GET( unvisitedVariables , children[ i ] ) ) continue ;
		std::vector<int> next = traverse( children[ i ] ) ;
		for(int j = 0 ; j < next.size() ; j++)
			visited.push_back( next[ j ] ) ;
	}
	return visited ;
}