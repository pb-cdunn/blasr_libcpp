#ifndef _BLASR_FRAGMENT_SORT_HPP_
#define _BLASR_FRAGMENT_SORT_HPP_


template<typename T_Fragment>
class LexicographicFragmentSort {
public:
	int operator()(const T_Fragment &a, const T_Fragment &b) const; 
};

template<typename T_Fragment>
class LexicographicFragmentSortByY {
public:
	int operator()(const T_Fragment &a, const T_Fragment &b) const;
};

#include "FragmentSortImpl.hpp"

#endif // _BLASR_FRAGMENT_SORT_HPP_
