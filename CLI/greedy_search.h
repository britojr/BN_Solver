/* 
 * File:   GreedySearch.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 03:37 PM
 */

#ifndef GREEDYSEARCH_H
#define	GREEDYSEARCH_H

#include <map>
#include <string>

#include "structure_optimizer.h"
#include "permutation_set.h"

namespace structureoptimizer {
	class GreedySearch : public structureoptimizer::StructureOptimizer {
		public :
			GreedySearch() ;
			GreedySearch( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
						std::string parametersFile ) ;
			~GreedySearch() ;

			void printParameters() ;

		private :
			void initialize() ;
			datastructures::BNStructure search_internal() ;
			structureoptimizer::PermutationSet* findBestNeighbour( structureoptimizer::PermutationSet* set ) ;
			structureoptimizer::PermutationSet* perturbSet( structureoptimizer::PermutationSet* set ) ;
			structureoptimizer::PermutationSet* doSwap( structureoptimizer::PermutationSet* set , int index ) ;

			void setDefaultParameters() ;
			void setFileParameters( std::map<std::string,std::string> params ) ;

			structureoptimizer::PermutationSet* current ;

			// Configurable Parameters
			int maxIterations ;
			int numPerturbationSwaps ;
			bool performSolutionPerturbation ;
	} ;
}

#endif	/* GREEDYSEARCH_H */