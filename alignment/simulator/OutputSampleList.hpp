#ifndef _SIMULATOR_OUTPUT_SAMPLE_LIST_HPP_
#define _SIMULATOR_OUTPUT_SAMPLE_LIST_HPP_

#include <vector>
#include "OutputSample.hpp"

class OutputSampleList: public std::vector<OutputSample> {
public:
    void Write(ofstream &out) {
        int nElem = this->size();
        out.write((char*)&nElem, sizeof(int));
        if (nElem > 0) {
            int i;
            for (i = 0; i < nElem; i++) {
                (*this)[i].Write(out);
            }
        }
    }

    void Read(std::ifstream &in) {
        int nElem;
        in.read((char*) &nElem, sizeof(int));
        if (nElem > 0) {
            this->resize(nElem);
            int i;
            for (i = 0; i < nElem; i++) {
                (*this)[i].Read(in);
            }
        }
    }
};

#endif
