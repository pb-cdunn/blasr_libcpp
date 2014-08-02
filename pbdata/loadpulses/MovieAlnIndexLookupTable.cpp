#include "MovieAlnIndexLookupTable.hpp"


MovieAlnIndexLookupTable::MovieAlnIndexLookupTable() {
    skip = true;
    //skip this alignment unless we can find all the information
}

void MovieAlnIndexLookupTable::SetValue(
                const bool & skipP,            
                const int  & movieAlignmentIndexP,
                const UInt & alignmentIndexP,  
                const int  & refGroupIndexP,   
                const int  & readGroupIndexP,  
                const UInt & holeNumberP,
                const UInt & offsetBeginP,     
                const UInt & offsetEndP,
                const int  & queryStartP,      
                const int  & queryEndP,
                const int  & readIndexP,
                const int  & readStartP,       
                const int  & readLengthP,
                const int  & plsReadIndexP) {
    skip = skipP; 
    movieAlignmentIndex = movieAlignmentIndexP;
    alignmentIndex      = alignmentIndexP;
    refGroupIndex       = refGroupIndexP;
    readGroupIndex      = readGroupIndexP;
    holeNumber          = holeNumberP;
    offsetBegin         = offsetBeginP;
    offsetEnd           = offsetEndP;
    queryStart          = queryStartP;
    queryEnd            = queryEndP;
    readIndex           = readIndexP;
    readStart           = readStartP;
    readLength          = readLengthP;
    plsReadIndex        = plsReadIndexP;
}


void MovieAlnIndexLookupTable::print() {
    // Print this lookup table for debugging . 
    if (skip) 
        std::cout << "skip = True, ";
    else 
        std::cout << "skip = False, ";
    std::cout << "movieAlnIndex    = " << alignmentIndex << ", refGroupIndex = " << refGroupIndex
            << ", readGroupIndex = " << readGroupIndex << ", holeNumber    = " << holeNumber
            << ", offsetBegin    = " << offsetBegin    << ", offsetEnd     = " << offsetEnd
            << ", queryStart     = " << queryStart     << ", queryEnd      = " << queryEnd
            << ", readIndex      = " << readIndex      << ", readStart     = " << readStart
            << ", readLength     = " << readLength     << ", plsReadIndex  = " << plsReadIndex
            << std::endl;
}
