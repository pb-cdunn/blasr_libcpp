#ifndef _BLASR_HDF_FILE_HPP_
#define _BLASR_HDF_FILE_HPP_

#include <iostream>
#include <string>
#include <vector>
#include "H5Cpp.h"
#include "HDFConfig.hpp"
#include "HDFGroup.hpp"

class HDFFile {
public:
    // Make this public for easy access.
    H5::H5File hdfFile;	
    HDFGroup rootGroup;

    HDFFile(); 

    //
    //  Open a file.  By default, if the file already exists, open it in
    //  read/write mode.  The only other flag that is allowed is
    //  H5F_ACC_TRUNC, which will truncate the file to zero size.
    //
    void Open(string fileName, unsigned int flags=H5F_ACC_RDWR, 
        const H5::FileAccPropList& fileAccPropList=H5::FileAccPropList::DEFAULT); 

    void Close(); 

};


#endif
