/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   permutation_set_creator.h
 * Author: nonwhite
 *
 * Created on October 26, 2016, 4:32 PM
 */

#ifndef PERMUTATION_SET_CREATOR_H
#define PERMUTATION_SET_CREATOR_H

#include "permutation_set.h"
#include "greedy_behavior_set.h"
#include "acyclic_behavior_set.h"

namespace structureoptimizer {
	static const int GREEDY_BEHAVIOR_SET = 0 ;
	static const int ACYCLIC_BEHAVIOR_SET = 1 ;

	// TODO: Move this to an static method in PermutationSet abstract class
	inline PermutationSet* createSet( int setType , int variableCount ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ){
		PermutationSet *set ;
		switch( setType ){
			case GREEDY_BEHAVIOR_SET :
				set = new structureoptimizer::GreedyBehaviorSet( variableCount , bestScoreCalculators ) ;
				break ;
			case ACYCLIC_BEHAVIOR_SET :
				set = new structureoptimizer::AcyclicBehaviorSet( variableCount , bestScoreCalculators ) ;
				break ;
			default :
				throw std::runtime_error( "Invalid permutation set type: " + TO_STRING( setType ) +
					"Valid options are 'greedy'(0) and 'acyclic'(1)" ) ;
		}
		return set ;
	}
}

#endif /* PERMUTATION_SET_CREATOR_H */