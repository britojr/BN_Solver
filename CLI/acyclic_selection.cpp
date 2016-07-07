/* 
 * File:   acyclic_selection.cpp
 * Author: nonwhite
 * 
 * Created on 28 de mayo de 2016, 13:07
 */

#include "acyclic_selection.h"
#include "utils.h"

structureoptimizer::AcyclicSelection::AcyclicSelection(){
	// Do nothing
}

structureoptimizer::AcyclicSelection::AcyclicSelection( initializers::Initializer* initializer ,
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ,
										std::string parametersFile ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->variableCount = bestScoreCalculator.size() ;
	setParameters( parametersFile ) ;
}

structureoptimizer::AcyclicSelection::~AcyclicSelection(){
	// Do nothing
}

void structureoptimizer::AcyclicSelection::setDefaultParameters(){
	// Do nothing
}

void structureoptimizer::AcyclicSelection::setFileParameters( std::map<std::string,std::string> params ){
	// Do nothing
}

void structureoptimizer::AcyclicSelection::printParameters(){
	// Do nothing
}

datastructures::BNStructure structureoptimizer::AcyclicSelection::search( int numSolutions ){
	datastructures::BNStructure best ;
	for(int k = 0 ; k < numSolutions ; k++){
		printf( " ======== Acyclic Selection ======== \n" ) ;
		structureoptimizer::PermutationSet initial = initializer->generate() ;
		printf(" === Initial solution ===\n" ) ;
		initial.print() ;
		
		m = std::vector<varset>( variableCount , VARSET( variableCount ) ) ;
		todo = std::vector<std::vector<int> >( variableCount ) ;
		partial_bn = datastructures::BNStructure( variableCount ) ;
		
		for(int j = variableCount - 1 ; j >= 0 ; j--){
			// Extract variable at position j in initial
			int v_j = initial[ j ] ;
			
			// (a) Pick best parent set with no descendants of V_j
			float score = bestScoreCalculators[ v_j ]->getScore( VARSET_NOT( m[ v_j ] ) ) ;
			varset parents = bestScoreCalculators[ v_j ]->getParents() ;
			std::vector<int> ancestors ;
			for(int i = 0 ; i < variableCount ; i++)
				if( VARSET_GET( parents , i ) ){
					VARSET_SET( m[ i ] , v_j ) ;
					ancestors.push_back( i ) ;
				}
			partial_bn.setParents( v_j , parents , score ) ;
			
			// (b1) Build a TODO list with descendants of V_j
			todo[ v_j ].clear() ;
			for(int i = 0 ; i < variableCount ; i++)
				if( VARSET_GET( m[ v_j ] , i ) )
					todo[ v_j ].push_back( i ) ;
			
			// (b2) Start an empty TODO list to all ancestors of V_j
			for(int i = 0 ; i < ancestors.size() ; i++)
				todo[ ancestors[ i ] ] = std::vector<int>() ;
			
			// (c) Start TODO lists of the parents of V_j with descendants of V_j
			for(int i = 0 ; i < variableCount ; i++)
				if( VARSET_GET( parents , i ) )
					todo[ i ] = todo[ v_j ] ;
			
			// (d) For each ancestor X of V_j
			for(int i = 0 ; i < ancestors.size() ; i++){
				int x = ancestors[ i ] ;
				if( partial_bn[ x ]->getInGrade() > 0 ) continue ;
				visit( x ) ;
			}
		}
		printf( "Score = %.6f\n" , partial_bn.getScore() ) ;
		if( best.size() == 0 || partial_bn.isBetter( best ) ){
			best = partial_bn ;
		}
	}
	printf(" === BEST === \n" ) ;
	printf( "Score = %.6f\n" , best.getScore() ) ;
	return best ;
}

void structureoptimizer::AcyclicSelection::visit( int x ){
	for(int i = 0 ; i < todo[ x ].size() ; i++){
		int y = todo[ x ][ i ] ;
		// if m(X, Y ) is true, then ignore Y and move on;
		if( VARSET_GET( m[ x ] , y ) ) continue ;
		// otherwise set m(X, Y ) to true
		VARSET_SET( m[ x ] , y ) ;
		varset parents = partial_bn[ x ]->getParents() ;
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