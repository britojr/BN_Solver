/* 
 * File:   acyclic_selection.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 13:07
 */

#ifndef ACYCLIC_SELECTION_H
#define	ACYCLIC_SELECTION_H

#include "structure_optimizer.h"

namespace structureoptimizer {
	class AcyclicSelection : public structureoptimizer::StructureOptimizer {
		public :
			AcyclicSelection() ;
			AcyclicSelection( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
						int maxIterations ) ;
			~AcyclicSelection() ;
		
			std::vector<structureoptimizer::Node*> search( int numSolutions ) ;
		
		private :
//			structureoptimizer::PermutationSet findBestNeighbor( structureoptimizer::PermutationSet set ) ;
//			structureoptimizer::PermutationSet disturbSet( structureoptimizer::PermutationSet set , int numSwaps = 5 ) ;
//			structureoptimizer::PermutationSet doSwap( structureoptimizer::PermutationSet set , int index ) ;
//			std::vector<structureoptimizer::Node*> reconstructSolution( structureoptimizer::PermutationSet set ) ;
			
			int numIterations ;
			int variableCount ;
	} ;
}

#endif	/* ACYCLIC_SELECTION_H */

