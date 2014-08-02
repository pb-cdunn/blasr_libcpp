#ifndef _BLASR_HDF_GROUP_HPP_
#define _BLASR_HDF_GROUP_HPP_

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "H5Cpp.h"
#include "HDFAttributable.hpp"
#include "StringUtils.hpp"


class HDFGroup : public HDFAttributable {
public:
    std::vector<std::string> objectNames;
    std::string objectName;
    H5::Group group;
    bool  groupIsInitialized;

    HDFGroup();

    void AddGroup(std::string groupName); 

    H5::H5Location* GetObject(); 

    int Initialize(H5::CommonFG& fg, std::string groupName);

    int Initialize(HDFGroup& parentGroup, std::string groupName); 

    bool ContainsObject(std::string queryObjectName); 

    void Close(); 
};


#endif
