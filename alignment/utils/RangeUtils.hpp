/*
 * ============================================================================
 *
 *       Filename:  RangeUtils.h
 *
 *    Description:  Parse a list of ranges separated by commas.
 *                  Designed for specifying a set of holeNumbers to analyze.
 *
 *        Version:  1.0
 *        Created:  05/02/2013 12:51:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * ============================================================================
 */
#include <stdlib.h>
#include <algorithm>
#include "StringUtils.hpp"
#include "Types.h"

class Range {
public:
    UInt start;  // Start position of a range, inclusive
    UInt end;    // End position of a range, inclusive

    Range(UInt pStart); 

    Range(UInt pStart, UInt pEnd); 

    bool contains(const UInt & query); 

    bool operator < (const Range & pRange) const; 
};

// Input is a comma-delimited string of ranges.
// e.g. 1,2,3,10-20
bool ParseRanges(string & rangesStr, vector<Range> & ranges); 

class Ranges {
public:
    std::vector<Range> ranges;
    Ranges(std::string rangesStr=""); 

    bool setRanges(std::string rangesStr); 
    
    int size(); 

    UInt max(); 

    bool contains(const UInt & query); 
};


