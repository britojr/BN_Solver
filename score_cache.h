/* 
 * File:   LongFloatScorer.h
 * Author: malone
 *
 * Created on August 7, 2012, 1:24 PM
 */

#ifndef LONGFLOATSCORER_H
#define	LONGFLOATSCORER_H

#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#include <vector>
#include <string>

#include <boost/unordered_map.hpp>

#include "typedefs.h"
#include "bayesian_network.h"

#ifdef __APPLE__
#include <machine/endian.h>
#include <libkern/OSByteOrder.h>

#define htobe16(x) OSSwapHostToBigInt16(x)
#define htole16(x) OSSwapHostToLittleInt16(x)
#define be16toh(x) OSSwapBigToHostInt16(x)
#define le16toh(x) OSSwapLittleToHostInt16(x)

#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole32(x) OSSwapHostToLittleInt32(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define le32toh(x) OSSwapLittleToHostInt32(x)

#define htobe64(x) OSSwapHostToBigInt64(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define be64toh(x) OSSwapBigToHostInt64(x)
#define le64toh(x) OSSwapLittleToHostInt64(x)

#define __BIG_ENDIAN    BIG_ENDIAN
#define __LITTLE_ENDIAN LITTLE_ENDIAN
#define __BYTE_ORDER    BYTE_ORDER
#else
#endif

namespace datastructures {
    class BayesianNetwork;
}

namespace scoring {

    class ScoreCache {
    public:

        ScoreCache() {
            // should never be called
        }

        ScoreCache(std::string filename);
        ~ScoreCache();
        
        void setVariableCount(int variableCount);

        float getScore(int variable, varset parents) const {
            return (*cache[variable])[parents];
        }

        void putScore(int variable, varset parents, float score) {
            (*cache[variable])[parents] = score;
        }

        void removeScore(int variable, varset parents) {
            (*cache[variable]).erase(parents);
        }

        int getVariableCount() const {
            return variableCount;
        }

        FloatMap *getCache(int variable) const {
            return cache[variable];
        }
        
        std::string getMetaInformation(std::string key) {
            return metaInformation[key];
        }
        
        void updateMetaInformation(std::string key, std::string value) {
            metaInformation[key] = value;
        }
        
        datastructures::BayesianNetwork *getNetwork() {
            return network;
        }

        void deleteCache(int variable) {
            if (cache[variable] != NULL) {
                cache[variable]->clear();
            }

            delete cache[variable];
        }

        void read(std::string filename);
        void readUrlBinary(std::string filename);
        void write(std::string filename);
        int writeExclude(std::string filename, varset exclude);

    private:
        int variableCount;
        datastructures::BayesianNetwork *network;
        std::vector<int> variableCardinalities;
        std::vector < FloatMap * > cache;
        boost::unordered_map<std::string, std::string> metaInformation;
    };

}
#endif	/* LONGFLOATSCORER_H */

