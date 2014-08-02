#ifndef _BLASR_UTILS_SUM_OF_LOG_HPP_
#define _BLASR_UTILS_SUM_OF_LOG_HPP_

#include <math.h>

#define LOG_EPSILON   -30
#define LOG_EPSILON2  -8
#define LOG_EPSILON4  (logEpsilon/4.0)
#define LOG10 2.3025850929

double LogSumOfTwo(double value1, double value2); 

double LogSumOfThree(double value1, double value2, double value3); 

#endif // _BLASR_UTILS_SUM_OF_LOG_HPP_
