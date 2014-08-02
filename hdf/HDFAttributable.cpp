#include <cassert>
#include "HDFAttributable.hpp"

using namespace std;
using namespace H5;

void CallStoreAttributeName(H5Location &obj, string attrName, void *attrList){ 
    ((vector<string>*)attrList)->push_back(attrName);
}

void HDFAttributable::StoreAttributeNames(H5Location &thisobject, 
    std::vector<std::string> &attributeNames) {
    void *destAndData[2];
    int nAttr = thisobject.getNumAttrs();
    unsigned int bounds[2];
    bounds[0] = 0;
    bounds[1] = nAttr;
    attributeNameList.clear();
    thisobject.iterateAttrs(&CallStoreAttributeName, 
            bounds, (void*) &attributeNames);
}

H5Location* HDFAttributable::GetObject() {
    return NULL;
}

int HDFAttributable::ContainsAttribute(string attributeName) {
    int i;
    std::vector<std::string> tmpAttributeNames;
    H5Location *obj = GetObject();
    assert(obj != NULL);
    StoreAttributeNames(*obj, tmpAttributeNames);
    for (i = 0; i < tmpAttributeNames.size(); i++) {
        if (tmpAttributeNames[i] == attributeName) return true;
    }
    return false;
}

