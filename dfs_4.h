/* 
 * File:   WPathInitializer.h
 * Author: nonwhite
 *
 * Created on 20 de febrero de 2016, 10:08 AM
 */

#ifndef DFS_4_H
#define	DFS_4_H

#include <boost/random.hpp>

#include <vector>
#include <random>

#include "node.h"
#include "best_score_calculator.h"
#include "initializer.h"
#include "typedefs.h"

namespace initializers {
	class DFS4Initializer : public initializers::Initializer {
		public :
			DFS4Initializer() ;
			DFS4Initializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ) ;
			~DFS4Initializer() ;
			
			greedysearch::PermutationSet generate() ;
			void initialize() ;

		private :
			std::vector<int> traverse( int index ) ;
			
			varset unvisitedVariables ;
			int variableCount ;
			std::vector<greedysearch::Node*> nodes ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
			std::vector<float> nodeWeights ;
			boost::mt19937 gen ;
	} ;
}

#endif	/* DFS_4_H */