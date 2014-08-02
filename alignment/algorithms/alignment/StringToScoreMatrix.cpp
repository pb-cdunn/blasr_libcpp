#include "StringToScoreMatrix.hpp"

bool StringToScoreMatrix(std::string &str, int matrix[5][5]) {
    std::stringstream strm(str);
    std::vector<int> values;
    while(strm) {
        int val;
        if ((strm >> val)) {
            values.push_back(val);
        }
    }
    if (values.size() != 25) {
        return 0;
    }
    else {
        int i,j;
        int index = 0;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                matrix[i][j] = values[index];
                ++index;
            }
        }
        return true;
    }
}
