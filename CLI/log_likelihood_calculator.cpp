#include "log_likelihood_calculator.h"

scoring::LogLikelihoodCalculator::LogLikelihoodCalculator() {
	// nothing
}

scoring::LogLikelihoodCalculator::LogLikelihoodCalculator( scoring::ADTree *adTree ,
														datastructures::BayesianNetwork &network ,
														std::vector<float> &ilogi ){
	initialize( adTree , network , ilogi ) ;
}

scoring::LogLikelihoodCalculator::~LogLikelihoodCalculator(){
	// no pointers that aren't deleted elsewhere	
}

void scoring::LogLikelihoodCalculator::initialize( ADTree *adTree ,
												datastructures::BayesianNetwork& network ,
												std::vector<float>& ilogi ){
	this->adTree = adTree ;
	this->network = network ;
	this->ilogi = ilogi ;
	this->recordFileSize = ilogi.size() - 2 ;
}

float scoring::LogLikelihoodCalculator::calculate( int variable , varset& parents ){
	boost::unordered_map<uint64_t, int> paCounts ;
	return calculate( variable , parents , paCounts ) ;
}

float scoring::LogLikelihoodCalculator::calculate( int variable , varset& parents ,
												boost::unordered_map<uint64_t,int> &paCounts ){
	VARSET_SET( parents , variable ) ;
	float score = 0 ;

	ContingencyTableNode *ct = adTree->makeContab( parents ) ;

	calculate( ct , 1 , 0 , paCounts , variable , parents , -1 , score ) ;

	delete ct ;

	for( boost::unordered_map<uint64_t,int>::iterator pc = paCounts.begin() ; pc != paCounts.end() ; pc++){
		score -= ilogi[ pc->second ] ;
	}

	VARSET_CLEAR( parents , variable ) ;

	return score ;
}

void scoring::LogLikelihoodCalculator::calculate( ContingencyTableNode *ct ,
												uint64_t base , uint64_t index ,
												boost::unordered_map<uint64_t,int> &paCounts ,
												int variable , varset variables ,
												int previousVariable , float &score ){
	// if this is a leaf
	if( ct->isLeaf() ){
		// update the instantiation count of this set of parents
		int count = paCounts[ index ] ;
		count += ct->getValue() ;
		paCounts[ index ] = count ;

		// update the score for this variable, parent instantiation
		score += ilogi[ ct->getValue() ] ;
		return ;
	}

	// which actual variable are we looking at
	int thisVariable = previousVariable + 1 ;
	for( ; thisVariable < network.size() ; thisVariable++){
		if( VARSET_GET( variables , thisVariable ) )
			break ;
	}

	// update the base and index if this is part of the parent set
	uint64_t nextBase = base ;
	if( thisVariable != variable ){
		nextBase *= network.getCardinality( thisVariable ) ;
	}

	// recurse
	for( int k = 0 ; k < network.getCardinality( thisVariable ) ; k++){
		ContingencyTableNode *child = ct->getChild( k ) ;
		if( child != NULL ){
			long newIndex = index ;
			if( thisVariable != variable ){
				newIndex += base * k ;
			}
			calculate( child , nextBase , newIndex , paCounts , variable , variables , thisVariable , score ) ;
		}
	}
}

float scoring::LogLikelihoodCalculator::interactionInformation( varset &p1 , varset &p2 , int variable ){
	// I( X , p1 , p2 ) = I( X , p1 | p2 ) - I( X , p1 )
	// I( X , p1 , p2 ) = [ H( X | p2 ) - H( X | p1+p2 ) ] - [ H( X | empty ) - H( X | p1 ) ]
	VARSET_NEW( set , network.size() ) ;
	VARSET_OR( set , p1 ) ;
	VARSET_OR( set , p2 ) ;
	float cond = calculate( variable , p2 ) - calculate( variable , set ) ;
	VARSET_CLEAR_ALL( set ) ;
	float unco = calculate( variable , set ) - calculate( variable , p1 ) ;
	return -( cond - unco ) / recordFileSize ;
}