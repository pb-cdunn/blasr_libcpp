#ifndef _BLASR_HDF_2DARRAY_HPP_
#define _BLASR_HDF_2DARRAY_HPP_

#include "BufferedHDF2DArray.hpp"

template<typename T>
class HDF2DArray : public BufferedHDF2DArray<T> {
public:

    void WriteRow(const T*data, int dataLength, int destRow=-1) {
        this->writeBuffer = (T*) data;
        this->bufferIndex = dataLength;
        this->bufferSize  = dataLength;
        this->Flush(destRow);
        //
        // Reset status of buffer so that no methods are tricked into
        // thinking this is a valid pointer.
        //
        this->writeBuffer = NULL;
        this->bufferIndex = 0;
        this->bufferSize  = 0;
    }
};

#endif
