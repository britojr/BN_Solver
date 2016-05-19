/* 
 * File:   greedy_selection.h
 * Author: nonwhite
 *
 * Created on 13 de marzo de 2016, 09:23 PM
 */

#ifndef GREEDY_SELECTION_H
#define	GREEDY_SELECTION_H

#include "parent_set_selection.h"
#include "utils.h"

struct compareGreedy {
	bool operator()( pqelem lhs , pqelem rhs ) const {
		float val = lhs.second - rhs.second ;
		return compare( val ) <= 0 ;
	}
} ;

namespace parentselection {
	class GreedySelection : public parentselection::ParentSetSelection {
		public :
			GreedySelection( scoring::ScoringFunction *scoringFunction ,
								int maxParents , int variableCount ,
								int runningTime , scoring::Constraints *constraints ) ;
			void calculateScores( int variable , FloatMap &cache ) ;

		private :
			void calculateScores_internal( int variable , FloatMap &pruned , FloatMap &cache ) ;
			void initialize( int variable , FloatMap &pruned , FloatMap &cache ) ;

			std::priority_queue<pqelem,std::vector<pqelem>,compareGreedy> open ;
			FloatMap openCache ;
	} ;
}

#endif	/* GREEDY_SELECTION_H */

