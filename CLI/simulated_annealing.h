/* 
 * File:   simulated_annealing.h
 * Author: nonwhite
 *
 * Created on 8 de junio de 2016, 11:38
 */

#ifndef SIMULATED_ANNEALING_H
#define	SIMULATED_ANNEALING_H

#include <boost/random.hpp>

#include "structure_optimizer.h"
#include "bn_structure.h"
#include "permutation_set.h"

namespace structureoptimizer {
	class SimulatedAnnealing : public StructureOptimizer {
		public :
			SimulatedAnnealing() ;
			SimulatedAnnealing( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
						std::string parametersFile ) ;
			~SimulatedAnnealing() ;

			void printParameters() ;

		private :
			void initialize() ;
			datastructures::BNStructure search_internal() ;

			float acceptanceProbability( PermutationSet* oldState ,
										PermutationSet* newState ,
										float temperature ) ;
			PermutationSet* neighbour( PermutationSet* currentState ) ;

			void setDefaultParameters() ;
			void setFileParameters( std::map<std::string,std::string> params ) ;

			PermutationSet* current ;

			// Configurable parameters
			int maxIterations ;
			int numRepeats ;
			int unchangedIterations ;
			bool useDiffZero ;
			float tempMax ;
			float tempMin ;
	} ;
}

#endif	/* SIMULATED_ANNEALING_H */