/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   beam_list.h
 * Author: nonwhite
 *
 * Created on October 21, 2016, 10:59 AM
 */

#ifndef BEAM_LIST_H
#define BEAM_LIST_H

#include "permutation_set.h"

namespace datastructures {
	template <typename _ItemType = structureoptimizer::PermutationSet> class BeamList {
		public:
			BeamList(){
				// Do nothing
			}

			BeamList( int maxSize ){
				this->maxSize = maxSize ;
				clear() ;
			}

			int size(){
				return q.size() ;
			}

			void add( _ItemType node ){
				if( !has( node ) ){
					q.insert( node ) ;
					if( size() > maxSize ) pop() ;
				}
			}

			void add( BeamList<_ItemType> blist ){
				for( typename std::set<_ItemType>::iterator it = blist.q.begin() ; it != blist.q.end() ; it++){
					add( *it ) ;
				}
			}

			bool has( _ItemType node ){
				return q.count( node ) ;
			}

			void clear(){
				q.clear() ;
			}

			bool empty(){
				return q.empty() ;
			}

			_ItemType pop(){
				_ItemType node = *q.begin() ;
				q.erase( *q.begin() ) ;
				return node ;
			}

			_ItemType top(){
				return *q.begin() ;
			}

		private :
			int maxSize ;
			std::set<_ItemType> q ;
	} ;
}

#endif /* BEAM_LIST_H */