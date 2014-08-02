#ifndef _BLASR_LISSIZE_WEIGHTOR_IMPL_HPP_
#define _BLASR_LISSIZE_WEIGHTOR_IMPL_HPP_
template<typename T_MatchList>
MatchWeight LISSizeWeightor<T_MatchList>:: operator()(
    T_MatchList &matchList) {
    MatchWeight size = 0;
    VectorIndex i;
    for (i = 0; i < matchList.size(); i++) {
        size += matchList[i].GetLength();
    }
    return size;
}
#endif
