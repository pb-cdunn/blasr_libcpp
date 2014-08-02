#ifndef _BLASR_FASTA_SEQUENCE_HPP_
#define _BLASR_FASTA_SEQUENCE_HPP_

#include <string>
#include <iostream>
#include <stdint.h>
#include <string>
#include <cstring>
#include <ostream>
#include "Types.h"
#include "NucConversion.hpp"
#include "Enumerations.h"
#include "DNASequence.hpp"
#include "reads/ZMWGroupEntry.hpp"

//
// NO proteins for now.
class FASTASequence : public DNASequence {
public:
    char *title;
    int titleLength;

    FASTASequence();

    void PrintSeq(std::ostream &out, int lineLength = 50, char delim='>');

    int GetStorageSize();

    std::string GetName();

    bool StoreHoleNumber(int holeNumber);
    bool StoreHoleStatus(unsigned char holeStatus);
    bool StorePlatformId(PlatformId platformId);
    bool StoreZMWData(ZMWGroupEntry &data);
    bool GetHoleNumber (int &holeNumberP); 

    bool StoreXY(int16_t xy[]);

    bool GetXY(int xyP[]); 

    void ShallowCopy(const FASTASequence &rhs); 

    std::string GetTitle() const; 

    void CopyTitle(const char* str, int strlen); 

    void CopyTitle(std::string str);

    void GetFASTATitle(std::string& fastaTitle); 

    void CopySubsequence(FASTASequence &rhs, int readStart, int readEnd=-1); 

    void AppendToTitle(std::string str); 

    void Assign(FASTASequence &rhs); 

    void MakeRC(FASTASequence &rhs, DNALength rhsPos=0, DNALength rhsLength=0); 

    void ReverseComplementSelf(); 

    void operator=(const FASTASequence &rhs); 

    void Copy(const FASTASequence &rhs); 

    void Free(); 
};


#endif
