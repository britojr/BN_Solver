/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   acyclic_behavior_set.cpp
 * Author: nonwhite
 * 
 * Created on October 25, 2016, 10:54 AM
 */

#include "acyclic_behavior_set.h"

//structureoptimizer::AcyclicBehavior::AcyclicBehavior(){
//	// Do nothing
//}
//
//structureoptimizer::AcyclicBehavior::AcyclicBehavior( int size ,
//													std::vector<bestscorecalculators::BestScoreCalculator*> &bestScoreCalculator ){
//	boost::mt19937 gen( time( NULL ) ) ;
//	for(int i = 0 ; i < size ; i++)
//		permutation.push_back( i ) ;
//	permutation = shuffle( permutation , gen ) ;
//	this->bestScoreCalculator = bestScoreCalculator ;
//	updateScore() ;
//}
//
//structureoptimizer::AcyclicBehavior::AcyclicBehavior( const structureoptimizer::PermutationSet &other ){
//	permutation.clear() ;
//	for(int i = 0 ; i < other.size() ; i++)
//		permutation.push_back( other[ i ] ) ;
//	this->bestScoreCalculator = other.getBestScoreCalculators() ;
//	updateScore() ;
//}
//
//structureoptimizer::AcyclicBehavior::~AcyclicBehavior(){
//	// Do nothing
//}
//
//void structureoptimizer::AcyclicBehavior::updateScore(){
//	// TODO
//}
//
//void structureoptimizer::AcyclicBehavior::swap( int idx1 , int idx2 ){
//	// TODO
//}
//
//bool structureoptimizer::AcyclicBehavior::operator <( structureoptimizer::PermutationSet other ) const {
//	return compare( other.getScore() , score ) > 0 ;
//}
//
//bool structureoptimizer::AcyclicBehavior::operator ==( structureoptimizer::PermutationSet other ) const {
//	return other.getPermutation() == permutation ;
//}