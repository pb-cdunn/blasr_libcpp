#ifndef _BLASR_LOOKUP_ANCHOR_DISTRIBUTION_HPP_
#define _BLASR_LOOKUP_ANCHOR_DISTRIBUTION_HPP_

#include "statistics/AnchorDistributionTable.hpp" // not ported

int LookupAnchorDistribution(int readLength, int minMatchLength, 
    int accuracy, float &mn, float &sdn, float &mnab, 
    float &sdnab);

#endif
