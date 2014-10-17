#include "utils/RegionUtils.hpp"

// General functions.
bool LookupHQRegion(int holeNumber, RegionTable &regionTable, 
    int &start, int &end, int &score) {

	int regionLowIndex, regionHighIndex;
	regionLowIndex = regionHighIndex = 0;

	regionTable.LookupRegionsByHoleNumber(holeNumber,
        regionLowIndex, regionHighIndex);

	bool readHasGoodRegion = true;
	int  regionIndex = regionLowIndex;
	while (regionIndex < regionHighIndex and 
		   regionTable.GetType(regionIndex) != HQRegion) {
		regionIndex++;
	}
	
	if (regionIndex == regionHighIndex) {
    start = end = score = 0;
		return false;
	}
	else {
		start = regionTable.GetStart(regionIndex);
		end   = regionTable.GetEnd(regionIndex);
        score = regionTable.GetScore(regionIndex);
		return true;
	}
}

// Functions of class CompareRegionIndicesByStart.
int CompareRegionIndicesByStart::
operator()(const int a, const int b) const {
    if (regionTablePtr->GetStart(a) == regionTablePtr->GetStart(b)) {
        return (regionTablePtr->GetEnd(a) < regionTablePtr->GetEnd(b));
    }
    else {
        return (regionTablePtr->GetStart(a) < regionTablePtr->GetStart(b));
    }
}

// General functions.
int SortRegionIndicesByStart(RegionTable &regionTable, 
    std::vector<int> &indices) {

    CompareRegionIndicesByStart cmpFctr;
    cmpFctr.regionTablePtr = &regionTable;
    std::sort(indices.begin(), indices.end(), cmpFctr);
    return indices.size();
}


// Functions of OrderRegionsByReadStart:
int OrderRegionsByReadStart::
operator()(const ReadInterval &lhs, const ReadInterval &rhs) const {
    return lhs.start < rhs.start;
}


// General functions.
int FindRegionIndices(unsigned int holeNumber, RegionTable *regionTablePtr,
    int &regionLowIndex, int &regionHighIndex) {

    int regionIndex;						 
    regionLowIndex = regionHighIndex = 0;

    regionTablePtr->LookupRegionsByHoleNumber(holeNumber, 
        regionLowIndex, regionHighIndex);  

    return regionHighIndex - regionLowIndex;
}


int FindRegionIndices(SMRTSequence &read, RegionTable *regionTablePtr, 
    int &regionLowIndex, int &regionHighIndex) {
    return FindRegionIndices(read.zmwData.holeNumber, 
        regionTablePtr, regionLowIndex, regionHighIndex);
}


//
// Collect region indices for either all region types, or just a few specific region types.
//
//
int CollectRegionIndices(SMRTSequence &read, RegionTable &regionTable, 
    std::vector<int> &regionIndices, RegionType *regionTypes,
    int numRegionTypes) {

    int regionLow, regionHigh;
    int prevNumRegionIndices = regionIndices.size();
    if (FindRegionIndices(read, &regionTable, regionLow, regionHigh)) {
        int i;
        for (i = regionLow; i < regionHigh; i++) {
            if (regionTypes == NULL) {
                regionIndices.push_back(i);
            }
            else {
                int t;
                for (t = 0; t < numRegionTypes; t++) {
                    if (regionTable.GetType(i) == regionTypes[t]) {
                        regionIndices.push_back(i);
                        break;
                    }
                }
            }
        }
    }
    return regionIndices.size() - prevNumRegionIndices;
}


// Given a vecotr of ReadInterval objects and their corresponding 
// directions, intersect each object with an interval 
// [hqStart, hqEnd), if there is no intersection or the intersected
// interval is less than minIntervalLength, remove this object and
// their corresponding directions; otherwise, replace this object 
// with the intersected interval and keep their directions. 
// Return index of the (left-most) longest subread interval in the
// updated vector.
int GetHighQualitySubreadsIntervals(
    std::vector<ReadInterval> & subreadIntervals, 
    std::vector<int> & subreadDirections, 
    int hqStart, int hqEnd, int minIntervalLength) {

   // Avoid using vector.erase() when possible, as it is slow.
    int ret = -1;
    int maxLength = 0;
    assert(subreadIntervals.size() == subreadDirections.size());
    std::vector<ReadInterval> subreadIntervals2; 
    std::vector<int> subreadDirections2;
    for(int i = 0; i < int(subreadIntervals.size()); i++) {
        int & thisStart = subreadIntervals[i].start;
        int & thisEnd   = subreadIntervals[i].end;
        int & thisScore = subreadIntervals[i].score;

        if (thisStart >= hqEnd or thisEnd <= hqStart) {
            continue;
        } 
        if (thisStart < hqStart and thisEnd > hqStart) {
            thisStart = hqStart;
        }
        if (thisStart < hqEnd   and thisEnd > hqEnd  ) {
            thisEnd   = hqEnd;
        }
        if (thisEnd - thisStart >= minIntervalLength) {
            if (maxLength < thisEnd - thisStart) {
                ret = subreadIntervals2.size();
                maxLength = thisEnd - thisStart;
            }
            subreadIntervals2.push_back(subreadIntervals[i]);
            subreadDirections2.push_back(subreadDirections[i]);
        }
    }
    subreadIntervals  = subreadIntervals2;
    subreadDirections = subreadDirections2;
    return ret;
}


