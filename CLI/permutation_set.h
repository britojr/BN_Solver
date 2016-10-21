/* 
 * File:   PermutationSet.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 05:22 PM
 */

#ifndef PERMUTATIONSET_H
#define	PERMUTATIONSET_H

#include <vector>

#include "best_score_calculator.h"
#include "typedefs.h"

namespace structureoptimizer {
	class PermutationSet {
		public :
			PermutationSet() ;
			PermutationSet( int size , std::vector<bestscorecalculators::BestScoreCalculator*> &bestScoreCalculator ) ;
			PermutationSet( const PermutationSet &other ) ;
			~PermutationSet() ;
			
			int operator [] ( int idx ) const ;
			bool operator < ( structureoptimizer::PermutationSet other ) const ;
			bool operator == ( structureoptimizer::PermutationSet other ) const ;
			
			void swap( int idx1 , int idx2 ) ;
			void reverse() ;
			
			void setScore( float score ) ;
			float getScore() ;
			void updateScore( int adjacentPos = -1 ) ;
			bool isBetter( PermutationSet other ) ;
			
			void setPermutation( std::vector<int> permutation ) ;
			std::vector<int> getPermutation() ;
			
			int size() const ;
			
			void print( bool printPermutation = false ) ;
			
			varset getVarset( int index ) ;
			
			std::vector<bestscorecalculators::BestScoreCalculator*> getBestScoreCalculators() const ;
			
		private :
			std::vector<int> permutation ;
			std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ;
			float score ;
	} ;
}

#endif	/* PERMUTATIONSET_H */

