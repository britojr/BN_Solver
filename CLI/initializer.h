/* 
 * File:   Initializer.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 04:33 PM
 */

#ifndef INITIALIZER_H
#define	INITIALIZER_H

#include <boost/random.hpp>

#include "permutation_set.h"

namespace initializers {
	class Initializer {
		public :
			virtual structureoptimizer::PermutationSet* generate( int setType = 0 ) = 0 ;
			virtual void initialize() = 0 ;
			
		protected :
			int variableCount ;
			boost::mt19937 gen ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
	} ;
}

#endif	/* INITIALIZER_H */

