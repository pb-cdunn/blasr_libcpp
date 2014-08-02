#ifndef _BLASR_POS_HPP_
#define _BLASR_POS_HPP_

#include <fstream>
#include <vector>

#include "PackedHash.hpp"

#include "DNASequence.hpp"
#include "Types.h"
#include "utils/BitUtils.hpp"

template< typename T_BWT_Sequence>
class Pos {
public:
    static const unsigned int stride=8;
    PackedHash packedHash;
    std::vector<int> hashCount;
    std::vector<int> fullPos;
    int hasDebugInformation;
    void Write(std::ostream &out) {
        packedHash.Write(out);
    }

    void Read(std::istream &in) {
        packedHash.Read(in);
    }

    void InitializeFromSuffixArray(DNALength suffixArray[], DNALength suffixArrayLength) {
        DNALength p;
        packedHash.Allocate(suffixArrayLength);
        std::fill(hashCount.begin(), hashCount.end(), 0);
        for (p = 0; p < suffixArrayLength; p++ ){
            if (suffixArray[p] % stride==0){
                packedHash.AddValue(p,suffixArray[p]);
            }
        }
    }

    int Lookup(DNALength bwtPos, DNALength &seqPos) {
        return packedHash.LookupValue(bwtPos-1, seqPos);
    }

};


#endif // _BLASR_POS_HPP_
