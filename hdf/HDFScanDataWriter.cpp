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

#include "HDFScanDataWriter.hpp"

void HDFScanDataWriter::CreateAcqParamsGroup() {
    if (acqParamsGroup.Initialize(scanDataGroup, "AcqParams") == 0) {
        std::cout << "ERROR could not create /ScanData/AcqParams." << std::endl;
        exit(1);
    }
    frameRateAtom.Create(acqParamsGroup.group, "FrameRate");
    numFramesAtom.Create(acqParamsGroup.group, "NumFrames");
    whenStartedAtom.Create(acqParamsGroup.group, "WhenStarted");
}

void HDFScanDataWriter::CreateDyeSetGroup(){
    if (dyeSetGroup.Initialize(scanDataGroup, "DyeSet") == 0) {
        std::cout << "ERROR could not create /ScanData/DyeSet." << std::endl;
        exit(1);
    }
    baseMapAtom.Create(dyeSetGroup.group, PacBio::AttributeNames::ScanData::DyeSet::basemap);
    numAnalogAtom.Create(dyeSetGroup.group, "NumAnalog");
}

void HDFScanDataWriter::CreateRunInfoGroup(){
    if (runInfoGroup.Initialize(scanDataGroup, "RunInfo") == 0) {
        std::cout << "ERROR, could not create /ScanDta/RunInfo." << std::endl;
        exit(1);
    }
    movieNameAtom.Create(runInfoGroup.group, "MovieName");
    platformIdAtom.Create(runInfoGroup.group, "PlatformId");
    platformNameAtom.Create(runInfoGroup.group, "PlatformName");
    instrumentNameAtom.Create(runInfoGroup.group, "InstrumentName");
    runCodeAtom.Create(runInfoGroup.group, "RunCode");
    bindingKitAtom.Create(runInfoGroup.group, "BindingKit");
    sequencingKitAtom.Create(runInfoGroup.group, "SequencingKit");
}

HDFScanDataWriter::HDFScanDataWriter(HDFFile & _outFile) {
    Initialize(_outFile.rootGroup);
}

HDFScanDataWriter::HDFScanDataWriter(HDFGroup & _rootGroup) {
    Initialize(_rootGroup);
}

HDFScanDataWriter::~HDFScanDataWriter() { 
    this->Close();
}

int HDFScanDataWriter::Initialize(HDFGroup & _rootGroup) {
    rootGroupPtr = &(_rootGroup);
    rootGroupPtr->AddGroup("ScanData"); 
    if (scanDataGroup.Initialize(*(rootGroupPtr), "ScanData") == 0) {
        std::cout << "ERROR, could not create /ScanData group." << std::endl;
        exit(1);
    }
    scanDataGroup.AddGroup("AcqParams");
    scanDataGroup.AddGroup("DyeSet");
    scanDataGroup.AddGroup("RunInfo");

    CreateAcqParamsGroup();
    CreateDyeSetGroup();
    CreateRunInfoGroup();

    return 1;
}

void HDFScanDataWriter::Write(const ScanData & scanData) {
    const float DEFAULT_FRAMERATE        = 75.0;
    const unsigned int DEFAULT_NUMFRAMES = 1000000;
    const std::string DEFAULT_DATE       = "2013-01-01T01:01:01";
    const uint16_t DEFAULT_NUMANALOG     = 4;
    const std::string DEFAULT_MOVIENAME  = "simulated_movie";
    const std::string DEFAULT_RUNCODE    = "simulated_runcode";

    WriteFrameRate((scanData.frameRate==0)?
                   (DEFAULT_FRAMERATE):(scanData.frameRate));
    WriteNumFrames((scanData.numFrames==0)?
                   (DEFAULT_NUMFRAMES):(scanData.numFrames));
    WriteWhenStarted((scanData.whenStarted.empty())?
                     (DEFAULT_DATE):(scanData.whenStarted));

    // Base map is VITAL, must be specified
    if (scanData.BaseMapStr().empty()) {
        assert("ScanData/DyeSet attribute BaseMap MUST be specified." == 0);
    }
    WriteBaseMap(scanData.BaseMapStr()); 
    WriteNumAnalog(DEFAULT_NUMANALOG);

    WriteMovieName((scanData.movieName.empty()?
                   (DEFAULT_MOVIENAME):scanData.movieName));
    WriteRunCode((scanData.runCode.empty())?
                 (DEFAULT_RUNCODE):(scanData.runCode));
    WritePlatformId((scanData.platformId==NoPlatform)?
            (Springfield):(scanData.platformId));

    WriteBindingKit(scanData.BindingKit());
    WriteSequencingKit(scanData.SequencingKit());
    _WriteAcqParams(scanData.GetAcqParams());
}

