/* 
 * File:   FASInitializer.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 05:00 PM
 */

#include <set>

#include "utils.h"
#include "fas_initializer.h"

initializers::FASInitializer::FASInitializer(){
	// Do nothing
}

initializers::FASInitializer::FASInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ){
	this->variableCount = bestScoreCalculators.size() ;
	this->bestScoreCalculators = bestScoreCalculators ;
	this->inGrades = std::vector<int>( variableCount ) ;
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
		inGrades[ i ] = nodes[ i ]->getInGrade() ;
		if( inGrades[ i ] == 0 )
			zeroGrade.push_back( i ) ;
	}
	zeroGrade = shuffle( zeroGrade , gen ) ;

	// Traverse graph and obtain a topological order
	std::vector<int> order ;
	for(int i = 0 ; i < zeroGrade.size() ; i++){
		if( !VARSET_GET( unvisitedVariables , zeroGrade[ i ] ) ) continue ;
		std::vector<int> visited = traverse( zeroGrade[ i ] ) ;
		for(int i = 0 ; i < visited.size() ; i++)
			order.push_back( visited[ i ] ) ;
	}

	// Build the permutation set
	structureoptimizer::PermutationSet set( variableCount , bestScoreCalculators ) ;
	set.setPermutation( order ) ;
	return set ;
}

void initializers::FASInitializer::initialize(){
	// Initialize adjacent lists
	nodes.clear() ;
	for(int i = 0 ; i < variableCount ; i++){
		structureoptimizer::Node* var = new structureoptimizer::Node( i , variableCount ) ;
		nodes.push_back( var ) ;
	}

	printf("Getting best possible parents for every variable\n" ) ;
	// Get best possible parents for every variable
	float totalScore = 0. , totalDegree = 0. ;
	int mxDegree = -1 ;
	VARSET_NEW( all , variableCount ) ;
	VARSET_SET_ALL( all , variableCount ) ;
	for(int i = 0 ; i < variableCount ; i++){
		VARSET_CLEAR( all , i ) ;

		float score = bestScoreCalculators[ i ]->getScore( all ) ;
		totalScore += score ;
		nodes[ i ]->setScore( score ) ;
		varset parents = bestScoreCalculators[ i ]->getParents() ;
		totalDegree += cardinality( parents ) ;
		mxDegree = std::max( mxDegree , cardinality( parents ) ) ;
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
	printf( "sc G completo = %.3f\n" , -totalScore ) ;
	printf( "dg G completo = %.3f\n" , totalDegree / variableCount ) ;
	printf( "max degree G  = %d\n" , mxDegree ) ;
	printf( "& %.3f & %.3f\n" , -totalScore , totalDegree / variableCount ) ;
	removeFeedbackArcSet() ;
}

void initializers::FASInitializer::removeFeedbackArcSet(){
	while( hasCycle() ){
		std::sort( cycle.begin() , cycle.end() ) ;
		float minWeight = cycle[ 0 ].first ;
		for(int i = 0 ; i < cycle.size() ; i++){
			int x = cycle[ i ].second.first ;
			int y = cycle[ i ].second.second ;
			float weight = nodes[ x ]->getWeight( y ) ;
			if( isZero( weight ) ){
				nodes[ x ]->removeChild( y ) ;
				nodes[ y ]->removeParent( x ) ;
			}else{
				nodes[ x ]->addChild( y , weight - minWeight ) ;
			}
		}
	}
}

bool initializers::FASInitializer::hasCycle(){
	cycle.clear() ;
	// TODO: Implement this in less than O( n^3 )
	// Initialize
	std::vector<std::vector<int> > graph ;

	for(int i = 0 ; i < variableCount ; i++){
		std::vector<int> row( variableCount , 123456789 ) ;
		graph.push_back( row ) ;
	}
	for(int i = 0 ; i < nodes.size() ; i++){
		std::vector<int> children = nodes[ i ]->getChildrenVector() ;
		for(int j = 0 ; j < children.size() ; j++)
			graph[ i ][ children[ j ] ] = 1 ;
	}
	std::vector<std::vector<int> > parents = graph ;
	for(int i = 0 ; i < variableCount ; i++)
		for(int j = 0 ; j < variableCount ; j++)
			parents[ i ][ j ] = i ;

	// Floyd-Warshall O( n^3 )
	for(int k = 0 ; k < variableCount ; k++)
		for(int i = 0 ; i < variableCount ; i++)
			for(int j = 0 ; j < variableCount ; j++){
				int aux = graph[ i ][ k ] + graph[ k ][ j ] ;
				if( aux < graph[ i ][ j ] ){
					graph[ i ][ j ] = aux ;
					parents[ i ][ j ] = parents[ k ][ j ] ;
				}
			}
	// Check if there is a cycle
	std::vector<int> path ;
	for(int i = 0 ; i < variableCount ; i++)
		if( graph[ i ][ i ] != 123456789 ){
			path.push_back( parents[ i ][ i ] ) ;
			int s = i ;
			int t = parents[ i ][ i ] ;
			while( s != t ){
				path.push_back( parents[ s ][ t ] ) ;
				t = parents[ s ][ t ] ;
			}
			break ;
		}
	for(int i = path.size() - 1 ; i >= 1 ; i--){
		int x = path[ i ] , y = path[ i - 1 ] ;
		edge e ;
		e.first = nodes[ x ]->getWeight( y ) ;
		e.second.first = x ;
		e.second.second = y ;
		cycle.push_back( e ) ;
	}

	return cycle.size() > 0 ;
}

std::vector<int> initializers::FASInitializer::traverse( int index ){
	std::vector<int> visited ;
	visited.push_back( index ) ;
	VARSET_CLEAR( unvisitedVariables , index ) ;
	std::vector<int> children = shuffle( nodes[ index ]->getChildrenVector() , gen ) ;
	for(int i = 0 ; i < children.size() ; i++){
		int ch = children[ i ] ;
		if( !VARSET_GET( unvisitedVariables , ch ) ) continue ;
		inGrades[ ch ]-- ;
		if( inGrades[ ch ] == 0 ){
			std::vector<int> next = traverse( ch ) ;
			for(int j = 0 ; j < next.size() ; j++)
				visited.push_back( next[ j ] ) ;
		}
	}
	return visited ;
}

void initializers::FASInitializer::printGraph(){
	for(int i = 0 ; i < variableCount ; i++){
		printf("%d:" , i ) ;
		std::vector<int> children = nodes[ i ]->getChildrenVector() ;
		for(int j = 0 ; j < children.size() ; j++) printf(" %d" , children[ j ] ) ;
		printf("\n" ) ;
	}
	printf("\n" ) ;
}