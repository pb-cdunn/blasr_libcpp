#ifndef _BLASR_SAMSUPPLEMENTALQVLIST_HPP_
#define _BLASR_SAMSUPPLEMENTALQVLIST_HPP_
#include "SMRTSequence.hpp"
#include "SAMQVConversion.hpp"

class SupplementalQVList {
public:
	enum QVList {Insertion=0x1, Deletion=0x2, Substitution=0x4, Merge=0x8, SubstitutionTag=0x10, DeletionTag=0x20};
	enum QVIndex {I_Insertion=1,I_Deletion=2,I_Substitution=3,I_Merge=4,I_SubstitutionTag=5,I_DeletionTag=6};
	unsigned int useqv;
	void SetDefaultQV() {
		useqv = Insertion | Deletion | Substitution | Merge | SubstitutionTag | DeletionTag;
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
