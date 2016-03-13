/* 
 * File:   log_likelihood_calculator.h
 * Author: bmmalone
 *
 * Created on May 24, 2013, 6:32 PM
 */

#ifndef LOG_LIKELIHOOD_CALCULATOR_H
#define	LOG_LIKELIHOOD_CALCULATOR_H

#include "ad_tree.h"
#include <boost/unordered_map.hpp>

namespace scoring {
    
    class LogLikelihoodCalculator {
        
    public:
        LogLikelihoodCalculator();
        LogLikelihoodCalculator(ADTree *adTree, datastructures::BayesianNetwork &network, std::vector<float> &ilogi);
        
        ~LogLikelihoodCalculator() {
            // no pointers that aren't deleted elsewhere
        }
        
        void initialize(ADTree *adTree, datastructures::BayesianNetwork &network, std::vector<float> &ilogi);
        float calculate(int variable, varset &parents);
        float calculate(int variable, varset &parents, boost::unordered_map<uint64_t, int> &paCounts);
		float interactionInformation( varset &p1 , varset &p2 , int variable ) ;
        
        static std::vector<float> getLogCache(int recordCount) {
            std::vector<float> logCache;
            logCache.push_back(0.0f);
            for (int i = 1; i < recordCount + 2; i++) {
                float l = (float) (i * log(i));
                logCache.push_back(l);
            }
            return logCache;
        }
        
    private:
        void calculate(ContingencyTableNode *ct, uint64_t base, uint64_t index, boost::unordered_map<uint64_t, int> &paCounts, int variable, varset variables, int previousVariable, float &score);
		float mutualInformation( varset &p1 , varset &p2 ) ; // TODO: Implement this
		float mutualInformation( varset &p1 , varset &p2 , int variable ) ; // TODO: Implement this
		
        ADTree *adTree;
        datastructures::BayesianNetwork network;
        std::vector<float> ilogi;
    };
}


#endif	/* LOG_LIKELIHOOD_CALCULATOR_H */

