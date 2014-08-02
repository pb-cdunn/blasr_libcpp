#ifndef _BLASR_BWT_SEARCH_IMPL_HPP_
#define _BLASR_BWT_SEARCH_IMPL_HPP_

template<typename T_MappingBuffers>
int MapReadToGenome(BWT & bwt,
    FASTASequence & seq,
    std::vector<ChainedMatchPos> &matchPosList,
    AnchorParameters & params, int & numBasesAnchored, 
    T_MappingBuffers & mappingBuffers) {
    return MapReadToGenome(bwt, seq, matchPosList, params,
        numBasesAnchored, mappingBuffers.spv, mappingBuffers.epv);
}

#endif
