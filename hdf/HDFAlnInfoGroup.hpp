#ifndef _BLASR_HDF_ALN_INFO_GROUP_HPP_
#define _BLASR_HDF_ALN_INFO_GROUP_HPP_

#include <cinttypes>
#include <vector>
#include <string>
#include "HDFGroup.hpp"
#include "HDFAtom.hpp"
#include "HDFArray.hpp"
#include "HDF2DArray.hpp"
#include "saf/AlnInfo.hpp"
#include "alignment/CmpAlignment.hpp"

class HDFAlnInfoGroup {
public:
    HDFGroup alnInfoGroup;
    HDF2DArray<unsigned int> alnIndexArray;
    HDFArray<float> startTime;
    static const int NCols=22;
    HDFArray<unsigned int> numPasses;
    HDFAtom<vector<string> > columnNames;
    HDFAtom<int> frameRate;

    int Initialize(HDFGroup &rootGroup); 

    int InitializeNumPasses(); 

    void InitializeDefaultColumnNames(std::vector<std::string> &defaultColumnNames); 

    bool Create(HDFGroup &parent); 

    ~HDFAlnInfoGroup(); 

    // Return size of /AlnInfo/AlnIndex in KB
    UInt GetAlnIndexSize(); 

    void Read(AlnInfo &alnInfo); 

    int GetNAlignments(); 

    unsigned int WriteAlnIndex(std::vector<unsigned int> &aln); 

    void ReadCmpAlignment(UInt alignmentIndex, CmpAlignment &cmpAlignment); 
};

#endif
