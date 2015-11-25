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

#ifndef DATA_HDF_HDF_SCAN_DATA_WRITER_H_
#define DATA_HDF_HDF_SCAN_DATA_WRITER_H_

#include <string>
#include <iostream>
#include "HDFFile.hpp"
#include "HDFGroup.hpp"
#include "HDFAtom.hpp"
#include "Enumerations.h"
#include "reads/ScanData.hpp"
#include "reads/AcqParams.hpp"


class HDFScanDataWriter {
private:
    HDFGroup * rootGroupPtr;
	HDFGroup scanDataGroup;
	HDFGroup acqParamsGroup;
    HDFGroup dyeSetGroup;
	HDFGroup runInfoGroup;

	HDFAtom<std::string> whenStartedAtom;
	HDFAtom<float> frameRateAtom;
	HDFAtom<unsigned int> numFramesAtom;

    HDFAtom<std::string> baseMapAtom;
    HDFAtom<unsigned int> numAnalogAtom;

	HDFAtom<std::string> movieNameAtom;
	HDFAtom<std::string> runCodeAtom;

	HDFAtom<std::string> bindingKitAtom;
	HDFAtom<std::string> sequencingKitAtom;

	HDFAtom<unsigned int> platformIdAtom;
	HDFAtom<std::string> platformNameAtom;

    void CreateAcqParamsGroup();

    void CreateDyeSetGroup();

    void CreateRunInfoGroup();

public:
	HDFScanDataWriter(HDFFile & _outFile);

    HDFScanDataWriter(HDFGroup & _rootGroup);

    ~HDFScanDataWriter();
    
    int Initialize(HDFGroup & _rootGroup);
      
    void Write(const ScanData & scanData);

    void Write(const ScanData & scanData, 
               const AcqParams & acqParam);
   
	void WriteFrameRate(const float frameRate);

    void WriteNumFrames(const unsigned int numFrames);

    void WriteWhenStarted(const std::string whenStarted);

	void Close();
  
private:
    void WriteBaseMap(const std::string baseMapStr);
   
    void WriteNumAnalog(const unsigned int numAnalog);

    void WritePlatformId(const PlatformId id);
   
    void WriteMovieName(const std::string movieName);

    void WriteRunCode(const std::string runCode);

    void WriteBindingKit(const std::string & bindingKit);

    void WriteSequencingKit(const std::string & sequencingKit);

private:
    /// Write attributes to /ScanData/AcqParams
    void _WriteAcqParams(const AcqParams & acqParams);

    void _WriteAduGain(const float aduGain);

    void _WriteCameraGain(const float cameraGain);

    void _WriteCameraType(const int cameraType);

    void _WriteHotStartFrame(const UInt hotStartFrame);

    void _WriteLaserOnFrame(const UInt laserOnFrame);

};

#endif
