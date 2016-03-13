/* 
 * File:   DFS4Initializer.cpp
 * Author: nonwhite
 * 
 * Created on 20 de febrero de 2016, 10:08 AM
 */

#include "dfs_4.h"
#include "utils.h"

#include <limits>

initializers::DFS4Initializer::DFS4Initializer(){
	// Do nothing
}

initializers::DFS4Initializer::DFS4Initializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ){
	this->bestScoreCalculators = bestScoreCalculators ;
	this->variableCount = bestScoreCalculators.size() ;
	this->nodeWeights = std::vector<float>( variableCount ) ;
	this->gen = boost::mt19937( time( NULL ) ) ;
}

initializers::DFS4Initializer::~DFS4Initializer(){
	// Do nothing
}

void initializers::DFS4Initializer::initialize(){
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

greedysearch::PermutationSet initializers::DFS4Initializer::generate(){
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

std::vector<int> initializers::DFS4Initializer::traverse( int index ){
	std::vector<int> visited ;
	visited.push_back( index ) ;

	VARSET_CLEAR( unvisitedVariables , index ) ;

	std::vector<int> children = nodes[ index ]->getChildrenVector() ;

	std::vector<float> childrenWeights ;
	std::vector<int> options ;
	for(int i = 0 ; i < children.size() ; i++){
		if( !VARSET_GET( unvisitedVariables , children[ i ] ) ) continue ;

		varset currentParents = VARSET_AND( nodes[ children[ i ] ]->getParents() , unvisitedVariables ) ;
		int currentInDegree = cardinality( currentParents ) ;
		childrenWeights.push_back( 1. / ( currentInDegree + 1 ) ) ;
		options.push_back( children[ i ] ) ;
	}
	if( !options.empty() ){
		int idx = random_generator( childrenWeights , gen ) ;
		std::vector<int> next = traverse( options[ idx ] ) ;
		for(int i = 0 ; i < next.size() ; i++)
			visited.push_back( next[ i ] ) ;
	}
	return visited ;
}