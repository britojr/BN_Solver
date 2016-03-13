/* 
 * File:   GreedySearch.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 03:37 PM
 */

#ifndef GREEDYSEARCH_H
#define	GREEDYSEARCH_H

#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#include <vector>

#include "initializer.h"
#include "permutation_set.h"
#include "best_score_calculator.h"
#include "node.h"

namespace greedysearch {
	class GreedySearch {
		public :
			GreedySearch() ;
			GreedySearch( initializers::Initializer* initializer ,
						std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ) ;
			~GreedySearch() ;
		
			std::vector<greedysearch::Node*> search( int numSolutions = 1 ) ;
		
		private :
			greedysearch::PermutationSet findBestNeighbor( greedysearch::PermutationSet set ) ;
			greedysearch::PermutationSet disturbSet( greedysearch::PermutationSet set , int numSwaps = 5 ) ;
			greedysearch::PermutationSet doSwap( greedysearch::PermutationSet set , int index ) ;
			std::vector<greedysearch::Node*> reconstructSolution( greedysearch::PermutationSet set ) ;
			
			initializers::Initializer* initializer ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ;
			int maxIterations ; // TODO: Set a limit (e.g 100))
			int numIterations ;
			int variableCount ;
	} ;
}

#endif	/* GREEDYSEARCH_H */

