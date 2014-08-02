#ifndef _BLASR_DISTANCE_MATRIX_SCORE_FUNCTION_HPP_
#define _BLASR_DISTANCE_MATRIX_SCORE_FUNCTION_HPP_

#include "BaseScoreFunction.hpp"
#include "ScoreMatrices.hpp"

template<typename T_RefSequence, typename T_QuerySequence>
class DistanceMatrixScoreFunction : public BaseScoreFunction {
public:
    int scoreMatrix[5][5];
    DistanceMatrixScoreFunction();

    DistanceMatrixScoreFunction(int scoreMatrixP[5][5], int insertionP, int deletionP);

    void InitializeScoreMatrix(int scoreMatrixP[5][5]);

    int Deletion(T_RefSequence &seq, DNALength pos, T_QuerySequence &querySeq, DNALength queryPos); 

    int Insertion(T_RefSequence &seq, DNALength pos, T_QuerySequence &querySeq, DNALength queryPos);

    int Deletion(T_RefSequence &seq, DNALength pos); 

    int Match(T_RefSequence &ref, DNALength refPos, T_QuerySequence &query, DNALength queryPos); 

    //
    // Define the score function on dereferenced pointers for speed.
    //
    int Match(Nucleotide ref, Nucleotide query); 

    int Insertion(T_QuerySequence &seq, DNALength pos); 

    float NormalizedMatch(T_RefSequence &ref, DNALength refPos, T_QuerySequence &query, DNALength queryPos);
    float NormalizedInsertion(T_RefSequence &ref, DNALength refPos, T_QuerySequence &query, DNALength queryPos);
    float NormalizedDeletion(T_RefSequence &ref, DNALength refPos, T_QuerySequence &query, DNALength queryPos);

};

#include "DistanceMatrixScoreFunctionImpl.hpp"

#endif // _BLASR_DISTANCE_MATRIX_SCORE_FUNCTION_HPP_
