#include "CmpFile.hpp"

void CmpFile::StoreReadType(std::string &readTypeStringP) {
    readTypeString = readTypeStringP;
    readType = ReadType::ParseReadType(readTypeString);
}
