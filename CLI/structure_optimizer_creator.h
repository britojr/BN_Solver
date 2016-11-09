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
#include "simulated_annealing.h"
#include "tabu_search.h"
#include "beam_search.h"
#include "swap_search.h"

namespace structureoptimizer {
	static std::string structureOptimizerString = "The method for structure learning. [\"greedy_search\", \"acyclic_selection\"]";

	inline StructureOptimizer* create( std::string type , initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ,
										std::string structureParameterFile ){
		StructureOptimizer *sto ;
		if( type == "greedy_search" ){
			sto = new GreedySearch( initializer , bestScoreCalculators , structureParameterFile ) ;
		}else if( type == "acyclic_selection" ){
			sto = new AcyclicSelection( initializer , bestScoreCalculators , structureParameterFile ) ;
		}else if( type == "simulated_annealing" ){
			sto = new SimulatedAnnealing( initializer , bestScoreCalculators , structureParameterFile ) ;
		}else if( type == "tabu_search" ){
			sto = new TabuSearch( initializer , bestScoreCalculators , structureParameterFile ) ;
		}else if( type == "beam_search" ){
			sto = new BeamSearch( initializer , bestScoreCalculators , structureParameterFile ) ;
		}else if( type == "swap_search" ){
			sto = new SwapSearch( initializer , bestScoreCalculators , structureParameterFile ) ;
		}else{
			throw std::runtime_error( "Invalid algorithm selection: '" + type + 
					"'.  Valid options are 'greedy_search', " +
					"'acyclic_selection', 'simulated_annealing', 'tabu_search', 'beam_search' and 'swap_search'" ) ;
		}
		return sto ;
	}
}

#endif	/* STRUCTURE_OPTIMIZER_CREATOR_H */

