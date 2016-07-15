/* 
 * File:   FASInitializer.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 05:00 PM
 */
#include "utils.h"
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
	H = datastructures::BNStructure( bestScoreCalculators , true ) ;
	printf( "sc H = %.3f\n" , -H.getScore() ) ;
	printf( "dg H = %.3f\n" , H.getMeanInDegree() ) ;
	printf( "max degree H  = %d\n" , H.getMaxInDegree() ) ;
	removeFeedbackArcSet() ;
}

void initializers::FASInitializer::removeFeedbackArcSet(){
	while( hasCycle() ){
		std::sort( cycle.begin() , cycle.end() ) ;
		float minWeight = cycle[ 0 ].first ;
		for(int i = 0 ; i < cycle.size() ; i++){
			int x = cycle[ i ].second.first ;
			int y = cycle[ i ].second.second ;
			float weight = H[ x ]->getWeight( y ) ;
			if( isZero( weight ) ){
				H[ x ]->removeChild( y ) ;
				H[ y ]->removeParent( x ) ;
			}else{
				H[ x ]->addChild( y , weight - minWeight ) ;
			}
		}
	}
}

// TODO: Implement this in less than O( n^3 )
bool initializers::FASInitializer::hasCycle(){
	cycle.clear() ;
	// Initialize
	std::vector<std::vector<int> > graph ;
	for(int i = 0 ; i < variableCount ; i++){
		std::vector<int> row( variableCount , 123456789 ) ;
		graph.push_back( row ) ;
	}
	for(int i = 0 ; i < H.size() ; i++){
		std::vector<int> children = H[ i ]->getChildrenVector() ;
		for(int j = 0 ; j < children.size() ; j++){
			int ch = children[ j ] ;
			graph[ i ][ ch ] = 1 ;
		}
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
		e.first = H[ x ]->getWeight( y ) ;
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