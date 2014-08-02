#ifndef _BLASR_FILE_OF_FILE_NAMES_HPP_
#define _BLASR_FILE_OF_FILE_NAMES_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "utils.hpp"

class FileOfFileNames {
public:
    static void StoreFileOrFileList(std::string fileName,
            std::vector<std::string> &fofnList);

    static void FOFNToList(std::string &fofnFileName, 
            std::vector<std::string> &fofnList);

    static bool IsFOFN(std::string &fileName);

    static bool IsBasH5(std::string &fileName);

    static std::vector<std::string> Bas2Bax(std::string &basFN);

    static int ExpandFileNameList(std::vector<std::string> &fileNames);
};

#endif
