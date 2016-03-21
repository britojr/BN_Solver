/* 
 * File:   DFSInitializer.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 05:00 PM
 */

#ifndef DFSINITIALIZER_H
#define	DFSINITIALIZER_H

#include <boost/random.hpp>

#include <vector>

#include "node.h"
#include "typedefs.h"
#include "permutation_set.h"
#include "initializer.h"
#include "best_score_calculator.h"

namespace initializers {
	class DFSInitializer : public initializers::Initializer {
		public :
			DFSInitializer() ;
			DFSInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ) ;
			~DFSInitializer() ;
			
			greedysearch::PermutationSet generate() ;
			void initialize() ;

		private :
			std::vector<int> traverse( int index ) ;
			void updateNodeWeights() ;
			void updateNodeWeights( std::vector<int> options ) ;
			int getUnvisitedInDegree( int n ) ;
			
			varset unvisitedVariables ;
			int variableCount ;
			std::vector<greedysearch::Node*> nodes ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
			
			std::vector<float> unvisitedWeights ;
			std::vector<int> unvisitedNodes ;
			boost::mt19937 gen ;
	} ;
}

#endif	/* DFSINITIALIZER_H */

