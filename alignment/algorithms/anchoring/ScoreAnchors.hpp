#ifndef _BLASR_SCORE_ANCHORS_HPP_
#define _BLASR_SCORE_ANCHORS_HPP_

#include <math.h>
#include "tuples/TupleCountTable.hpp"
#include "tuples/DNATuple.hpp"
#include "tuples/TupleMetrics.hpp"
#include "statistics/cdfs.hpp"
#include "statistics/pdfs.hpp"

template<typename TSequence, typename T_Tuple>
int GetTupleCount(TSequence &seq, DNALength startPos, 
    TupleMetrics &tm, TupleCountTable<TSequence, T_Tuple> &ct, 
    int &count);

template<typename TSequence, typename T_Tuple>
int PMatch(TSequence &seq, DNALength startPos, DNALength length,
    TupleMetrics &tm, TupleCountTable<TSequence, T_Tuple> &ct,
	float &pMatch); 

template<typename TSequence, typename T_Tuple>
int POneOrMoreMatches(TSequence &seq, DNALength startPos, 
    DNALength length, TupleMetrics &tm, 
	TupleCountTable<TSequence, T_Tuple> &ct,
    float &pValue); 

template<typename TSequence, typename T_Tuple>
int SumRightShiftMarginalTupleCounts(TupleMetrics &tm, 
    TupleCountTable<TSequence, T_Tuple> &ct, T_Tuple curTuple,
    int nextNuc, int &nextSeqCount);

template<typename TSequence, typename T_Tuple>
int ComputeTotalTupleCount(TupleMetrics &tm,
    TupleCountTable<TSequence, T_Tuple> &ct, TSequence &seq,
    int start=0, int end=-1);

template<typename TSequence, typename T_Tuple>
int ComputeAverageTupleCount(TupleMetrics &tm, 
    TupleCountTable<TSequence, T_Tuple> &ct, TSequence &seq);

inline
int ComputeExpectedFirstWaitingTime(float lambda);

#include "ScoreAnchorsImpl.hpp"

#endif
