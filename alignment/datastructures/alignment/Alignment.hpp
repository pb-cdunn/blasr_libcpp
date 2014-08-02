#ifndef _BLASR_ALIGNMENT_HPP_
#define _BLASR_ALIGNMENT_HPP_

#include "Path.h"
#include <vector>
#include <string>
#include "DNASequence.hpp"
#include "datastructures/alignment/AlignmentStats.hpp"

namespace blasr {
class Block {
public:
    //
    // An alignment is a collection of blocks. The qPos and tPos in a block
    // is relative to the beginning of the alignment rather than the
    // target or query.
    //
    DNALength qPos, tPos, length;
    friend std::ostream &operator<<(std::ostream &out, const Block &b);

    Block& Assign(Block &rhs);

    DNALength QEnd(); 

    DNALength TEnd();

    void Clear(); 
};

class Gap {
public:
    enum GapSeq {Query, Target};
    GapSeq seq;
    int length;
    Gap();
    Gap(GapSeq seqP, int lengthP); 
};

typedef std::vector<Gap> GapList;

class Alignment : public AlignmentStats {
public:
    // the FASTA titles of each sequence
    std::string qName, tName;

    // Strands represented in the alignment, 0=forward, 1=reverse
    int qStrand, tStrand;

    // The starting pos in the text and query of the start of the 
    // alignment, in the window that is matched.
    DNALength qPos, tPos;
    DNALength  qAlignLength;
    DNALength tAlignLength;
    DNALength qLength;
    DNALength tLength;

    double probability;
    float zScore;
    float probScore;
    int   sumQVScore; 
    int   nCells;
    int   nSampledPaths;
    std::vector<Block> blocks;
    std::vector<GapList> gaps;

    Alignment();

    void CopyStats(Alignment &rhs);

    // 
    // The position in the query is qPos + block[i].qPos
    // and the position in the text is tPos + block[i].tPos
    //
    void Clear();

    Alignment& operator=(const Alignment &rhs);

    unsigned int size(); 

    void Assign(Alignment &rhs);

    int ComputeNumAnchors(int minAnchorSize, int &nAnchors, int &nAnchorBases);

    void AllocateBlocks(int nBlocks); 

    void AppendAlignmentGaps(Alignment &next, bool mergeFirst=false); 

    void AppendAlignmentBlocks(Alignment &next, int qOffset = 0, int tOffset = 0); 

    void AppendAlignment(Alignment &next); 

    /*
       Transform the series of operations in an optimal dynamic
       programming path to a block representation of the alignment.

       Since it is possible to have an adjacent insertion and deletion,
       the gap blocks are tracked in addition to the match blocks.
       */

    void ArrowPathToAlignment(std::vector<Arrow> &optPath); 

    //
    // samtools / picard do not like the pattern
    // insertion/deletion/insertion (or the opposite).  To get around
    // this, reorder the idi patterns to iid (or did to idd).  This
    // produces the same scoring alignment, however it is reordered so
    // that Picard / samtools accepts the alignments.
    //
    void OrderGapsByType(); 

    //
    // Transform an alignment that has up to one long gap in it to a
    // block based alignment.

    void LongGapArrowPathToAlignment(std::vector<Arrow> &optPath, DNALength lengthOfLongGap); 

    //
    // The length of the aligned sequence in the query.
    //
    DNALength QEnd(); 

    //
    // The lenght of the aligned sequence in the target.
    //
    DNALength TEnd(); 

    DNALength GenomicTBegin(); 

    DNALength GenomicTEnd(); 

    //
    // Some programs do not accept alignments that have gaps at their
    // ends.  This is used to trim gaps at the ends of alignments (even
    // if the structure represents an acceptable alignment).
    //

    void RemoveEndGaps();

};

//
// This data structure holds two things: alignments, of course, and in addition
// the coordinates of sequences that are successively refined in order to produce 
// the alignment.  This is somewhat tricky when the target genome has been
// transformed by some noise-reducing function phi(t). 
//
// Before aligning a read, it is first mapped to the genome, or transformed 
// then mapped to the transformed genome.  Because the mapping is inexact, the
// region a read is mapped to is typically much larger than the read.  
// The coordinates of the mapped region are stored in tStart and tEnd
// Alignments are performed in native nucleotide space (not transformed).

// For now, the query is always qStart=0, qEnd = queryLength.


//
// When mapping a read to a set of concatenated chromosomes, each chromosome
// has an offset into the file.  Therefore though a sequence may be aligned 
// to a region starting at tStart, the relative offset into the chromosome
// is tStart - tChromOffset.  This is used when printing the coordinates of a match.
//
class MatchedAlignment : public Alignment {
public: 
    int refIndex;
    int readIndex;
    DNALength tStart, tEnd, qStart, qEnd;
    int tChromOffset;

    MatchedAlignment &Assign(MatchedAlignment &rhs); 
};


/*
 *  Create a structure for storing the information output by compare sequences.
 *  Namely, the two string representations of the alignment.
 */
class CompSeqAlignment : public Alignment {
    public:
        std::string tString, qString, alignString;
};

} // namespace blasr

#endif // _BLASR_ALIGNMENT_HPP_
