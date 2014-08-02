#ifndef _BLASR_SW_ALIGN_HPP_
#define _BLASR_SW_ALIGN_HPP_

template<typename T_QuerySequence, typename T_TargetSequence, typename T_Alignment, typename T_ScoreFn>
int SWAlign(T_QuerySequence &qSeq, T_TargetSequence &tSeq, 
        std::vector<int> &scoreMat,
        std::vector<Arrow> &pathMat, 
        T_Alignment &alignment,
        T_ScoreFn &scoreFn,
        AlignmentType alignType = Local,
        bool trustSequences = false,
        bool printMatrix = false
        ); 

#include "SWAlignImpl.hpp"

#endif // _BLASR_SW_ALIGN_HPP_
