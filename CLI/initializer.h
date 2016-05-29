/* 
 * File:   Initializer.h
 * Author: nonwhite
 *
 * Created on 26 de enero de 2016, 04:33 PM
 */

#ifndef INITIALIZER_H
#define	INITIALIZER_H

#include "permutation_set.h"

namespace initializers {
	class Initializer {
		public :
			virtual structureoptimizer::PermutationSet generate() = 0 ;
			virtual void initialize() = 0 ;
	} ;
}

#endif	/* INITIALIZER_H */

