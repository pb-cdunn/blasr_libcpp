#ifndef _BLASR_TUPLE_COUNT_TABLE_IMPL_HPP_
#define _BLASR_TUPLE_COUNT_TABLE_IMPL_HPP_

using namespace std;

template<typename TSequence, typename TTuple>
void TupleCountTable<TSequence, TTuple>::InitCountTable(TupleMetrics &ptm) {
    tm = ptm;
    tm.InitializeMask();
    assert(tm.tupleSize > 0);
    // create the mask just in case the ptm is not initialized 
    // properly.
    countTableLength = 4;
    countTableLength = countTableLength << ((tm.tupleSize - 1)*2);
    InitCountTable(countTableLength);
}


template<typename TSequence, typename TTuple>
TupleCountTable<TSequence, TTuple>::TupleCountTable() {
    countTable = NULL;
    countTableLength = 0;
    nTuples = 0;
    deleteStructures = true;
}


template<typename TSequence, typename TTuple>
TupleCountTable<TSequence, TTuple>::~TupleCountTable() {
    if (deleteStructures == false) {
        //
        // Do not delete this if it is referencing another structure
        //
        return;
    }
    if (countTable != NULL) {
        delete [] countTable;
    }
}


template<typename TSequence, typename TTuple>
void TupleCountTable<TSequence, TTuple>::InitCountTable(
    int p_countTableLength ) { 
    countTableLength = p_countTableLength;
    assert(countTableLength > 0);
    countTable = new int[countTableLength];
    fill(&countTable[0], &countTable[countTableLength], 0);
    nTuples = 0;
}


template<typename TSequence, typename TTuple>
void TupleCountTable<TSequence, TTuple>::IncrementCount(
    TTuple &tuple) {
    long tupleIndex = tuple.ToLongIndex();
    assert(tupleIndex < countTableLength);
    countTable[tupleIndex]++;
    ++nTuples;
}


template<typename TSequence, typename TTuple>
void TupleCountTable<TSequence, TTuple>::AddSequenceTupleCountsLR(
    TSequence &seq) {
    VectorIndex i;
    TTuple tuple;
    if (seq.length>= tm.tupleSize) {
        for (i = 0; i < seq.length - tm.tupleSize + 1; i++ ) { 
            if (tuple.FromStringLR(&seq.seq[i], tm)) {
                IncrementCount(tuple);
            }
        }
    }
}


template<typename TSequence, typename TTuple>
void TupleCountTable<TSequence, TTuple>::Write(ofstream &out) {
    out.write((char*) &countTableLength, sizeof(int));
    out.write((char*) &nTuples, sizeof(int));
    out.write((char*) &tm.tupleSize, sizeof(int));
    out.write((char*) countTable, sizeof(int) * countTableLength);
}


template<typename TSequence, typename TTuple>
void TupleCountTable<TSequence, TTuple>::Read(ifstream &in) {
    in.read((char*) &countTableLength, sizeof(int));
    in.read((char*) &nTuples, sizeof(int));
    in.read((char*) &tm.tupleSize, sizeof(int));
    tm.InitializeMask();
    countTable = new int[countTableLength];
    in.read((char*) countTable, sizeof(int) * countTableLength);
}

#endif
