#include <stdint.h>
#include "Types.h"
#include "TupleMask.h"
#include "TupleMetrics.hpp"
#include "BaseTuple.hpp"

ULong BaseTuple::HashPowerOfFour(int nBases, TupleMetrics &tm) {
    //
    // When the hash can fit inside the entire tuple, just return the
    // tuple.
    //
    if (tm.tupleSize > nBases) {
        return tuple;
    }
    else {
        return ((tuple & TupleMask[nBases]) + (tuple % 1063)) % (1 << (nBases*2));
    }
}

int BaseTuple::operator<(const BaseTuple &rhs) const {
    return tuple < rhs.tuple;
}

int BaseTuple::operator==(const BaseTuple &rhs) const {
    return tuple == rhs.tuple;
}

int BaseTuple::operator!= (const BaseTuple &rhs) const {
    return tuple != rhs.tuple;
}

BaseTuple BaseTuple::ShiftLeft(TupleMetrics &tm, ULong shift) {
    tuple = tuple << shift;
    tuple = tuple & tm.tupleMask;
    return *this;
}

BaseTuple BaseTuple::ShiftRight(ULong shift) {
    tuple = tuple >> shift;
    return *this;
}

BaseTuple BaseTuple::Append(ULong val, TupleMetrics &tm, ULong nBits) {
    tuple = tuple << nBits;
    tuple = tuple & tm.tupleMask;
    tuple = tuple + val;
    return *this;
}

long BaseTuple::ToLongIndex() {
    long tempTuple = tuple;
    return tempTuple;
}
