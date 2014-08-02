#ifndef _BLASR_LISPVALUE_WEIGHTOR_HPP_
#define _BLASR_LISPVALUE_WEIGHTOR_HPP_

#include "algorithms/anchoring/LISPValue.hpp"
#include "tuples/TupleMetrics.hpp"

template<typename T_RefSequence, typename T_MatchList>
class LISSumOfLogPWeightor {
public:
	DNALength genomeLength;
	LISSumOfLogPWeightor(T_RefSequence &targetGenome);
    float ComputePValue(T_MatchList &matchList, 
        int &noOvpLisNBases, int &noOvpLisSize);
    float operator()(T_MatchList &matchList);
};


template<typename T_RefSequence, typename T_Tuple, typename T_MatchList>
class LISSMatchFrequencyPValueWeightor {
public:
	T_RefSequence target;
	LISSMatchFrequencyPValueWeightor(T_RefSequence &_target);
    float ComputePValue(T_MatchList &lis, 
        int &noOvpLisNBases, int &noOvpLisSize);
    float operator() (T_MatchList &lis);
};	


template<typename T_RefSequence, typename T_Tuple, typename T_MatchList>
class LISPValueWeightor {
public:
    //
    // All of these must be initialized prior to 
    // computing weights (running the functor).
    //
    FASTASequence query;
    T_RefSequence target;
    TupleMetrics tm;
    TupleCountTable<T_RefSequence, T_Tuple> *ct;

    LISPValueWeightor(FASTASequence &_query, T_RefSequence &_target, 
        TupleMetrics _tm, TupleCountTable<T_RefSequence, T_Tuple> *_ct);

    float ComputePValue(T_MatchList &matchList, int &noOvpLisNBases,
        int &noOvpLisSize);

    float operator()(T_MatchList &matchList);
};

#include "algorithms/anchoring/LISPValueWeightorImpl.hpp"

#endif
