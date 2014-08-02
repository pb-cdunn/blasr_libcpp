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
  else {
      return ReadType::NoReadType;
  }
}
