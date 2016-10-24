/* 
 * File:   acyclic_selection.cpp
 * Author: nonwhite
 * 
 * Created on 28 de mayo de 2016, 13:07
 */
#include <boost/timer/timer.hpp>

#include "acyclic_selection.h"
#include "utils.h"

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
	// Do nothing
	// TODO: Remove test implementation
	testFlag = false ;
}

void structureoptimizer::AcyclicSelection::setFileParameters( std::map<std::string,std::string> params ){
	// Do nothing
	// TODO: Remove test implementation
	if( params.count( "test_flag" ) )
		testFlag = true ;
//		int p ;
//		sscanf( params[ "test_flag" ].c_str() , "%d" , &p ) ;
//		testFlag = ( p > 0 ) ;
//	}
}

void structureoptimizer::AcyclicSelection::printParameters(){
	// Do nothing
}

void structureoptimizer::AcyclicSelection::initialize(){
	printf( " ======== Acyclic Selection ======== \n" ) ;
	initial = initializer->generate() ;
	printf(" === Initial solution ===\n" ) ;
	initial.print() ;
}

datastructures::BNStructure structureoptimizer::AcyclicSelection::search_internal(){
	// TODO: Remove test implementation
	return ( testFlag ? searchEfficient() : searchBruteForce() ) ;
}

datastructures::BNStructure structureoptimizer::AcyclicSelection::searchEfficient(){
	datastructures::BNStructure best ;
	m = std::vector<varset>( variableCount , VARSET( variableCount ) ) ;
	todo = std::vector<varset>( variableCount , VARSET( variableCount ) ) ;
	partial_bn = datastructures::BNStructure( variableCount ) ;

	for(int j = variableCount - 1 ; j >= 0 ; j--){
		// Extract variable at position j
		int v_j = initial[ j ] ;

		// (a1) Pick best parent set with no descendants of V_j
		float score = bestScoreCalculators[ v_j ]->getScore( VARSET_NOT( m[ v_j ] ) ) ;
		varset parents = bestScoreCalculators[ v_j ]->getParents() ;
		partial_bn.setParents( v_j , parents , score ) ;

		// (a2) Update matrix representation and get ancestors of V_j
		VARSET_NEW( ancestors , variableCount ) ;
		for(int i = 0 ; i < variableCount  ; i++){
			if( VARSET_GET( parents , i ) )
				VARSET_SET( m[ i ] , v_j ) ;
			if( VARSET_GET( m[ i ] , v_j ) )
				VARSET_SET( ancestors , i ) ;
		}

		// (b1) Build a TODO list with descendants of V_j
		todo[ v_j ] = m[ v_j ] ;

		// (b2) Start an empty TODO list to all ancestors of V_j
		VARSET_OR( ancestors , parents ) ;
		for(int i = 0 ; i < variableCount ; i++)
			if( VARSET_GET( ancestors , i ) )
				todo[ i ] = VARSET( variableCount ) ;

		// (c) Start TODO lists of the parents of V_j with descendants of V_j
		for(int i = 0 ; i < variableCount ; i++)
			if( VARSET_GET( parents , i ) )
				todo[ i ] = m[ v_j ] ;

		// (d) For each ancestor X of V_j
	}
	return best ;
}

datastructures::BNStructure structureoptimizer::AcyclicSelection::searchBruteForce(){
	boost::timer::auto_cpu_timer cpu( 6 , "CPU time = %w\n" ) ; // TODO: Rethink location of timer

	partial_bn = datastructures::BNStructure( variableCount ) ;

	for(int j = variableCount - 1 ; j >= 0 && !outOfTime ; j--){
		// Extract variable at position j in initial
		int v_j = initial[ j ] ;

		// Pick best parent set with no descendants of V_j
		varset descendants = getDescendants( v_j ) ;
		float score = bestScoreCalculators[ v_j ]->getScore( VARSET_NOT( descendants ) ) ;
		varset parents = bestScoreCalculators[ v_j ]->getParents() ;
		partial_bn.setParents( v_j , parents , score ) ;
	}
	printf( "Score = %.6f\n" , partial_bn.getScore() ) ;
	t->cancel() ;
	return partial_bn ;
}

void structureoptimizer::AcyclicSelection::visit( int x ){
	for(int i = 0 ; i < todo[ x ].size() ; i++){
		int y = todo[ x ][ i ] ;
		// if m(X, Y ) is true, then ignore Y and move on;
		if( VARSET_GET( m[ x ] , y ) ) continue ;
		// otherwise set m(X, Y ) to true
		VARSET_SET( m[ x ] , y ) ;
		varset parents = partial_bn[ x ]->getParents() ;
		// add Y to the todo of parents of X.
		for(int j = 0 ; j < variableCount ; j++)
			if( VARSET_GET( parents , j ) ){
				bool in_todo = false ;
				for(int k = 0 ; k < todo[ j ].size() ; k++)
					if( todo[ j ][ k ] == y ){
						in_todo = true ;
						break ;
					}
				if( !in_todo ) todo[ j ].push_back( y ) ;
			}
	}
}

varset structureoptimizer::AcyclicSelection::getDescendants( int index ){
	VARSET_NEW( visited , variableCount ) ;
	VARSET_SET( visited , index ) ;
	std::vector<int> children = partial_bn[ index ]->getChildrenVector() ;
	for(int i = 0 ; i < children.size() ; i++){
		varset chVisited = getDescendants( children[ i ] ) ;
		VARSET_OR( visited , chVisited ) ;
	}
	return visited ;
}