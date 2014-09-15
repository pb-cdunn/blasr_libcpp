#ifndef _SIMULATOR_OUTPUT_LIST_HPP_
#define _SIMULATOR_OUTPUT_LIST_HPP_

#include <string>
#include <vector>

#include "CDFMap.hpp"

class Output {
public:
    std::string output;
	int    count;
};

class OutputList {
public:
	int totalCount;
    std::vector<Output> outputs;
	CDFMap<std::vector<Output>::iterator> cdf;

	OutputList() {
		totalCount = 0;
	}

	int AddOutput(std::string str, int count) {
		outputs.resize(outputs.size()+1);
		outputs[outputs.size()-1].output = str;
		outputs[outputs.size()-1].count  = count;
		totalCount += count;
	}
	
	void StoreCumulativeCounts() {
		int outputIndex;
		int total = 0;
		for (outputIndex = 0; outputIndex < outputs.size(); outputIndex++) {
			total += outputs[outputIndex].count;
			cdf.cdf.push_back(total);
			cdf.data.push_back(outputs.begin() + outputIndex);
		}
		assert(total == totalCount);
	}

	int ReturnUniformRandomContextIt(std::vector<Output>::iterator &outputIt) {
		return cdf.SelectRandomValue(outputIt);
	}

	int SelectRandomContect(std::string &outputContext) {
        std::vector<Output>::iterator outIt;
		ReturnUniformRandomContextIt(outIt);
		outputContext = outIt->output;
		return outIt - outputs.begin();
	}
		
};


#endif
