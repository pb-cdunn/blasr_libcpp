#ifndef _BLASR_SDP_ALIGN_HPP_
#define _BLASR_SDP_ALIGN_HPP_

#include "DNASequence.hpp"
#include "tuples/TupleMatching.hpp"
#include "sdp/SDPFragment.hpp"
#include "FASTASequence.hpp"
#include "FASTQSequence.hpp"
#include "DistanceMatrixScoreFunction.hpp"

#define SDP_DETAILED_WORD_SIZE 5
#define SDP_PREFIX_LENGTH 50
#define SDP_SUFFIX_LENGTH 50

template<typename T_QuerySequence, typename T_TargetSequence, typename T_ScoreFn>
int SDPAlign(T_QuerySequence &query, T_TargetSequence &target,
        T_ScoreFn &scoreFn, int wordSize, 
        int sdpIns, int sdpDel, float indelRate,
        blasr::Alignment &alignment, 
        AlignmentType alignType=Global,
        bool detailedAlignment=true,
        bool extendFrontByLocalAlignment=true,
        DNALength noRecurseUnder=10000,
        bool fastSDP=true,
        unsigned int minFragmentsToUseGraphPaper=100000);


template<typename T_QuerySequence, typename T_TargetSequence, typename T_ScoreFn, typename T_BufferCache>
int SDPAlign(T_QuerySequence &query, T_TargetSequence &target,
        T_ScoreFn &scoreFn, int wordSize, 
        int sdpIns, int sdpDel, float indelRate,
        blasr::Alignment &alignment, 
        T_BufferCache &buffers,
        AlignmentType alignType=Global,
        bool detailedAlignment=true,
        bool extendFrontByLocalAlignment=true, 
        DNALength noRecurseUnder=10000,
        bool fastSDP=true,
        unsigned int minFragmentsToUseGraphPaper=100000);

template<typename T_QuerySequence, typename T_TargetSequence, typename T_ScoreFn, typename T_TupleList>
int SDPAlign(T_QuerySequence &query, T_TargetSequence &target,
        T_ScoreFn &scoreFn,
        int wordSize, 
        int sdpIns, int sdpDel, float indelRate,
        blasr::Alignment &alignment, 
        std::vector<Fragment> &fragmentSet,
        std::vector<Fragment> &prefixFragmentSet,
        std::vector<Fragment> &suffixFragmentSet,
        T_TupleList &targetTupleList,
        T_TupleList &targetPrefixTupleList,
        T_TupleList &targetSuffixTupleList,
        std::vector<int> &maxFragmentChain,
        // A few optinal parameters, should delete that last one.
        AlignmentType alignType=Global,
        bool detailedAlignment=true,
        bool extendFrontByLocalAlignment=true, 
        DNALength noRecurseUnder=10000,
        bool fastSDP=true,
        unsigned int minFragmentsToUseGraphPaper=100000);

#include "SDPAlignImpl.hpp"

#endif // _BLASR_SDP_ALIGN_HPP_
