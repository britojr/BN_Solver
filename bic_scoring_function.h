/* 
 * File:   mdl_score_calculator.h
 * Author: malone
 *
 * Created on November 23, 2012, 9:15 PM
 */

#ifndef MDL_SCORE_CALCULATOR_H
#define	MDL_SCORE_CALCULATOR_H

#include <stdint.h>
#include <vector>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include "ad_tree.h"
#include "bayesian_network.h"
#include "scoring_function.h"
#include "typedefs.h"
#include "log_likelihood_calculator.h"
#include "constraints.h"

namespace scoring {

    class BICScoringFunction : public ScoringFunction {
    public:
        BICScoringFunction(datastructures::BayesianNetwork &network, datastructures::RecordFile &recordFile, LogLikelihoodCalculator *llc, Constraints *constraints, bool enableDeCamposPruning);

        ~BICScoringFunction() {
            // no pointers 
        }

        float calculateScore(int variable, varset parents, FloatMap &cache);
		approxStruct approximateScore( int variable , varset parents , FloatMap &cache ) ;
		float getFromApproximation( int variable , varset &p1 , varset &p2 , float approxValue , FloatMap &cache ) ;

    private:
        float t(int variable, varset parents);
        
        datastructures::BayesianNetwork network;
        Constraints *constraints;
        boost::unordered_set<varset> invalidParents;
        LogLikelihoodCalculator *llc;
        

        float baseComplexityPenalty;
		int recordFileSize ;
        bool enableDeCamposPruning;
    };

}

#endif	/* MDL_SCORE_CALCULATOR_H */

