#ifndef _BLASR_SHARED_SUFFIX_ARRAY_HPP_
#define _BLASR_SHARED_SUFFIX_ARRAY_HPP_

#include <stdlib.h>
#include <sstream>
#include "SuffixArray.hpp"
#include "ipc/SharedMemoryAllocator.hpp"
#include "tuples/DNATuple.hpp"
#include "tuples/CompressedDNATuple.hpp"
#include "algorithms/compare/CompareStrings.hpp"


template<typename T, 
    typename Sigma,
    typename Compare = DefaultCompareStrings<T>,
    typename Tuple   = DNATuple >
class SharedSuffixArray : public SuffixArray<T, Sigma, Compare, Tuple> {
public:
    std::string shmIdTag;
    SAIndex *indexShared;
    int indexID;
    std::string indexHandle;
    SAIndex *lookupTableShared;
    int lookupTableID;
    std::string lookupTableHandle;
    int lookupPrefixLength;

    void InitShmIdTag() {
        stringstream tagStrm;
        tagStrm << "_" << getpid();
        shmIdTag = tagStrm.str();
    }


    void ReadSharedArray(ifstream &saIn) {
        std::cout << "reading a shared suffix array index." << std::endl;
        saIn.read((char*) &this->length, sizeof(int));
        indexHandle = "suffixarray.index." + shmIdTag;
        AllocateMappedShare(indexHandle, this->length + 1, indexShared, indexID);
        std::cout << "the shared index is: " << indexShared << std::endl;
        this->index = indexShared;
        std::cout << "the index used is: " << this->index << std::endl;
        this->ReadAllocatedArray(saIn);
    }

    void ReadSharedLookupTable(ifstream &saIn) {
        this->ReadLookupTableLengths(saIn);
        lookupTableHandle = "suffixarray.lookuptable." + shmIdTag;
        AllocateMappedShare(lookupTableHandle, this->lookupTableLength + 1, lookupTableShared, lookupTableID);
        this->lookupTable = lookupTableShared;
        this->ReadAllocatedLookupTable(saIn);
    }

    void ReadShared(string &inFileName) {
        ifstream saIn;
        InitShmIdTag();
        saIn.open(inFileName.c_str(), ios::binary);
        this->ReadComponentList(saIn);
        if (this->componentList[SuffixArray<T,Sigma,Compare,Tuple>::CompArray]) {
            this->ReadSharedArray(saIn);
        }
        if (this->componentList[SuffixArray<T,Sigma,Compare,Tuple>::CompLookupTable]) {
            this->ReadSharedLookupTable(saIn);
        }
        saIn.close();
    }

    void FreeShared() {

        if (this->componentList[SuffixArray<T,Sigma,Compare,Tuple>::CompArray]) {
            shm_unlink(indexHandle.c_str());
        }
        if (this->componentList[SuffixArray<T,Sigma,Compare,Tuple>::CompLookupTable]) {
            shm_unlink(lookupTableHandle.c_str());
        }
    }


};


#endif // _BLASR_SHARED_SUFFIX_ARRAY_HPP_
