/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TabuSearch.h
 * Author: nonwhite
 *
 * Created on September 5, 2016, 3:37 PM
 */

#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <boost/random.hpp>

#include "structure_optimizer.h"
#include "bn_structure.h"
#include "permutation_set.h"
#include "tabu_list.h"

namespace structureoptimizer {
	class TabuSearch : public StructureOptimizer {
		public :
			TabuSearch() ;
			TabuSearch( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
						std::string parametersFile ) ;
			~TabuSearch() ;

			void printParameters() ;

		private :
			void initialize() ;
			datastructures::BNStructure search_internal() ;
			
			PermutationSet* findBestNeighbour( PermutationSet* currentState ) ;
			bool isTabuMove( PermutationSet* currentState , int swapIndex ) ;

			void setDefaultParameters() ;
			void setFileParameters( std::map<std::string,std::string> params ) ;

			datastructures::TabuList tabuList ;
			int bestSwap ;
			PermutationSet* current ;
			
			// Configurable parameters
			int maxIterations ;
			int lengthTabuList ;
			bool useAspirationCriterion ;
	} ;
}

#endif /* TABUSEARCH_H */

