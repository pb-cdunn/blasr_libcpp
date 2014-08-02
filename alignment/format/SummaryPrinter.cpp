#include "SummaryPrinter.hpp"

void SummaryOutput::Print(
    AlignmentCandidate<DNASequence,FASTQSequence> &alignment, 
    std::ostream &outFile) {

    int lastBlock = alignment.blocks.size()-1;
    outFile << alignment.qName << " "
        << alignment.tName << " " 
        << alignment.qStrand << " " 
        << alignment.tStrand << " " 
        << alignment.score << " " 
        << alignment.pctSimilarity << " "
        << alignment.tAlignedSeqPos + alignment.blocks[0].tPos << " " 
        << alignment.tAlignedSeqPos + alignment.blocks[lastBlock].tPos + alignment.blocks[lastBlock].length << " " 
        << alignment.tLength << " "
        << alignment.qAlignedSeqPos + alignment.blocks[0].qPos << " " 
        << alignment.qAlignedSeqPos + alignment.blocks[lastBlock].qPos + alignment.blocks[lastBlock].length << " " 
        << alignment.qLength << " " << alignment.nCells << std::endl;
}

void SummaryOutput::PrintHeader(std::ostream &out) {
    out << "qName tName qStrand tStrand score percentSimilarity tStart tEnd tLength qStart qEnd qLength nCells" 
        << std::endl;
}

