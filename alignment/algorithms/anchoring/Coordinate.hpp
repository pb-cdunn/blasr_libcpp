#ifndef _BLASR_COORDINATE_HPP_
#define _BLASR_COORDINATE_HPP_

#include "Types.h"

class Coordinate {
private:
    UInt x;
    UInt y; 
public:
    inline UInt GetX() const; 
    inline UInt GetY() const;
    inline UInt SetX(UInt _x);
    inline UInt SetY(UInt _y);
    inline int operator<(const Coordinate &rhs) const;
    int operator<=(const Coordinate &rhs) const;
    int Equals(const Coordinate &rhs) const;
    //
    // Synonym for Equals.
    //
    inline int operator==(const Coordinate &rhs) const;
    inline Coordinate &operator=(const Coordinate &rhs);
};

inline UInt Coordinate::GetX() const {return x;}
inline UInt Coordinate::GetY() const {return y;}

inline UInt Coordinate::SetX(UInt _x) {return (x = _x);}
inline UInt Coordinate::SetY(UInt _y) {return (y = _y);}

inline int  Coordinate::operator<(const Coordinate &rhs) const {
    if (x == rhs.GetX()) return y < rhs.GetY();
    else return x < rhs.GetX();
}

inline int Coordinate::operator==(const Coordinate &rhs) const {
    return this->Equals(rhs);
}

inline Coordinate& Coordinate::operator=(const Coordinate &rhs) {
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}
#endif
