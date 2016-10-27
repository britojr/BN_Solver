/* 
 * File:   acyclic_selection.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 13:07
 */

#ifndef ACYCLIC_SELECTION_H
#define	ACYCLIC_SELECTION_H

#include "structure_optimizer.h"
#include "bn_structure.h"

namespace structureoptimizer {
	class AcyclicSelection : public structureoptimizer::StructureOptimizer {
		public :
			AcyclicSelection() ;
			AcyclicSelection( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
						std::string parametersFile ) ;
			~AcyclicSelection() ;

			void printParameters() ;

		private :
			void initialize() ;
			datastructures::BNStructure search_internal() ;
			structureoptimizer::PermutationSet* findBestNeighbour( structureoptimizer::PermutationSet* set ) ;
			structureoptimizer::PermutationSet* doSwap( structureoptimizer::PermutationSet* set , int index ) ;

			void setDefaultParameters() ;
			void setFileParameters( std::map<std::string, std::string> params ) ;

			structureoptimizer::PermutationSet* current ;

			// Configuration variables
			int maxIterations ;
			bool testFlag ;
	} ;
}

#endif	/* ACYCLIC_SELECTION_H */