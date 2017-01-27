/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   acyclic_behavior_set.h
 * Author: nonwhite
 *
 * Created on October 25, 2016, 10:54 AM
 */

#ifndef ACYCLIC_BEHAVIOR_SET_H
#define ACYCLIC_BEHAVIOR_SET_H

#include "permutation_set.h"
#include "bn_structure.h"

namespace structureoptimizer {
	class AcyclicBehaviorSet : public PermutationSet {
		public :
			AcyclicBehaviorSet(){
				// Do nothing
			}

			AcyclicBehaviorSet( int size ,
						std::vector<bestscorecalculators::BestScoreCalculator*> &bestScoreCalculator ){
				boost::mt19937 gen( time( NULL ) ) ;
				for(int i = 0 ; i < size ; i++)
					permutation.push_back( i ) ;
				permutation = shuffle( permutation , gen ) ;
				this->bestScoreCalculator = bestScoreCalculator ;
				structure = new datastructures::BNStructure( size ) ;
				ancestors = VARSET( size ) ;
				empty = VARSET( size ) ;
				updateScore() ;
			}

			PermutationSet* clone() {
				// TODO: Do not recalculate structure
				AcyclicBehaviorSet* set ;
				set = new AcyclicBehaviorSet( permutation.size() , bestScoreCalculator ) ;
				set->setPermutation( permutation ) ;
				return set ;
			}

			datastructures::BNStructure* getStructure(){
				return structure ;
			}

		private :
			void updateScore( int adjacentPos = -1 ){
				int variableCount = size() ;
				m = std::vector<varset>( variableCount , VARSET( variableCount ) ) ;
				todo = std::vector<varset>( variableCount , VARSET( variableCount ) ) ;
				structure = new datastructures::BNStructure( variableCount ) ;

				for(int j = variableCount - 1 ; j >= 0 ; j--){
					// Extract variable at position j
					int v_j = permutation[ j ] ;

					// (a1) Pick best parent set with no descendants of V_j
					float score = bestScoreCalculator[ v_j ]->getScore( VARSET_NOT( m[ v_j ] ) ) ;
					varset parents = bestScoreCalculator[ v_j ]->getParents() ;
					structure->setParents( v_j , parents , score ) ;

					// (a2) Update matrix representation and get ancestors of V_j
					ancestors = VARSET( variableCount ) ;
					for(int i = 0 ; i < variableCount  ; i++){
						if( VARSET_GET( parents , i ) || ( m[ i ] & parents ).any() )
							VARSET_SET( m[ i ] , v_j ) ;
						if( VARSET_GET( m[ i ] , v_j ) )
							VARSET_SET( ancestors , i ) ;
					}

					// (b) Start an empty TODO list to all ancestors of V_j
					for(int i = 0 ; i < variableCount ; i++)
						if( VARSET_GET( ancestors , i ) )
							todo[ i ] = VARSET( variableCount ) ;

					// (c) Start TODO lists of the parents of V_j with descendants of V_j
					for(int i = 0 ; i < variableCount ; i++)
						if( VARSET_GET( parents , i ) )
							todo[ i ] = m[ v_j ] ;

					// TODO: remove this
					std::cout << "--------------------------------------------------------------" << std::endl ;
					std::cout << "IT=" << variableCount - j << "; v_j = " << v_j << std::endl ;
					if( ( (*structure)[ v_j ]->getParents() & m[ v_j ] ).any() ){
						throw std::runtime_error("Chose descendant parents!") ;
					}
					std::cout << "     parents  : " ;
					for (int i = 0; i < variableCount; i++) {
						if( VARSET_GET( parents , i ) )
						std::cout << i << ' ';
					}
					std::cout << std::endl ;

					varset ca, na ;
					na = (*structure)[ v_j ]->getParents() ;
					ca = (*structure)[ v_j ]->getParents() ;
					do {
						ca = ( ca | na ) ;
						for(int i = 0; i < variableCount; i++){
							if( VARSET_GET( ca , i ) ){
								na = ( na | (*structure)[ i ]->getParents() ) ;
							}
						}
					} while( ca != na ) ;

					std::cout << "calc ancestors: " ;
					for (int i = 0; i < variableCount; i++) {
						if( VARSET_GET( ca , i ) )
						std::cout << i << ' ';
					}
					std::cout << std::endl ;
					if( ca != ancestors ){
						std::cout << "     ancestors: " ;
						for (int i = 0; i < variableCount; i++) {
							if( VARSET_GET( ancestors , i ) )
							std::cout << i << ' ';
						}
						std::cout << "<<<" << std::endl ;
					}

					// TODO: remove
					std::cout << "beg visits of: " << v_j << std::endl ;

					// (d) For each ancestor X of V_j
					for(int i = 0 ; i < variableCount ; i++){
						if( VARSET_GET( ancestors , i ) )
							if( (*structure)[ i ]->getInGrade() == 0 ){
								visit( i ) ;
							}
					}
					// TODO: remove
					std::cout << "end visits of: " << v_j << std::endl ;

					// check descendants for each variable
					for(int k = 0; k < variableCount; k++){
						varset cd, nd ;
						nd = (*structure)[ k ]->getChildren() ;
						cd = (*structure)[ k ]->getChildren() ;
						do {
							cd = ( cd | nd ) ;
							for(int i = 0; i < variableCount; i++){
								if( VARSET_GET( cd , i ) ){
									nd = ( nd | (*structure)[ i ]->getChildren() ) ;
								}
							}
						} while(cd != nd) ;

						varset auxd = m[ k ] ;
						if( cd != auxd ){
							std::cout << "var: " << k << std::endl ;
							std::cout << "calculated descendants: " ;
							for (int i = 0; i < variableCount; i++) {
								if( VARSET_GET( cd , i ) )
								std::cout << i << ' ';
							}
							std::cout << std::endl ;

							std::cout << "m[k]       descendants: " ;
							for (int i = 0; i < variableCount; i++) {
								if( VARSET_GET( auxd , i ) )
								std::cout << i << ' ';
							}
							std::cout << std::endl ;
							structure->print() ;
							throw std::runtime_error("wrong descendants update!") ;
						}
					}

					// TODO: remove this check for acyclicity
					if( structure->hasCycle() ){
						structure->print() ;
						throw std::runtime_error("structure has a cycle!") ;
					}
				}
				score = structure->getScore() ;
			}

