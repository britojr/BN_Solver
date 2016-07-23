/* 
 * File:   independence_selection.h
 * Author: nonwhite
 *
 * Created on 13 de marzo de 2016, 09:23 PM
 */

#ifndef INDEPENDENCE_SELECTION_H
#define	INDEPENDENCE_SELECTION_H

#include "parent_set_selection.h"
#include "utils.h"

struct compareIndependence {
	bool operator()( approxStruct lhs , approxStruct rhs ) const {
		float val = lhs.first - rhs.first ;
		return compare( val ) <= 0 ;
	}
} ;

namespace parentselection {
	class IndependenceSelection : public parentselection::ParentSetSelection {
		public :
			IndependenceSelection( scoring::ScoringFunction *scoringFunction ,
								int maxParents , int variableCount ,
								int runningTime , scoring::Constraints *constraints ) ;

		private :
			void calculateScores_internal( int variable , FloatMap &pruned , FloatMap &cache ) ;
			void initialize( int variable , FloatMap &pruned , FloatMap &cache ) ;

			std::priority_queue<approxStruct,std::vector<approxStruct>,compareIndependence> open ;
			ApproxMap openCache ;
	} ;
}

#endif	/* INDEPENDENCE_SELECTION_H */