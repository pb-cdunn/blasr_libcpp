#ifndef _BLASR_DNA_TUPLE_HPP_
#define _BLASR_DNA_TUPLE_HPP_

#include <cassert>
#include <vector>
#include <stdint.h>
#include <ostream>
#include <string>
#include "Types.h"
#include "SeqUtils.hpp"
#include "DNASequence.hpp"
#include "NucConversion.hpp"
#include "tuples/BaseTuple.hpp"
#include "tuples/TupleMetrics.hpp"
#include "tuples/TupleList.hpp"
#include "tuples/TupleOperations.h"

class DNATuple : public BaseTuple {
public:
    DNALength pos;

    inline int FromStringLR(Nucleotide *strPtr, TupleMetrics &tm);

    int FromStringRL(Nucleotide *strPtr, TupleMetrics &tm); 

    inline int ShiftAddRL(Nucleotide nuc, TupleMetrics &tm); 

    int MakeRC(DNATuple &dest, TupleMetrics &tm); 

    std::string ToString(TupleMetrics &tm); 
};

class CompareByTuple {
public:
    bool operator()(const DNATuple &lhs, const DNATuple &rhs) const; 
};


class CountedDNATuple : public DNATuple {
public:
    int count;
};

class PositionDNATuple : public DNATuple {
public:
    PositionDNATuple& operator=(const PositionDNATuple &rhs) {
        pos = rhs.pos;
        tuple = rhs.tuple;
        return *this;
    }

    int operator<(const PositionDNATuple & pTuple) const {
        if (tuple < pTuple.tuple) 
            return 1;
        else if (tuple == pTuple.tuple) 
            return pos < pTuple.pos;
        else 
            return 0;
    }

    int operator==(const PositionDNATuple &pTuple) const {
        return tuple == pTuple.tuple and pos == pTuple.pos;
    }

    int operator<(const DNATuple &pTuple) const {
        return (tuple < pTuple.tuple);
    }

    int operator==(const DNATuple &pTuple) const; 

    int operator!=(const DNATuple &pTuple) const {
        return tuple != pTuple.tuple;
    }

    PositionDNATuple();

    PositionDNATuple(PositionDNATuple &tupleP, DNALength posP); 

};

class OrderPositionDNATuplesByPosition {
public:
    int operator()(const PositionDNATuple &lhs, const PositionDNATuple &rhs) const; 
};

class OrderPositionDNATuplesByTuple {
public:
    int operator()(const PositionDNATuple &lhs, const PositionDNATuple &rhs) const; 
};


template<typename Sequence> 
int SearchSequenceForTuple(Sequence &seq, TupleMetrics &tm, DNATuple &queryTuple); 

template<typename Sequence>
int SequenceToTupleList(Sequence &seq, TupleMetrics &tm, TupleList<DNATuple> &tupleList);

template<typename Sequence>
int SequenceToTupleList(Sequence &seq, TupleMetrics &tm, TupleList<PositionDNATuple> &tupleList); 

#include "DNATupleImpl.hpp"

#endif // _BLASR_DNA_TUPLE_HPP_
