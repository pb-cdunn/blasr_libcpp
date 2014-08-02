#ifndef _BLASR_BASIC_ENDPOINT_HPP_
#define _BLASR_BASIC_ENDPOINT_HPP_

#include "Types.h"
#include "algorithms/anchoring/Coordinate.hpp"
//
// An endpoint is one of the ends of a fragment, where
// a fragment is an exact match between two genomes. 
// So, a fragment is a 2D object that has a position and length,
// and an endpoint is 1D, where it just has a position.
// A fragment may be associated with a score that is the score
// of the fragment in a maximum scoring chain.  When finding a 
// maximum scoring chain using priority search trees, one must 
// be able to set the score of a fragment when indexing solely 
// a point. 
//

enum WhichEnd {Start, End};
typedef UInt KeyType;

template<typename T_ScoredFragment>
class BasicEndpoint {
private:
	Coordinate p;
	WhichEnd side;
    T_ScoredFragment *fragmentPtr;

public:
    class LessThan {
    public:
        int operator()(const BasicEndpoint<T_ScoredFragment> & lhs, const BasicEndpoint<T_ScoredFragment> & rhs) const {
            return lhs.p < rhs.p;
        }
    };
    BasicEndpoint();
	WhichEnd GetSide();
	void FragmentPtrToStart(T_ScoredFragment* fragment);
   	void FragmentPtrToEnd(T_ScoredFragment* fragment);
   	int GetScore();
	int SetScore(int score);
   	T_ScoredFragment* SetScoredReference(T_ScoredFragment* _fragmentPtr);
	int operator<(const BasicEndpoint &rhs) const;
	KeyType GetKey();
	T_ScoredFragment* GetFragmentPtr();
    void SetChainPrev(T_ScoredFragment* prevChainFragment);
};

#include "algorithms/anchoring/BasicEndpointImpl.hpp"

#endif
