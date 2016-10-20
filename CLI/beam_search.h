/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   beam_search.h
 * Author: nonwhite
 *
 * Created on October 20, 2016, 3:52 PM
 */

#ifndef BEAM_SEARCH_H
#define BEAM_SEARCH_H

#include "structure_optimizer.h"
#include "permutation_set.h"

namespace structureoptimizer {
	class BeamSearch : public structureoptimizer::StructureOptimizer {
		public :
			BeamSearch() ;
			BeamSearch( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
						std::string parametersFile ) ;
			~BeamSearch() ;
		
			void printParameters() ;
		
		private :
			void initialize() ;
			datastructures::BNStructure search_internal() ;
			std::vector<structureoptimizer::PermutationSet> updateLayer(
						std::priority_queue<structureoptimizer::PermutationSet> &q ) ;
			std::vector<structureoptimizer::PermutationSet> getNeighbours(
						structureoptimizer::PermutationSet currentState ) ;
			structureoptimizer::PermutationSet doSwap(
						structureoptimizer::PermutationSet currentState , int index ) ;

			void setDefaultParameters() ;
			void setFileParameters( std::map<std::string,std::string> params ) ;
			
			structureoptimizer::PermutationSet current ;
			
			// Configurable Parameters
			int maxDepth ;
			int queueLength ;
	} ;
}

#endif /* BEAM_SEARCH_H */

