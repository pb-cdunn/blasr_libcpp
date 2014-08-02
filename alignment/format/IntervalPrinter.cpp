#include "IntervalPrinter.hpp"

void IntervalOutput::Print(T_AlignmentCandidate &alignment, 
    std::ostream &outFile) {

    int mapQV = alignment.mapQV;
    int lastBlock = alignment.blocks.size()-1;
    if (lastBlock < 0) return;

    outFile << alignment.qName << " " << alignment.tName << " " 
            << alignment.score << " " 
            << alignment.pctSimilarity << " " 
            << alignment.qStrand << " " 
            << alignment.QAlignStart() << " "
            << alignment.QAlignEnd() << " "
            << alignment.qLength << " "
            << alignment.tStrand << " "
            << alignment.TAlignStart() << " "
            << (alignment.tAlignedSeqPos + alignment.tPos
                + alignment.blocks[lastBlock].tPos 
                + alignment.blocks[lastBlock].length) << " "
            << alignment.tLength << " " 
            << mapQV << std::endl;
    //Remove the last four fields from m4 format.
    //<< " " << alignment.nCells << " " << alignment.clusterScore 
    //<< " " << alignment.probScore << " " 
    //<< alignment.numSignificantClusters 
} 

// Print an alignment from a sam file in Interval (m 4) format.
void IntervalOutput::PrintFromSAM(AlignmentCandidate<> &alignment, 
    std::ostream &outFile) {

    int mapQV = alignment.mapQV;
    int lastBlock = alignment.blocks.size()-1;
    if (lastBlock < 0) return;

    outFile << alignment.qName << " " 
            << alignment.tName << " " 
            << alignment.score << " " 
            << alignment.pctSimilarity << " " 
            << alignment.qStrand << " " 
            << alignment.QAlignStart() << " "
            << alignment.QAlignEnd() << " "
            << alignment.qLength << " "
            << alignment.tStrand << " ";

    DNALength tS = alignment.TAlignStart(); 
    DNALength tE = alignment.tAlignedSeqPos + alignment.tPos
                    + alignment.blocks[lastBlock].tPos 
                    + alignment.blocks[lastBlock].length;

    if (alignment.tStrand == 1) {
        // Since the alignment is from a SAM file and the reference 
        // is reverse, compute tS and tE in the coordinate of the reverse
        // complementary sequence
        DNALength tmp = tS;
        tS = alignment.tLength - tE;
        tE = alignment.tLength - tmp;
    }
    outFile << tS << " " << tE << " " << alignment.tLength << " " 
            << mapQV << std::endl;
}

void IntervalOutput::PrintHeader(std::ostream &out) {
    out << "qName tName score percentSimilarity qStrand " 
        << "qStart qEnd qLength tStrand tStart tEnd tLength mapQV" 
        << std::endl;
    //ncells clusterScore probscore numSigClusters" << endl;
}
