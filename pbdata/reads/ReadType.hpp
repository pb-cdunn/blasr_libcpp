#ifndef _BLASR_READ_TYPE_H 
#define _BLASR_READ_TYPE_H 

#include <string>

class ReadType {
 public:
  typedef enum E_ReadTypeEnum {NoReadType, Standard, CCS, RCCS} ReadTypeEnum;
  static ReadTypeEnum ParseReadType(std::string &readTypeString);
};

#endif
