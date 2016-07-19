/* 
 * File:   simulated_annealing.cpp
 * Author: nonwhite
 * 
 * Created on 8 de junio de 2016, 11:38
 */
#include <cstdio>

#include "simulated_annealing.h"
#include "utils.h"

structureoptimizer::SimulatedAnnealing::SimulatedAnnealing(){
	// Do nothing
}

structureoptimizer::SimulatedAnnealing::SimulatedAnnealing( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										std::string parametersFile ){
	this->variableCount = bestScoreCalculator.size() ;
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->gen = boost::mt19937( time( NULL ) ) ;

	setParameters( parametersFile ) ;
}

void structureoptimizer::SimulatedAnnealing::setDefaultParameters(){
	this->maxIterations = 10000 ;
	this->t_max = 2500.0 ;
	this->t_min = 5.0 ;
}

void structureoptimizer::SimulatedAnnealing::setFileParameters( std::map<std::string,std::string> params ){
	if( params.count( "max_iterations" ) )
		sscanf( params[ "max_iterations" ].c_str() , "%d" , &maxIterations ) ;
	
	if( params.count( "max_temperature" ) )
		sscanf( params[ "max_temperature" ].c_str() , "%f" , &t_max ) ;
	
	if( params.count( "min_temperature" ) )
		sscanf( params[ "min_temperature" ].c_str() , "%f" , &t_min ) ;
}

void structureoptimizer::SimulatedAnnealing::printParameters(){
	printf( "Max number of iterations: '%d'\n" , maxIterations ) ;
	printf( "Initial temperature: %.6f\n" , t_max ) ;
	printf( "Final temperature: %.6f\n" , t_min ) ;
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
		current.print( true ) ;
		for(int i = 0 ; i < maxIterations ; i++){
			printf(" === Iteration %d ===\n" , i+1 ) ;
			float temperature = t_max * exp( cooling_rate * i / maxIterations ) ;
			structureoptimizer::PermutationSet neigh = neighbour( current ) ;
			float accProb = acceptanceProbability( current , neigh , temperature ) ;
			if( compare( accProb , random_generator( gen ) ) >= 0 )
				current = neigh ;
			if( best.size() == 0 || current.isBetter( best ) )
				best = current ;
			best.print() ;
		}
	}
	return datastructures::BNStructure( best , bestScoreCalculators ) ;
}

structureoptimizer::PermutationSet structureoptimizer::SimulatedAnnealing::neighbour( structureoptimizer::PermutationSet set ){
	int index = random_generator( variableCount - 1 , gen ) ;
	structureoptimizer::PermutationSet newSet( set ) ;
	newSet.swap( index , index + 1 ) ;
	return newSet ;
}

float structureoptimizer::SimulatedAnnealing::acceptanceProbability( structureoptimizer::PermutationSet oldState ,
																	structureoptimizer::PermutationSet newState ,
																	float temperature ){
	if( newState.isBetter( oldState ) ) return 1.0 ;
	float oldEnergy = oldState.getScore() ;
	float newEnergy = newState.getScore() ;
	float diffE = newEnergy - oldEnergy ;
	return exp( -diffE / temperature ) ;
}