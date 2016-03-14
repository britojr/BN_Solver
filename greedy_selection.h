/* 
 * File:   greedy_selection.h
 * Author: nonwhite
 *
 * Created on 13 de marzo de 2016, 09:23 PM
 */

#ifndef GREEDY_SELECTION_H
#define	GREEDY_SELECTION_H

#include "parent_set_selection.h"

namespace parentselection {
	class GreedySelection : public parentselection::ParentSetSelection {
		public :
			GreedySelection( scoring::ScoringFunction *scoringFunction ,
								int maxParents , int variableCount ,
								int runningTime , scoring::Constraints *constraints ) ;
			void calculateScores( int variable , FloatMap &cache ) ;

		private :
			void calculateScores_internal( int variable , FloatMap &cache ) ;

	} ;
}

#endif	/* GREEDY_SELECTION_H */

