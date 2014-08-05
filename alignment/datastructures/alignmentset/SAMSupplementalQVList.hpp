#ifndef _BLASR_SAMSUPPLEMENTALQVLIST_HPP_
#define _BLASR_SAMSUPPLEMENTALQVLIST_HPP_
#include "SMRTSequence.hpp"
#include "SAMQVConversion.hpp"

class SupplementalQVList {
public:
	enum QVList {InsertionQV=0x1, DeletionQV=0x2, SubstitutionQV=0x4, MergeQV=0x8, SubstitutionTag=0x10, DeletionTag=0x20};
	enum QVIndex {I_InsertionQV=1,I_DeletionQV=2,I_SubstitutionQV=3,I_MergeQV=4,I_SubstitutionTag=5,I_DeletionTag=6};
	unsigned int useqv;
	void SetDefaultQV() {
		useqv = InsertionQV | DeletionQV | SubstitutionQV | MergeQV | DeletionTag;
	}
	static const char* qvTags[];
	static const char* qvNames[];
	static int nqvTags;
	static int nTags;

	int UseQV(std::vector<std::string> &qvList);
   	void FormatQVOptionalFields(SMRTSequence &alignedSubsequence);
    	
	void PrintQVOptionalFields(SMRTSequence &alignedSubsequence, std::ostream &out);
    void clear();
};

#endif
