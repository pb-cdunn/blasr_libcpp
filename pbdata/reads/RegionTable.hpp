#ifndef _BLASR_REGION_TABLE_HPP_
#define _BLASR_REGION_TABLE_HPP_

#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include "Enumerations.h"

class RegionAnnotation {
public:
    typedef enum T_AnnotationRow {HoleNumber, RegionType, RegionStart, 
        RegionEnd, RegionScore} AnnotationRow;
    static const int NCOLS=5;
    int row[NCOLS];
    int operator<(const RegionAnnotation &rhs) const; 

    int operator<(int holeNumber); 

    RegionAnnotation& operator=(const RegionAnnotation &rhs); 

    int GetHoleNumber(); 

    int SetHoleNumber(int holeNumber); 

    int GetType(); 

    int SetType(int regionType); 

    int GetStart(); 

    void SetStart(int start); 

    int GetEnd(); 

    void SetEnd(int end); 

    int GetScore(); 

    void SetScore(int score); 
};

class RegionTable {
public:
    std::vector<RegionAnnotation> table;
    std::vector<std::string> columnNames;
    std::vector<std::string> regionTypes;
    std::vector<std::string> regionDescriptions;
    std::vector<std::string> regionSources;
    std::vector<RegionType> regionTypeEnums;

    int LookupRegionsByHoleNumber(int holeNumber, int &low, int &high); 

    //
    // Define a bunch of accessor functions.
    //

    //
    // Different region tables have different ways of encoding regions.
    // This maps from the way they are encoded in the rgn table to a
    // standard encoding.
    //

    RegionType GetType(int regionIndex); 

    int GetStart(int regionIndex); 

    void SetStart(int regionIndex, int start); 

    int GetEnd(int regionIndex); 

    void SetEnd(int regionIndex, int end); 

    int GetHoleNumber(int regionIndex); 

    int SetHoleNumber(int regionIndex, int holeNumber); 

    int GetScore(int regionIndex); 

    int SetScore(int regionIndex, int score); 

    void SortTableByHoleNumber(); 

    void Reset(); 

    void CreateDefaultAttributes(); 
};


#endif // _BLASR_REGION_TABLE_HPP_
