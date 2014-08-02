#include "algorithms/anchoring/BWTSearch.hpp"

int MapReadToGenome(BWT & bwt,
	FASTASequence & seq,
    DNALength subreadStart, DNALength subreadEnd,
    std::vector<ChainedMatchPos> &matchPosList,
	AnchorParameters & params, int &numBasesAnchored, 
    std::vector<DNALength> & spv, 
    std::vector<DNALength> & epv) {
	
    FASTASequence prefix;
    numBasesAnchored = 0;
    if (subreadEnd - subreadStart < params.minMatchLength) {
        return 0;
    }
    else {
        DNALength p;
        prefix.seq = seq.seq;
        for (p = subreadStart + params.minMatchLength; 
             p < subreadEnd; p++) {
            // 
            // Try reusing the vectors between calls - not thread
            // safe replace function call with one that has access 
            // to a buffer class.
            //
            spv.clear(); epv.clear();
            prefix.length = p;
            bwt.Count(prefix, spv, epv);

            DNALength matchLength = spv.size();
            //
            // Keep going without subtracting from zero if there 
            // are no hits.
            //
            if (spv.size() == 0) {
                continue;
            }

            DNALength i;
            std::vector<DNALength> matches;
            while (matchLength >= params.minMatchLength) {
                i = matchLength - 1;

                if (matchLength > 0 and epv[i] >= spv[i]) {
                    // 
                    // Add the positions of the matches here.
                    //
                    matches.clear();
                    if (epv[i] - spv[i] + 1 < params.maxAnchorsPerPosition) {
                        numBasesAnchored++;
                        bwt.Locate(spv[i], epv[i], matches);
                    }
                    break;
                }
                matchLength--;
            }

            // Convert from genome positions to tuples
            DNALength m;
            for (m = 0; m < matches.size(); m++ ) {
                // This if statement is a workaround for a bug
                // that is allowing short matches
                if (matches[m] >= matchLength) {
                    matchPosList.push_back(ChainedMatchPos(
                        matches[m] - matchLength, 
                        p-matchLength, matchLength , 
                        matches.size()));
                }
            }
        }
    }
    return matchPosList.size();
}

int MapReadToGenome(BWT & bwt,
	FASTASequence & seq,
    DNALength start, DNALength end,
	std::vector<ChainedMatchPos> & matchPosList,
	AnchorParameters  & params, int &numBasesAnchored) {
    std::vector<DNALength> spv,epv;  

    return MapReadToGenome(bwt, seq, start, end, matchPosList,
        params, numBasesAnchored, spv, epv);
}

