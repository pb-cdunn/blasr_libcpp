#ifndef _SIMULATOR_CDF_MAP_HPP_
#define _SIMULATOR_CDF_MAP_HPP_
#include <algorithm>
#include <vector>
#include <assert.h>
#include "statistics/StatUtils.hpp"

template<typename T_Data>
class CDFMap {
public:
    std::vector<int> cdf;
    std::vector<T_Data> data;
    /* Tests:
     * indices                0 1 2 3 4  5  6
     * lengths:               1 3 5 9 10 10 11
     * lengthHistogram.data:  1 3 5 9 10 11
     * lengthHistogram.cdf :  1 2 3 4 6  7
     *
     * lengths:               1 3 5 9 10 11
     * lengthHistogram.data:  1 3 5 9 10 11
     * lengthHistogram.cdf :  1 2 3 4 5  6
     *
     * lengths:               10
     * lengthHistogram.data:  10
     * lengthHistogram.cdf :  1 
     */ 
     int SelectRandomValue(T_Data &value);

};

template<typename T_Data>
int CDFMap<T_Data>::SelectRandomValue(T_Data &value)
{
    std::vector<int>::iterator search_it;
    assert(cdf.size() >= 0);
    int randomIndex = RandomInt(cdf[cdf.size()-1]);
    search_it = lower_bound(cdf.begin(), cdf.end(), randomIndex);
    assert(search_it != cdf.end());
    int valueIndex = search_it - cdf.begin();
    value = data[valueIndex];
    return valueIndex;
}

#endif
