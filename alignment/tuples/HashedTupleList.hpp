#ifndef _BLASR_HASHED_TUPLE_LIST_HPP_
#define _BLASR_HASHED_TUPLE_LIST_HPP_

#include "tuples/TupleList.hpp"
#include "tuples/TupleMetrics.hpp"
#include "DNASequence.hpp"

template<typename T_Tuple>
class HashedTupleList {
public:
    long mask;
    std::vector<TupleList<T_Tuple> > hashTable;
    int hashLength;
    int hashTableLength;
    typedef T_Tuple Tuple;

    //
    // Provide a default constructor with a small 
    // tuple size for testing.
    //
    HashedTupleList();

    void Initialize(int _hashLength);

    HashedTupleList(int _hashLength);

    void clear();

    void Clear();

    void Sort();

    void Append(T_Tuple tuple);

    void Insert(T_Tuple tuple);

    int Find(T_Tuple tuple);

    void Print();

    //
    // Provide a version of find that stores easy access to 
    // the original tuple.
    //
    int Find(T_Tuple tuple, int &hashValue, int &index);

    void FindAll(T_Tuple &tuple, 
        typename std::vector<T_Tuple>::const_iterator &firstPos, 
        typename std::vector<T_Tuple>::const_iterator &endPos);

    int GetHashLength();
};


template<typename T_Tuple>
void SequenceToHash(DNASequence &seq, HashedTupleList<T_Tuple> &hash, 
    TupleMetrics &tm);

#include "tuples/HashedTupleList.hpp"

#endif
