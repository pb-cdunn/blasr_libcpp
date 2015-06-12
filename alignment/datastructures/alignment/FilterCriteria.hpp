#ifndef _BLASR_FILTER_CRITERIA_HPP_
#define _BLASR_FILTER_CRITERIA_HPP_
#include <string>
#include <iostream>
#include <vector>
#include <algorithm> // transform
#include <ctype.h>   // toupper
#include "AlignmentCandidate.hpp"


/// POSITIVE - larger score value is better.
/// NEGATIVE - smaller score value is better.
enum class ScoreSign {NEGATIVE=-1, POSITIVE=1};
static const std::string AS = "AS";

class Score {
public:
    Score(const float & value, const ScoreSign & sign);
    Score(const Score & another);
    ~Score();

    /// \returns float score value in [0, 100]
    float Value() const;

    /// \returns score sign, NEGATIVE or POSITIVE
    ScoreSign Sign() const;

    bool operator == (const Score & another) const;

    /// \returns true if this score value is better than another's.
    bool BetterThan(const Score & another) const;

    /// \returns true if this score value is better than or equal to another's.
    bool BetterThanOrEqual(const Score & another) const; 

    /// \returns true if this score value is worse than another's.
    bool WorseThan(const Score & another) const;

private:
    float _value;
    ScoreSign _sign;
    static constexpr float errorunit = 1e-6;
};

class HitPolicy {
    /// \name Hit Policy
    /// \{
public:

    /// \note Constructor
    HitPolicy(const std::string & hitPolicyStr, const ScoreSign & sign);
    ~HitPolicy(void);

    const std::string ToString() const;
    std::ostream & operator << (std::ostream & os);

    /// \returns score sign, NEGATIVE or POSITIVE
    ScoreSign Sign() const;

    /// \returns a help string describing hit policies.
    const std::string Help(const std::string & pad = "") const;

    /// \returns true if HitPolicy is RANDOM.
    bool IsRandom() const;

    /// \returns true if HitPolicy is RANDOMBEST.
    bool IsRandombest() const;

    /// \returns true if HitPolicy is ALL.
    bool IsAll() const;

    /// \returns true if HitPolicy is ALLBEST.
    bool IsAllbest() const;

    /// \returns true if HitPolicy is LEFTMOST.
    bool IsLeftmost() const;

    /// Apply hit policy on a list of AlignmentCandidate pointers.
    /// \returns apply hit policy and return alignment candidate pointers.
    /// \params createRand, call rand() to generate a random number 
    ///         or use the random number passed from caller.
    /// \params passedRand, random int passed from caller
    std::vector<T_AlignmentCandidate*> 
    Apply(const std::vector<T_AlignmentCandidate*> alnPtrs, 
          const bool & createRand = true,
          const int  & passedRand = 0) const;

    //std::vector<AlignmentCandidate<>> & 
    //Apply(std::vector<AlignmentCandidate<>> & records) const;

#ifdef USE_PBBAM
    /// Compare aligned bamRecords by query names, scores and target positions.
    bool compareByQNameScoreTStart(const PacBio::BAM::BamRecord & a, 
                                   const PacBio::BAM::BamRecord & b) const;

    /// Compare aligned bamRecords by scores and target positions.
    /// \note BamRecords must share the same query name.
    bool compareByScoreTStart(const PacBio::BAM::BamRecord & a, 
                              const PacBio::BAM::BamRecord & b) const;

    std::vector<PacBio::BAM::BamRecord> 
    Apply(const std::vector<PacBio::BAM::BamRecord> & records,
          const bool & createRand = true,
          const int  & passedRand = 0) const;
#endif

private:
    enum class HitPolicyEnum{RANDOM, ALL, ALLBEST, RANDOMBEST, LEFTMOST};
    HitPolicyEnum _hit;
    ScoreSign _sign;
    /// \}
};

class FilterCriteria {
    /// \name FilterCriteria
    /// \{
public:
    FilterCriteria(const DNALength & minAlnLength,
                   const float & minPctSimilarity,
                   const float & minPctAccuracy,
                   const bool & useScore,
                   const Score & score); 
    ~FilterCriteria(void);
    bool MakeSane(std::string & errMsg) const;
    void Verbose(bool verbose);

    template<typename T_TSequence, typename T_QSequence>
    bool Satisfy(AlignmentCandidate<T_TSequence, T_QSequence> * a) const;

#ifdef USE_PBBAM
    bool Satisfy(const PacBio::BAM::BamRecord & record) const;
#endif

public:
    /// \retuns a string describing criteria for filtering alignments.
    // const std::string Help(const std::string & pad = "");
    const std::string MinAlnLengthHelp();
    const std::string MinPctSimilarityHelp();
    const std::string MinPctAccuracyHelp();
    const std::string ScoreSignHelp();
    const std::string ScoreCutoffHelp();

private:
    DNALength _minAlnLength;
    float _minPctSimilarity;
    float _minPctAccuracy;
    bool _useScore;
    Score _scoreCutoff;
    bool _verbose;

    bool Satisfy(const DNALength & alnLength, 
                 const float & pctSimilarity, 
                 const float & pctAccuracy,
                 const Score & score) const;
    /// \}
};

template<typename T_TSequence, typename T_QSequence>
bool FilterCriteria::Satisfy(AlignmentCandidate<T_TSequence, T_QSequence> * a) const {
    float pctAccuracy = 100 * a->nMatch / static_cast<float>(a->nMismatch
            + a->nMatch + a->nIns + a->nDel);
    Score s(a->score, _scoreCutoff.Sign());
    return Satisfy(a->qAlignedSeqLength, a->pctSimilarity, pctAccuracy, s);
}
#endif //_BLASR_FILTER_CRITERIA_HPP_
