#ifndef _BLASR_SDP_SET_HPP_
#define _BLASR_SDP_SET_HPP_


/*
	A SDPSet is a collection of types T that have strict ordering
	defined.  It supports ways to query for points immediately less or 
	immediately greater than another value.
*/
	
template<typename T>
class SDPSet {
private:
    typedef std::set<T> Tree;
    typename SDPSet<T>::Tree tree;
public:
    int size();

    /*
     * Remove a fragment f if it exists.
     */
    int Delete(T &f); 

    /*
     * Insert a fresh copy of f into the set.  If a copy
     * already exists, replace it with this one.
     */
    inline VectorIndex Insert(T &f); 

    /*
       Returns true if there is a value such that value == f
     */
    int Member(T &f); 

    int Min(T &f); 

    /*
     * Given f, set succ to be the first value greater than f.
     * Return 1 if such a value exists, 0 otherwise.
     */
    int Successor(T &f, T &succ); 

    /*
     * Given f, set pred to the first value less than f.
     * Returns 1 if such a value exists, 0 otherwise.
     */
    int Predecessor(T &f, T &pred); 
};

#include "SDPSetImpl.hpp"

#endif // _BLASR_SDP_SET_HPP_
