#include "CompareSequencesPrinter.hpp"

void CompareSequencesOutput::PrintHeader(std::ostream &out) {
  out << "qName qLength qStart qEnd qStrand "
      << "tName tLength tStart tEnd tStrand "
      << "score numMatch numMismatch numIns numDel "
      << "mapQV qAlignedSeq matchPattern tAlignedSeq"
      << std::endl;
}

