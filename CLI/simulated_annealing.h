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
	class SimulatedAnnealing : public structureoptimizer::StructureOptimizer {
		public :
			SimulatedAnnealing() ;
			SimulatedAnnealing( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
						int maxIterations ) ;
			~SimulatedAnnealing() ;

			datastructures::BNStructure search( int numSolutions ) ;

		private :
			float acceptanceProbability( structureoptimizer::PermutationSet oldState ,
										structureoptimizer::PermutationSet newState ,
										float temperature ) ;
			structureoptimizer::PermutationSet neighbour( structureoptimizer::PermutationSet currentState ) ;
			
			int maxIterations ;
			int variableCount ;
			float t_max ;
			float t_min ;
			
			boost::mt19937 gen ;
	} ;
}

#endif	/* SIMULATED_ANNEALING_H */

