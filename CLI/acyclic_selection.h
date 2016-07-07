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

			datastructures::BNStructure search( int numSolutions ) ;
			void printParameters() ;

		private :
			void visit( int index ) ;
			void setDefaultParameters() ;
			void setFileParameters( std::map<std::string, std::string> params ) ;
			
			std::vector<varset> m ; // Descendants
			std::vector<std::vector<int> > todo ; // To-Do lists
			datastructures::BNStructure partial_bn ; // Partial BN structure
	} ;
}

#endif	/* ACYCLIC_SELECTION_H */

