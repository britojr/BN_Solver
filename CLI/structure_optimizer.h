/* 
 * File:   StructureOptimizer.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 12:09
 */

#ifndef STRUCTUREOPTIMIZER_H
#define	STRUCTUREOPTIMIZER_H

#include <vector>

#include "best_score_calculator.h"
#include "initializer.h"
#include "node.h"

namespace structureoptimizer {
	class StructureOptimizer {
		public :
			virtual std::vector<structureoptimizer::Node*> search( int numSolutions ) = 0 ;

			initializers::Initializer* initializer ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
			int maxIterations ;
	} ;
}

#endif	/* STRUCTUREOPTIMIZER_H */

