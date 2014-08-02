#ifndef _BLASR_SDP_COLUMN_HPP_
#define _BLASR_SDP_COLUMN_HPP_

class SDPColumn {
 public:
	int col;
	int optFragment;
    SDPColumn() : col(0), optFragment(0) {}
    int operator<(const SDPColumn & rhs) const {
        return col < rhs.col;
    }
    int operator<(const int y) const {
        return col < y;
    }
    int operator==(const SDPColumn &rhs) const {
        return col == rhs.col;
    }
    int operator>(const SDPColumn &rhs) const {
        return (!(*this < rhs) && !(*this == rhs));
    }
};

#endif // _BLASR_SDP_COLUMN_HPP_