			void visit( int x ){
				if( ancestors == empty ) return ;
				// TODO: remove
				std::cout << " enter: " << x << std::endl ;
				VARSET_CLEAR( ancestors , x ) ;
				int variableCount = size() ;
				std::vector<int> children = (*structure)[ x ]->getChildrenVector() ;
				for( int i = 0 ; i < children.size() ; i++){
					int ch = children[ i ] ;
					if( VARSET_GET( ancestors , ch ) ){
						// VARSET_CLEAR( ancestors , ch ) ;
						// TODO: remove
						std::cout << "    >>: " << ch << std::endl ;
						visit( ch ) ;
					}
				}
				// TODO: remove
				std::cout << " process: " << x << std::endl ;
				int y ;
				while( ( y = VARSET_FIND_FIRST_SET( todo[ x ] ) ) != -1 ){
					// if m(X, Y ) is true, then ignore Y and move on;
					if( !VARSET_GET( m[ x ] , y ) ){
						// otherwise set m(X, Y ) to true
						VARSET_SET( m[ x ] , y ) ;

						varset parents = (*structure)[ x ]->getParents() ;
						// add Y to the todo of parents of X.
						for(int i = 0 ; i < variableCount ; i++)
							if( VARSET_GET( parents , i ) )
								VARSET_SET( todo[ i ] , y ) ;
					}
					VARSET_CLEAR( todo[ x ] , y ) ;
				}
			}

			std::vector<varset> m ; // Descendants
			std::vector<varset> todo ; // To-Do lists
			varset empty ;
			varset ancestors ;
	} ;
}

#endif /* ACYCLIC_BEHAVIOR_SET_H */
