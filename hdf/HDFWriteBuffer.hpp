#ifndef _BLASR_HDF_WRITE_BUFFER_HPP_
#define _BLASR_HDF_WRITE_BUFFER_HPP_

#include <cstddef>
#include "utils.hpp"

template<typename T>
class HDFWriteBuffer {
public:
    T         *writeBuffer;
    int       bufferIndex;
    int       bufferSize;

    HDFWriteBuffer() {
        writeBuffer = NULL;
        bufferIndex = 0;
        bufferSize  = 0;
    }

    void InitializeBuffer(int pBufferSize) {
        Free(); // Free before reusing the buffer.
        bufferSize = pBufferSize;
        if (bufferSize > 0) {
            writeBuffer = ProtectedNew<T>(bufferSize);
        }
        else {
            writeBuffer = NULL;
        }
    }		

    void Free() {
        if (writeBuffer) {
            delete[] writeBuffer;
            writeBuffer = NULL;
        }
    }

    ~HDFWriteBuffer() {
        Free();
    }

    void ResetWriteBuffer() {
        bufferIndex = 0;
    }

    bool WriteBufferEmpty() {
        return (bufferIndex == 0);
    }

};


#endif
