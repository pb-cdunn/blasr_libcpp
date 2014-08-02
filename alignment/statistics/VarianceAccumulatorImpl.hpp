#ifndef _BLASR_VARIANCE_ACCUMULATOR_IMPL_HPP_
#define _BLASR_VARIANCE_ACCUMULATOR_IMPL_HPP_

template<typename T>
VarianceAccumulator<T>::
VarianceAccumulator() {
    Reset();
}

template<typename T>
void VarianceAccumulator<T>::Reset() {
    sumSqVal = 0;
    sumVal   = 0;
    nSamples = 0;
    maxVal = minVal = 0;
}

template<typename T>
T VarianceAccumulator<T>::
GetMean() {return ((1.0)*sumVal)/nSamples;}

template<typename T>
T VarianceAccumulator<T>::
GetVariance() {
    return (1.0*sumSqVal)/nSamples -  GetMean()*GetMean();
}
 
template<typename T>
float VarianceAccumulator<T>::
GetNStdDev(T value) {
    T variance = GetVariance();
    T mean     = GetMean();
    if (variance > 0) {
        return fabs(value - mean)/(sqrt(variance));
    }
    else {
        return 0;
    }
}

template<typename T>
void VarianceAccumulator<T>::
Append(T v) {
    if (nSamples == 0) {
        maxVal = minVal = v;
    }
    else {
        if (maxVal < v) {
            maxVal = v;
        }
        if (minVal > v) {
            minVal = v;
        }
    }
    sumSqVal += v*v;
    sumVal   += v;
    nSamples++;
}

#endif
