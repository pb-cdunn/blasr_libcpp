#ifndef _BLASR_ALIGNMENT_UTILS_HPP_
#define _BLASR_ALIGNMENT_UTILS_HPP_

#include <string>
#include "DNASequence.hpp"
#include "datastructures/alignment/Alignment.hpp"
#include "algorithms/alignment/DistanceMatrixScoreFunction.hpp"

enum AlignmentType { 
    Local,     // Standard Smith-Waterman
    Global,    // Standard Needleman-Wuncsh
    QueryFit,  // No gap penalties from query.  
    TargetFit, // For when the query engulfs the target.  
    Overlap,    // No gap penalty at the beginning of
    // query, nor at the end of text **
    // not yet implemented for k-band **, 
    FrontAnchored, // Require the alignment to align
    // pos 0,0 in the matrix 
    EndAnchored,   // Require the alignment to align
    // the pos m,n in the matrix 
    // Score alignment types solely compute the score
    // of an alignment and do not store the actual
    // alignment itself.  This is fast for filtering
    // potential alignments that may be re-aligned
    // later to store the actual alignment.
    Fit,  // No gap penalties at the beginning nor ends of alignments.
    TSuffixQPrefix, // Same as overlap 
    TPrefixQSuffix, // so that the order of the alignment does not have to be reversed
    ScoreGlobal,
    ScoreLocal,
    ScoreQueryFit,
    ScoreTargetFit,
    ScoreOverlap,
    ScoreFrontAnchored,
    ScoreEndAnchored,
    ScoreTSuffixQPrefix,
    ScoreTPrefixQSuffix,
    //
    // A LocalBoundaries alignment is in-between a
    // score-only and full-alignment. The full path
    // matrix is computed, but rather 
    // than computing an alignment, simply the  
    // (qStart, qLength), (tStart, tLength)
    // coordinates of the alignment are returned.  
    //
    LocalBoundaries,
    //
    // A SignificanceLimited alignment is a banded
    // alignment that continues alignment until the
    // score drops below a certain threshold below
    // the maximum score.
    //
    SignificanceLimited
};

inline
int ComputeAlignmentScore(
        std::string& queryStr, std::string& textStr, 
        int matchScores[5][5], int ins, int del);

template<typename T_ScoreFn>
inline
int ComputeAlignmentScore(
        std::string& queryStr, std::string& textStr, 
        T_ScoreFn & scoreFn, bool useAffineScore = false);

template<typename T_QuerySequence, typename T_TargetSequence, typename T_ScoreFn>
int ComputeAlignmentScore(blasr::Alignment& alignment,
        T_QuerySequence& query,
        T_TargetSequence& text,
        T_ScoreFn& scoreFn,
        bool useAffinePenalty = false);

template<typename T_QuerySequence, typename T_TargetSequence>
int ComputeAlignmentScore(blasr::Alignment &alignment,
        T_QuerySequence &query,
        T_TargetSequence &text,
        int matchScores[5][5],
        int ins,
        int del);

int GetNumberWidth(unsigned int value); 

template<typename T_Alignment>
inline void PrintCompareSequencesAlignmentStats(T_Alignment &alignment, std::ostream &out); 

template<typename T_Alignment>
inline int ReadCompareSequencesAlignmentStats(std::istream &in, T_Alignment &alignment); 

template<typename T_Alignment>
inline int ReadCompSeqAlignment(std::istream &in, T_Alignment &alignment); 

/*
 * This should be changed to read any type of alignment, since templates are being
 * used.
 */
inline void ReadCompSeqAlignments(std::string &compSeqAlignmentFileName, std::vector<blasr::CompSeqAlignment> &alignments); 

inline void PrintAlignmentStats(blasr::Alignment &alignment, std::ostream &out); 

template<typename T_QuerySequence, typename T_TargetSequence>
void  AppendGapCharacters(blasr::Gap &gap, 
        T_QuerySequence &query, T_TargetSequence &text, 
        DNALength &q, DNALength &t,
        char mismatchChar, char gapChar,
        std::string &textStr, std::string &alignStr, std::string &queryStr); 

template<typename T_Alignment, typename T_QuerySequence, typename T_TargetSequence>
void CreateAlignmentStrings(T_Alignment &alignment, 
        T_QuerySequence &query, T_TargetSequence &text, 
        std::string &textStr, std::string &alignStr, std::string &queryStr, DNALength queryLength=0, DNALength textLength=0); 

template<typename T_Alignment, typename T_ScoreFn>
void ComputeAlignmentStats(T_Alignment & alignment, Nucleotide* qSeq, Nucleotide * tSeq, T_ScoreFn & scoreFn, bool useAffineScore = false);
 
template<typename T_Alignment>
void ComputeAlignmentStats(T_Alignment &alignment, Nucleotide* qSeq, Nucleotide *tSeq, int matchMatrix[5][5], int ins, int del); 

template<typename T_Alignment>
int ComputeDrift(T_Alignment &alignment); 

int ComputeDrift(blasr::Block &cur, blasr::Block &next); 

template<typename T_Alignment>
void RemoveAlignmentPrefixGaps(T_Alignment &alignment); 

#include "AlignmentUtilsImpl.hpp"

#endif // _BLASR_ALIGNMENT_UTILS_HPP_
