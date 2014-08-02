#ifndef _BLASR_QUALITY_VALUE_SCORE_FUNCTION_HPP_
#define _BLASR_QUALITY_VALUE_SCORE_FUNCTION_HPP_
#include "FASTASequence.hpp"
#include "FASTQSequence.hpp"
#include "NucConversion.hpp"
#include "ScoreMatrices.hpp"
#include "BaseScoreFunction.hpp"

template<typename T_RefSequence, typename T_QuerySequence>
class QualityValueScoreFunction: public BaseScoreFunction{
public:
    int Deletion(T_RefSequence &seq, DNALength refPos, 
        T_QuerySequence &querySeq, DNALength queryPos);
    int Deletion(T_RefSequence &seq, DNALength pos);

    int Match(T_RefSequence &ref, DNALength refPos, 
        T_QuerySequence &query, DNALength queryPos);

    int Insertion(T_RefSequence &ref, DNALength refPos,
        T_QuerySequence &seq, DNALength pos);
    int Insertion(T_QuerySequence &seq, DNALength pos);
};


//
// Define all specializations for a FASTA reference and 
// FASTQSequence for the query, or FASTA sequence for query.
//
template<>
int QualityValueScoreFunction<FASTASequence, FASTQSequence>::Deletion(
    FASTASequence &ref, DNALength pos);

template<>
int QualityValueScoreFunction<DNASequence, FASTQSequence>::Deletion(
    DNASequence &ref, DNALength pos);

template<>
int QualityValueScoreFunction<DNASequence, FASTQSequence>::Deletion(
    DNASequence &seq, DNALength refPos, FASTQSequence &querySeq, 
    DNALength queryPos);

template<>
int QualityValueScoreFunction<DNASequence, FASTQSequence>::Insertion(
    FASTQSequence &query, DNALength pos);

template<>
int QualityValueScoreFunction<DNASequence, FASTQSequence>::Insertion(
    DNASequence &ref, DNALength refPos, FASTQSequence &query, 
    DNALength pos);

template<>
int QualityValueScoreFunction<DNASequence, FASTQSequence>::Match(
    DNASequence &ref, DNALength refPos, FASTQSequence &query, 
    DNALength queryPos);

#endif
