#ifndef _BLASR_BASE_TUPLE_HPP_
#define _BLASR_BASE_TUPLE_HPP_

#include "tuples/TupleMetrics.hpp"

class BaseTuple {
public:
    ULong  tuple;

    ULong  HashPowerOfFour(int nBases, TupleMetrics &tm);

    int operator<(const BaseTuple &rhs) const; 

    int operator==(const BaseTuple &rhs) const; 

    int operator!= (const BaseTuple &rhs) const;

    BaseTuple ShiftLeft(TupleMetrics &tm, ULong shift=1L); 

    BaseTuple ShiftRight(ULong shift=1L); 

    BaseTuple Append(ULong val, TupleMetrics &tm, ULong nBits); 

    long ToLongIndex(); 
};

#endif
