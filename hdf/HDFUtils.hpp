#ifndef _BLASR_HDF_UTILS_HPP_
#define _BLASR_HDF_UTILS_HPP_

#include <vector>
#include <string>

#include "HDFFile.hpp"
#include "HDFScanDataReader.hpp"
#include "HDFBasReader.hpp"
#include "HDFRegionTableReader.hpp"
#include "reads/RegionTable.hpp"


// Given a PacBio (pls/plx/bas/bax/ccs/rgn).h5 file, which contains its movie 
// name in group /ScanData/RunInfo attribute MovieName, return its' movie name
std::string GetH5MovieName(std::string fileName);

// Given a vector of h5 files, return their movie names.
std::vector<std::string> GetH5MovieNames(const std::vector<std::string> & fileNames);

// Given a PacBio rgn.h5 file, return the smallest and largest holeNumber in
// group /PulseData/Regions.
std::pair<UInt, UInt> GetMinMaxHoleNumber(std::string fileName, 
                                          bool isRGN=false);

std::vector<std::pair<UInt, UInt> > GetMinMaxHoleNumbers(
    std::string fileName, bool isRGN=false);

// Pulse files in input.fofn and regions tables in rgn.fofn may not
// match, return mapping from plsFNs indices to rgnFNs indices.
//
// Input : plsFNs - pulse file names in input.fofn, e.g.,
//                  P=(p_0, ..., p_{n-1})
//         rgnFNs - region table file names in rgn.fofn, e.g.,
//                  R=(r_0, ..., p_{n-1})
// Output: mapping from plsFNs indices to rgnFNs indices, e.g.,
//                  M=(m_0, ..., m_{n-1})
//         so that for all i from 0 to n-1,
//                  r_{m_{i}} matches p_i
//
std::vector<int> MapPls2Rgn(const std::vector<std::string> & plsFNs,
                            const std::vector<std::string> & rgnFNs);

#endif
