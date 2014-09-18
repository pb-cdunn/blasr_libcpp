#ifndef _SIMULATOR_QUALITY_SAMPLE_HPP_
#define _SIMULATOR_QUALITY_SAMPLE_HPP_

#include <iostream>
#include "Types.h"
#include "SMRTSequence.hpp"
#include "qvs/QualityValue.hpp"

#define NQV 4
#define NFV 3
#define NT  2

class QualitySample {
public:
	QualityValue qv[NQV];
	HalfWord     frameValues[NFV];
	Nucleotide   tags[NT];

    void CopyFromSequence(SMRTSequence &seq, int pos);
    
    void Write(std::ofstream &out);
   
    void Read(std::ifstream &in);
   
    void CreateFromRead(SMRTSequence &seq, DNALength pos);
};

#endif
