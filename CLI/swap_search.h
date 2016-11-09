/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   variable_neighborhood.h
 * Author: nonwhite
 *
 * Created on November 1, 2016, 11:06 AM
 */

#ifndef VARIABLE_NEIGHBORHOOD_H
#define VARIABLE_NEIGHBORHOOD_H

#include <map>
#include <string>

#include "structure_optimizer.h"
#include "permutation_set.h"

namespace structureoptimizer {
	class SwapSearch : public StructureOptimizer {
		public :
			SwapSearch() ;
			SwapSearch( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
						std::string parametersFile ) ;
			~SwapSearch() ;

			void printParameters() ;

		private :
			void initialize() ;
			datastructures::BNStructure search_internal() ;
			PermutationSet* findBestNeighbour( PermutationSet* set ) ;
			PermutationSet* doSwap( PermutationSet* set , int index ) ;

			void setDefaultParameters() ;
			void setFileParameters( std::map<std::string,std::string> params ) ;

			PermutationSet* current ;

			// Configurable Parameters
			int maxIterations ;
	} ;
}

#endif /* VARIABLE_NEIGHBORHOOD_H */