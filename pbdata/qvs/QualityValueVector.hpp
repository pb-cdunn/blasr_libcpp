#ifndef _BLASR_QUALITY_VALUE_VECTOR_HPP_
#define _BLASR_QUALITY_VALUE_VECTOR_HPP_
#include <stdint.h>
#include <cstddef>
#include <ostream>
#include <cstring>
#include "Types.h"
#include "utils.hpp"
#include "DNASequence.hpp"
#include "QualityValue.hpp"

template<typename T_QV>
class QualityValueVector {
public:
    T_QV   *data;
    QVScale qvScale;

    T_QV &operator[](unsigned int pos); 

    QualityValueVector(); 

    QualityProbability ToProbability(unsigned int pos); 

    T_QV ToPhred(unsigned int pos); 

    void Copy(const QualityValueVector<T_QV> &rhs, const DNALength length); 

    void Free(); 

    void Allocate(unsigned int length); 

    bool Empty() const; 

    void ShallowCopy(const QualityValueVector<T_QV> &ref, int pos = 0); 

};



#endif // _BLASR_QUALITY_VALUE_VECTOR_HPP_
