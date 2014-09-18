#ifndef _SIMULATOR_CONTEXT_SAMPLE_HPP_
#define _SIMULATOR_CONTEXT_SAMPLE_HPP_

#include<string>
#include<vector>
#include<iostream>
#include "simulator/QualitySample.hpp"
#include "statistics/StatUtils.hpp"

class ContextSample {
public:
    std::vector<QualitySample> samples;
    int minSamples;
    int maxSamples;
    int reachedMinSamples;

    ContextSample();

    int GetNSamples();

    int AppendSample(SMRTSequence &seq, DNALength pos);

    QualitySample* GetRandomQualitySample();

    void Write(std::ofstream &out);

    void Read(std::ifstream &in);
};

#endif
