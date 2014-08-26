#ifndef _BLASR_HDF_CMP_EXPERIMENT_GROUP_HPP_
#define _BLASR_HDF_CMP_EXPERIMENT_GROUP_HPP_

#include <map>
#include <vector>
#include <set>
#include <cstdint>
#include "Types.h"
#include "HDFGroup.hpp"
#include "HDFArray.hpp"
#include "HDFCmpSupportedFields.hpp"

class HDFCmpExperimentGroup {
public:
    HDFCmpSupportedFields supportedFields;
    HDFArray<unsigned int> startTimeOffset;
    HDFArray<HalfWord> ipd;
    HDFArray<HalfWord> preBaseFrames;
    HDFArray<char>  deletionTag;
    HDFArray<char>  substitutionTag;
    HDFArray<UChar> qualityValue;
    HDFArray<UChar> deletionQV;
    HDFArray<UChar> insertionQV;
    HDFArray<float> classifierQV; 
    // ClassifierQV date type is float in cmp.h5
    HDFArray<UChar> substitutionQV;
    HDFArray<UChar> mergeQV;
    HDFArray<HalfWord> light;
    HDFArray<HalfWord> widthInFrames;
    HDFArray<HalfWord> pulseWidth;
    HDFArray<unsigned int> startTime;
    // StartFrame computed from Pulse metrics and Base metric
    HDFArray<unsigned int> startTimeBase;
    HDFArray<unsigned int> startTimePulse;
    HDFArray<float> pkmid;
    HDFArray<float> pkmax;
    HDFArray<float> pkmean;
    HDFArray<uint32_t>   numPasses;
    HDFArray<uint32_t> pulseIndex;
    std::map<std::string, HDFData*> fields;
    HDFGroup experimentGroup;
    HDFArray<unsigned char> alignmentArray;

    bool Create(HDFGroup &parent, string experimentGroupName); 

    void AddAlignment(std::vector<unsigned char> &alignment, 
        unsigned int &offsetBegin, unsigned int &offsetEnd); 
    
    // AddQVs and AddTags are like AddAlignment, but for QVs and Tags,
    // respectively. They are responsible for initializing and writing to the
    // correct member HDFArray, given a vector of values to write and the name
    // of the QV or Tag 
    void AddQVs(const std::vector<UChar> &qualityValues, const std::string &fieldName,
                unsigned int *offsetBegin, unsigned int *offsetEnd);
    void AddTags(const std::vector<char> &qualityValues, const std::string &fieldName,
                 unsigned int *offsetBegin, unsigned int *offsetEnd);
                           
    int Initialize(HDFGroup &refGroup, std::string experimentGroupName, 
        std::set<string> &fieldNames); 

    int Initialize(HDFGroup &refGroup, std::string experimentGroupName); 

    void Read();

    HDFCmpExperimentGroup(); 

    // Return reference alignment AlnArray size in KB.
    UInt GetAlnArraySize(); 
};
#endif
