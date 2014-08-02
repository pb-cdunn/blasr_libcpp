#ifndef _BLASR_LIS_SIZE_WEIGHTOR_HPP_
#define _BLASR_LIS_SIZE_WEIGHTOR_HPP_

#include "Types.h"

template<typename T_MatchList>
class LISSizeWeightor {
public:
	MatchWeight operator()(T_MatchList &matchList);
};

#include "algorithms/anchoring/LISSizeWeightorImpl.hpp"

#endif
