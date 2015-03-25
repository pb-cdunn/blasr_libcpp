#include "HDFUtils.hpp"

std::string GetH5MovieName(std::string fileName) {
    HDFScanDataReader reader;
    return reader.GetMovieName_and_Close(fileName);
}

std::vector<std::string> GetH5MovieNames(const std::vector<std::string> & fileNames) {
    std::vector<std::string> ret;
    for (size_t i = 0 ; i < fileNames.size(); i++) {
        ret.push_back(GetH5MovieName(fileNames[i]));
    }
    return ret;
}

std::vector< std::pair<UInt, UInt> > GetMinMaxHoleNumbers(
    const std::vector<std::string> & fileNames, bool isRGN) {
    std::vector< std::pair<UInt, UInt> > ret;
    for (size_t i = 0 ; i < fileNames.size(); i++) {
        ret.push_back(GetMinMaxHoleNumber(fileNames[i], isRGN));
    }
    return ret;
}

std::pair<UInt, UInt> GetMinMaxHoleNumber(
        std::string fileName, bool isRGN) {
    UInt minHole, maxHole;

    if (isRGN) { // is region table
        HDFRegionTableReader rgnReader;
        rgnReader.Initialize(fileName);
        rgnReader.GetMinMaxHoleNumber(minHole, maxHole);
        rgnReader.Close();
    } else { // is bas/bax/pls/plx/ccs.h5
        HDFBasReader basReader;
        basReader.Initialize(fileName);
        vector<UInt> holes;
        basReader.GetMinMaxHoleNumber(minHole, maxHole);
        basReader.Close();
    }
    return std::make_pair(minHole, maxHole);
}

std::vector<int> MapPls2Rgn(const std::vector<std::string> & plsFNs,
        const std::vector<std::string> & rgnFNs) {
    if (plsFNs.size() != rgnFNs.size() && rgnFNs.size() != 0) {
        std::cout << "ERROR, the number of plx/bax.h5 files and the number of "
            << "region tables are not the same." << std::endl;
        exit(1);
    }

    // Movie names of pulse files in P.
    std::vector<std::string> plsMovies = GetH5MovieNames(plsFNs);
    // Movie names of region tables in R.
    std::vector<std::string> rgnMovies = GetH5MovieNames(rgnFNs);

    // The first and last hole numbers of pulse files in P.
    std::vector< std::pair<UInt, UInt> > plsHoles = GetMinMaxHoleNumbers(plsFNs, false);
    // The first and last hole numbers of region tables in R.
    std::vector< std::pair<UInt, UInt> > rgnHoles = GetMinMaxHoleNumbers(rgnFNs, true);

    std::vector<int> ret;
    for (size_t i = 0; i < plsFNs.size(); i++) {
        size_t j = 0;
        for (; j < rgnFNs.size(); j++) {
            if (plsMovies[i] == rgnMovies[j] and
                plsHoles[i].first <= rgnHoles[j].first and
                plsHoles[i].second >= rgnHoles[j].second) {
                break;
            }
        }
        if (j >= rgnFNs.size()) {
            std::cout << "ERROR, could not find any region table for file "
                 << plsFNs[i] << " [" << plsHoles[i].first << ", " << plsHoles[i].second 
                 <<"." << std::endl;
            exit(1);
        }
        ret.push_back(j);
    }
    return ret;
}

