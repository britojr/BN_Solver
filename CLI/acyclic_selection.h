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
	class AcyclicSelection : public StructureOptimizer {
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
			PermutationSet* chooseNeighbour( PermutationSet* set ) ;
			PermutationSet* findBestNeighbour( PermutationSet* set ) ;
			PermutationSet* getTopologicNeighbour( PermutationSet* set ) ;
			PermutationSet* doSwap( PermutationSet* set , int index ) ;

			void setDefaultParameters() ;
			void setFileParameters( std::map<std::string, std::string> params ) ;

			PermutationSet* current ;

			// Configuration variables
			int maxIterations ;
			bool testFlag ;
			bool useTopologicalSort ;
	} ;
}

#endif	/* ACYCLIC_SELECTION_H */
