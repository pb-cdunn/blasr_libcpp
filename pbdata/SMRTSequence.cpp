#include "SMRTSequence.hpp"

using namespace std;

void SMRTSequence::SetNull() {
    pulseIndex    = NULL;
    preBaseFrames = NULL;
    widthInFrames = NULL;
    xy[0] = 0; xy[1] = 0;
    // These are not allocted by default.
    meanSignal = maxSignal = midSignal = NULL;
    classifierQV = NULL;
    startFrame   = NULL;
    platform     = NoPlatform;
    // By default, allow the entire read.
    lowQualityPrefix = lowQualitySuffix = 0;
}

SMRTSequence::SMRTSequence() : FASTQSequence() {
    holeNumber = -1;
    SetNull();
}

void SMRTSequence::Allocate(DNALength length) {
    FASTQSequence::AllocateRichQualityValues(length);
    seq           = new Nucleotide[length];
    qual.Allocate(length);
    preBaseFrames = new HalfWord[length];
    widthInFrames = new HalfWord[length];
    pulseIndex    = new int[length];
    subreadEnd    = length;
    deleteOnExit  = true;
}

void SMRTSequence::SetSubreadTitle(SMRTSequence &subread, DNALength subreadStart, DNALength  subreadEnd) {
    stringstream titleStream;
    titleStream << title << "/"<< subreadStart << "_" << subreadEnd;
    subread.CopyTitle(titleStream.str());
}    

void SMRTSequence::SetSubreadBoundaries(SMRTSequence &subread, DNALength &subreadStart, int &subreadEnd) {
    if (subreadEnd == -1) {
        subreadEnd = length;
    }
    assert(subreadEnd - subreadStart <= length);
    subread.subreadStart= subreadStart;
    subread.subreadEnd  = subreadEnd;
    SetSubreadTitle(subread, subreadStart, subreadEnd);
}

void SMRTSequence::MakeSubreadAsMasked(SMRTSequence &subread, 
    DNALength subreadStart, int subreadEnd) {

    //
    // This creates the entire subread, but masks out the portions
    // that do not correspond to this insert.
    //
    subread.Copy(*this);
    SetSubreadBoundaries(subread, subreadStart, subreadEnd);
    DNALength pos;
    for (pos = 0; pos < subreadStart; pos++) { subread.seq[pos] = 'N'; }
    for (pos = subreadEnd; pos < length; pos++) { subread.seq[pos] = 'N'; }
    // This is newly allocated memory, free it on exit.
    subread.deleteOnExit = true;
}

void SMRTSequence::MakeSubreadAsReference(SMRTSequence &subread, 
    DNALength subreadStart, int subreadEnd) {
    //
    // Just create a reference to a substring of this read.  
    //
    SetSubreadBoundaries(subread, subreadStart, subreadEnd);
    subread.ReferenceSubstring(*this, subreadStart, subreadEnd - subreadStart);
    // The subread references this read, protect the memory.
    subread.deleteOnExit = false;
}

void SMRTSequence::Copy(const SMRTSequence &rhs) {
    Copy(rhs, 0, rhs.length);
}


void SMRTSequence::Copy(const SMRTSequence &rhs, int rhsPos, int rhsLength) {
    //
    // Make sure not attempting to copy into self.
    //
    SMRTSequence subseq;
    subseq.ReferenceSubstring(rhs, rhsPos, rhsLength);
    subseq.title = rhs.title;
    subseq.titleLength = strlen(rhs.title);
    if (rhs.length == 0) {
        if (preBaseFrames != NULL) { 
            delete[] preBaseFrames;
            preBaseFrames = NULL;
        }
        if (widthInFrames != NULL) {
            delete[] widthInFrames;
            widthInFrames = NULL;
        }
        if (pulseIndex != NULL) {
            delete[] pulseIndex;
            pulseIndex = NULL;
        }
        ((FASTQSequence*)this)->Copy(subseq);
        //
        // Make sure that no values of length 0 are allocated by returning here.
        //
    }
    else {

        assert(rhs.seq != seq);
        assert(rhsLength <= rhs.length);
        assert(rhsPos < rhs.length);

        ((FASTQSequence*)this)->Copy(subseq);
        if (rhs.preBaseFrames != NULL) {
            preBaseFrames = new HalfWord[length];
            memcpy(preBaseFrames, rhs.preBaseFrames, length*sizeof(HalfWord));
        }
        if (rhs.widthInFrames != NULL) {
            widthInFrames = new HalfWord[length];
            memcpy(widthInFrames, rhs.widthInFrames, length*sizeof(HalfWord));
        }
        if (rhs.pulseIndex != NULL) {
            pulseIndex = new int[length];
            memcpy(pulseIndex, rhs.pulseIndex, sizeof(int) * length);
        }
    }
    subreadStart = rhs.subreadStart;
    subreadEnd   = rhs.subreadEnd;
    lowQualityPrefix = rhs.lowQualityPrefix;
    lowQualitySuffix = rhs.lowQualitySuffix;
    zmwData = rhs.zmwData;
}

void SMRTSequence::Print(ostream &out) {
    out << "SMRTSequence for zmw " << zmwData.holeNumber
        << ", [" << subreadStart << ", " << subreadEnd << ")" << endl;
    DNASequence::Print(out);
}

SMRTSequence& SMRTSequence::operator=(const SMRTSequence &rhs) {
    Copy(rhs);
    return *this;
}

void SMRTSequence::Free() {
    FASTQSequence::Free();
    if (deleteOnExit == true) {
        if (preBaseFrames)  {
            delete[] preBaseFrames;
            preBaseFrames = NULL;
        }
        if (widthInFrames) {
            delete[] widthInFrames;
            widthInFrames = NULL;
        }
        if (pulseIndex) {
            delete[] pulseIndex;
            pulseIndex = NULL;
        }
        if (startFrame) {
            delete[] startFrame;
            startFrame = NULL;
        }
        // meanSignal, maxSignal, midSignal and classifierQV
        // need to be handled separatedly.
    }
    xy[0] = 0; xy[1] = 0;
    lowQualityPrefix = lowQualitySuffix = 0;
    holeNumber = -1;
}

bool SMRTSequence::StoreXY(int16_t xyP[]) {
    xy[0] = xyP[0];
    xy[1] = xyP[1];
    return true;
}

bool SMRTSequence::StorePlatformId(PlatformId pid) {
    platform = pid;
    return true;
}

bool SMRTSequence::StoreHoleNumber(int holeNumberP){ 
    zmwData.holeNumber = holeNumber = holeNumberP;
    return true;
}

bool SMRTSequence::StoreHoleStatus(unsigned int s) {
    zmwData.holeStatus = s;
    return true;
}

bool SMRTSequence::StoreZMWData(ZMWGroupEntry &data) {
    zmwData = data;
    return true;
}

bool SMRTSequence::GetXY(int xyP[]) {
    xyP[0] = xy[0];
    xyP[1] = xy[1];
    return true;
}

bool SMRTSequence::GetHoleNumber(int& holeNumberP) {
    holeNumberP = holeNumber;
    return true;
}
