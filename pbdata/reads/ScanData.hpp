#ifndef DATASTRUCTURES_READS_SCAN_DATA_H_
#define DATASTRUCTURES_READS_SCAN_DATA_H_

#include <string>
#include <map>
#include "Enumerations.h"

class ScanData {
public:
    PlatformId platformId;
    float frameRate;
    unsigned int numFrames;
    std::string movieName, runCode;
    std::string whenStarted;
    std::map<char, int> baseMap;
    ScanData();
    std::string GetMovieName(); 
};

#endif
