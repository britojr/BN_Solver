/* 
 * File:   DFSInitializer.cpp
 * Author: nonwhite
 * 
 * Created on 26 de enero de 2016, 05:00 PM
 */

#include <stack>

#include "node.h"
#include "dfs_initializer.h"
#include "utils.h"

initializers::DFSInitializer::DFSInitializer(){
    // Do nothing
}

initializers::DFSInitializer::DFSInitializer( std::vector<bestscorecalculators::BestScoreCalculator*> bestScoreCalculators ){
    this->variableCount = bestScoreCalculators.size() ;
    this->bestScoreCalculators = bestScoreCalculators ;
    this->gen = boost::mt19937( time( NULL ) ) ;
}

initializers::DFSInitializer::~DFSInitializer(){
    // Do nothing
}

greedysearch::PermutationSet initializers::DFSInitializer::generate(){
    this->unvisitedVariables = varset( variableCount ) ;
    VARSET_SET_ALL( this->unvisitedVariables , variableCount ) ;
    // Traverse graph and obtain an order
    std::vector<int> order ;
    while( !unvisitedVariables.none() ){
        std::vector<int> unvisited ;
        for(int i = 0 ; i < variableCount ; i++)
            if( VARSET_GET( unvisitedVariables , i ) )
                unvisited.push_back( i ) ;
        int rIndex = random_generator( unvisited.size() , gen ) ;
        std::vector<int> visited = traverse( unvisited[ rIndex ] ) ;
        for(int i = 0 ; i < visited.size() ; i++)
            order.push_back( visited[ i ] ) ;
    }
    
    // Build the permutation set
    greedysearch::PermutationSet set( variableCount ) ;
    set.setPermutation( order ) ;
    float score = 0.0 ;
    for(int i = 0 ; i < variableCount ; i++){
        varset options = set.getVarset( i ) ;
        score += bestScoreCalculators[ i ]->getScore( options ) ;
    }
    set.setScore( score ) ;
    
    return set ;
}

std::vector<int> initializers::DFSInitializer::traverse( int index ){
    std::vector<int> visited ;
    visited.push_back( index ) ;
    VARSET_CLEAR( unvisitedVariables , index ) ;
    std::vector<int> children = shuffle( nodes[ index ]->getChildrenVector() , gen ) ;
    for(int i = 0 ; i < children.size() ; i++){
        if( !VARSET_GET( unvisitedVariables , children[ i ] ) ) continue ;
        std::vector<int> next = traverse( children[ i ] ) ;
        for(int j = 0 ; j < next.size() ; j++)
            visited.push_back( next[ j ] ) ;
    }
    return visited ;
}

void initializers::DFSInitializer::initialize(){
    // Initialize adjacent lists
    nodes.clear() ;
    for(int i = 0 ; i < variableCount ; i++){
        greedysearch::Node* var = new greedysearch::Node( i , variableCount ) ;
        nodes.push_back( var ) ;
    }
    
    printf("Getting best possible parents for every variable\n" ) ;
    // Get best possible parents for every variable
    VARSET_NEW( all , variableCount ) ;
    VARSET_SET_ALL( all , variableCount ) ;
    float totalScore = 0. , indegree = 0. ;
    for(int i = 0 ; i < variableCount ; i++){
//        printf("Getting best parents for variable %d\n" , i ) ;
        VARSET_CLEAR( all , i ) ;
        
        float score = bestScoreCalculators[ i ]->getScore( all ) ; 
        nodes[ i ]->setScore( score ) ;
        varset parents = bestScoreCalculators[ i ]->getParents() ; 
        nodes[ i ]->setParents( parents ) ;
        indegree += cardinality( parents ) ;
        for(int j = 0 ; j < variableCount ; j++){
            if( !VARSET_GET( parents , j ) ) continue ;
            nodes[ j ]->addChild( i ) ;
        }
        totalScore += score ;
        
        VARSET_SET( all , i ) ;
    }
    printf("sc( G completo ) = %.3f\n" , -totalScore ) ;
    printf("m/n = %.2f\n" , indegree / variableCount ) ;
    
//    srand( time( NULL ) ) ;
}