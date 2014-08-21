#include "ScanData.hpp"

ScanData::ScanData() {
    platformId = NoPlatform;
    frameRate = numFrames = 0;
    movieName = runCode = whenStarted = "";
    baseMap.clear();
}

std::string ScanData::GetMovieName() {
    return movieName;
}
