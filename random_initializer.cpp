/* 
 * File:   RandomInitializer.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 04:31 PM
 */

#include <cstdlib>

#include "random_initializer.h"
#include "utils.h"

initializers::RandomInitializer::RandomInitializer(){
    // Do nothing
}

initializers::RandomInitializer::RandomInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ){
    this->variableCount = bestScoreCalculators.size() ;
    this->bestScoreCalculators = bestScoreCalculators ;
    this->gen = boost::mt19937( time( NULL ) ) ;
}

initializers::RandomInitializer::~RandomInitializer(){
    // Do nothing
}

greedysearch::PermutationSet initializers::RandomInitializer::generate(){
    greedysearch::PermutationSet set( variableCount ) ;
    std::vector<int> permut = shuffle( set.getPermutation() , gen ) ;
    set.setPermutation( permut ) ;
    float score = 0.0 ;
    for(int i = 0 ; i < variableCount ; i++){
        varset parents = set.getVarset( i ) ;
        score += bestScoreCalculators[ i ]->getScore( parents ) ;
    }
    set.setScore( score ) ;
    return set ;
}

void initializers::RandomInitializer::initialize(){
    // Do nothing
}