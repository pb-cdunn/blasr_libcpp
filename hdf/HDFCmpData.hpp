#ifndef _BLASR_HDF_CMP_DATA_HPP_
#define _BLASR_HDF_CMP_DATA_HPP_

#include "HDFAtom.hpp"
#include "HDFCmpRefAlignmentGroup.hpp"

class HDFCmpData {
public:
    HDFAtom<std::string> commandLine;
    H5::H5File hdfCmpFile;
    HDFArray<int> movieNameIdArray;
    HDFStringArray movieNameArray;

    HDFStringArray readGroupPathArray;
    HDFArray<int>    readGroupPathIdArray;

    HDFArray<int>    refSeqNameIdArray;
    HDFStringArray refSeqNameArray;
    static const int NCols=22;
    vector<HDFAtom<std::string> >  colNameAtoms;
    vector<HDFCmpRefAlignmentGroup*> refAlignGroups;
    map<std::string, int> nameToAlignmentGroupIndex;
    static const char *colNameIds[];

    void Close() {
        hdfCmpFile.close();
    }
};

const char * HDFCmpData::colNameIds[] = {
    "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
    "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
    "20", "21"};


#endif
