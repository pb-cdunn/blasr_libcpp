#ifndef _BLASR_MAP_BY_SUFFIX_ARRAY_HPP_
#define _BLASR_MAP_BY_SUFFIX_ARRAY_HPP_

#include <algorithm>
#include "suffixarray/SuffixArray.hpp"
#include "datastructures/anchoring/MatchPos.hpp"
#include "datastructures/anchoring/AnchorParameters.hpp"
#include "algorithms/alignment/SWAlign.hpp"
#include "algorithms/alignment/ScoreMatrices.hpp"

/*
 * Parameters:
 * Eventually this should be strongly typed, since this is specific to
 * suffix array searching on DNASequence read/genome types.
 * reference  - should be of type DNASequence
 * sa         - shuld be of type SuffixArray
 * read       - may be of any DNASequence subclass.
 * tupleSize  - The length of the keyword used to speed up searching.
 * Out:
 *   matchLow - The starting point in the suffix array for the LCP
 *              match for the read at pos p.
 *   matchHigh -The same array but for the upper bound.
 *   saMatchLength - The length of the lcp.
 */
template<typename T_SuffixArray, 
         typename T_RefSequence, 
         typename T_Sequence>
int LocateAnchorBoundsInSuffixArray(T_RefSequence &reference,
	T_SuffixArray &sa, T_Sequence &read, unsigned int minPrefixMatchLength,
	std::vector<DNALength> &matchLow, std::vector<DNALength> &matchHigh,
	std::vector<DNALength> &matchLength, AnchorParameters &params);

template<typename T_SuffixArray, 
         typename T_RefSequence, 
         typename T_Sequence, 
         typename T_MatchPos>
int MapReadToGenome(T_RefSequence &reference,
	T_SuffixArray &sa, T_Sequence &read, 
	unsigned int minPrefixMatchLength,
	vector<T_MatchPos> &matchPosList,
	AnchorParameters &anchorParameters);

#include "algorithms/anchoring/MapBySuffixArrayImpl.hpp"
#endif
