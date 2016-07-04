/* 
 * File:   GreedySearch.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 03:37 PM
 */

#ifndef GREEDYSEARCH_H
#define	GREEDYSEARCH_H

#include <boost/random.hpp>

#include "structure_optimizer.h"
#include "permutation_set.h"

namespace structureoptimizer {
	class GreedySearch : public structureoptimizer::StructureOptimizer {
		public :
			GreedySearch() ;
			GreedySearch( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
						int maxIterations ) ;
			~GreedySearch() ;
		
			datastructures::BNStructure search( int numSolutions ) ;
		
		private :
			structureoptimizer::PermutationSet findBestNeighbor( structureoptimizer::PermutationSet set ) ;
			structureoptimizer::PermutationSet perturbSet( structureoptimizer::PermutationSet set , int numSwaps = 3 ) ;
			structureoptimizer::PermutationSet doSwap( structureoptimizer::PermutationSet set , int index ) ;
			
			int numIterations ;
			int maxIterations ;
			int variableCount ;
			boost::mt19937 gen ;
	} ;
}

#endif	/* GREEDYSEARCH_H */

