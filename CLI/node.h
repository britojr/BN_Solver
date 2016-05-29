/* 
 * File:   node.h
 * Author: nonwhite
 *
 * Created on 28 de enero de 2016, 09:56 AM
 */

#ifndef NODE_H
#define	NODE_H

#include <vector>

#include "typedefs.h"

namespace structureoptimizer {
	class Node {
		public:
			Node() ;
			Node( int variable , int size ){
				this->variableIndex = variable ;
				
				VARSET_NEW( parentsAux , size ) ;
				this->parents = parentsAux ;
				
				VARSET_NEW( childrenAux , size ) ;
				this->children = childrenAux ;
				
				for(int i = 0 ; i < size ; i++) weights.push_back( 0. ) ;
			}

			void addChild( int index , float weight = 0. ){
				if( !VARSET_GET( children , index ) ){
					VARSET_SET( this->children , index );
					childrenVector.push_back( index ) ;
				}
				weights[ index ] = weight ;
			}
			
			void removeChild( int index ){
				if( VARSET_GET( children , index ) ){
					VARSET_CLEAR( children , index ) ;
					for(int i = 0 ; i < childrenVector.size() ; i++){
						if( childrenVector[ i ] == index ){
							childrenVector.erase( childrenVector.begin() + i ) ;
							break ;
						}
					}
				}
				weights[ index ] = 0. ;
			}
			
			varset getChildren(){
				return children ;
			}
			
			std::vector<int> getChildrenVector(){
				return childrenVector ;
			}

			void setParents( varset parents ){
				this->parents = parents ;
			}
			
			varset getParents(){
				return parents ;
			}
			
			void removeParent( int index ){
				if( VARSET_GET( parents , index ) ){
					VARSET_CLEAR( parents , index ) ;
				}
			}
			
			void setScore( float score ){
				this->score = score ;
			}
			
			float getScore(){
				return score ;
			}
			
			float getWeight( int index ){
				return weights[ index ] ;
			}
			
			int getInGrade(){
				return cardinality( parents ) ;
			}
			
			int getOutGrade(){
				return cardinality( children ) ;
			}
		
		private :
			varset children ;
			varset parents ;
			int variableIndex ;
			float score ;
			std::vector<float> weights ;
			std::vector<int> childrenVector ;
	} ;
}

#endif	/* NODE_H */