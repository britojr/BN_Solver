/* 
 * File:   GreedySearch.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 03:37 PM
 */

#ifndef GREEDYSEARCH_H
#define	GREEDYSEARCH_H

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
		
			std::vector<structureoptimizer::Node*> search( int numSolutions ) ;
		
		private :
			structureoptimizer::PermutationSet findBestNeighbor( structureoptimizer::PermutationSet set ) ;
			structureoptimizer::PermutationSet disturbSet( structureoptimizer::PermutationSet set , int numSwaps = 5 ) ;
			structureoptimizer::PermutationSet doSwap( structureoptimizer::PermutationSet set , int index ) ;
			std::vector<structureoptimizer::Node*> reconstructSolution( structureoptimizer::PermutationSet set ) ;
			
			int numIterations ;
			int variableCount ;
	} ;
}

#endif	/* GREEDYSEARCH_H */

