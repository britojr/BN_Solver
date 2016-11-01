/* 
 * File:   parent_set_selection_creator.h
 * Author: nonwhite
 *
 * Created on 13 de marzo de 2016, 07:54 PM
 */

#ifndef PARENT_SET_SELECTION_CREATOR_H
#define	PARENT_SET_SELECTION_CREATOR_H

#include "scoring_function.h"
#include "sequential_selection.h"
#include "greedy_selection.h"
#include "independence_selection.h"

namespace parentselection {
    
	static std::string parentSetSelectionString = "The method to selecting parent sets. [\"sequential\", \"greedy\", \"independence\"]";

	inline ParentSetSelection* create( std::string type , scoring::ScoringFunction *scoringFunction ,
										int maxParents , int variableCount , int runningTime ,
										scoring::Constraints *constraints ){
		ParentSetSelection *pss ;
		if( type == "sequential" ){
			pss = new SequentialSelection( scoringFunction , maxParents , variableCount , runningTime , constraints ) ;
		}else if( type == "greedy" ){
			pss = new GreedySelection( scoringFunction , maxParents , variableCount , runningTime , constraints ) ;
		}else if( type == "independence" ){
			pss = new IndependenceSelection( scoringFunction , maxParents , variableCount , runningTime , constraints ) ;
		}else{
			throw std::runtime_error( "Invalid PS selection: '" + type + "'.  Valid options are 'sequential', 'greedy' and 'independence'.");
		}
		return pss ;
	}
}

#endif	/* PARENT_SET_SELECTION_CREATOR_H */

