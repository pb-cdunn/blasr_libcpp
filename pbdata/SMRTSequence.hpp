#ifndef _BLASR_SMRT_SEQUENCE_HPP_
#define _BLASR_SMRT_SEQUENCE_HPP_

#include <cassert>
#include <iostream>
#include <sstream>

#include "Types.h"
#include "Enumerations.h"
#include "NucConversion.hpp"
#include "FASTQSequence.hpp"
#include "reads/RegionTable.hpp"
#include "reads/ZMWGroupEntry.hpp"

class SMRTSequence : public FASTQSequence {
public:
    int16_t xy[2];
    UInt holeNumber;
    float hqRegionSnr[4];
    float readScore;
    ZMWGroupEntry zmwData;
    PlatformId platform;
    HalfWord *preBaseFrames;
    HalfWord *widthInFrames;
    //
    // The following are fields that are read in from the pulse file.
    // Because they are not standard in bas.h5 files, these fields
    // should not be preallocated when resizing a SMRTSequence, and
    // memory should be managed separately.  For now, these fields all
    // have the same length as the number of bases, but this could
    // change so that all pulse values are stored in a SMRTSequence.
    //
    HalfWord *meanSignal, *maxSignal, *midSignal;
    float *classifierQV;
    unsigned int *startFrame;
    int *pulseIndex;
    DNALength lowQualityPrefix, lowQualitySuffix;
    int highQualityRegionScore; // High quality region score in region table.

protected:
    // read group id associated with each SMRTSequence
    std::string readGroupId; 

public:
    // Whether or not this is originally copied from a BamRecord.
    bool copiedFromBam;

    void SetNull(); 

    SMRTSequence();
    inline ~SMRTSequence();

    void Allocate(DNALength length); 

    void SetSubreadTitle(SMRTSequence &subread, DNALength subreadStart, 
        DNALength subreadEnd); 

    void SetSubreadBoundaries(SMRTSequence &subread, DNALength &subreadStart, 
        int &subreadEnd); 

    void MakeSubreadAsMasked(SMRTSequence &subread, DNALength subreadStart = 0, 
        int subreadEnd = -1); 

    void MakeSubreadAsReference(SMRTSequence &subread, DNALength subreadStart = 0, 
        int subreadEnd = -1); 

    void Copy(const SMRTSequence &rhs); 

    void Copy(const SMRTSequence &rhs, int rhsPos, int rhsLength); 

    void Print(std::ostream &out); 

    SMRTSequence& operator=(const SMRTSequence &rhs); 

    void Free(); 

    bool StoreXY(int16_t xyP[]); 

    bool StorePlatformId(PlatformId pid); 

    bool StoreHoleNumber(UInt holeNumberP);

    bool StoreHoleStatus(unsigned char s); 

    bool StoreZMWData(ZMWGroupEntry &data); 

    bool GetXY(int xyP[]); 

    bool GetHoleNumber(UInt & holeNumberP);   

    // Get read group id for this sequence.
    std::string GetReadGroupId();

    // Set readGroup Id for this sequence.
    void SetReadGroupId(const std::string & rid);
    
#ifdef USE_PBBAM
public:
    // Copy read sequence, title, holeNumber, readGroupId, and QVs
    // (iq, dq, sq, mq, st, dt) from BamRecord to this SMRTSequence.
    void Copy(const PacBio::BAM::BamRecord & record);

    // Keep track of BamRecord from which this SMRTSequence is 
    // originally copied. However, one should NOT assume
    // that this SMRTSequence has the same sequence, title, QVs as 
    // the BamRecord, because this SMRTSequence may be created by
    // MakeSubreadAsMasked(...) or MakeRC(...).
    PacBio::BAM::BamRecord bamRecord;
#endif 
};

inline SMRTSequence::~SMRTSequence(){
    SMRTSequence::Free();
}
#endif  // _BLASR_SMRT_SEQUENCE_HPP_
