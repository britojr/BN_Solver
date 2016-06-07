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
										std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculator ){
	this->initializer = initializer ;
	this->bestScoreCalculators = bestScoreCalculator ;
	this->variableCount = bestScoreCalculator.size() ;
}

structureoptimizer::AcyclicSelection::~AcyclicSelection(){
	// Do nothing
}

datastructures::BNStructure structureoptimizer::AcyclicSelection::search( int numSolutions ){
	datastructures::BNStructure best ;
	for(int k = 0 ; k < numSolutions ; k++){
		printf( " ======== Acyclic Selection ======== \n" ) ;
		structureoptimizer::PermutationSet initial = initializer->generate() ;
		printf(" === Initial solution ===\n" ) ;
		initial.print() ;
		std::vector<varset> m( variableCount , VARSET( variableCount ) ) ; // Descendants
		std::vector<std::vector<int> > todo( variableCount ) ; // To-Do lists
		datastructures::BNStructure current( variableCount ) ; // Partial BN structure
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
			current.setParents( v_j , parents , score ) ;
			
			// (b1) Build a TODO list with descendants of V_j
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
				int anc = ancestors[ i ] ; // TODO <---------------------------------------------------
			}
		}
		if( best.size() == 0 || current.isBetter( best ) ){
			best = current ;
			printf( "Score = %.6f\n" , best.getScore() ) ;
		}else
			printf( "No improvement in score\n" ) ;
	}
	return best ;
}