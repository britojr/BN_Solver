/* 
 * File:   structure_optimizer_creator.h
 * Author: nonwhite
 *
 * Created on 28 de mayo de 2016, 12:01
 */

#ifndef STRUCTURE_OPTIMIZER_CREATOR_H
#define	STRUCTURE_OPTIMIZER_CREATOR_H

#include "initializer.h"
#include "best_score_calculator.h"
#include "greedy_search.h"
#include "acyclic_selection.h"

namespace structureoptimizer {

	static std::string structureOptimizerString = "The method for structure learning. [\"greedy_search\", \"acyclic_selection\"]";

	inline StructureOptimizer* create( std::string type , initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ,
										int maxIterations ){
		StructureOptimizer *sto ;
		if( type == "greedy_search" ){
			sto = new structureoptimizer::GreedySearch( initializer , bestScoreCalculators , maxIterations ) ;
		}else if( type == "asobs" ){
			sto = new structureoptimizer::AcyclicSelection( initializer , bestScoreCalculators ) ;
		}else{
			throw std::runtime_error( "Invalid SO selection: '" + type + "'.  Valid options are 'greedy_search' and 'acyclic_selection'." ) ;
		}
		return sto ;
	}
}

#endif	/* STRUCTURE_OPTIMIZER_CREATOR_H */

