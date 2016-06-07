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
#include "bn_structure.h"

namespace structureoptimizer {
	class StructureOptimizer {
		public :
			virtual datastructures::BNStructure search( int numSolutions ) = 0 ;

			initializers::Initializer* initializer ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
	} ;
}

#endif	/* STRUCTUREOPTIMIZER_H */

