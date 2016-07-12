/* 
 * File:   bn_structure.cpp
 * Author: nonwhite
 * 
 * Created on 7 de junio de 2016, 13:26
 */

#include "bn_structure.h"
#include "best_score_calculator.h"
#include "utils.h"

datastructures::BNStructure::BNStructure(){
	// Do nothing
}

datastructures::BNStructure::BNStructure( int size ){
	for(int i = 0 ; i < size ; i++){
		structureoptimizer::Node* var = new structureoptimizer::Node( i , size ) ;
		nodes.push_back( var ) ;
	}
	this->variableCount = size ;
	this->score = 0. ;
}

datastructures::BNStructure::BNStructure( structureoptimizer::PermutationSet order ,
											std::vector<bestscorecalculators::BestScoreCalculator*> &bsc ){
	for(int i = 0 ; i < order.size() ; i++){
		structureoptimizer::Node* var = new structureoptimizer::Node( i , order.size() ) ;
		nodes.push_back( var ) ;
	}
	this->variableCount = nodes.size() ;
	this->score = 0. ;
	for(int i = 0 ; i < variableCount ; i++){
		varset options = order.getVarset( i ) ;
		int variable = order[ i ] ;
		float score = bsc[ variable ]->getScore( options ) ;
		varset parents = bsc[ variable ]->getParents() ;
		setParents( variable , parents , score ) ;
		for(int j = 0 ; j < variableCount ; j++){
			if( !VARSET_GET( parents , j ) ) continue ;
			nodes[ j ]->addChild( variable ) ;
		}
	}
}

float datastructures::BNStructure::getScore(){
	return score ;
}

bool datastructures::BNStructure::isBetter( datastructures::BNStructure other ){
	return compare( other.getScore() , score ) > 0 ;
}

int datastructures::BNStructure::size(){
	return nodes.size() ;
}

void datastructures::BNStructure::setParents( int indexnode , varset parents , float score ){
	nodes[ indexnode ]->setParents( parents ) ;
	nodes[ indexnode ]->setScore( score ) ;
	this->score = 0 ;
	for(int i = 0 ; i < variableCount ; i++) this->score += nodes[ i ]->getScore() ;
	for(int j = 0 ; j < variableCount ; j++){
		if( !VARSET_GET( parents , j ) ) continue ;
		nodes[ j ]->addChild( indexnode ) ;
	}
}

structureoptimizer::Node* datastructures::BNStructure::operator[]( int index ){
	return nodes[ index ] ;
}