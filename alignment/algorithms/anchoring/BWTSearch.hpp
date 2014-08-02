#ifndef _BLASR_BWT_SEARCH_HPP_
#define _BLASR_BWT_SEARCH_HPP_

#include <vector>
#include "FASTASequence.hpp"
#include "bwt/BWT.hpp"
#include "datastructures/anchoring/MatchPos.hpp"
#include "datastructures/anchoring/AnchorParameters.hpp"

int MapReadToGenome(BWT & bwt,
	FASTASequence & seq,
    DNALength subreadStart, DNALength subreadEnd,
    std::vector<ChainedMatchPos> &matchPosList,
	AnchorParameters & params, int &numBasesAnchored, 
    std::vector<DNALength> & spv, 
    std::vector<DNALength> & epv);


int MapReadToGenome(BWT & bwt,
	FASTASequence & seq,
    DNALength start, DNALength end,
	std::vector<ChainedMatchPos> & matchPosList,
	AnchorParameters  & params, int &numBasesAnchored);


template<typename T_MappingBuffers>
int MapReadToGenome(BWT & bwt,
    FASTASequence & seq,
    std::vector<ChainedMatchPos> &matchPosList,
    AnchorParameters & params, int & numBasesAnchored, 
    T_MappingBuffers & mappingBuffers);

#include "algorithms/anchoring/BWTSearchImpl.hpp"

#endif
