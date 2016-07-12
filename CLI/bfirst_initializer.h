/* 
 * File:   bfirst_initializer.h
 * Author: nonwhite
 *
 * Created on 10 de julio de 2016, 21:05
 */

#ifndef BFIRST_INITIALIZER_H
#define	BFIRST_INITIALIZER_H

#include <vector>

#include "node.h"
#include "best_score_calculator.h"
#include "initializer.h"
#include "typedefs.h"

namespace initializers {
	class BFirstInitializer : public initializers::Initializer {
		public :
			BFirstInitializer() ;
			BFirstInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ) ;
			~BFirstInitializer() ;
			
			structureoptimizer::PermutationSet generate() ;
			void initialize() ;

		private :
			int getRandomVariable() ;
			
			varset unvisitedVariables ;
	} ;
}

#endif	/* BFIRST_INITIALIZER_H */

