#ifndef _BLASR_LONGEST_INCREASING_SUBSEQUENCE_HPP_
#define _BLASR_LONGEST_INCREASING_SUBSEQUENCE_HPP_

#include <assert.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class RawValue {
	int operator()(T &t) {
		return t;
	}
};

template<typename T, typename F_IntValue>
int BinarySearch(T *x, vector<int> &m, int i, int lenM, F_IntValue IntValue);

template<typename T, typename F_IntValue >
int LongestIncreasingSubset(T *x, int xLength, vector<int> &subsetIndices, 
    vector<int> &m, vector<int> &p, F_IntValue IntValue, 
    int start=0, int end = -1);

template<typename T, typename F_IntValue>
int LongestIncreasingSubset(T*x, int& xLength, vector<int> &subsetIndices);

#include "algorithms/anchoring/LongestIncreasingSubsequenceImpl.hpp"

#endif
