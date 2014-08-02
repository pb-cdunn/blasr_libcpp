#include "AlignmentStats.hpp"

using namespace blasr;

AlignmentStats::AlignmentStats() {
    nMatch = nMismatch = nIns = nDel = 0;
    pctSimilarity = 0.0;
    mapQV = 0;
    score = 0;
}

AlignmentStats& AlignmentStats::Assign(const AlignmentStats &rhs) {
    nMatch = rhs.nMatch;						  		
    nMismatch = rhs.nMismatch;				 
    nIns = rhs.nIns;							  
    nDel = rhs.nDel;							  
    pctSimilarity = rhs.pctSimilarity;
    score = rhs.score;             
    return *this;
}

AlignmentStats& AlignmentStats::operator=(const AlignmentStats &rhs) {
    Assign(rhs);
    return *this;
}   

void AlignmentStats::CopyStats(AlignmentStats rhs) {
    *this = rhs;
  }
