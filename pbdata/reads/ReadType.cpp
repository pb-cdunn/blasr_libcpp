#include "ReadType.hpp"

ReadType::ReadTypeEnum ReadType::ParseReadType(std::string &readTypeString) {
  if (readTypeString == "Standard") {
    return ReadType::Standard;
  }
  else if (readTypeString == "CCS") {
    return ReadType::CCS;
  }
  else if (readTypeString == "RCCS") {
    return ReadType::RCCS;
  }
  else if (readTypeString == "POLYMERASE") {
    return ReadType::POLYMERASE;
  }
  else if (readTypeString == "HQREGION") {
    return ReadType::HQREGION;
  }
  else if (readTypeString == "SUBREAD") {
    return ReadType::SUBREAD;
  }
  else if (readTypeString == "SCRAP") {
    return ReadType::SCRAP;
  }
  else if (readTypeString == "UNKNOWN") {
    return ReadType::UNKNOWN;
  }
  else {
      return ReadType::NoReadType;
  }
}

std::string ReadType::ToString(const ReadType::ReadTypeEnum & readType) {
    if (readType == ReadType::Standard) return "Standard";
    if (readType == ReadType::CCS) return "CCS";
    if (readType == ReadType::RCCS) return "RCCS";
    if (readType == ReadType::HQREGION) return "HQREGION";
    if (readType == ReadType::POLYMERASE) return "POLYMERASE";
    if (readType == ReadType::SUBREAD) return "SUBREAD";
    if (readType == ReadType::SCRAP) return "SCRAP";
    if (readType == ReadType::UNKNOWN) return "UNKNOWN";
    return "NoReadType";
}
