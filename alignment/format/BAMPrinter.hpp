#ifndef _BLASR_FORMAT_BAMPRINTER_HPP_
#define _BLASR_FORMAT_BAMPRINTER_HPP_ 

#ifdef USE_PBBAM
#include <sstream>
#include <stdint.h>
#include "format/SAMPrinter.hpp"
#include "pbbam/BamHeader.h"
#include "pbbam/BamWriter.h"

namespace BAMOutput {

template<typename T_Sequence>
void SetAlignedSequence(T_AlignmentCandidate &alignment, T_Sequence &read,
        T_Sequence &alignedSeq);

template<typename T_Sequence>
void CreateCIGARString(T_AlignmentCandidate &alignment,
        T_Sequence &read, std::string &cigarString, const bool cigarUseSeqMatch);

template<typename T_Sequence>
void AlignmentToBamRecord(T_AlignmentCandidate & alignment, 
        T_Sequence & read, PacBio::BAM::BamRecord & bamRecord, 
        AlignmentContext & context, SupplementalQVList & qvList,
        Clipping clipping, bool cigarUseSeqMatch);



template<typename T_Sequence>
void PrintAlignment(T_AlignmentCandidate &alignment, T_Sequence &read,
        PacBio::BAM::BamWriter &bamWriter, AlignmentContext &context, 
        SupplementalQVList & qvList, Clipping clipping, 
        bool cigarUseSeqMatch=false);
}


#include "BAMPrinterImpl.hpp"

#endif
#endif
