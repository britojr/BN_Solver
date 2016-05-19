/* 
 * File:   SequentialSelection.h
 * Author: nonwhite
 *
 * Created on 13 de marzo de 2016, 08:49 PM
 */

#ifndef SEQUENTIALSELECTION_H
#define	SEQUENTIALSELECTION_H

#include <queue>

#include "parent_set_selection.h"

namespace parentselection {
	class SequentialSelection : public parentselection::ParentSetSelection {
		public :
			SequentialSelection( scoring::ScoringFunction *scoringFunction ,
								int maxParents , int variableCount ,
								int runningTime , scoring::Constraints *constraints ) ;
			void calculateScores( int variable , FloatMap &cache ) ;

		private :
			void initialize( int variable , FloatMap &pruned , FloatMap &cache ) ;
			void calculateScores_internal( int variable , FloatMap &pruned , FloatMap &cache ) ;

			std::queue<varset> open ;
			FloatMap openCache ;
	} ;
}

#endif	/* SEQUENTIALSELECTION_H */

