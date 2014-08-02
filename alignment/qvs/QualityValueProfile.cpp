#include "QualityValueProfile.hpp"

QualityValueProfile::QualityValueProfile(int _wordSize, 
    int _numQualityValues) {
    wordSize = _wordSize;
    numQualityValues = _numQualityValues;
    // Initialize the tuple metrics to map from seq->index
    tm.Initialize(wordSize);
    nWords = 1 << (2*wordSize);
    // Initialize the matrix of quality values.
    profile.Grow(nWords, numQualityValues);
    profile.Initialize(0);
}

void QualityValueProfile::Update(Nucleotide *seq, QualityValue qv) {
    DNATuple tuple;
    if (tuple.FromStringLR(seq, tm)) {
        profile.Set(tuple.tuple, qv, profile(tuple.tuple, qv) + 1);
    }
}

void QualityValueProfile::Print(std::ofstream &out) {
    out << wordSize << " " << numQualityValues 
        << " " << CDF_GRANULARITY << std::endl;
    profile.Print(out);
}

void QualityValueProfile::ProfileToCDF() {
    int qv;
    int wordIndex;
    for (wordIndex = 0 ; wordIndex < nWords; wordIndex++) {
        int totalSamples = 0;			
        for (qv = 0; qv < numQualityValues; qv++) {
            totalSamples += profile(wordIndex, qv);
            profile.Set(wordIndex, qv, totalSamples);
        }
        for (qv = 0; qv < numQualityValues; qv++ ){ 
            profile.Set(wordIndex, qv, ((profile(wordIndex,qv) * 1.0) / totalSamples)  * CDF_GRANULARITY);
        }
    }
}
