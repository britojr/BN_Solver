/* 
 * File:   parent_set_selection.h
 * Author: nonwhite
 *
 * Created on 13 de marzo de 2016, 07:23 PM
 */

#ifndef PARENTSETSELECTION_H
#define	PARENTSETSELECTION_H

namespace parentset {
	class ParentSetSelection {
		public :
			virtual void calculateScores( int variable , FloatMap &cache ) = 0 ;
	} ;
}

#endif	/* PARENTSETSELECTION_H */

