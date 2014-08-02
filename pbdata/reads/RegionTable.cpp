#include <algorithm>
#include "RegionTable.hpp"

using namespace std;

int RegionAnnotation::operator<(const RegionAnnotation &rhs) const {
    return row[0] < rhs.row[0];
}

int RegionAnnotation::operator<(int holeNumber) {
    return row[0] < holeNumber;
}

RegionAnnotation& RegionAnnotation::operator=(const RegionAnnotation &rhs) {
    memcpy(row, rhs.row, sizeof(int)*NCOLS);
    return *this;
}
int RegionAnnotation::GetHoleNumber() {
    return row[HoleNumber];
}

int RegionAnnotation::SetHoleNumber(int holeNumber) {
    row[HoleNumber] = holeNumber;
}

int RegionAnnotation::GetType() {
    return row[RegionType];
}

int RegionAnnotation::SetType(int regionType) {
    row[RegionType] = regionType;
}

int RegionAnnotation::GetStart() {
    return row[RegionStart];
}

void RegionAnnotation::SetStart(int start) {
    row[RegionStart] = start;
}
int RegionAnnotation::GetEnd() {
    return row[RegionEnd];
}

void RegionAnnotation::SetEnd(int end) {
    row[RegionEnd] = end;
}

int RegionAnnotation::GetScore() {
    return row[RegionScore];
}

void RegionAnnotation::SetScore(int score) {
    row[RegionScore] = score;
}

int RegionTable::LookupRegionsByHoleNumber(int holeNumber, int &low, int &high) {
    std::vector<RegionAnnotation>::iterator lowIt, highIt;
    lowIt  = std::lower_bound(table.begin(), table.end(), holeNumber);
    highIt = std::lower_bound(table.begin(), table.end(), holeNumber+1);
    low =  lowIt - table.begin();
    high = highIt - table.begin();
    return high-low;
}

//
// Define a bunch of accessor functions.
//

//
// Different region tables have different ways of encoding regions.
// This maps from the way they are encoded in the rgn table to a
// standard encoding.
//

RegionType RegionTable::GetType(int regionIndex) {
    assert(regionIndex < table.size());
    assert(regionIndex >= 0);
    return (RegionType) regionTypeEnums[table[regionIndex].GetType()];
}

int RegionTable::GetStart(int regionIndex) {
    assert(regionIndex < table.size());
    assert(regionIndex >= 0);
    return table[regionIndex].GetStart();
}

void RegionTable::SetStart(int regionIndex, int start) {
    assert(regionIndex < table.size());
    assert(regionIndex >= 0);
    table[regionIndex].SetStart(start);
}

int RegionTable::GetEnd(int regionIndex) {
    assert(regionIndex < table.size());
    assert(regionIndex >= 0);
    return table[regionIndex].GetEnd();
}

void RegionTable::SetEnd(int regionIndex, int end) {
    assert(regionIndex < table.size());
    assert(regionIndex >= 0);
    table[regionIndex].SetEnd(end);
}

int RegionTable::GetHoleNumber(int regionIndex) {
    assert(regionIndex < table.size());
    assert(regionIndex >= 0);
    return table[regionIndex].GetHoleNumber();
}

int RegionTable::SetHoleNumber(int regionIndex, int holeNumber) {
    assert(regionIndex < table.size());
    assert(regionIndex >= 0);
    return table[regionIndex].SetHoleNumber(holeNumber);
}

int RegionTable::GetScore(int regionIndex) {
    assert(regionIndex < table.size());
    assert(regionIndex >= 0);
    return table[regionIndex].row[RegionAnnotation::RegionScore];
}

int RegionTable::SetScore(int regionIndex, int score) {
    assert(regionIndex < table.size());
    assert(regionIndex >= 0);
    return table[regionIndex].row[RegionAnnotation::RegionScore] = score;
}

void RegionTable::SortTableByHoleNumber() {
    std::sort(table.begin(), table.end());
}

void RegionTable::Reset() {
    table.clear();
    columnNames.clear();
    regionTypes.clear();
    regionDescriptions.clear();
    regionSources.clear();
    regionTypeEnums.clear();
}

void RegionTable::CreateDefaultAttributes() {
    columnNames.clear();
    columnNames.push_back("HoleNumber");
    columnNames.push_back("Region type index");
    columnNames.push_back("Region start in bases");
    columnNames.push_back("Region end in bases");
    columnNames.push_back("Region score");

    regionTypes.push_back("Adapter");
    regionTypes.push_back("Insert");
    regionTypes.push_back("HQRegion");

    regionDescriptions.push_back("Adapter Hit");
    regionDescriptions.push_back("Insert Region");
    regionDescriptions.push_back("High Quality bases region. Score is 1000 * "
            "predicted accuracy, where predicted accuary is 0 to 1.0"); 

    regionSources.push_back("AdapterFinding");
    regionSources.push_back("AdapterFinding");
    regionSources.push_back("PulseToBase Region classifer");

    regionTypeEnums.push_back(Adapter);
    regionTypeEnums.push_back(Insert);
    regionTypeEnums.push_back(HQRegion);
}
