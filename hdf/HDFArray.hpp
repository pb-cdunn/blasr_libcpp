#ifndef _BLASR_HDF_ARRAY_HPP_
#define _BLASR_HDF_ARRAY_HPP_

#include <assert.h>
#include <iostream>

#include "H5Cpp.h"

#include "HDFConfig.hpp"
#include "HDFData.hpp"
#include "BufferedHDFArray.hpp"
#include "DNASequence.hpp"
#include "FASTQSequence.hpp"

/*
 *
 * Implementation of a 1-D array for IO from an HDF array.
 * This is templated, but specialized for a few data types, so that 
 * the HDF data types do not need to be specified by anybody.
 *
 *  Two examples of the usage of this class follow:
 *
 *	HDFArray<int> nElemArray;
 * 	nElemArray.Initialize(hdfFile, "PulseData/BaseCalls/ZMW/NumEvent");
 *  nElemArray.Read(i, i+1, &nElem);
 *
 * 	HDFArray<unsigned char> qualArray;
 *	qualArray.Initialize(hdfFile, "PulseData/BaseCalls/QualityValue");
 *  qualArray.Read(cur, cur + nElem, qual);
 *
 */

template<typename T>
class HDFArray : public BufferedHDFArray<T> {
public:

    HDFArray() : BufferedHDFArray<T>() {}
    HDFArray(H5::CommonFG* _container, std::string _datasetName) : 
        BufferedHDFArray<T>(_container, _datasetName) {}

    /*
     *  An unbuffered write is simply a write immediately followed by a flush. 
     */
    void WriteToPos(const T*data, int dataLength, UInt writePos) {
        this->writeBuffer = (T*) data;
        this->bufferIndex = dataLength;
        this->bufferSize  = dataLength;
        this->Flush(false, writePos);
        ResetBuffer();
    }

    void ResetBuffer() {
        this->writeBuffer = NULL;
        this->bufferIndex = 0;
        this->bufferSize  = 0;
    }

    void Write(const T *data, int dataLength) {
        this->writeBuffer = (T*) data;
        this->bufferIndex = dataLength;
        this->bufferSize  = dataLength;
        this->Flush();
        //
        // Reset status of buffer so that no methods are tricked into
        // thinking this is a valid pointer.
        //
        ResetBuffer();
    }

    ~HDFArray() {} 
};


class HDFStringArray: public HDFArray<std::string> {
public:
    void Read(UInt start, UInt end, std::string* dest) {
        std::vector<char*> tmpDestCharPtrs;
        if (end == start) return;
        assert(end > start);
        tmpDestCharPtrs.resize(end-start);
        //  ReadCharArray(start, end, (char**) &tmpDestCharPtrs[0]);
        ReadCharArray(start, end, dest);
    }
};
#endif
