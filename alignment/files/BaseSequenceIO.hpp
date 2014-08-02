#ifndef _BLASR_DATA_FILE_TYPE_HPP_
#define _BLASR_DATA_FILE_TYPE_HPP_

#include <string>
#include <iostream>
#include <cassert>
#include "Enumerations.h"

class BaseSequenceIO {

protected:

    FileType fileType;
    std::string fileName;

public:

    void SetFiles(FileType &pFileType, std::string &pFileName); 

    FileType GetFileType(); 

    static int DetermineFileTypeByExtension(std::string &fileName, FileType &type, 
        bool exitOnFailure=true); 
};	

#endif // _BLASR_DATA_FILE_TYPE_HPP_
