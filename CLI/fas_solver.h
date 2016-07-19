/* 
 * File:   fas_solver.h
 * Author: nonwhite
 *
 * Created on 19 de julio de 2016, 17:07
 */

#ifndef FAS_SOLVER_H
#define	FAS_SOLVER_H

#include "bn_structure.h"

namespace initializers {
	class MinCostFASSolver {
		public :
			MinCostFASSolver(){} ;
			~MinCostFASSolver(){} ;
			
			datastructures::BNStructure removeFAS( datastructures::BNStructure digraph ){
				variableCount = digraph.size() ;
				H = digraph ;
				while( hasCycle() ){
					std::sort( cycle.begin() , cycle.end() ) ;
					float minWeight = cycle[ 0 ].first ;
					for(int i = 0 ; i < cycle.size() ; i++){
						int x = cycle[ i ].second.first ;
						int y = cycle[ i ].second.second ;
						float weight = H[ x ]->getWeight( y ) ;
						float diff = weight - minWeight ;
						if( isZero( diff ) ){
							H[ x ]->removeChild( y ) ;
							H[ y ]->removeParent( x ) ;
						}else{
							H[ x ]->addChild( y , weight - minWeight ) ;
						}
					}
				}
				return H ;
			}
			
		private :
			void initialize(){
				visited = VARSET( variableCount ) ;
				VARSET_CLEAR_ALL( visited ) ;

				onstack = VARSET( variableCount ) ;
				VARSET_CLEAR_ALL( onstack ) ;

				edgeTo = std::vector<int>( variableCount , -1 ) ;
				cycle.clear() ;
				path.clear() ;
			}
			
			bool hasCycle(){
				initialize() ;
				for(int i = 0 ; i < variableCount ; i++){
					if( VARSET_GET( visited , i ) ) continue ;
					if( path.size() > 0 ) break ;
					dfs( i ) ;
				}
				for(int i = path.size() - 1 ; i >= 1 ; i--){
					int x = path[ i ] , y = path[ i - 1 ] ;
					edge e ;
					e.first = H[ x ]->getWeight( y ) ;
					e.second.first = x ;
					e.second.second = y ;
					cycle.push_back( e ) ;
				}
				return cycle.size() > 0 ;
			}
			
			void dfs( int x ){
				VARSET_SET( visited , x ) ;
				VARSET_SET( onstack , x ) ;
				std::vector<int> children = H[ x ]->getChildrenVector() ;
				for(int i = 0 ; i < children.size() ; i++){
					if( path.size() > 0 ) break ;
					int u = children[ i ] ;
					if( !VARSET_GET( visited , u ) ){
						edgeTo[ u ] = x ;
						dfs( u ) ;
					}else if( VARSET_GET( onstack , u ) ){
						for(int y = x ; y != u ; y = edgeTo[ y ] ){
							path.push_back( y ) ;
							if( y < 0 ) break ;
						}
						path.push_back( u ) ;
						path.push_back( x ) ;
					}
				}
				VARSET_CLEAR( onstack , x ) ;
			}
			
			varset visited ;
			varset onstack ;
			std::vector<int> path ;
			std::vector<edge> cycle ;
			std::vector<int> edgeTo ;
			datastructures::BNStructure H ;
			int variableCount ;
	} ;
}

#endif	/* FAS_SOLVER_H */

