#ifndef _BLASR_GLOBAL_CHAIN_HPP_
#define _BLASR_GLOBAL_CHAIN_HPP_

#include <vector>
#include "Types.h"
#include "DNASequence.hpp"
#include "algorithms/anchoring/PrioritySearchTree.hpp"

template<typename T_Fragment, typename T_Endpoint>
void FragmentSetToEndpoints(T_Fragment* fragments, int nFragments, 
     std::vector<T_Endpoint> &endpoints);

template<typename T_Fragment>
UInt RestrictedGlobalChain(T_Fragment *fragments, 
    DNALength nFragments, float maxIndelRate,
    std::vector<VectorIndex>& optFragmentChainIndices,
    std::vector<UInt>& scores, std::vector<UInt>& prevOpt);

template<typename T_Fragment, typename T_Endpoint>
int GlobalChain( T_Fragment *fragments, 
	DNALength nFragments, 
    std::vector<VectorIndex> &optFragmentChainIndices,
	std::vector<T_Endpoint> *bufEndpointsPtr = NULL);

template<typename T_Fragment, typename T_Endpoint>
int GlobalChain(std::vector<T_Fragment> &fragments, 
    std::vector<VectorIndex> &optFragmentChainIndices);

template<typename T_Fragment, typename T_Endpoint>
int GlobalChain(std::vector<T_Fragment> &fragments, 
    DNALength start, DNALength end, 
    std::vector<VectorIndex> &optFragmentChainIndices,
    std::vector<T_Endpoint> *bufEndpointsPtr = NULL);

#include "algorithms/anchoring/GlobalChainImpl.hpp"

#endif
