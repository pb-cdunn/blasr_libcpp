#include "AlnGroup.hpp"

int AlnGroup::FindPath(int idKey, std::string &val) {
    int i;
    for (i = 0; i < id.size(); i++) {
        if (idKey == id[i]) {
            val = path[i];
            return 1;
        }
    }
    return 0;
}
