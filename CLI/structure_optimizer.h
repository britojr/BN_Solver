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
#include <boost/asio.hpp>

#include "best_score_calculator.h"
#include "initializer.h"
#include "bn_structure.h"

namespace structureoptimizer {
	class StructureOptimizer {
		public :
			datastructures::BNStructure search( int numSolutions , int timePerSolution ) ;

			// Abstract methods
			virtual void printParameters() = 0 ;

		protected :
			void timeout( const boost::system::error_code &/*e*/ ) ;
			
			void setParameters( std::string parametersFile ) ;
			std::map<std::string,std::string> readParametersFile( std::string parametersFile ) ;
			
			// Abstract methods
			virtual void setDefaultParameters() = 0 ;
			virtual void setFileParameters( std::map<std::string,std::string> params ) = 0 ;
			virtual void initialize() = 0 ;
			virtual datastructures::BNStructure search_internal() = 0 ;
			
			int variableCount ;
			boost::mt19937 gen ;

			initializers::Initializer* initializer ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ;
			
			// Timer variables
			boost::asio::io_service io ;
			boost::asio::deadline_timer *t ;
			bool outOfTime ;

	} ;
}

#endif	/* STRUCTUREOPTIMIZER_H */

