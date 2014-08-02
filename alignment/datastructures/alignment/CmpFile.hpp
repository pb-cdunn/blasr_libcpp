#ifndef _BLASR_CMP_FILE_HPP_
#define _BLASR_CMP_FILE_HPP_

#include "reads/ReadType.hpp"
#include "datastructures/alignment/CmpIndexedStringTable.h"
#include "saf/AlnGroup.hpp"
#include "saf/AlnInfo.hpp"
#include "saf/RefGroup.hpp"
#include "saf/RefInfo.hpp"
#include "saf/MovieInfo.hpp"
#include "Enumerations.h"

#include <vector>

class CmpFile {
 public:
	int lastRow;
    std::string readTypeString, index, version, commandLine;
    ReadType::ReadTypeEnum readType;

    void StoreReadType(std::string &readTypeStringP);

    CmpIndexedStringTable readGroupTable, movieNameTable, refSeqTable;
    vector<string> colNames;
    PlatformId platformId;
    AlnGroup  alnGroup;
    AlnInfo   alnInfo;
    RefGroup  refGroup;
    RefInfo   refInfo;
    MovieInfo movieInfo;
};

#endif
