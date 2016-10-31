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
				updateScore() ;
			}
			
			void print( bool printPermutation ){
				// TODO: Check if changes needed
				if( printPermutation ){
					for(int i = 0 ; i < permutation.size() ; i++){
						if( i ) printf(" " ) ;
						printf("%d" , permutation[ i ] ) ;
					}
					printf("\n" ) ;
				}
				printf("Score = %.6f\n" , score ) ;
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
				// TODO: implement this efficiently
				
				for(int j = size() - 1 ; j >= 0 ; j--){
					// Extract variable at position j in initial
					int v_j = permutation[ j ] ;

					// Pick best parent set with no descendants of V_j
					varset descendants = getDescendants( v_j ) ;
					float score = bestScoreCalculator[ v_j ]->getScore( VARSET_NOT( descendants ) ) ;
					varset parents = bestScoreCalculator[ v_j ]->getParents() ;
					structure->setParents( v_j , parents , score ) ;
				}
				score = structure->getScore() ;
			}

			void updateScoreEfficient( int adjacentPos = -1 ){
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
					VARSET_NEW( ancestors , variableCount ) ;
					for(int i = 0 ; i < variableCount  ; i++){
						if( VARSET_GET( parents , i ) )
							VARSET_SET( m[ i ] , v_j ) ;
						if( VARSET_GET( m[ i ] , v_j ) )
							VARSET_SET( ancestors , i ) ;
					}

					// (b1) Build a TODO list with descendants of V_j
					todo[ v_j ] = m[ v_j ] ;

					// (b2) Start an empty TODO list to all ancestors of V_j
					VARSET_OR( ancestors , parents ) ;
					for(int i = 0 ; i < variableCount ; i++)
						if( VARSET_GET( ancestors , i ) )
							todo[ i ] = VARSET( variableCount ) ;

					// (c) Start TODO lists of the parents of V_j with descendants of V_j
					for(int i = 0 ; i < variableCount ; i++)
						if( VARSET_GET( parents , i ) )
							todo[ i ] = m[ v_j ] ;

					// (d) For each ancestor X of V_j
					// TODO: implement this
				}
			}
			
			varset getDescendants( int index ){
				VARSET_NEW( visited , size() ) ;
				VARSET_SET( visited , index ) ;
				std::vector<int> children = (*structure)[ index ]->getChildrenVector() ;
				for(int i = 0 ; i < children.size() ; i++){
					varset chVisited = getDescendants( children[ i ] ) ;
					VARSET_OR( visited , chVisited ) ;
				}
				return visited ;
			}

			void visit( int x ){
				int variableCount = size() ;
				for(int i = 0 ; i < todo[ x ].size() ; i++){
					int y = todo[ x ][ i ] ;
					// if m(X, Y ) is true, then ignore Y and move on;
					if( VARSET_GET( m[ x ] , y ) ) continue ;
					// otherwise set m(X, Y ) to true
					VARSET_SET( m[ x ] , y ) ;
					varset parents = (*structure)[ x ]->getParents() ;
					// add Y to the todo of parents of X.
					for(int j = 0 ; j < variableCount ; j++)
						if( VARSET_GET( parents , j ) ){
							bool in_todo = false ;
							for(int k = 0 ; k < todo[ j ].size() ; k++)
								if( todo[ j ][ k ] == y ){
									in_todo = true ;
									break ;
								}
							if( !in_todo ) todo[ j ].push_back( y ) ;
						}
				}
			}

			std::vector<varset> m ; // Descendants
			std::vector<varset> todo ; // To-Do lists
	} ;
}

#endif /* ACYCLIC_BEHAVIOR_SET_H */