#ifndef _BLASR_BASE_CCS_ITERATOR_HPP_
#define _BLASR_BASE_CCS_ITERATOR_HPP_

#include "CCSSequence.hpp"

class CCSIterator {
public:
    CCSSequence *seqPtr;
    int curPass;
    int numPasses;
  
	virtual void Initialize(CCSSequence *_seqPtr);

	virtual int GetNext(int &direction, int &startBase, int &numBases);

   	void Reset();

    int GetNumPasses();
};

#endif
