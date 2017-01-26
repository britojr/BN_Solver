#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE bn_structure_module
#include <boost/test/unit_test.hpp>
#include <boost/format.hpp>

#include "bn_structure.h"

struct Initilize {
	Initilize(){
		size = 7 ;
		parents = std::vector<varset>( size , VARSET( size ) ) ;
		VARSET_SET( parents[0] , 6 ) ;
		VARSET_SET( parents[1] , 0 ) ;
		VARSET_SET( parents[1] , 3 ) ;
		VARSET_SET( parents[3] , 2 ) ;
		VARSET_SET( parents[3] , 4 ) ;
		VARSET_SET( parents[5] , 0 ) ;
		structure = new datastructures::BNStructure( size ) ;
		for(int i = 0 ; i < size ; i++){
			structure->setParents( i , parents[i] , 0. ) ;
		}

		//cyclic structure
		int s = 6 ;
		std::vector<varset> p = std::vector<varset>( s , VARSET( s ) ) ;
		VARSET_SET( p[1] , 0 ) ;
		VARSET_SET( p[0] , 2 ) ;
		VARSET_SET( p[0] , 4 ) ;
		VARSET_SET( p[2] , 1 ) ;
		VARSET_SET( p[3] , 1 ) ;
		VARSET_SET( p[3] , 2 ) ;
		VARSET_SET( p[4] , 2 ) ;
		VARSET_SET( p[4] , 3 ) ;
		VARSET_SET( p[4] , 5 ) ;
		VARSET_SET( p[5] , 1 ) ;
		VARSET_SET( p[5] , 3 ) ;
		cyclic = new datastructures::BNStructure( s ) ;
		for(int i = 0 ; i < s ; i++){
			cyclic->setParents( i , p[i] , 0. ) ;
		}
	}
	~Initilize(){

	}
	int size ;
	std::vector<varset> parents ;
	datastructures::BNStructure* structure ;
	datastructures::BNStructure* cyclic ;
};

BOOST_FIXTURE_TEST_SUITE( bn_structure_suite, Initilize )

// This one is just to test the compilaiton and execution of tests
BOOST_AUTO_TEST_CASE( structure_size ){
	BOOST_CHECK_EQUAL( structure->size() , size ) ;
}

BOOST_AUTO_TEST_CASE( topological_order ){
	bool correct = true ;
	std::vector<int> got = structure->getTopologic() ;
	for(int i = 0 ; i < size ; i++){
		for(int j = i+1 ; j < size ; j++){
			if( VARSET_GET( parents[got[i]] , got[j] ) ){
				correct = false ;
				break ;
			}
		}
	}
	std::stringstream ss ;
	for(int i = 0 ; i < size ; i++){
		ss << got[i] ;
		ss << ' ' ;
	}
	ss << "is not a topologic sort" ;
	BOOST_CHECK_MESSAGE( correct , ss.str() ) ;
}

BOOST_AUTO_TEST_CASE( no_cycle ){
	BOOST_CHECK_MESSAGE( structure->hasCycle() == false , "wrongly found a cycle" ) ;
}
BOOST_AUTO_TEST_CASE( cycle ){
	BOOST_CHECK_MESSAGE( cyclic->hasCycle() == true , "didn't find the cycle" ) ;
}

BOOST_AUTO_TEST_SUITE_END()
