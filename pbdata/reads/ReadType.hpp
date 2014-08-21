#ifndef _BLASR_READ_TYPE_HPP 
#define _BLASR_READ_TYPE_HPP 

#include <string>

class ReadType {
 public:
  typedef enum E_ReadTypeEnum {NoReadType, Standard, CCS, RCCS} ReadTypeEnum;
  static ReadTypeEnum ParseReadType(std::string &readTypeString);
};

#endif
