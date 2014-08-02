#ifndef _BLASR_HASHED_TUPLE_LIST_IMPL_HPP_
#define _BLASR_HASHED_TUPLE_LIST_IMPL_HPP_

template<typename T_Tuple>
HashedTupleList<T_Tuple>::
HashedTupleList() {
    Initialize(5);
}

template<typename T_Tuple>
HashedTupleList<T_Tuple>::
HashedTupleList(int _hashLength) {
    Initialize(_hashLength);
    cout << hashTable.size() << endl;
}

template<typename T_Tuple>
void HashedTupleList<T_Tuple>::
Initialize(int _hashLength) {
    mask = 0;
    int i;
    hashLength = _hashLength;
    hashTable.resize(1L << (hashLength*2));
    hashTableLength = hashTable.size();

    for (i = 0; i < hashLength; i++ ){
        mask = mask << 2L;
        mask = mask + 3L;
    }
}

template<typename T_Tuple>
void HashedTupleList<T_Tuple>::
clear() {
    // Synonym.
    Clear();
}

template<typename T_Tuple>
void HashedTupleList<T_Tuple>::
Clear() {
    int i;
    for (i = 0; i < hashTableLength; i++ ){ 
        hashTable[i].tupleList.clear();
    }
}


template<typename T_Tuple>
void HashedTupleList<T_Tuple>::
Sort() {
    int i;
    for (i = 0; i < hashTableLength; i++ ){ 
        sort(hashTable[i].tupleList.begin(), 
             hashTable[i].tupleList.end());
    }
}    

template<typename T_Tuple>
void HashedTupleList<T_Tuple>::
Append(T_Tuple tuple) {
    int hashValue = tuple.tuple & mask;
    std::cout << "htl adding " << tuple.tuple << std::endl;
    hashTable[hashValue].tupleList.push_back(tuple);
}


template<typename T_Tuple>
void HashedTupleList<T_Tuple>::
Insert(T_Tuple tuple) {
    std::cout << "htl adding " << tuple.tuple << std::endl;
    int hashValue = tuple.tuple & mask;
    hashTable[hashValue].Insert(tuple);
}

template<typename T_Tuple>
int HashedTupleList<T_Tuple>::
Find(T_Tuple tuple) {
    int hashValue, index;
    return Find(tuple, hashValue, index);
}


template<typename T_Tuple>
void HashedTupleList<T_Tuple>::
Print() {
    int i;
    for (i = 0; i < hashTableLength; i++ ){ 
        hashTable[i].Print();
    }
}

//
// Provide a version of find that stores easy access to 
// the original tuple.
//
template<typename T_Tuple>
int HashedTupleList<T_Tuple>::
Find(T_Tuple tuple, int &hashValue, int &index) {
    hashValue = tuple.tuple & mask;
    if (hashTable[hashValue].size()) {
        return ((index = hashTable[hashValue].Find(tuple)) != -1);
    }
    else {
        return 0;
    }
}


template<typename T_Tuple>
void HashedTupleList<T_Tuple>::
FindAll(T_Tuple &tuple, 
        typename vector<T_Tuple>::const_iterator &firstPos, 
        typename vector<T_Tuple>::const_iterator &endPos ) {
    int hashValue;
    hashValue = tuple.tuple & mask;
    hashTable[hashValue].FindAll(tuple, firstPos, endPos);
}


template<typename T_Tuple>
int HashedTupleList<T_Tuple>::
GetHashLength() {
    return hashLength;
}


template<typename T_Tuple>
void SequenceToHash(DNASequence &seq, HashedTupleList<T_Tuple> &hash, 
    TupleMetrics &tm) {

    int i;
    T_Tuple tuple;
    int res = 0;
    for (i = 0; i < seq.length - hash.hashLength + 1; i++ ) {
        if ((res and 
             (res = tuple.ShiftAddRL(seq.seq[i+tm.tupleSize-1], tm))) or
            (!res and (res = tuple.FromStringRL(&seq.seq[i], tm)))) {
            hash.Insert(tuple);
        }
    }
}

#endif
