/* 
 * File:   fas_initializer.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 05:00 PM
 */

#ifndef FASINITIALIZER_H
#define	FASINITIALIZER_H

#include <vector>

#include "bn_structure.h"
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
			
			varset unvisitedVariables ;
			std::vector<edge> cycle ;
			std::vector<int> inDegree ;
			datastructures::BNStructure H ;
	} ;
}

#endif	/* FASINITIALIZER_H */

