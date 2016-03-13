/* 
 * File:   RandomInitializer.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 04:31 PM
 */

#ifndef RANDOMINITIALIZER_H
#define	RANDOMINITIALIZER_H

#include <boost/random.hpp>

#include "score_cache.h"
#include "initializer.h"
#include "best_score_calculator.h"

namespace initializers {
	class RandomInitializer : public initializers::Initializer {
		public :
			RandomInitializer() ;
			RandomInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ) ;
			~RandomInitializer() ;
			
			greedysearch::PermutationSet generate() ;
			void initialize() ;

		private :
			int variableCount ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
			boost::mt19937 gen ;
	} ;
}

#endif	/* RANDOMINITIALIZER_H */

