/* 
 * File:   FASInitializer.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 05:00 PM
 */

#ifndef FASINITIALIZER_H
#define	FASINITIALIZER_H

#include <boost/random.hpp>

#include <vector>

#include "node.h"
#include "best_score_calculator.h"
#include "initializer.h"
#include "typedefs.h"

namespace initializers {
	class FASInitializer : public initializers::Initializer {
		public :
			FASInitializer() ;
			FASInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ) ;
			~FASInitializer() ;
			
			structureoptimizer::PermutationSet generate() ;
			void initialize() ;

		private :
			std::vector<int> traverse( int index ) ;
			void removeFeedbackArcSet() ;
			bool hasCycle() ;
			void printGraph() ;
			
			varset unvisitedVariables ;
			int variableCount ;
			std::vector<structureoptimizer::Node*> nodes ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
			std::vector<edge> cycle ;
			std::vector<int> inGrades ;
			boost::mt19937 gen ;
	} ;
}

#endif	/* FASINITIALIZER_H */

