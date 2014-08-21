#ifndef _BLASR_HDF_REGION_TABLE_READER_HPP_
#define _BLASR_HDF_REGION_TABLE_READER_HPP_

#include <string>
#include <vector>

#include "H5Cpp.h"

#include "reads/RegionTable.hpp"
#include "HDFFile.hpp"
#include "HDFArray.hpp"
#include "HDF2DArray.hpp"
#include "HDFAtom.hpp"


class HDFRegionTableReader {
public:
    HDFFile regionTableFile;
    HDFGroup pulseDataGroup;
    HDF2DArray<int> regions;

    HDFAtom<std::vector<std::string> > regionTypes;
    HDFAtom<std::vector<std::string> > regionDescriptions;
    HDFAtom<std::vector<std::string> > regionSources;
    HDFAtom<std::vector<std::string> > columnNames;
    int curRow;
    int nRows;
    bool fileContainsRegionTable;

    int Initialize(std::string &regionTableFileName, 
            const H5::FileAccPropList & fileAccPropList = H5::FileAccPropList::DEFAULT); 

    int GetNext(RegionAnnotation &annotation); 

    void RegionTypesToMap(RegionTable &table); 

    int ReadTableAttributes(RegionTable &table); 

    void Close(); 

    void ReadTable(RegionTable &table); 
    
    void GetMinMaxHoleNumber(UInt &minHole, UInt &maxHole);
};


#endif
