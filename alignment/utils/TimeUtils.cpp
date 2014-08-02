#include <sstream> 
#include <time.h>
#include <iomanip> // std::setfill setd::setw
#include "utils/TimeUtils.hpp"

std::string GetTimestamp() {
  time_t timer;
  time(&timer);  // t is an integer type
  // Prepare timestamp in the format : 2012-04-05T09:26:02.689093
  std::stringstream timeStrm;
  struct tm t;
  localtime_r(&timer, &t);
  timeStrm << t.tm_year + 1900 << "-"
           << std::setfill('0') << std::setw(2) << t.tm_mon + 1 << "-"
           << std::setfill('0') << std::setw(2) << t.tm_mday << "T"
           << std::setfill('0') << std::setw(2) << t.tm_hour << ":"
           << std::setfill('0') << std::setw(2) << t.tm_min << ":"
           << std::setfill('0') << std::setw(2) << t.tm_sec;
  return timeStrm.str();
}
