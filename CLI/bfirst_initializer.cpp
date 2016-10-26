/* 
 * File:   bfirst_initializer.cpp
 * Author: nonwhite
 * 
 * Created on 10 de julio de 2016, 21:05
 */
#include "bfirst_initializer.h"
#include "permutation_set_creator.h"
#include "utils.h"

initializers::BFirstInitializer::BFirstInitializer(){
	// Do nothing
}

initializers::BFirstInitializer::BFirstInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ){
	this->variableCount = bestScoreCalculators.size() ;
	this->bestScoreCalculators = bestScoreCalculators ;
	this->gen = boost::mt19937( time( NULL ) ) ;
}

initializers::BFirstInitializer::~BFirstInitializer(){
	// Do nothing
}

void initializers::BFirstInitializer::initialize(){
	// Do nothing
}

structureoptimizer::PermutationSet* initializers::BFirstInitializer::generate( int setType ){
	std::vector<int> order( variableCount ) ;
	unvisitedVariables = varset( variableCount ) ;
	VARSET_SET_ALL( unvisitedVariables , variableCount ) ;
	for(int i = variableCount - 1 ; i >= 0 ; i--){
		int rvar = getRandomVariable() ;
		order[ i ] = rvar ;
		VARSET_CLEAR( unvisitedVariables , rvar ) ;
	}
	structureoptimizer::PermutationSet* set = structureoptimizer::createSet( setType , variableCount , bestScoreCalculators ) ;
	set->setPermutation( order ) ;
	return set ;
}

int initializers::BFirstInitializer::getRandomVariable(){
	std::vector<std::pair<float,int> > options ;
	std::vector<float> weights ;
	// Get possible options
	for(int i = 0 ; i < variableCount ; i++){
		if( !VARSET_GET( unvisitedVariables , i ) ) continue ;
		float bestSc = bestScoreCalculators[ i ]->getScore( unvisitedVariables ) ;
		options.push_back( PAIR( bestSc , i ) ) ;
	}
	std::sort( options.begin() , options.end() ) ;
	// Calculate weights (probabilities)
	for(int i = 0 ; i < options.size() ; i++)
		weights.push_back( 1. / ( i + 1 ) ) ;
	// Get random variable based on weights
	int rindex = random_generator( weights , gen ) ;
	return options[ rindex ].second ;
}