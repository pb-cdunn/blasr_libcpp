#include "MovieInfo.hpp"


int MovieInfo::FindMovie(int idKey, string &nameVal) {
    int i;
    for (i = 0; i < id.size(); i++) {
        if (id[i] == idKey) {
            nameVal = name[i];
            return 1;
        }
    }
    return 0;
}
