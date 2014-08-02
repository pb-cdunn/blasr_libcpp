#include "RefGroup.hpp"


bool RefGroup::IdToIndex(int idKey, int &idIndex) {
    int i;
    for (i = 0; i < refInfoId.size(); i++) {
        if (refInfoId[i] == idKey) {
        idIndex = i; return true;
        }
    }
    return false;
}
	

int RefGroup::FindPath(int idKey, string &pathVal, string &groupNameVal) {
    int i;
    for (i = 0; i < id.size(); i++) {
        if (id[i] == idKey) {
            pathVal = path[i];
            groupNameVal = refGroupName[i];
            return 1;
        }
    }
    return 0;
}
