#ifndef _SIMULATOR_CONTEXT_OUTPUT_LIST_HPP_
#define _SIMULATOR_CONTEXT_OUTPUT_LIST_HPP_

#include <stdlib.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "utils.hpp"
#include "simulator/OutputList.hpp"


class ContextOutputList {
public:
    std::map<std::string, OutputList*> outputMap;
    int contextLength;
    int ParsePair(std::string &output, std::string &outStr, int &outCount){ 
        std::string contextStr, outCountStr;
        int i;
        for (i = 0; i < output.size(); i++) {
            if (output[i] == '=') {
                int start = 0;
                while(start < i and (output[start] == ' ' or output[start] == '\t')) { start++;}
                outStr.assign(&output[start], i-start);
                outCountStr.assign(&output[i+1], output.size()-i-1);
                outCount = atoi(outCountStr.c_str());
                return 1;
            }
        }
        return 0;
    }

    int SampleRandomContext(std::string refContext, std::string &readContext) {
        //
        // Chec to see if there is a distribution for this ref context, if
        // not, just return the ref context so that things may proceed,
        // but return a fail code.
        //
        if (outputMap.find(refContext) == outputMap.end()) {
            readContext = refContext;
            return 0;
        }
        else {
            outputMap[refContext]->SelectRandomContect(readContext);
            return 1;
        }
    }


    void Read(std::string &inName) {
        ifstream in;
        CrucialOpen(inName, in, std::ios::in);
        Read(in);
    }

    void Read(ifstream &in) {
        int nLines = 0;
        contextLength = 0;
        while(in) {
            std::string context;
            if (!(in >> context)) break;

            contextLength = context.size();
            std::string outputsLine;
            getline(in,outputsLine);
            // parse ctx=num; pairs
            int i;
            int e;
            i = 0;
            if (outputMap.find(context) == outputMap.end()) {
                outputMap[context] = ProtectedNew<OutputList>();
            }

            while(i < outputsLine.size()) {
                e = i+1;
                while(e < outputsLine.size() and outputsLine[e] != ';') e++;
                std::string pairStr;
                pairStr.assign(&outputsLine[i], e-i);
                if (e > i + 1) {
                    std::string outStr;
                    int outCount;
                    ParsePair(pairStr, outStr, outCount);
                    outputMap[context]->AddOutput(outStr, outCount);
                }
                i = e + 1;
            }
            outputMap[context]->StoreCumulativeCounts();
        }
    }

    void Free() {
        std::map<std::string,OutputList*>::iterator mapIt;
        for (mapIt = outputMap.begin(); mapIt != outputMap.end(); ++mapIt) {
            if (mapIt->second) {delete mapIt->second;}
        }
    }
};


#endif