// Given a vector of subreads and a vector of adapters, return 
// indices of all fullpass subreads in the input subreads vector.
std::vector<int> 
GetFullPassSubreadIndices(std::vector<ReadInterval> & subreadIntervals,
                          std::vector<ReadInterval> & adapterIntervals) {
    std::vector<int> indices; // Indices of fullpass subread.
    for(int i = 0; i < subreadIntervals.size(); i++) {
        ReadInterval & subread = subreadIntervals[i];
        bool ladapter = false, radapter = false;
        for(int j = 0; j < adapterIntervals.size(); j++) {
            ReadInterval & adapter = adapterIntervals[j];
            if (abs(subread.start - adapter.end) < 10) {
                ladapter = true;
            } else if(abs(subread.end - adapter.start) < 10) {
                radapter = true;
            }
            if (ladapter && radapter) {
                indices.push_back(i);
                break;
            }
        }
    }
    return indices;
}

bool cmp_index_len_pair(std::pair<int, int> x, std::pair<int, int> y) { 
    if (x.second == y.second) {
        return x.first < y.first;
    } else 
    return x.second < y.second;
}

// Given a vector of subreads and a vector of adapters, return
// index of the (left-most) longest subread which has both
// adapters before & after itself. If no full-pass subread available, 
// return -1;
int GetLongestFullSubreadIndex(std::vector<ReadInterval> & subreadIntervals,
                               std::vector<ReadInterval> & adapterIntervals) {

    std::vector<int> indices = GetFullPassSubreadIndices(subreadIntervals, adapterIntervals);
    if (indices.size() == 0)
        return -1;
    std::vector<std::pair<int, int>> indices_lens;

    for (int i = 0; i < indices.size(); i++) {
        ReadInterval & subread = subreadIntervals[indices[i]];
        indices_lens.push_back(std::make_pair(indices[i], subread.end - subread.start));
    }

    std::sort(indices_lens.begin(), indices_lens.end(), cmp_index_len_pair);
    return indices_lens[int(indices_lens.size()-1)].first;
}

    
// Given a vector of subreads and a vector of adapters, return
// index of the typical fullpass subread which can represent subreads
// of this zmw.
// * if there is no fullpass subread, return -1;
// * if number of fullpass subreads is less than 4, return index of the 
//   left-most longest subread
// * if number of fullpass subreads is greater than or equal 4, 
//   * if length of the longest read does not exceed 
//      meanLength + 1.96 * deviationLength
//     then, return index of the longest left-most subread 
//   * otherwise, return index of the second longest left-most subread
int GetTypicalFullSubreadIndex(std::vector<ReadInterval> & subreadIntervals,
                               std::vector<ReadInterval> & adapterIntervals) {

    std::vector<int> indices = GetFullPassSubreadIndices(subreadIntervals, adapterIntervals);
    if (indices.size() == 0)
        return -1; // no full-pass subread in this zmw
    std::vector<std::pair<int, int>> indices_lens;
    std::vector<int> lengths;

    for (int i = 0; i < indices.size(); i++) {
        ReadInterval & subread = subreadIntervals[indices[i]];
        indices_lens.push_back(std::make_pair(indices[i], subread.end - subread.start));
        lengths.push_back(subread.end - subread.start);
    }

    std::sort(indices_lens.begin(), indices_lens.end(), cmp_index_len_pair);

    int longestIndex = indices_lens[int(indices_lens.size()-1)].first; 
    int secondLongestIndex = (indices_lens.size() <= 1)?(-1): (indices_lens[int(indices_lens.size()-2)].first);

    if (indices.size() < 4) { 
        // very few fullpass subreads, use the longest subread anyway.
        return longestIndex;
    } else { 
        // if length of the longest falls out of 95% CI of all other 
        // fullpass subreads, use the second longest. 
        sort(lengths.begin(), lengths.end());
        float meanLength, varLength;
        MeanVar(lengths, meanLength, varLength);
        if (lengths[int(lengths.size()-1)] > meanLength + 1.96 * sqrt(varLength)) {
            return secondLongestIndex;
        } else {
            return longestIndex;
        }
    }
}


// Given a vector of subreads and a vector of adapters, return
// index of the median length subread which has both
// adapters before & after itself. If no full-pass subreads are
// available, return -1.
int GetMedianLengthFullSubreadIndex(
    std::vector<ReadInterval> & subreadIntervals,
    std::vector<ReadInterval> & adapterIntervals) {

    std::vector<int> indices = GetFullPassSubreadIndices(subreadIntervals, adapterIntervals);
    if (indices.size() == 0)
        return -1;
    std::vector<std::pair<int, int>> indices_lens;

    for (int i = 0; i < indices.size(); i++) {
        ReadInterval & subread = subreadIntervals[indices[i]];
        indices_lens.push_back(std::make_pair(indices[i], subread.end - subread.start));
    }
    std::sort(indices_lens.begin(), indices_lens.end(), cmp_index_len_pair);
    return indices_lens[int(indices_lens.size()/2)].first;
}

// Create a vector of n directions consisting of interleaved 0 and 1s.
void CreateDirections(std::vector<int> & directions, const int & n) {
    directions.clear();
    directions.resize(n);
    for(int i = 0; i < n; i++) {
        directions[i] = i % 2;
    }
}

// Flop all directions in the given vector, if flop is true.
void UpdateDirections(std::vector<int> & directions, bool flop) { 
    if (not flop) return;
    for (int i = 0; i < int(directions.size()); i++) {
        assert(directions[i] == 0 or directions[i] == 1);
        directions[i] = (directions[i] == 0)?1:0;
    }
}

