#include "algorithms/anchoring/FindMaxInterval.hpp"

unsigned int NumRemainingBases(DNALength curPos, DNALength intervalLength) {
  if (curPos > intervalLength) {
    return 0;
  }
  else {
    return intervalLength - curPos;
  }
}

IntervalSearchParameters::IntervalSearchParameters() {
    advanceHalf         = false;
    globalChainType     = 0;
    maxPValue           = log(0.1);
    aboveCategoryPValue = 0;
    warp                = true;
    fastMaxInterval     = false;
    aggressiveIntervalCut = false;
    verbosity           = 0;
    ddPValueThreshold   = -500; 
}

