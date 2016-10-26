/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   greedy_behavior_set.h
 * Author: nonwhite
 *
 * Created on October 25, 2016, 10:43 AM
 */

#ifndef GREEDYBEHAVIORSET_H
#define GREEDYBEHAVIORSET_H

#include "permutation_set.h"
#include "best_score_calculator.h"
#include "utils.h"

namespace structureoptimizer {
	class GreedyBehaviorSet : public PermutationSet {
		public :
			GreedyBehaviorSet( int size ,
						std::vector<bestscorecalculators::BestScoreCalculator*> &bestScoreCalculator ){
				boost::mt19937 gen( time( NULL ) ) ;
				for(int i = 0 ; i < size ; i++)
					permutation.push_back( i ) ;
				permutation = shuffle( permutation , gen ) ;
				this->bestScoreCalculator = bestScoreCalculator ;
				updateScore() ;
			}

			void print( bool printPermutation ){
				if( printPermutation ){
					for(int i = 0 ; i < permutation.size() ; i++){
						if( i ) printf(" " ) ;
						printf("%d" , permutation[ i ] ) ;
					}
					printf("\n" ) ;
				}
				printf("Score = %.6f\n" , score ) ;
			}

		private :
			void updateScore( int adjacentPos = -1 ){
				if( adjacentPos < 0 ){ // Not adjacent move
					float newScore = 0.0 ;
					for(int i = 0 ; i < size() ; i++){
						varset options = getVarset( i ) ;
						int variable = permutation[ i ] ;
						newScore += bestScoreCalculator[ variable ]->getScore( options ) ;
					}
					setScore( newScore ) ;
				}else{ // Adjacent move in "adjacentPos"
					VARSET_NEW( vset , permutation.size() ) ;
					VARSET_CLEAR_ALL( vset ) ;
					for( int i = 0 ; i < adjacentPos ; i++)
						VARSET_SET( vset , permutation[ i ] ) ;
					float newScore = getScore() ;

					// TODO: Add an if in case P[ adj + 1 ] was not a parent of P[ adj ] before swap
					// Remove previous scores
					newScore -= bestScoreCalculator[ permutation[ adjacentPos + 1 ] ]->getScore( vset ) ;
					VARSET_SET( vset , permutation[ adjacentPos + 1 ] ) ;
					newScore -= bestScoreCalculator[ permutation[ adjacentPos ] ]->getScore( vset ) ;

					// Add current scores
					VARSET_CLEAR( vset , permutation[ adjacentPos + 1 ] ) ;
					newScore += bestScoreCalculator[ permutation[ adjacentPos ] ]->getScore( vset ) ;
					VARSET_SET( vset , permutation[ adjacentPos ] ) ;
					newScore += bestScoreCalculator[ permutation[ adjacentPos + 1 ] ]->getScore( vset ) ;

					setScore( newScore ) ;
				}
			}
	} ;
}

#endif /* GREEDYBEHAVIORSET_H */