/* 
 * File:   WPathInitializer.h
 * Author: nonwhite
 *
 * Created on 20 de febrero de 2016, 10:08 AM
 */

#ifndef WPATHINITIALIZER_H
#define	WPATHINITIALIZER_H

#include <boost/random.hpp>

#include <vector>
#include <random>

#include "node.h"
#include "best_score_calculator.h"
#include "initializer.h"
#include "typedefs.h"

namespace initializers {
	class WPathInitializer : public initializers::Initializer {
		public :
			WPathInitializer() ;
			WPathInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ) ;
			~WPathInitializer() ;
			
			structureoptimizer::PermutationSet generate() ;
			void initialize() ;

		private :
			std::vector<int> traverse( int index ) ;
			
			varset unvisitedVariables ;
			int variableCount ;
			std::vector<structureoptimizer::Node*> nodes ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
			std::vector<float> nodeWeights ;
			boost::mt19937 gen ;
	} ;
}

#endif	/* WPATHINITIALIZER_H */

