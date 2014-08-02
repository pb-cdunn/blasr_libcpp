#ifndef _BLASR_HDF_NEW_BAS_READER_HPP_
#define _BLASR_HDF_NEW_BAS_READER_HPP_

#include <stdlib.h>
#include <sstream>
#include <vector>

#include "HDFArray.hpp"
#include "HDFGroup.hpp"

const int BAXPERBAS = 3; // Number of bax files per base file.

class HDFNewBasReader {
// The new bas.h5 file contains:
// /MultiPart group, 
// /MultiPart/HoleLookup Dataset (which is ignored), and
// /MultiPart/Parts Dataset.
public:
    H5::H5File hdfBasFile;
	HDFGroup rootGroup;
	HDFGroup multiPartGroup; 
	//HDFArray<std::string> partsArray;
    HDFStringArray partsArray;
    std::string basFileName;

	HDFNewBasReader() {
        basFileName = "";
    }

    int Initialize (const std::string & hdfBasFileName);
   
    std::vector<std::string> GetBaxMovieNames();

    std::vector<std::string> GetBaxFileNames();

    void Close();
};

#endif
