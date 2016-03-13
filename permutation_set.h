/* 
 * File:   PermutationSet.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 05:22 PM
 */

#ifndef PERMUTATIONSET_H
#define	PERMUTATIONSET_H

#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#include <vector>

#include "typedefs.h"

namespace greedysearch {
	class PermutationSet {
		public :
			PermutationSet() ;
			PermutationSet( int size ) ;
			~PermutationSet() ;
			
			int operator [] ( int idx ) ;
			
			void swap( int idx1 , int idx2 ) ;
			
			void setScore( float score ) ;
			float getScore() ;
			bool isBetter( PermutationSet other ) ;
			
			void setPermutation( std::vector<int> permutation ) ;
			std::vector<int> getPermutation() ;
			
			int size() ;
			
			void print() ;
			
			varset getVarset( int index ) ;
			
		private :
			std::vector<int> permutation ;
			float score ;
	} ;
}

#endif	/* PERMUTATIONSET_H */

