/* 
 * File:   independence_selection.h
 * Author: nonwhite
 *
 * Created on 13 de marzo de 2016, 09:23 PM
 */

#ifndef INDEPENDENCE_SELECTION_H
#define	INDEPENDENCE_SELECTION_H

#include "parent_set_selection.h"

namespace parentselection {
	class IndependenceSelection : public parentselection::ParentSetSelection {
		public :
			IndependenceSelection( scoring::ScoringFunction *scoringFunction ,
								int maxParents , int variableCount ,
								int runningTime , scoring::Constraints *constraints ) ;
			void calculateScores( int variable , FloatMap &cache ) ;

		private :
			void calculateScores_internal( int variable , FloatMap &pruned , FloatMap &cache ) ;

	} ;
}

#endif	/* INDEPENDENCE_SELECTION_H */

