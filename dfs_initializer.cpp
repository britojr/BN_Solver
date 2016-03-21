/* 
 * File:   DFSInitializer.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 05:00 PM
 */

#include <stack>

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
		greedysearch::Node* var = new greedysearch::Node( i , variableCount ) ;
		nodes.push_back( var ) ;
	}

	printf("Getting best possible parents for every variable\n" ) ;
	// Get best possible parents for every variable
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
//		printf("\tNode: %2d\tParents:" , i ) ;
		for(int j = 0 ; j < variableCount ; j++){
			if( !VARSET_GET( parents , j ) ) continue ;
			nodes[ j ]->addChild( i ) ;
//			printf( " %2d" , j ) ;
		}
//		printf("\n" ) ;
		totalScore += score ;

		VARSET_SET( all , i ) ;
	}
	printf("sc( H^* ) = %.3f\n" , -totalScore ) ;
	printf("m/n = %.2f\n" , indegree / variableCount ) ;
}

greedysearch::PermutationSet initializers::DFSInitializer::generate(){
	this->unvisitedVariables = varset( variableCount ) ;
	VARSET_SET_ALL( this->unvisitedVariables , variableCount ) ;

	// Traverse graph and obtain an order
	std::vector<int> order ;
	while( !unvisitedVariables.none() ){
		updateNodeWeights() ;
		int rIndex = random_generator( unvisitedWeights , gen ) ;
//		printf("\tChoose node %d\n" , unvisitedNodes[ rIndex ] ) ;
		std::vector<int> visited = traverse( unvisitedNodes[ rIndex ] ) ;
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

std::vector<int> initializers::DFSInitializer::traverse( int index ){
	std::vector<int> visited ;
	visited.push_back( index ) ;
	VARSET_CLEAR( unvisitedVariables , index ) ;
	std::vector<int> children = nodes[ index ]->getChildrenVector() ;
	std::vector<int> options ;
	for(int i = 0 ; i < children.size() ; i++){
		if( !VARSET_GET( unvisitedVariables , children[ i ] ) ) continue ;
		options.push_back( children[ i ] ) ;
	}
	if( !options.empty() ){
//		printf("\tOptions:" ) ;
//		for(int i = 0 ; i < options.size() ; i++) printf(" %2d" , options[ i ] ) ;
//		printf("\n" ) ;
		updateNodeWeights( options ) ;
		int idx = random_generator( unvisitedWeights , gen ) ;
//		printf("\tChoose node %d\n" , unvisitedNodes[ idx ] ) ;
		std::vector<int> next = traverse( unvisitedNodes[ idx ] ) ;
		for(int i = 0 ; i < next.size() ; i++)
			visited.push_back( next[ i ] ) ;
	}
	return visited ;
}

void initializers::DFSInitializer::updateNodeWeights(){
	unvisitedNodes.clear() ;
	unvisitedWeights.clear() ;
	std::map<int,int> indegreeM ;
	int mxInDegree = -1 ;
	for(int i = 0 ; i < variableCount ; i++){
		if( VARSET_GET( unvisitedVariables , i ) ){
			int indegree = getUnvisitedInDegree( i ) ;
			unvisitedNodes.push_back( i ) ;
			unvisitedWeights.push_back( indegree ) ;
			indegreeM[ indegree ]++ ;
			mxInDegree = std::max( indegree , mxInDegree ) ;
		}
	}
	float C = unvisitedNodes.size() ;
//	printf("All Unvisited\n" ) ;
	for(int i = 0 ; i < C ; i++){
		int indegree = unvisitedWeights[ i ] + 1 ;
		unvisitedWeights[ i ] = ( float( mxInDegree ) / indegree ) * ( 1. / indegree ) ;
//		printf( "\tNode: %2d\t weight: %.6f (%d)\n" , unvisitedNodes[ i ] , unvisitedWeights[ i ] , indegree - 1 ) ;
	}
	indegreeM.clear() ;
}

void initializers::DFSInitializer::updateNodeWeights( std::vector<int> options ){
	unvisitedNodes.clear() ;
	unvisitedWeights.clear() ;
	int n = options.size() ;
	std::map<int,int> indegreeM ;
	int mxInDegree = -1 ;
	for(int i = 0 ; i < n ; i++){
		int indegree = getUnvisitedInDegree( options[ i ] ) ;
		unvisitedNodes.push_back( options[ i ] ) ;
		unvisitedWeights.push_back( indegree ) ;
		indegreeM[ indegree ]++ ;
		mxInDegree = std::max( indegree , mxInDegree ) ;
	}
	mxInDegree++ ;
	float C = options.size() ;
//	printf("Unvisited childs\n" ) ;
	for(int i = 0 ; i < C ; i++){
		int indegree = unvisitedWeights[ i ] + 1 ;
		unvisitedWeights[ i ] = ( float( mxInDegree ) / indegree ) * ( 1. / indegree ) ;
//		printf( "\tNode: %2d\t weight: %.6f (%d)\n" , unvisitedNodes[ i ] , unvisitedWeights[ i ] , indegree - 1 ) ;
	}
	indegreeM.clear() ;
}

int initializers::DFSInitializer::getUnvisitedInDegree( int n ){
	varset currentParents = VARSET_AND( nodes[ n ]->getParents() , unvisitedVariables ) ;
	return cardinality( currentParents ) ;
}