void HDFScanDataWriter::_WriteAcqParams(const AcqParams & acqParams) {
    _WriteAduGain(acqParams.aduGain_);
    _WriteCameraGain(acqParams.cameraGain_);
    _WriteCameraType(acqParams.cameraType_);
    _WriteHotStartFrame(acqParams.hotStartFrame_);
    _WriteLaserOnFrame(acqParams.laserOnFrame_);
}

void HDFScanDataWriter::WriteFrameRate(const float frameRate) {
    // Write /ScanData/AcqParams/FrameRate attribute.
    frameRateAtom.Write(frameRate);
}

void HDFScanDataWriter::WriteNumFrames(const unsigned int numFrames) {
    // Write /ScanData/AcqParams/NumFrames attribute.
    numFramesAtom.Write(numFrames);
}

void HDFScanDataWriter::WriteWhenStarted(const std::string whenStarted) {
    // Write /ScanData/AcqParams/WhenStarted attribute.
    whenStartedAtom.Write(whenStarted);
}

void HDFScanDataWriter::_WriteAduGain(const float aduGain) {
    HDFAtom<float> aduGainAtom;
    aduGainAtom.Create(acqParamsGroup.group, "AduGain");
    aduGainAtom.Write(aduGain);
    aduGainAtom.Close();
}

void HDFScanDataWriter::_WriteCameraGain(const float cameraGain) {
    HDFAtom<float> cameraGainAtom;
    cameraGainAtom.Create(acqParamsGroup.group, "CameraGain");
    cameraGainAtom.Write(cameraGain);
    cameraGainAtom.Close();
}

void HDFScanDataWriter::_WriteCameraType(const int cameraType) {
    HDFAtom<int> cameraTypeAtom;
    cameraTypeAtom.Create(acqParamsGroup.group, "CameraType");
    cameraTypeAtom.Write(cameraType);
    cameraTypeAtom.Close();
}

void HDFScanDataWriter::_WriteHotStartFrame(const UInt hotStartFrame) {
    HDFAtom<UInt> hotStartFrameAtom;
    hotStartFrameAtom.Create(acqParamsGroup.group, "HotStartFrame");
    hotStartFrameAtom.Write(hotStartFrame);
    hotStartFrameAtom.Close();
}

void HDFScanDataWriter::_WriteLaserOnFrame(const UInt laserOnFrame) {
    HDFAtom<UInt> laserOnFrameAtom;
    laserOnFrameAtom.Create(acqParamsGroup.group, "LaserOnFrame");
    laserOnFrameAtom.Write(laserOnFrame);
    laserOnFrameAtom.Close();
}

void HDFScanDataWriter::WriteBaseMap(const std::string baseMapStr) {
    //Write /ScanData/DyeSet/BaseMap attribute.
    baseMapAtom.Write(baseMapStr);
}

void HDFScanDataWriter::WriteNumAnalog(const uint16_t numAnalog) {
    //Write /ScanData/DyeSet/NumAnalog attribute.
    numAnalogAtom.Write(numAnalog);
}

void HDFScanDataWriter::WritePlatformId(const PlatformId id) {
    //Write /ScanData/RunInfo/Platform attribute.
    std::string name, instrumentName;
    if (id == Springfield) { name = "Springfield"; instrumentName = name;}
    else if (id == Sequel) { name = "SequelAlpha"; instrumentName = "Sequel";}
    else if (id == Astro)  { name = "Astro"; instrumentName = name;}
    else { name = "Unknown"; }
    platformIdAtom.Write(id);
    platformNameAtom.Write(name);
    instrumentNameAtom.Write(instrumentName);
}

void HDFScanDataWriter::WriteMovieName(const std::string movieName) {
    //Write /ScanData/RunInfo/MovieName attribute.
    movieNameAtom.Write(movieName);
}

void HDFScanDataWriter::WriteRunCode(const std::string runCode) {
    //Write /ScanData/RunInfo/MovieName attribute.
    runCodeAtom.Write(runCode);
}

void HDFScanDataWriter::WriteBindingKit(const std::string & bindingKit) {
    bindingKitAtom.Write(bindingKit);
}

void HDFScanDataWriter::WriteSequencingKit(const std::string & sequencingKit) {
    sequencingKitAtom.Write(sequencingKit);
}

void HDFScanDataWriter::Close() {
    // Close /ScanData/AcqParams attributes.
    whenStartedAtom.Close();
    frameRateAtom.Close();
    numFramesAtom.Close();

    // Close /ScanData/DyeSet attributes.
    baseMapAtom.Close();

    // Close /ScanData/RunInfo attributes.
    movieNameAtom.Close();
    runCodeAtom.Close();
    platformIdAtom.Close();
    platformNameAtom.Close();
    instrumentNameAtom.Close();
    bindingKitAtom.Close();
    sequencingKitAtom.Close();

    // Close /ScanData/AcqParams|DyeSet|RunInfo.
    acqParamsGroup.Close();
    dyeSetGroup.Close();
    runInfoGroup.Close();

    // Close /ScanData
    scanDataGroup.Close();
}
