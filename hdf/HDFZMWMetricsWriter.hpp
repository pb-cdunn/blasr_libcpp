// Copyright (c) 2014-2015, Pacific Biosciences of California, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the
// disclaimer below) provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//  * Neither the name of Pacific Biosciences nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
// GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY PACIFIC
// BIOSCIENCES AND ITS CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL PACIFIC BIOSCIENCES OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
// USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// Author: Yuan Li


#ifndef _BLASR_HDF_HDFZMWMETRICSWriter_HPP_
#define _BLASR_HDF_HDFZMWMETRICSWriter_HPP_

#include "SMRTSequence.hpp"
#include "HDFWriterBase.hpp"
#include "BufferedHDFArray.hpp"
#include "BufferedHDF2DArray.hpp"


class HDFBaseCallerWriter;

class HDFZMWMetricsWriter: public HDFWriterBase {

friend class HDFBaseCallerWriter;
private:
    /// \name Private variable
    /// \{
    HDFGroup & parentGroup_;
    
	HDFGroup zmwMetricsGroup_;

    /// HDF2DArray for writing average SNR within HQRegion.
   	BufferedHDF2DArray<float> hqRegionSNRArray_;

    /// HDFArray for writing read raw accuracy prediction.
   	BufferedHDFArray<float> readScoreArray_;

    /// Map bases (e.g., ACGT) to indices
    std::map<char, size_t> baseMap_;

    int curRow_;

    static const int SNRNCOLS = 4;
    /// \}

public:
    /// \name Constructors and Destructors
    /// \{
    HDFZMWMetricsWriter(const std::string & filename, 
                        HDFGroup & parentGroup,
                        const std::map<char, size_t> & baseMap);

    ~HDFZMWMetricsWriter(void) ;
    /// \}

    /// \name Public Methods
    /// \{
    
    /// \note Write info of a SMRTSequence to ZMWMetrics,
    ///       (1) add average signal to noise ratio in HQRegion to HQRegionSNR 
    ///       (2) add read raw accuracy prediction to ReadScore 
    bool WriteOneZmw(const SMRTSequence & read);


    /// \note Flushes all data from cache to disc.
    void Flush(void);

    /// \note Closes this zmw group as well as child hdf groups.
    void Close(void);
    /// \}

private:
    /// \name Private Methods
    /// \{
    
    /// \note Initialize child hdf groups under ZMWMetrics, including
    ///       HQRegionSNR and ReadScore 
    /// \reutrns bool, whether or not child hdf groups successfully initialized.
    bool InitializeChildHDFGroups(void);

    /// \note Write Attributes.
    bool WriteAttributes(void);
    /// \}
};

#endif
