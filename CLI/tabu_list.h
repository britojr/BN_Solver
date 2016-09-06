/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tabu_list.h
 * Author: nonwhite
 *
 * Created on September 5, 2016, 4:07 PM
 */

#ifndef TABU_LIST_H
#define TABU_LIST_H

#include <queue>

#include "typedefs.h"

namespace datastructures {
	class TabuList {
		public:
			TabuList(){
				// Do nothing
			}
			
			TabuList( int maxSize , int variableCount ){
				this->maxSize = maxSize ;
				this->size = 0 ;
				this->variableCount = variableCount ;
				
				for(int i = 0 ; i < variableCount ; i++)
					swaps.push_back( VARSET( variableCount) ) ;
			}

			void add( int variable1 , int variable2 ){
				if( size == maxSize ) removeOldestMove() ;
				if( variable1 > variable2 ){
					int aux = variable1 ;
					variable1 = variable2 ;
					variable2 = aux ;
				}
				tlist.push( PAIR( variable1 , variable2 ) ) ;
				VARSET_SET( swaps[ variable1 ] , variable2 ) ;
				size++ ;
			}

			bool has( int variable1 , int variable2 ){
				if( variable1 > variable2 ){
					int aux = variable1 ;
					variable1 = variable2 ;
					variable2 = aux ;
				}
				return VARSET_GET( swaps[ variable1 ] , variable2 ) ;
			}

		private :
			void removeOldestMove(){
				if( !tlist.empty() ){
					pii oldest = tlist.front() ;
					tlist.pop() ;
					int variable1 = oldest.first , variable2 = oldest.second ;
					VARSET_CLEAR( swaps[ variable1 ] , variable2 ) ;
					size-- ;
					printf( "Removed: %d, %d\n" , variable1 , variable2 ) ;
				}
			}
			
			int variableCount ;
			int maxSize ;
			int size ;
			std::queue<pii > tlist ;
			std::vector<varset> swaps ;
	} ;
}

#endif /* TABU_LIST_H */

