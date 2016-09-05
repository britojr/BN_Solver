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
	this->maxIterations = 1000.0 ;
	this->unchangedIterations = maxIterations ;
	this->numRepeats = 1 ;
	this->useDiffZero = true ;
	this->tempMax = 100.0 ;
	this->tempMin = 1.0 ;
}

void structureoptimizer::SimulatedAnnealing::setFileParameters( std::map<std::string,std::string> params ){
	if( params.count( "max_iterations" ) )
		sscanf( params[ "max_iterations" ].c_str() , "%d" , &maxIterations ) ;

	if( params.count( "unchanged_iterations" ) )
		sscanf( params[ "unchanged_iterations" ].c_str() , "%d" , &unchangedIterations ) ;

	if( params.count( "num_repeat" ) )
		sscanf( params[ "num_repeat" ].c_str() , "%d" , &numRepeats ) ;
	
	if( params.count( "use_diff_zero" ) ){
		int p ;
		sscanf( params[ "use_diff_zero" ].c_str() , "%d" , &p ) ;
		useDiffZero = ( p > 0 ) ;
	}

	if( params.count( "max_temperature" ) )
		sscanf( params[ "max_temperature" ].c_str() , "%f" , &tempMax ) ;

	if( params.count( "min_temperature" ) )
		sscanf( params[ "min_temperature" ].c_str() , "%f" , &tempMin ) ;
}

void structureoptimizer::SimulatedAnnealing::printParameters(){
	printf( "Max number of iterations: %d\n" , maxIterations ) ;
	printf( "Iterations at same temperature: %d\n" , numRepeats ) ;
	printf( "Iterations without changes: %d\n" , unchangedIterations ) ;
	printf( "Move always on diff zero: %s\n" , useDiffZero ? "true" : "false" ) ;
	printf( "Initial temperature: %.6f\n" , tempMax ) ;
	printf( "Final temperature: %.6f\n" , tempMin ) ;
}

structureoptimizer::SimulatedAnnealing::~SimulatedAnnealing(){
	// Do nothing
}

datastructures::BNStructure structureoptimizer::SimulatedAnnealing::search( int numSolutions ){
	structureoptimizer::PermutationSet best ;
	float cooling_rate = -log( tempMax / tempMin ) ;
	for(int k = 0 ; k < numSolutions ; k++){
		printf( " ======== Simulated Annealing ======== \n" ) ;
		structureoptimizer::PermutationSet current = initializer->generate() ;
		printf(" === Iteration %d ===\n" , 0 ) ;
		current.print( true ) ;
		int counter = 0 ;
		int numIterations = 0 ;
		for(int i = 0 ; i < maxIterations && counter != unchangedIterations ; i++,numIterations++){
			float temperature = tempMax * exp( cooling_rate * i / maxIterations ) ;
			bool hasChange = false ;
			for(int j = 0 ; j < numRepeats ; j++){
				structureoptimizer::PermutationSet neigh = neighbour( current ) ;
				float accProb = acceptanceProbability( current , neigh , temperature ) ;
				if( compare( accProb , random_generator( gen ) ) >= 0 )
					current = neigh ;
				if( best.size() == 0 || current.isBetter( best ) ){
					best = current ;
					counter = 0 ;
					hasChange = true ;
				}
			}
			if( hasChange ){
				printf(" === Iteration %d ===\n" , i+1 ) ;
				best.print() ;
			}else{
				counter++ ;
			}
		}
		printf("Iterations = %d\n" , numIterations ) ;
	}
	printf(" === BEST === \n" ) ;
	printf( "Score = %.6f\n" , best.getScore() ) ;
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
	if( !useDiffZero && isZero( diffE ) ) return temperature / tempMax ;
	return exp( -diffE / temperature ) ;
}