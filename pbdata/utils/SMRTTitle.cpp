#include "utils/SMRTTitle.hpp"

/// Parse a Pacbio read name, it is a SMRTTitle, get movieName, 
/// holeNumber, start and end, set isSMRTTitle to be true. 
/// Otherwise, set isSMRTTitle to be false.
/// Two types of smrtTitles are supported:
///     movie/zmw/start_end --> start = start, end = end
///     movie/zmw/start_end/start2_end2 --> start = start+start2, end = start+end2
/// \param[in]: readName, a PacBio read name string.
SMRTTitle::SMRTTitle(const std::string & readName) {
    isSMRTTitle = false;
    movieName = "";
    holeNumber = 0; 
    start = end = 0;

    std::vector<std::string> values;
    ParseSeparatedList(readName, values, '/');

    int numValues = values.size();
    if (numValues == 3 or numValues == 4) {
        movieName = values[0];
        holeNumber = static_cast<UInt>(atoi(values[1].c_str()));
        std::vector<std::string> offsets;
        ParseSeparatedList(values[2], offsets, '_');
        if (offsets.size() == 2) {
            start = static_cast<DNALength>(atoi(offsets[0].c_str()));
            end   = static_cast<DNALength>(atoi(offsets[1].c_str()));
            if (numValues == 3) {
                isSMRTTitle = true;
            } else if (numValues == 4) {
                offsets.clear();
                ParseSeparatedList(values[3], offsets, '_');
                if (offsets.size() == 2) {
                    end   = static_cast<DNALength>(start + atoi(offsets[1].c_str()));
                    start = static_cast<DNALength>(start + atoi(offsets[0].c_str()));
                    isSMRTTitle = true;
                }
            }
        }
    }
}

std::string SMRTTitle::ToString() {
    if (not isSMRTTitle) {
        return "";
    } else {
        std::stringstream ss;
        ss << movieName << "/" << holeNumber << "/" << start << "_" << end;
        return ss.str();
    }
}

