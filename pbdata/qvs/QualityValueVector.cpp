#include "QualityValueVector.hpp"

template<typename T_QV>
T_QV& QualityValueVector<T_QV>::operator[](unsigned int pos) {
    return data[pos];
}

template<typename T_QV>
QualityValueVector<T_QV>::QualityValueVector() {
    data = NULL;
    // Default to phred.
    qvScale = PHRED;
}

template<typename T_QV>
QualityProbability QualityValueVector<T_QV>::ToProbability(unsigned int pos) {
    return QualityValueToProbability(data[pos], qvScale);
}

template<typename T_QV>
T_QV QualityValueVector<T_QV>::ToPhred(unsigned int pos) {
    if (qvScale == PHRED) {
        return data[pos];
    }
    else {
        return PacBioQVToPhred(data[pos]);
    }
}

template<typename T_QV>
void QualityValueVector<T_QV>::Copy(const QualityValueVector<T_QV> &rhs, const DNALength length) {
    Free();
    if (rhs.Empty()) { 
        return;
    }
    Allocate(length);
    std::memcpy(data, rhs.data, length * sizeof(T_QV));
}

template<typename T_QV>
void QualityValueVector<T_QV>::Free() {
    if (data != NULL) {
        delete[] data;
        data = NULL;
    }
}

template<typename T_QV>
void QualityValueVector<T_QV>::Allocate(unsigned int length) {
    data = ProtectedNew<T_QV>(length);
}

template<typename T_QV>
bool QualityValueVector<T_QV>::Empty() const {
    return data == NULL;
}

template<typename T_QV>
void QualityValueVector<T_QV>::ShallowCopy(const QualityValueVector<T_QV> &ref, int pos) {
    data = &ref.data[pos];
    qvScale = ref.qvScale;
}

template class QualityValueVector<QualityValue>;
