#ifndef  _BLASR_DNA_SEQUENCE_HPP_
#define  _BLASR_DNA_SEQUENCE_HPP_

#include <stdint.h>
#include <ostream>
#include <string>
#include <cassert>
#include "NucConversion.hpp"

typedef uint32_t DNALength;
typedef unsigned char Nucleotide;

class DNASequence {
public:
    DNALength length;
    Nucleotide *seq;
    int bitsPerNuc;
    bool deleteOnExit;

    inline DNASequence();

    //--- functions ---//
    
    DNALength size();

    void TakeOwnership(DNASequence &rhs);

    void Append(const DNASequence &rhs, DNALength appendPos=0);

    DNASequence &Copy(const DNASequence &rhs, DNALength rhsPos=0, DNALength rhsLength=0);

    void ShallowCopy(const DNASequence &rhs);

    int GetStorageSize();

    DNASequence &operator=(const DNASequence &rhs);

    void Print(std::ostream &out, int lineLength = 50);

    void PrintSeq(std::ostream &out, int lineLength = 50);

    void Allocate(DNALength plength);

    void ReferenceSubstring(const DNASequence &rhs, DNALength pos=0, int substrLength=0); 

    DNALength MakeRCCoordinate(DNALength forPos );

    inline void CopyAsRC(DNASequence &rc, DNALength pos=0, DNALength rcLength =0);

    void MakeRC(DNASequence &rc, DNALength pos=0, DNALength rcLength=0);

    void ToTwoBit();

    inline void ToThreeBit();

    void ToFourBit();

    void ConvertThreeBitToAscii();

    void ToAscii();

    void Assign(DNASequence &ref, DNALength start=0, DNALength plength=0);

    void ToLower();

    void ToUpper(); 

    void Concatenate(const Nucleotide *moreSeq, DNALength moreSeqLength); 

    std::string GetTitle() const; 

    void Concatenate(const Nucleotide* moreSeq);

    void Concatenate(DNASequence &seq); 

    int Compare(DNALength pos, DNASequence &rhs, DNALength rhsPos, DNALength length); 

    int LessThanEqual(DNALength pos, DNASequence &rhs, DNALength rhsPos, DNALength length); 

    int Equals(DNASequence &rhs, DNALength rhsPos, DNALength length, DNALength pos=0 ); 

    int LessThan(DNALength pos,  DNASequence &rhs, DNALength rhsPos, DNALength length); 

    void CleanupASCII(); 

    Nucleotide operator[](int i) {
        return seq[i];
    }

    Nucleotide GetNuc(DNALength i); 

    DNALength GetRepeatContent(); 

    void CleanupOnFree();

    void FreeIfControlled(); 

    virtual void Free(); 

    void Resize(DNALength newLength);

    DNALength GetSeqStorage();
};

inline DNASequence::DNASequence() {
    seq = NULL;
    length = 0;
    bitsPerNuc = 8;
    deleteOnExit = false;
}

inline void DNASequence::ToThreeBit() {
    DNALength i;
    if (bitsPerNuc != 3) 
        for (i = 0; i < length; i++) { seq[i] = ThreeBit[seq[i]]; }
    bitsPerNuc = 3;
}

inline void DNASequence::CopyAsRC(DNASequence &rc, DNALength pos, DNALength rcLength) {
    //
    // Different way of acocunting for position. The position is on
    // the rc strand, not the forward strand.
    //
    if (rcLength == 0) {
        rcLength = length - pos;
    }
    DNALength rcStart = length - (pos + rcLength);
    rc.Resize(rcLength);
    DNALength i;
    for (i = 0; i < rcLength; i++) {
        rc.seq[i] = ReverseComplementNuc[seq[rcStart - 1 + (rcLength - i)]];
    }

    // The reverse complement controls its own memory now.
    rc.deleteOnExit = true;
}

template<typename T>
DNALength ResizeSequence(T &dnaseq, DNALength newLength) {
    assert(newLength > 0);
    if (dnaseq.seq != NULL) {
        delete[] dnaseq.seq;
    }
    dnaseq.seq = new Nucleotide[newLength];
    dnaseq.length = newLength;
    dnaseq.deleteOnExit = true;
    return newLength;
}

#endif // _BLASR_DNA_SEQUENCE_HPP_
