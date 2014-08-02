#ifndef _BLASR_ALIGNMENT_CONTEXT_HPP_
#define _BLASR_ALIGNMENT_CONTEXT_HPP_

#include <string>
#include "Enumerations.h"

class AlignmentContext {
public:
    bool isPrimary;
    int  subreadIndex;
    int  numProperlyAlignedSubreads;
    bool allSubreadsProperlyAligned;
    bool isFinal;
    int  nextSubreadPos;
    int  nextSubreadDir;
    bool hasNextSubreadPos;
    int  nSubreads;
    std::string rNext;
    std::string readGroupId;
    std::string chipId;
    AlignMode alignMode;
    int editDist;
    AlignmentContext(); 

    bool IsFirst(); 

    bool IsLast(); 

    bool AllSubreadsAligned(); 
};

#endif // _BLASR_ALIGNMENT_CONTEXT_HPP_
