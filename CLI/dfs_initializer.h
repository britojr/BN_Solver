/* 
 * File:   dfs_initializer.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 05:00 PM
 */

#ifndef DFSINITIALIZER_H
#define	DFSINITIALIZER_H

#include <boost/random.hpp>

#include <vector>

#include "bn_structure.h"
#include "node.h"
#include "typedefs.h"
#include "permutation_set.h"
#include "initializer.h"
#include "best_score_calculator.h"

namespace initializers {
	class DFSInitializer : public initializers::Initializer {
		public :
			DFSInitializer() ;
			DFSInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ) ;
			~DFSInitializer() ;
			
			structureoptimizer::PermutationSet generate() ;
			void initialize() ;

		private :
			void updateNodeWeights() ;
			int getUnvisitedInDegree( int n ) ;
			
			datastructures::BNStructure H ;
			varset unvisitedVariables ;
			std::vector<hnode> unvisitedNodes ;
	} ;
}

#endif	/* DFSINITIALIZER_H */

