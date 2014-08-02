#include "SparseDynamicProgramming.hpp"

int IndelPenalty(int x1, int y1, int x2, int y2, int insertion, int deletion) {
    int drift, driftPenalty;
    drift = (x1 - y1) - (x2 - y2);
    if (drift > 0) {
        driftPenalty = drift * insertion;
    }
    else if (drift < 0) {
        driftPenalty = -drift * deletion;
    }
    else {
        driftPenalty = 0;
    }
    return driftPenalty;
}


