/* 
 * File:   utils.h
 * Author: nonwhite
 *
 * Created on 30 de enero de 2016, 01:40 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#include <string>
#include <sys/stat.h>
inline bool file_exists( std::string filePath ){
	struct stat buffer ;
	return (stat (filePath.c_str(), &buffer) == 0 ) ; 
}

inline int compare( float a , float b = 0.0 ){
	float EPS = 1e-7 ;
	return ( a + EPS < b ? -1 : a - EPS > b ? 1 : 0 ) ;
}

inline bool isZero( float a ){
	return compare( a ) == 0 ;
}

inline int mod( int x , int m ){
	return ( ( x % m ) + m ) % m ;
}

#include <vector>

#include <boost/random.hpp>
#include <boost/random/discrete_distribution.hpp>

inline int random_generator( std::vector<float> weights , boost::mt19937 &gen ){
	boost::random::discrete_distribution<> dist( weights ) ;
	return dist( gen ) ;
}

#include <boost/random/uniform_int_distribution.hpp>
inline int random_generator( int n , boost::mt19937 &gen ){
	boost::random::uniform_int_distribution<> dist( 0 , n - 1 ) ;
	return dist( gen ) ;
}

template<typename T>
std::vector<T> shuffle( std::vector<T> v , boost::mt19937 &gen ){
	int n = v.size() ;
	for(int i = 0 ; i < n - 2 ; i++){
		int idx = random_generator( i + 1 , gen ) ;
		T aux = v[ idx ] ;
		v[ idx ] = v[ i ] ;
		v[ i ] = aux ;
	}
	return v ;
}

#endif	/* UTILS_H */
