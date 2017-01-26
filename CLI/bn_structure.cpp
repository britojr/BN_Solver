/*
 * File:   bn_structure.cpp
 * Author: nonwhite
 *
 * Created on 7 de junio de 2016, 13:26
 */

#include "bn_structure.h"
#include "best_score_calculator.h"
#include "utils.h"
#include "typedefs.h"

datastructures::BNStructure::BNStructure(){
	// Do nothing
}

datastructures::BNStructure::BNStructure( int size ){
	for(int i = 0 ; i < size ; i++){
		structureoptimizer::Node* var = new structureoptimizer::Node( i , size ) ;
		nodes.push_back( var ) ;
	}
	variableCount = size ;
	structureScore = 0. ;
}

// Create structure based on a fixed order
datastructures::BNStructure::BNStructure( structureoptimizer::PermutationSet* order ,
											std::vector<bestscorecalculators::BestScoreCalculator*> &bsc ){
	for(int i = 0 ; i < order->size() ; i++){
		structureoptimizer::Node* var = new structureoptimizer::Node( i , order->size() ) ;
		nodes.push_back( var ) ;
	}
	variableCount = nodes.size() ;
	for(int i = 0 ; i < variableCount ; i++){
		varset options = order->getVarset( i ) ;
		int variable = (*order)[ i ] ;
		float score = bsc[ variable ]->getScore( options ) ;
		varset parents = bsc[ variable ]->getParents() ;
		setParents( variable , parents , score ) ;
		for(int j = 0 ; j < variableCount ; j++){
			if( !VARSET_GET( parents , j ) ) continue ;
			nodes[ j ]->addChild( variable ) ;
		}
	}
}

// Create cyclic graph with best parent sets for every variable
datastructures::BNStructure::BNStructure( std::vector<bestscorecalculators::BestScoreCalculator*> &bsc ,
											bool calculateEdgeWeights ){
	for(int i = 0 ; i < bsc.size() ; i++){
		structureoptimizer::Node* var = new structureoptimizer::Node( i , bsc.size() ) ;
		nodes.push_back( var ) ;
	}
	variableCount = bsc.size() ;
	VARSET_NEW( all , variableCount ) ;
	VARSET_SET_ALL( all , variableCount ) ;
	for(int variable = 0 ; variable < variableCount ; variable++){
		VARSET_CLEAR( all , variable ) ;
		float score = bsc[ variable ]->getScore( all ) ;
		varset parents = bsc[ variable ]->getParents() ;
		setParents( variable , parents , score ) ;
		for(int j = 0 ; j < variableCount ; j++){
			if( !VARSET_GET( parents , j ) ) continue ;
			if( calculateEdgeWeights ){
				VARSET_CLEAR( parents , j ) ;
				float weight = score - bsc[ variable ]->getScore( parents ) ;
				nodes[ j ]->addChild( variable , weight ) ;
				VARSET_SET( parents , j ) ;
			}else{
				nodes[ j ]->addChild( variable ) ;
			}
		}
		VARSET_SET( all , variable ) ;
	}
}

float datastructures::BNStructure::getScore(){
	return structureScore ;
}

bool datastructures::BNStructure::isBetter( datastructures::BNStructure other ){
	return compare( other.getScore() , structureScore ) > 0 ;
}

int datastructures::BNStructure::size(){
	return nodes.size() ;
}

void datastructures::BNStructure::setParents( int indexnode , varset parents , float score ){
	nodes[ indexnode ]->setParents( parents ) ;
	nodes[ indexnode ]->setScore( score ) ;
	structureScore = 0. ;
	for(int i = 0 ; i < variableCount ; i++) structureScore += nodes[ i ]->getScore() ;
	for(int j = 0 ; j < variableCount ; j++){
		if( !VARSET_GET( parents , j ) ) continue ;
		nodes[ j ]->addChild( indexnode ) ;
	}
}

float datastructures::BNStructure::getMeanInDegree(){
	float indegree = 0. ;
	for(int i = 0 ; i < variableCount ; i++) indegree += nodes[ i ]->getInGrade() ;
	return indegree / size() ;
}

int datastructures::BNStructure::getMaxInDegree(){
	int indegree = -1 ;
	for(int i = 0 ; i < variableCount ; i++) indegree = std::max( indegree , nodes[ i ]->getInGrade() ) ;
	return indegree ;
}

structureoptimizer::Node* datastructures::BNStructure::operator[]( int index ){
	return nodes[ index ] ;
}

void datastructures::BNStructure::print(){
	for(int i = 0 ; i < variableCount ; i++){
		printf("%d:" , i ) ;
		std::vector<int> children = nodes[ i ]->getChildrenVector() ;
		for(int j = 0 ; j < children.size() ; j++) printf(" %d" , children[ j ] ) ;
		printf("\n" ) ;
	}
	printf("\n" ) ;
}

std::vector<int> datastructures::BNStructure::getTopologic(){
	varset gray = VARSET( variableCount ), black = VARSET( variableCount ) ;
	std::vector<int> topSort(variableCount) ;
	int n = variableCount ;
	std::stack<int> stk ;
	for( int j = 0 ; j < variableCount ; j++ ){
		varset parents = nodes[ j ]->getParents() ;
		if( cardinality( parents ) != 0 ) continue ;
		stk.push( j ) ;
		while( !stk.empty() ){
			int v = stk.top() ;
			if( !VARSET_GET( gray , v ) ){
				VARSET_SET( gray , v ) ;
				std::vector<int> children = nodes[ v ]->getChildrenVector() ;
				for(int i = 0 ; i < children.size() ; i++ ){
					if( VARSET_GET( black , children[ i ] ) ) continue ;
					if( !VARSET_GET( gray , children[ i ] ) )
						stk.push( children[ i ] ) ;
					else
						throw std::runtime_error("Structure is not acyclic!") ;
				}
			} else {
				if( !VARSET_GET( black, v ) ){
					VARSET_SET( black , v ) ;
					topSort[--n] = v ;
				}
				stk.pop() ;
			}
		}
	}
	if( n != 0 ) throw std::runtime_error("Structure is not acyclic!") ;
	return topSort ;
}

// TODO: remove this
bool datastructures::BNStructure::hasCycle(){
	varset gray = VARSET( variableCount ), black = VARSET( variableCount ) ;
	std::stack<varset::size_type> stk ;
	while( !black.all() ){
		varset::size_type v = (~gray).find_first() ;
		stk.push( v ) ;
		while( !stk.empty() ){
			v = stk.top() ;
			if( !gray[ v ] ){
				gray.set( v ) ;
				varset children = nodes[ v ]->getChildren() ;
				for(varset::size_type i = children.find_first() ; i != varset::npos ; i = children.find_next(i) ){
					if ( black[ i ] )
						continue ;
					if( !gray[ i ] ){
						stk.push( i ) ;
					} else {
						// pointing to a gray children means a cycle
						std::cout << v << " is parent of " << i << std::endl;
						return true ;
					}
				}
			} else {
				black.set( v ) ;
				stk.pop() ;
			}
		}
	}
	return false ;
}
