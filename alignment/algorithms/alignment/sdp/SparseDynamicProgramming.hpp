#ifndef SPARSE_DYNAMIC_PROGRAMMING_H_
#define SPARSE_DYNAMIC_PROGRAMMING_H_

#include <vector>
#include <string>
#include "Types.h"
#include "defs.h"
#include "DNASequence.hpp"
#include "datastructures/alignment/Alignment.hpp"
#include "algorithms/alignment/AlignmentUtils.hpp"

/*******************************************************************************
 *  Sparse dynamic programming implementation of Longest Common Subsequence
 *  
 *  Implementation of method described in Baker and Giancarlo, Journal of
 *  Algorithms 42, 231-254, 2002.
 * 
 *  5/7/09 -- Modified to incorporate different linear cost functions, and 
 *  local alignments.
 *  
 ******************************************************************************/

int IndelPenalty(int x1, int y1, int x2, int y2, int insertion, int deletion); 

template<typename T_Fragment>
void StoreAbove(std::vector<T_Fragment> &fragmentSet, DNALength fragmentLength);

template<typename T_Fragment>
int SDPLongestCommonSubsequence(DNALength queryLength,
        std::vector<T_Fragment> &fragmentSet, 
        DNALength fragmentLength,
        int insertion, int deletion, int match,
        std::vector<int> &maxFragmentChain, AlignmentType alignType=Global); 

#include "SparseDynamicProgrammingImpl.hpp"

#endif
