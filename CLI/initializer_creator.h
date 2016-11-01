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
#include "best_score_calculator.h"
#include "bfirst_initializer.h"

namespace initializers {
	
    static std::string initializerTypeString = "The type of solution initialization in greedy search [\"random\", \"dfs\", \"fas\"]" ;
	
    Initializer* create( std::string type ,
									std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ){
        Initializer* init = NULL ;
		if( type == "random" ){
			init = new RandomInitializer( bestScoreCalculator ) ;
		}else if( type == "dfs" ){
			init = new DFSInitializer( bestScoreCalculator ) ;
		}else if( type == "fas" ){
			init = new FASInitializer( bestScoreCalculator ) ;
		}else if( type == "bfirst" ){
			init = new BFirstInitializer( bestScoreCalculator ) ;
		}else{
			throw std::runtime_error( "Invalid Initializer type: '" + type + "'.  Valid options are 'random', 'dfs' and 'fas'.");
        }
		init->initialize() ;
		return init ;
    }
}

#endif	/* INITIALIZER_CREATOR_H */

