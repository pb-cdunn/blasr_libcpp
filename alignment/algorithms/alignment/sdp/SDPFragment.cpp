#include "SDPFragment.hpp"

int Fragment::operator>(const Fragment &f) const {
    return (!(*this < f) &&  !(*this == f));
}
int Fragment::GetLength() {
    return length;
}
void Fragment::SetLength(int _length) {
    length = _length;
}

bool Fragment::SetAbove(int a) {
    above = a;
    return true;
}

bool Fragment::GetAbove(int & a) {
    if (above >= 0) {
        a = above;
        return true;
    } else {
        a = -1;
        return false;
    }
}

