/* 
 * File:   score_calculator.h
 * Author: malone
 *
 * Created on November 24, 2012, 5:46 PM
 */

#ifndef SCORE_CALCULATOR_H
#define	SCORE_CALCULATOR_H

#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#include "score_cache.h"
#include "typedefs.h"

#include <boost/asio.hpp>


namespace scoring {
    
    class Constraints;
    class ScoringFunction;

    class ScoreCalculator {
    public:
        ScoreCalculator(scoring::ScoringFunction *scoringFunction,
						int maxParents,
						int variableCount,
						int runningTime,
						Constraints *constraints ,
						std::string selectionType ) ;

        ~ScoreCalculator() {
            // no pointers that are not deleted elsewhere
            // these could possibly be "smart pointers" or something...
        }
        
        void calculateScores(int variable, FloatMap &cache);
        void prune(FloatMap &cache);

    private:
        void calculateScores_sequential( int variable , FloatMap &cache ) ;
		void calculateScores_greedy( int variable , FloatMap &cache ) ;
		void calculateScores_independence( int variable , FloatMap &cache ) ;
        void timeout( const boost::system::error_code& /*e*/ ) ;
		
        int highestCompletedLayer ;
        
        /**
         * A timer to keep track of how long the algorithm has been running.
         */
        boost::asio::io_service io ;
        boost::asio::deadline_timer *t ;

        /**
         * A variable to check if the user-specified time limit has expired.
         */
        bool outOfTime ;
        
        ScoringFunction *scoringFunction ;
        int maxParents ;
        int variableCount ;
        int runningTime ;
        Constraints *constraints ;
		int parentSetSelectionType ;
    };

}

#endif	/* SCORE_CALCULATOR_H */

