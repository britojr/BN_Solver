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
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ) ;
			~AcyclicSelection() ;

			datastructures::BNStructure search( int numSolutions ) ;

		private :
			void visit( int index ) ;
			
			std::vector<varset> m ; // Descendants
			std::vector<std::vector<int> > todo ; // To-Do lists
			datastructures::BNStructure partial_bn ; // Partial BN structure
			int variableCount ;
	} ;
}

#endif	/* ACYCLIC_SELECTION_H */

