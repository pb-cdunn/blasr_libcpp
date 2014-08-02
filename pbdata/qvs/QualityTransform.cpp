#include <cassert>
#include "QualityTransform.hpp"
/*
* Base lookup table class for quality values.
*/

float QualityToProb::operator()(int index) {
    assert(index >= 0);
    assert(index <= MAX_QUALITY_VALUE);
    return prob[index];
}

/* 
* Create a lookup table for transforming from quality value
* to p-value using Patrick Marks' low-end expand qv = -100*log10(p/(1-p))
*/
void LowEndExpandQualityTransform::operator()(QualityToProb &qt) {
    int i;
    for (i = MIN_QUALITY_VALUE; i <= MAX_QUALITY_VALUE; i++) {
        float v = pow(10,i/-100.0);
        qt.prob[i] = 1 - v/(1+v);
    }
}
