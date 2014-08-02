#include "AlignmentContext.hpp"

AlignmentContext::AlignmentContext() {
    isPrimary = true;
    subreadIndex = 0;
    isFinal   = true;
    nextSubreadPos = 0;
    hasNextSubreadPos = false;
    numProperlyAlignedSubreads = 0;
    allSubreadsProperlyAligned = false;
    nSubreads = 0;
    nextSubreadDir = 0;
    rNext = "";
    readGroupId = "";
    chipId = "";
    alignMode = NoAlignMode;
    editDist = 0;
}

bool AlignmentContext::IsFirst() {
    return subreadIndex == 0;
}

bool AlignmentContext::IsLast() {
    return subreadIndex == nSubreads-1;
}

bool AlignmentContext::AllSubreadsAligned() {
    if (numProperlyAlignedSubreads == nSubreads) {
        return true;
    }
    else {
        return false;
    }
}
