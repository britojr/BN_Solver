/* 
 * File:   simulated_annealing.cpp
 * Author: nonwhite
 * 
 * Created on 8 de junio de 2016, 11:38
 */

#include "simulated_annealing.h"
#include "utils.h"

structureoptimizer::SimulatedAnnealing::SimulatedAnnealing(){
	// Do nothing
}

structureoptimizer::SimulatedAnnealing::SimulatedAnnealing( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										int maxIterations ){
	this->variableCount = bestScoreCalculator.size() ;
	this->maxIterations = maxIterations ;
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->t_max = 2500.0 ;
	this->t_min = 5.0 ;
	this->gen = boost::mt19937( time( NULL ) ) ;
}

structureoptimizer::SimulatedAnnealing::~SimulatedAnnealing(){
	// Do nothing
}

datastructures::BNStructure structureoptimizer::SimulatedAnnealing::search( int numSolutions ){
	structureoptimizer::PermutationSet best ;
	float cooling_rate = -log( t_max / t_min ) ;
	for(int k = 0 ; k < numSolutions ; k++){
		printf( " ======== Simulated Annealing ======== \n" ) ;
		structureoptimizer::PermutationSet current = initializer->generate() ;
		printf(" === Iteration %d ===\n" , 0 ) ;
		current.print() ;
		for(int i = 0 ; i < maxIterations ; i++){
			printf(" === Iteration %d ===\n" , i+1 ) ;
//			current.print() ;
			float temperature = t_max * exp( cooling_rate * i / maxIterations ) ;
			structureoptimizer::PermutationSet move = neighbour( current ) ;
			float accProb = acceptanceProbability( current , move , temperature ) ;
			if( compare( accProb , random_generator( gen ) ) >= 0 ){
				current = move ;
				if( best.size() == 0 || current.isBetter( best ) )
					best = current ;
			}
			best.print() ;
		}
	}
	return datastructures::BNStructure( best , bestScoreCalculators ) ;
}

structureoptimizer::PermutationSet structureoptimizer::SimulatedAnnealing::neighbour( structureoptimizer::PermutationSet set ){
	int index = random_generator( variableCount - 1 , gen ) ;
	
	structureoptimizer::PermutationSet newSet = set ;
	newSet.swap( index , index + 1 ) ;
	float newScore = set.getScore() ;

	// Remove previous scores
	varset previousOptions1 = set.getVarset( index ) ;
	newScore -= bestScoreCalculators[ set[ index ] ]->getScore( previousOptions1 ) ;

	varset previousOptions2 = set.getVarset( index + 1 ) ;
	newScore -= bestScoreCalculators[ set[ index + 1 ] ]->getScore( previousOptions2 ) ;

	// Add current scores
	varset currentOptions1 = newSet.getVarset( index ) ;
	newScore += bestScoreCalculators[ newSet[ index ] ]->getScore( currentOptions1 ) ;

	varset currentOptions2 = newSet.getVarset( index + 1 ) ;
	newScore += bestScoreCalculators[ newSet[ index + 1 ] ]->getScore( currentOptions2 ) ;

	newSet.setScore( newScore ) ;
	return newSet ;
}

float structureoptimizer::SimulatedAnnealing::acceptanceProbability( structureoptimizer::PermutationSet oldState ,
												structureoptimizer::PermutationSet newState ,
												float temperature ){
	float oldEnergy = oldState.getScore() ;
	float newEnergy = newState.getScore() ;
	float diffE = newEnergy - oldEnergy ;
	if( compare( diffE ) < 0 ) return 1.0 ;
	return exp( -diffE / temperature ) ;
}