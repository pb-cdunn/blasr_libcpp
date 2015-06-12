#include "AlignmentCandidate.hpp"

int SortAlignmentPointersByScore::operator() (T_AlignmentCandidate *lhs, 
                                              T_AlignmentCandidate* rhs) {
    if (lhs->score == rhs->score) {
        return lhs->tPos + lhs->tAlignedSeqPos < rhs->tPos + rhs->tAlignedSeqPos;
    }
    else {
        return lhs->score < rhs->score;
    }
}

int SortAlignmentPointersByMapQV::operator() (T_AlignmentCandidate *lhs,
                                              T_AlignmentCandidate* rhs) {
    if (lhs->mapQV == rhs->mapQV) {
        if (lhs->score == rhs->score) {
            return lhs->tPos + lhs->tAlignedSeqPos < rhs->tPos + rhs->tAlignedSeqPos;
        }
        else {
            return lhs->score < rhs->score;
        }
    }
    else {
        return lhs->mapQV > rhs->mapQV;
    }
}
