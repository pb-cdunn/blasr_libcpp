#ifndef _BLASR_VARIANCE_ACCUMULATOR_HPP_
#define _BLASR_VARIANCE_ACCUMULATOR_HPP_

template<typename T>
class VarianceAccumulator {
public:
    int nSamples;
    T sumSqVal;
    T sumVal;
    T maxVal;
    T minVal;

    VarianceAccumulator<T>();

    T GetMean();

    T GetVariance();

    void Reset();

    float GetNStdDev(T value);

    void Append(T v);
};

#include "statistics/VarianceAccumulatorImpl.hpp"

#endif
