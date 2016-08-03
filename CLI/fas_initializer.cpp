/* 
 * File:   FASInitializer.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 05:00 PM
 */
#include "utils.h"
#include "fas_solver.h"
#include "fas_initializer.h"
#include "bn_structure.h"

initializers::FASInitializer::FASInitializer(){
	// Do nothing
}

initializers::FASInitializer::FASInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ){
	this->variableCount = bestScoreCalculators.size() ;
	this->bestScoreCalculators = bestScoreCalculators ;
	this->inDegree = std::vector<int>( variableCount ) ;
	this->gen = boost::mt19937( time( NULL ) ) ;
}

initializers::FASInitializer::~FASInitializer(){
	// Do nothing
}

structureoptimizer::PermutationSet initializers::FASInitializer::generate(){
	this->unvisitedVariables = varset( variableCount ) ; 
	VARSET_SET_ALL( this->unvisitedVariables , variableCount ) ;

	std::vector<int> zeroGrade ;
	for(int i = 0 ; i < variableCount ; i++){
		inDegree[ i ] = H[ i ]->getInGrade() ;
		if( inDegree[ i ] == 0 )
			zeroGrade.push_back( i ) ;
	}
	zeroGrade = shuffle( zeroGrade , gen ) ;

	// Traverse graph and obtain a topological order
	std::vector<int> order ;
	for(int i = 0 ; i < zeroGrade.size() ; i++){
		int root = zeroGrade[ i ];
		if( !VARSET_GET( unvisitedVariables , root ) ) continue ;
		std::vector<int> visited = traverse( root ) ;
		for(int i = 0 ; i < visited.size() ; i++)
			order.push_back( visited[ i ] ) ;
	}

	// Build the permutation set
	structureoptimizer::PermutationSet set( variableCount , bestScoreCalculators ) ;
	set.setPermutation( order ) ;
	return set ;
}

void initializers::FASInitializer::initialize(){
	bool withEdgeWeights = true ;
	H = datastructures::BNStructure( bestScoreCalculators , withEdgeWeights ) ;
	printf( "sc H = %.3f\n" , -H.getScore() ) ;
	printf( "dg H = %.3f\n" , H.getMeanInDegree() ) ;
	printf( "max degree H  = %d\n" , H.getMaxInDegree() ) ;
	initializers::MinCostFASSolver solver = MinCostFASSolver() ;
	H = solver.removeFAS( H ) ;
}

std::vector<int> initializers::FASInitializer::traverse( int index ){
	std::vector<int> visited ;
	visited.push_back( index ) ;
	VARSET_CLEAR( unvisitedVariables , index ) ;
	std::vector<int> children = shuffle( H[ index ]->getChildrenVector() , gen ) ;
	for(int i = 0 ; i < children.size() ; i++){
		int ch = children[ i ] ;
		if( !VARSET_GET( unvisitedVariables , ch ) ) continue ;
		inDegree[ ch ]-- ;
		if( inDegree[ ch ] == 0 ){
			std::vector<int> next = traverse( ch ) ;
			for(int j = 0 ; j < next.size() ; j++)
				visited.push_back( next[ j ] ) ;
		}
	}
	return visited ;
}