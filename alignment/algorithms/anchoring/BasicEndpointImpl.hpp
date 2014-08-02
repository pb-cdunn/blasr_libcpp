#ifndef _BLASR_BASIC_ENDPOINT_IMPL_HPP_
#define _BLASR_BASIC_ENDPOINT_IMPL_HPP_

#include "algorithms/anchoring/BasicEndpoint.hpp"
/*
 An endpoint is one of the ends of a fragment, where
 a fragment is an exact match between two genomes. 
 So, a fragment is a 2D object that has a position and length,
 and an endpoint is 1D, where it just has a position.
 A fragment may be associated with a score that is the score
 of the fragment in a maximum scoring chain.  When finding a 
 maximum scoring chain using priority search trees, one must 
 be able to set the score of a fragment when indexing solely 
 a point. 
*/

template<typename T_ScoredFragment>
BasicEndpoint<T_ScoredFragment>::
BasicEndpoint(){}

template<typename T_ScoredFragment>
WhichEnd BasicEndpoint<T_ScoredFragment>::
GetSide() {return side;}

template<typename T_ScoredFragment>
void BasicEndpoint<T_ScoredFragment>::
FragmentPtrToStart(T_ScoredFragment *fragment) {
    p.SetX(fragment->GetX());
    p.SetY(fragment->GetY());
    side = Start;
    fragmentPtr = fragment;
}

template<typename T_ScoredFragment>
void BasicEndpoint<T_ScoredFragment>::FragmentPtrToEnd(
    T_ScoredFragment *fragment) {
    p.SetX(fragment->GetX() + fragment->GetLength());
    p.SetY(fragment->GetY() + fragment->GetLength());
    side = End;
    fragmentPtr = fragment;
}

template<typename T_ScoredFragment>
int BasicEndpoint<T_ScoredFragment>::GetScore() {
    return fragmentPtr->GetScore();
}

template<typename T_ScoredFragment>
int BasicEndpoint<T_ScoredFragment>::SetScore(int score) {
    return (fragmentPtr->SetScore(score));
}

template<typename T_ScoredFragment>
T_ScoredFragment* BasicEndpoint<T_ScoredFragment>::
SetScoredReference(
    T_ScoredFragment *_fragmentPtr) {
    return (fragmentPtr = _fragmentPtr);
}

template<typename T_ScoredFragment>
int BasicEndpoint<T_ScoredFragment>::
operator<(const BasicEndpoint &rhs) const {return p < rhs.p;} 

template<typename T_ScoredFragment>
KeyType BasicEndpoint<T_ScoredFragment>::
GetKey() {return p.GetY();}

template<typename T_ScoredFragment>
T_ScoredFragment* BasicEndpoint<T_ScoredFragment>::
GetFragmentPtr() {return fragmentPtr;}

template<typename T_ScoredFragment>
void BasicEndpoint<T_ScoredFragment>::
SetChainPrev(T_ScoredFragment* prevChainFragment) {
    fragmentPtr->SetChainPrev(prevChainFragment);
}

#endif
