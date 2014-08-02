#ifndef _BLASR_COMPARE_SEQUENCES_PRINTER_HPP_
#define _BLASR_COMPARE_SEQUENCES_PRINTER_HPP_

#include <fstream>
#include <iostream>
#include "algorithms/alignment/AlignmentUtils.hpp"

namespace CompareSequencesOutput{

void PrintHeader(std::ostream &out);

template<typename T_Alignment, typename T_QuerySequence, typename T_TargetSequence>
void Print(T_Alignment &alignment, 
    T_QuerySequence &qseq, T_TargetSequence &tseq, 
    std::ostream &out, bool refForward=true);

}

#include "CompareSequencesPrinterImpl.hpp"

#endif
