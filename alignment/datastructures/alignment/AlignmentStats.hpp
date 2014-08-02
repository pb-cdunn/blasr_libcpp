#ifndef _BLASR_ALIGNMENT_STATS_HPP_
#define _BLASR_ALIGNMENT_STATS_HPP_

namespace blasr {
class AlignmentStats {
public:
    int nMatch;
    int nMismatch;
    int nIns;
    int nDel;	 
    float pctSimilarity;
    int score;             
    int mapQV;
    AlignmentStats();
    
    AlignmentStats &Assign(const AlignmentStats &rhs);

    AlignmentStats& operator=(const AlignmentStats &rhs); 

    void CopyStats(AlignmentStats rhs); 

};
}

#endif // _BLASR_ALIGNMENT_STATS_HPP_
