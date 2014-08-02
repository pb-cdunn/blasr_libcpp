#include "algorithms/anchoring/Coordinate.hpp"


int Coordinate::operator<=(const Coordinate &rhs) const {
    return (*this < rhs) or (x == rhs.x && y == rhs.y);
}

int Coordinate::Equals(const Coordinate &rhs) const {
    return (x == rhs.GetX() and y == rhs.GetY());
}


