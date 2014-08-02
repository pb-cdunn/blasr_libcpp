#ifndef _BLASR_ALIGNMENT_MAP_HPP_
#define _BLASR_ALIGNMENT_MAP_HPP_

class AlignmentMap {
 public:
	int qPos, tPos;
	std::vector<int> alignPos;
};


// Build a map of positions from (unaligned) bases to an aligned sequence
void 
CreateSequenceToAlignmentMap(const std::string & alignedSequence,
        std::vector<int> & baseToAlignmentMap); 


#endif // _BLASR_ALIGNMENT_MAP_HPP_

