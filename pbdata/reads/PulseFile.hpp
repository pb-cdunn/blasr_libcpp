#ifndef _BLASR_PULSE_FILE_HPP_
#define _BLASR_PULSE_FILE_HPP_

#include <map>
#include <vector>
#include "Types.h"
#include "Enumerations.h"
#include "DNASequence.hpp"
#include "SMRTSequence.hpp"
#include "PulseBaseCommon.hpp"
#include "ScanData.hpp"

class PulseFile : public PulseBaseCommon {
 public:
    unsigned int numFrames;
    PlatformId platformId;
    std::vector<unsigned int> startFrame;
    std::vector<uint16_t> plsWidthInFrames;
    int midSignalNDims, maxSignalNDims, meanSignalNDims;
    std::vector<uint16_t> midSignal;
    std::vector<uint16_t> maxSignal;
    std::vector<uint16_t> meanSignal; 
    std::vector<int>      numEvent;
    std::vector<int>      pulseStartPositions;
    std::vector<float>    classifierQV;

    void CopySignal(HalfWord *signalData, // either a vector or matrix
                    int signalNDims,
                    int pulseStartPos,    // 0 if baseToPulseIndex maps to abs position
                    int *baseToPulseIndex,
                    Nucleotide *readSeq,
                    int readLength,
                    HalfWord *readData);
    
    // plsReadIndex: index of this hole number in /PulseCalls/ZMW/HoleNumber.
    // baseToPulseIndex: index from pulse to base from the beginning of the read.
    // read: a SMRTSequence.
    void CopyReadAt(uint32_t plsReadIndex, int *baseToPulseIndex, SMRTSequence &read);

    template<typename T_FieldType>
    void StoreField(std::vector<T_FieldType> &source, int *basToPlsIndex, T_FieldType *dest, int destLength);
    
    template <typename T>
    bool Realloc(T *&ptr, int length);


};

#include "PulseFileImpl.hpp"

#endif
