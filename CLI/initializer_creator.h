/* 
 * File:   initializer_creator.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 04:18 PM
 */

#ifndef INITIALIZER_CREATOR_H
#define	INITIALIZER_CREATOR_H

#include "score_cache.h"

#include <stdexcept>
#include <string>

#include "initializer.h"
#include "random_initializer.h"
#include "dfs_initializer.h"
#include "fas_initializer.h"
#include "weighted_path_initializer.h"
#include "best_score_calculator.h"

namespace initializers {
	
    static std::string initializerTypeString = "The type of solution initialization in greedy search [\"random\", \"dfs\", \"fas\"]" ;
	
    initializers::Initializer* create( std::string type ,
									std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ){
        initializers::Initializer* init = NULL ;
		if( type == "random" ){
			init = new initializers::RandomInitializer( bestScoreCalculator ) ;
		}else if( type == "dfs" ){
			init = new initializers::DFSInitializer( bestScoreCalculator ) ;
		}else if( type == "fas" ){
			init = new initializers::FASInitializer( bestScoreCalculator ) ;
		}else if( type == "path" ){
			init = new initializers::WPathInitializer( bestScoreCalculator ) ;
		}else{
			throw std::runtime_error( "Invalid Initializer type: '" + type + "'.  Valid options are 'random', 'dfs' and 'fas'.");
        }
		init->initialize() ;
		return init ;
    }
}

#endif	/* INITIALIZER_CREATOR_H */

