#ifndef _BLASR_HDF_ALN_GROUP_HPP_
#define _BLASR_HDF_ALN_GROUP_HPP_

#include <string>
#include "HDFArray.hpp"
#include "HDFGroup.hpp"
#include "saf/AlnGroup.hpp"

class HDFAlnGroupGroup {
public:
    HDFGroup alnGroup;
    HDFArray<unsigned int> idArray;
    HDFStringArray pathArray;

    bool Create(HDFGroup &parent); 

    int AddPath(std::string path); 

    int Initialize(HDFGroup &parent); 

    void Read(AlnGroup &aln); 

    ~HDFAlnGroupGroup(); 
};


#endif
