#include "HoleXY.hpp"

bool HoleXY::operator<(const HoleXY &rhs) const {
    return *this < rhs.xy;
}

bool HoleXY::operator<(const int16_t xyP[2]) const {
    if (xy[0] == xyP[0]) {
        return xy[1] < xyP[1];
    }
    else {
        return xy[0] < xyP[0];
    }
}       
