#ifndef _BLASR_FASTQ_READER_HPP_
#define _BLASR_FASTQ_READER_HPP_

#include "FASTASequence.hpp"
#include "FASTAReader.hpp"
#include "FASTQSequence.hpp"
#include "qvs/QualityValue.hpp"

class FASTQReader : public FASTAReader {
public:

    FASTQReader();

    long GetNext(FASTASequence &seq); 

    unsigned char phredQVtoPacbioQV(unsigned char phredQV);

    int GetNext(FASTQSequence &seq); 

    int Advance(int nSteps); 
};


#endif // _BLASR_FASTQ_READER_HPP_
