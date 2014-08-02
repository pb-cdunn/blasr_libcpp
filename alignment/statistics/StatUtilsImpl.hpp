#ifndef _BLASR_STAT_UTILS_IMPL_HPP_
#define _BLASR_STAT_UTILS_IMPL_HPP_

#include <vector>
#include <time.h>

inline int Choose(int a, int b) {
	// A quick choose for small values.
	assert(a >= b);
	if (a < FactorialTableLength and b < FactorialTableLength) {
		return (FactorialTable[a] /
                (FactorialTable[b] * FactorialTable[a-b]));
	} else {
		//
		// Less quick choose for numerically stable values.
		//
		unsigned long al =a, bl=b, fact=0;
		fact = al;
		//
		// The full value of b! must be able to be computed.
		//
		if (b >= FactorialTableLength) {
			return 0;
		}
		while (al > bl) {
			--al;
			if (ULONG_MAX / al < fact) {
				// there is overflow in the computation of a!/(a-b)!
				return 0;
			}
			else {
				fact = fact * al;
			}
		}
		return fact / FactorialTable[b];
	}
}


template<typename T>
void MeanVar(std::vector<T> &values, float &mean, float &var) {
  T sum = 0;
  T sumsq = 0;
  int i;
  if (values.size() == 0) {
    mean = 0; var = 0;
    return;
  }
  for (i = 0; i < values.size(); i++) {
    sum += values[i];
    sumsq += values[i]*values[i];
  }
  mean = (1.0*sum) / values.size();
  var  = sumsq / values.size() - (mean*mean);
}

#endif
