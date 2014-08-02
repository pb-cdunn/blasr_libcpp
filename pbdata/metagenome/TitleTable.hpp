#ifndef _BLASR_TITLE_TABLE_HPP_
#define _BLASR_TITLE_TABLE_HPP_

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "utils.hpp"

class TitleTable {
public: 
    char **table;
    int tableLength;
    TitleTable();

    void Copy(char **src, int nSrc);

    void Write(std::string &name);

    void Write(std::ofstream &out);

    void Read(std::string &inFileName);

    void CopyFromVector(std::vector<std::string> &titles);

    void Read(std::ifstream &in);

    void Free();

    bool Lookup(std::string title, int &index) ;

    static void ResetTableToIntegers(char **table, 
        int *tableLengths, int nTable);
};

#endif
