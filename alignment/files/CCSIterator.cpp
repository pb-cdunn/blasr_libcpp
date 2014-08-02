#include "files/CCSIterator.hpp"

void CCSIterator::Initialize(CCSSequence *_seqPtr) {
    seqPtr = _seqPtr;
    curPass = 0;
    numPasses = seqPtr->passDirection.size();
}

int CCSIterator::GetNext(int &direction, int &startBase, int &numBases) {
    if (curPass >= numPasses) {
        return 0;
    }
    else {
        direction = seqPtr->passDirection[curPass];
        startBase = seqPtr->passStartBase[curPass];
        numBases  = seqPtr->passNumBases[curPass];
        ++curPass;
        return 1;
    }
}

void CCSIterator::Reset() {
    curPass = 0;
}

int CCSIterator::GetNumPasses() {
    return numPasses;
}
