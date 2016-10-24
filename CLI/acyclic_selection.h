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

			varset getDescendants( int index ) ;
			void setDefaultParameters() ;
			void setFileParameters( std::map<std::string, std::string> params ) ;

			// Test methods
			datastructures::BNStructure searchEfficient() ;
			datastructures::BNStructure searchBruteForce() ;
			void visit( int index ) ;

			structureoptimizer::PermutationSet initial ;

			std::vector<varset> m ; // Descendants
			std::vector<varset> todo ; // To-Do lists
			datastructures::BNStructure partial_bn ; // Partial BN structure

			// Configuration variables
			bool testFlag ;
	} ;
}

#endif	/* ACYCLIC_SELECTION_H */