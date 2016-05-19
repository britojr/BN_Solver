/* 
 * File:   parent_set_selection.h
 * Author: nonwhite
 *
 * Created on 13 de marzo de 2016, 07:23 PM
 */

#ifndef PARENTSETSELECTION_H
#define	PARENTSETSELECTION_H

#include <boost/asio.hpp>

#include "scoring_function.h"
#include "constraints.h"

namespace parentselection {
	class ParentSetSelection {
		public :
			void prune( FloatMap &cache ) ;
			void timeout( const boost::system::error_code& /*e*/ ) ;

			virtual void calculateScores( int variable , FloatMap &cache ) = 0 ;
			virtual void calculateScores_internal( int variable , 
													FloatMap &pruned ,
													FloatMap &cache ) = 0 ;
			virtual void initialize( int variable , FloatMap &pruned ,
										FloatMap &cache ) = 0 ;

			boost::asio::io_service io ;
			boost::asio::deadline_timer *t ;
			bool outOfTime ;

			scoring::ScoringFunction *scoringFunction ;
			int maxParents ;
			int variableCount ;
			int runningTime ;
			scoring::Constraints *constraints ;
			int highestCompletedLayer ;
	} ;
}

#endif	/* PARENTSETSELECTION_H */