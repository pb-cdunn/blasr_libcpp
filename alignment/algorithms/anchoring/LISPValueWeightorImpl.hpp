#ifndef _BLASR_LISPVALUE_WEIGHTOR_IMPL_HPP_
#define _BLASR_LISPVALUE_WEIGHTOR_IMPL_HPP_

#include "algorithms/anchoring/LISPValue.hpp"
#include "tuples/TupleMetrics.hpp"

template<typename T_RefSequence, typename T_MatchList>
LISSumOfLogPWeightor<T_RefSequence, T_MatchList>::LISSumOfLogPWeightor(
    T_RefSequence &targetGenome) {
    genomeLength = targetGenome.length;
}

template<typename T_RefSequence, typename T_MatchList>
float LISSumOfLogPWeightor<T_RefSequence, T_MatchList>::ComputePValue(
    T_MatchList &matchList, int &noOvpLisNBases, int &noOvpLisSize) {
    float pMatch = 0;
    int i;
    T_MatchList noOvpLis;
    StoreNonOverlappingIndices(matchList, noOvpLis);
    noOvpLisSize = noOvpLis.size();
    noOvpLisNBases = 0;
    for (i = 0; i < noOvpLis.size(); i++) {
        noOvpLisNBases += noOvpLis[i].l;
    }
    for (i = 0; i < noOvpLis.size(); i++ ) {	
        pMatch += -1 * ((int)noOvpLis[i].l);
        // log(matchList[i].GetMultiplicity() / (1.0*genomeLength));
    }
    noOvpLisNBases = 0;
    for (i = 0; i < matchList.size(); i++) {
        noOvpLisNBases += matchList[i].l;
    }
    return pMatch;
}


template<typename T_RefSequence, typename T_MatchList>
float LISSumOfLogPWeightor<T_RefSequence, T_MatchList>::operator()(
    T_MatchList &matchList) {
    int temp;
    return ComputePValue(matchList, temp, temp);
}


template<typename T_RefSequence, typename T_Tuple, typename T_MatchList>
LISSMatchFrequencyPValueWeightor<T_RefSequence, T_Tuple, T_MatchList>::LISSMatchFrequencyPValueWeightor(
    T_RefSequence &_target) {
    target.seq    = _target.seq;
    target.length = _target.length;
}


template<typename T_RefSequence, typename T_Tuple, typename T_MatchList>
float LISSMatchFrequencyPValueWeightor<T_RefSequence, T_Tuple, T_MatchList>::ComputePValue(
    T_MatchList &lis, int &noOvpLisNBases, int &noOvpLisSize) {
    T_MatchList noOvpLis;
    StoreNonOverlappingIndices(lis, noOvpLis);
    noOvpLisSize = noOvpLis.size();
    int i;
    noOvpLisNBases = 0;
    for (i = 0; i < noOvpLis.size(); i++) {
        noOvpLisNBases += noOvpLis[i].l;
    }
    if (noOvpLis.size() == 0){
        return 1;
    }

    float pMatch = 0;
    for (i = 0; i < noOvpLis.size(); i++ ) {
        assert(noOvpLis[i].GetMultiplicity() > 0);
        pMatch += log((1.0*noOvpLis[i].GetMultiplicity()) / target.length) * noOvpLis[i].l;
    }
    return pMatch;
}


template<typename T_RefSequence, typename T_Tuple, typename T_MatchList>
float LISSMatchFrequencyPValueWeightor<T_RefSequence, T_Tuple, T_MatchList>::operator() (
    T_MatchList &lis) {
    int noOvpLisSize = 0;
    return ComputePValue(lis, noOvpLisSize, noOvpLisSize);
}


template<typename T_RefSequence, typename T_Tuple, typename T_MatchList>
LISPValueWeightor<T_RefSequence, T_Tuple, T_MatchList>::LISPValueWeightor(
    FASTASequence &_query, T_RefSequence &_target, TupleMetrics _tm, 
    TupleCountTable<T_RefSequence, T_Tuple> *_ct) {
    query.seq     = _query.seq;
    query.length  = _query.length;
    target.seq    = _target.seq;
    target.length = _target.length;
    ct = _ct;
    tm = _tm;
}


template<typename T_RefSequence, typename T_Tuple, typename T_MatchList>
float LISPValueWeightor<T_RefSequence, T_Tuple, T_MatchList>::ComputePValue(
    T_MatchList &matchList, int &noOvpLisNBases, int &noOvpLisSize) {
    return ComputeLISPValue(matchList, target, query, tm, *ct, 
        noOvpLisNBases, noOvpLisSize);    
}


template<typename T_RefSequence, typename T_Tuple, typename T_MatchList>
float LISPValueWeightor<T_RefSequence, T_Tuple, T_MatchList>::operator()(
    T_MatchList &matchList){
    int noOvpLisSize = 0, noOvpLisNBases = 0;
    return ComputeLISPValue(matchList, target, query, tm, *ct, noOvpLisNBases, noOvpLisSize);    
}
#endif
