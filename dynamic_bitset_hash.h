/* 
 * File:   dynamic_bitset_hash.h
 * Author: malone
 *
 * Created on October 18, 2012, 10:18 PM
 */

#ifndef DYNAMIC_BITSET_HASH_H
#define	DYNAMIC_BITSET_HASH_H

#include <vector>

#include <boost/functional/hash.hpp>
#include <boost/dynamic_bitset.hpp>

// make sure we can use dynamic_bitsets as values in the hash table
namespace boost {
    template <typename B, typename A>
    std::size_t hash_value(const boost::dynamic_bitset<B, A>& bs) {     
		return boost::hash_value( bs.m_bits ) ;
    }
}

//template <typename B, typename A>
struct hasher
{
  bool operator()(const boost::dynamic_bitset<>& bs) const {
		return boost::hash_value( bs.m_bits ) ;
    }
};

//template <typename B, typename A>
struct key_eq
{
  bool operator()(const boost::dynamic_bitset<>& bs1, const boost::dynamic_bitset<>& bs2) const {
        return (bs1 == bs2);
    }
};


#endif	/* DYNAMIC_BITSET_HASH_H */

