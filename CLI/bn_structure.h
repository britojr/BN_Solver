/* 
 * File:   bn_structure.h
 * Author: nonwhite
 *
 * Created on 7 de junio de 2016, 13:26
 */

#ifndef BNSTRUCTURE_H
#define	BNSTRUCTURE_H

#include "node.h"
#include "permutation_set.h"
#include "best_score_calculator.h"

namespace datastructures {
	class BNStructure {
		public :
			BNStructure() ;
			BNStructure( int size ) ;
			BNStructure( structureoptimizer::PermutationSet order ,
						std::vector<bestscorecalculators::BestScoreCalculator*> &bsc ) ;
			
			structureoptimizer::Node* operator []( int index ) ;
			
			float getScore() ;
			
			int size() ;
			
			bool isBetter( datastructures::BNStructure other ) ;
			
			void setParents( int indexnode , varset parents , float score ) ;
			
		private :
			std::vector<structureoptimizer::Node*> nodes ;
			float score ;
			int variableCount ;
	} ;
}

#endif	/* BNSTRUCTURE_H */

