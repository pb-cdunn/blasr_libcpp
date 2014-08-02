#ifndef _BLASR_HDF_SCAN_DATA_READER_HPP_
#define _BLASR_HDF_SCAN_DATA_READER_HPP_

#include <map>
#include <string>
#include "Enumerations.h"
#include "reads/ScanData.hpp"
#include "HDFGroup.hpp"
#include "HDFFile.hpp"
#include "HDFAtom.hpp"

//
// The SanDataReader cannot live outside 

class HDFScanDataReader {
public:
    bool fileHasScanData, useRunCode;
    HDFGroup scanDataGroup;
    HDFGroup dyeSetGroup;
    HDFGroup acqParamsGroup;
    HDFGroup runInfoGroup;
    bool initializedAcqParamsGroup, initializedRunInfoGroup;
    bool useWhenStarted;
    HDFAtom<std::string> whenStartedAtom;
    HDFAtom<unsigned int> platformIdAtom;
    HDFAtom<float> frameRateAtom;
    HDFAtom<unsigned int> numFramesAtom;
    HDFAtom<std::string> movieNameAtom;
    HDFAtom<std::string> runCodeAtom;
    HDFAtom<std::string> baseMapAtom;

    //
    // It is useful to cache the movie name in the reader since this is
    // loaded once upon initialization, and may be fetched when loading
    // reads one at a time.
    //
    bool   useMovieName;
    std::string movieName, runCode;
    std::map<char, int> baseMap;
    PlatformId platformId;
    HDFScanDataReader(); 

    int InitializeAcqParamsAtoms(); 

    //
    // This is created on top of a file that is already opened, so
    // instead of initializing by opening a file, it is initialized by
    // passing the root group that should contain the ScanData group.  
    // When shutting down, no file handle needs to be closed.
    //
    int Initialize(HDFGroup *pulseDataGroup); 

    std::string GetMovieName(); 
    
    // Given a PacBio (pls/plx/bas/bax/ccs/rgn).h5 file, which contains its movie 
    // name in group /ScanData/RunInfo attribute MovieName, open the file, return
    // its movie name and finally close the file. Return "" if the movie name 
    // does not exist. This is a short path to get movie name.
    std::string GetMovieName_and_Close(std::string & fileName);

    std::string GetRunCode(); 

    int Read(ScanData &scanData); 

    void ReadWhenStarted(std::string &whenStarted); 

    PlatformId GetPlatformId(); 

    int ReadPlatformId(PlatformId &pid); 

    int LoadMovieName(std::string &movieName); 

    int LoadBaseMap(map<char, int> & baseMap); 

    void Close(); 

};

#endif
