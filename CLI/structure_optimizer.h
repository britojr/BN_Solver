/* 
 * File:   StructureOptimizer.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 12:09
 */

#ifndef STRUCTUREOPTIMIZER_H
#define	STRUCTUREOPTIMIZER_H

#include <map>
#include <vector>

#include <boost/random.hpp>

#include "best_score_calculator.h"
#include "initializer.h"
#include "bn_structure.h"

namespace structureoptimizer {
	class StructureOptimizer {
		public :
			virtual datastructures::BNStructure search( int numSolutions ) = 0 ;
			virtual void printParameters() = 0 ;

		protected :
			initializers::Initializer* initializer ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
			
			void setParameters( std::string parametersFile ) ;
			std::map<std::string,std::string> readParametersFile( std::string parametersFile ) ;
			virtual void setDefaultParameters() = 0 ;
			virtual void setFileParameters( std::map<std::string,std::string> params ) = 0 ;
			
			int variableCount ;
			boost::mt19937 gen ;
	} ;
}

#endif	/* STRUCTUREOPTIMIZER_H */

