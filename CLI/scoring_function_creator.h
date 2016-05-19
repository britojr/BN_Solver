/* 
 * File:   scoring_function_creator.h
 * Author: nonwhite
 *
 * Created on 13 de marzo de 2016, 10:13 PM
 */

#ifndef SCORING_FUNCTION_CREATOR_H
#define	SCORING_FUNCTION_CREATOR_H

#include <boost/algorithm/string.hpp>

#include "ad_tree.h"
#include "record_file.h"
#include "constraints.h"
#include "bayesian_network.h"
#include "log_likelihood_calculator.h"
#include "bic_scoring_function.h"

namespace scoring {
    
	static std::string scoringFunctionString = "The scoring function to use. [\"BIC\"]" ;

	inline ScoringFunction* create( std::string sf , scoring::ADTree *adTree ,
									datastructures::BayesianNetwork &network ,
									datastructures::RecordFile &recordFile ,
									scoring::Constraints *constraints ,
									bool enableDeCamposPruning ){
		ScoringFunction *scoringFunction ;
		boost::algorithm::to_lower( sf ) ;
		if( sf == "bic" ){
			std::vector<float> ilogi = scoring::LogLikelihoodCalculator::getLogCache( recordFile.size() ) ;
			scoring::LogLikelihoodCalculator *llc = new scoring::LogLikelihoodCalculator( adTree , network , ilogi ) ;
			scoringFunction = new scoring::BICScoringFunction( network , recordFile , llc , constraints , enableDeCamposPruning ) ;
		}else{
			throw std::runtime_error( "Invalid PS selection: '" + sf + "'.  Valid options are 'sequential', 'greedy' and 'independence'.");
		}
		return scoringFunction ;
	}
	
	inline int parentsize( std::string sf ,
							int maxParents ,
							datastructures::BayesianNetwork &network ,
							datastructures::RecordFile &recordFile ){
		boost::algorithm::to_lower( sf ) ;
		if( maxParents > network.size() || maxParents < 1 ){
			maxParents = network.size() - 1 ;
		}
		if( sf.compare( "bic" ) == 0 ){
			int maxParentCount = log( 2 * recordFile.size() / log( recordFile.size() ) ) ;
			if( maxParentCount < maxParents )
				maxParents = maxParentCount ;
		}else{
			throw std::runtime_error( "Invalid scoring function.  Options are: 'BIC'" ) ;
		}
		return maxParents ;
	}
}

#endif	/* SCORING_FUNCTION_CREATOR_H */

