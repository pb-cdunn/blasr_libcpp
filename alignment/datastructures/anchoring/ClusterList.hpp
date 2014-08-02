#ifndef _BLASR_CLUSTER_LIST_HPP_
#define _BLASR_CLUSTER_LIST_HPP_

#include <vector>
#include "DNASequence.hpp"

class ClusterList {
public:
    std::vector<int> numBases;
    std::vector<int> numAnchors;
    std::vector<unsigned int> startPos;
    std::vector<int> indices;
    int lowerSizeLimit;
    int lowerSizeLimitNumAnchors;
    DNALength curp, cure; // cur - p, and cur - e.
    int curIndex;
    bool onContigStart;

    ClusterList();
    void Clear();
    bool Store(int n, DNALength p, DNALength e, int b);
    void ResetCoordinates();
};

#endif
