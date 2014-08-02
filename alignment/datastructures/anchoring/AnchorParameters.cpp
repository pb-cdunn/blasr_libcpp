#include "AnchorParameters.hpp"

AnchorParameters::AnchorParameters() {
    branchQualityThreshold = 0;
    minMatchLength         = 0;
    maxMatchScore          = 0;
    expand                 = 0;
    contextAlignLength     = 0;
    useLookupTable         = true;
    numBranches            = 0;
    maxAnchorsPerPosition  = 1000;
    advanceExactMatches    = 0;
    maxLCPLength           = 0; // 0 Defaults to full lcp length
    stopMappingOnceUnique  = false;
    removeEncompassedMatches=false;
    verbosity              = 0;
    lcpBoundsOutPtr        = NULL;
    branchExpand           = 0;
}

AnchorParameters &AnchorParameters::Assign(const AnchorParameters &rhs) {
    //
    // Manually handle assignment in case there is some deep copy
    // that is necessary eventually.
    //
    branchQualityThreshold = rhs.branchQualityThreshold;
    minMatchLength         = rhs.minMatchLength;
    maxMatchScore          = rhs.maxMatchScore;
    expand                 = rhs.expand;
    contextAlignLength     = rhs.contextAlignLength;
    numBranches            = rhs.numBranches;
    maxAnchorsPerPosition  = rhs.maxAnchorsPerPosition;
    advanceExactMatches    = rhs.advanceExactMatches;
    maxLCPLength           = rhs.maxLCPLength;
    stopMappingOnceUnique  = rhs.stopMappingOnceUnique;
    verbosity              = rhs.verbosity;
    removeEncompassedMatches= rhs.removeEncompassedMatches;
    branchExpand           = rhs.branchExpand;
    return *this;
}

AnchorParameters &AnchorParameters::operator=(const AnchorParameters &rhs) {
    return this->Assign(rhs);
}
