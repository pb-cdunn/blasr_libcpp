#ifndef _BLASR_READER_AGGLOMERATE_IMPL_HPP_
#define _BLASR_READER_AGGLOMERATE_IMPL_HPP_

template<typename T_Sequence>
int ReaderAgglomerate::GetNext(T_Sequence & seq, int & randNum) {
    randNum = rand();
    return GetNext(seq);
}

template<typename T_Sequence>
int ReadChunkByNReads(ReaderAgglomerate &reader, vector<T_Sequence> &reads, int maxNReads) {
    T_Sequence seq;
    int nReads = 0;
    while(nReads < maxNReads) {
        if (reader.GetNext(seq)) {
            reads.push_back(seq);
            ++nReads;
        }
        else {
            break;
        }
    }
    return nReads;
}

template<typename T_Sequence>
int ReadChunkBySize (ReaderAgglomerate &reader, vector<T_Sequence> &reads, int maxMemorySize) {
    T_Sequence seq;
    int nReads = 0;
    int totalStorage = 0;
    while (totalStorage < maxMemorySize) {
        if (reader.GetNext(seq)) {
            reads.push_back(seq);
            totalStorage += seq.GetStorageSize();
            nReads++;
        }
        else {
            break;
        }
    }
    return nReads;
}

#endif
