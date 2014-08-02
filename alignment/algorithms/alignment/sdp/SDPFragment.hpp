#ifndef _BLASR_SDP_FRAGMENT_HPP_
#define _BLASR_SDP_FRAGMENT_HPP_

class Fragment {
public:
	unsigned int x;
	unsigned int y;
	unsigned int weight;
	unsigned int length;
	int index;
	int chainPrev;
	int cost;
    int above;
	unsigned int chainLength;

	inline Fragment(unsigned int px, unsigned int py, int pweight=0); 

	inline Fragment();

	unsigned int GetX() const {return x;}

	unsigned int GetY() const {return y;}

    bool SetAbove(int a);
    bool GetAbove(int & a);

	inline int LessThanXY(const Fragment &f) const;

	inline int LessThanYX(const Fragment &f) const;

    inline int operator<(const Fragment &f) const;

    inline Fragment& operator=(const Fragment &rhs);

    inline int operator==(const Fragment &f) const;

	int operator>(const Fragment &f) const; 

	int GetLength(); 

	void SetLength(int _length); 
};

inline Fragment::Fragment(unsigned int px, unsigned int py, int pweight) {
    x = px;
    y = py;
    weight = pweight;
    length = index = 0;
    chainPrev = cost = chainLength = 0;
    above = -1;
}

//
// Provide default constructor that will
// give bad results if members are not properly initialized
// later on.
//
inline Fragment::Fragment() {
    x = -1;
    y = -1;
    weight = length = index = 0;
    chainPrev = cost = chainLength = 0;
    above = -1;
}

inline int Fragment::LessThanXY(const Fragment &f) const {
    if (x < f.x)
        return 1;
    else if (x == f.x) 
        return y < f.y;
    else 
        return 0;
}

inline int Fragment::LessThanYX(const Fragment &f) const {
    if (y < f.y)
        return 1;
    else if (y == f.y) 
        return x < f.x;
    else 
        return 0;
}

inline Fragment& Fragment::operator=(const Fragment &rhs) {
    x           = rhs.x;
    y           = rhs.y;
    index       = rhs.index;
    cost        = rhs.cost;
    weight      = rhs.weight;
    length      = rhs.length;
    chainLength = rhs.chainLength;
    chainPrev   = rhs.chainPrev;
    above       = rhs.above;
    return *this;
}

inline int Fragment::operator==(const Fragment &f) const {
    return (x == f.x and y == f.y);
}

inline int Fragment::operator<(const Fragment &f) const {
    // 
    // Sort fragments by diagonal:
    //
    int diag, fDiag;
    diag = (y - x);
    fDiag = f.y - f.x;
    if (diag < fDiag)
        return 1;
    else if (diag == fDiag)
        return (x < f.x);
    else
        return 0;
}

#endif // _BLASR_SDP_FRAGMENT_HPP_
