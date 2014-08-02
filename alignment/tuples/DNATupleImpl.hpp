#include <cassert>
#include "NucConversion.hpp"

inline int DNATuple::FromStringLR(Nucleotide *strPtr, TupleMetrics &tm) {
    DNASequence tmpSeq;
    tmpSeq.seq = strPtr;
    tmpSeq.length = tm.tupleSize;
    if (!OnlyACTG(tmpSeq))
        return 0;

    if (tm.tupleSize == 0)
        return 1;

    tuple = 0;
    Nucleotide *p;
    Nucleotide *endPtr = &strPtr[tm.tupleSize - 1];
    for (p = strPtr; p != endPtr; p++) {
        // If it is not possible to convert this string, return null.
        if (ThreeBit[*p] > 3) {
            return 0;
        }
        tuple += TwoBit[*p];
        tuple <<=2;
    }
    //
    // The tuple size is guaranteed to be at least 
    // 1, so it's safe to add the last value.
    // This cannot be in the previous loop since
    // the shift shouldn't happen.
    tuple += TwoBit[*p];
    return 1;
}


inline int DNATuple::ShiftAddRL(Nucleotide nuc, TupleMetrics &tm) {
    if (ThreeBit[nuc] > 3) {
        return 0;
    }
    else {
        tuple >>= 2;
        tuple += (TwoBit[nuc] << ((tm.tupleSize-1)*2));
        return 1;
    }
}


template<typename Sequence> 
int SearchSequenceForTuple(Sequence &seq, TupleMetrics &tm, DNATuple &queryTuple) {
    DNALength p;
    PositionDNATuple tempTuple, upperTuple;

    p = 0;
    DNALength cur = 0;
    DNALength curValidEnd = 0;

    //
    // Construct the mask-off bit pair for the shifted tuple.
    //
    PositionDNATuple maskLeftTuple;
    maskLeftTuple.tuple = 3;
    maskLeftTuple.tuple = maskLeftTuple.tuple << 2*tm.tupleSize;
    maskLeftTuple.tuple = ~maskLeftTuple.tuple;
    PositionDNATuple testTuple;
    while (curValidEnd < seq.length) {
        //
        // Search for the next available window that can be translated into a tuple.
        //
        cur = curValidEnd;
        while(curValidEnd < seq.length and IsACTG[seq.seq[curValidEnd]]) {
            curValidEnd++;
        }
        if (curValidEnd - cur >= tm.tupleSize) {
            //
            // Found a span that does not have N's in it, 
            //
            assert (tempTuple.FromStringRL(&(seq.seq[cur]), tm) == 1);
            p = cur;
            if (tempTuple.tuple == queryTuple.tuple) {
                return 1;
            }
            for (p++; p < curValidEnd - tm.tupleSize + 1; p++) {
                tempTuple.tuple >>=2;
                //				tempTuple.tuple &= maskLeftTuple.tuple;
                upperTuple.tuple = TwoBit[seq.seq[p+tm.tupleSize-1]];
                upperTuple.tuple = upperTuple.tuple << (2 * (tm.tupleSize-1));
                tempTuple.tuple += upperTuple.tuple;
                if (tempTuple.tuple == queryTuple.tuple) {
                    return 1;
                }
            }
        }
        else {
            ++curValidEnd;
        }
    }
}


template<typename Sequence>
int SequenceToTupleList(Sequence &seq, TupleMetrics &tm, TupleList<DNATuple> &tupleList) {
    DNALength p;
    PositionDNATuple tempTuple, upperTuple;

    p = 0;
    DNALength cur = 0;
    DNALength curValidEnd = 0;

    //
    // Construct the mask-off bit pair for the shifted tuple.
    //
    PositionDNATuple maskLeftTuple;
    maskLeftTuple.tuple = 3;
    maskLeftTuple.tuple = maskLeftTuple.tuple << 2*tm.tupleSize;
    maskLeftTuple.tuple = ~maskLeftTuple.tuple;
    PositionDNATuple testTuple;
    while (curValidEnd < seq.length) {
        //
        // Search for the next available window that can be translated into a tuple.
        //
        cur = curValidEnd;
        while(curValidEnd < seq.length and IsACTG[seq.seq[curValidEnd]]) {
            curValidEnd++;
        }
        if (curValidEnd - cur >= tm.tupleSize) {
            //
            // Found a span that does not have N's in it, 
            //
            assert (tempTuple.FromStringRL(&(seq.seq[cur]), tm) == 1);
            p = cur;
            tupleList.Append(tempTuple);
            for (p++; p < curValidEnd - tm.tupleSize + 1; p++) {
                tempTuple.tuple >>=2;
                //				tempTuple.tuple &= maskLeftTuple.tuple;
                upperTuple.tuple = TwoBit[seq.seq[p+tm.tupleSize-1]];
                upperTuple.tuple = upperTuple.tuple << (2 * (tm.tupleSize-1));
                tempTuple.tuple += upperTuple.tuple;
                //testTuple.FromStringRL(&seq.seq[p], tm);
                //assert(testTuple.tuple == tempTuple.tuple);
                tupleList.Append(tempTuple);
            }
        }
        else {
            ++curValidEnd;
        }
    }
    return tupleList.size();
}


template<typename Sequence>
int SequenceToTupleList(Sequence &seq, TupleMetrics &tm, TupleList<PositionDNATuple> &tupleList) {
    DNALength p;
    PositionDNATuple tempTuple, upperTuple;

    p = 0;
    DNALength cur = 0;
    DNALength curValidEnd = 0;

    //
    // Construct the mask-off bit pair for the shifted tuple.
    //
    PositionDNATuple maskLeftTuple;
    maskLeftTuple.tuple = 3;
    maskLeftTuple.tuple = maskLeftTuple.tuple << 2*tm.tupleSize;
    maskLeftTuple.tuple = ~maskLeftTuple.tuple;
    PositionDNATuple testTuple;
    while (curValidEnd < seq.length) {
        //
        // Search for the next available window that can be translated into a tuple.
        //
        cur = curValidEnd;
        while(curValidEnd < seq.length and IsACTG[seq.seq[curValidEnd]]) {
            curValidEnd++;
        }
        if (curValidEnd - cur >= tm.tupleSize) {
            //
            // Found a span that does not have N's in it, 
            //
            assert (tempTuple.FromStringRL(&(seq.seq[cur]), tm) == 1);
            p = cur;
            tempTuple.pos = p;
            tupleList.Append(tempTuple);
            for (p++; p < curValidEnd - tm.tupleSize + 1; p++) {
                tempTuple.tuple >>=2;
                //				tempTuple.tuple &= maskLeftTuple.tuple;
                upperTuple.tuple = TwoBit[seq.seq[p+tm.tupleSize-1]];
                upperTuple.tuple = upperTuple.tuple << (2 * (tm.tupleSize-1));
                tempTuple.tuple += upperTuple.tuple;
                tempTuple.pos = p;
                //testTuple.FromStringRL(&seq.seq[p], tm);
                //assert(testTuple.tuple == tempTuple.tuple);
                tupleList.Append(tempTuple);
            }
        }
        else {
            ++curValidEnd;
        }
    }
    return tupleList.size();
}
