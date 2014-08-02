#ifndef GRAPH_PAPER_HPP_
#define GRAPH_PAPER_HPP_

#include "datastructures/alignment/Path.h"
#include "matrix/FlatMatrix.hpp"

template<typename T_Point>
bool SetBounds(vector<T_Point> &points, 
               DNALength &minPos, 
               DNALength &maxPos, 
               int axis);

inline int GetIndex(DNALength pos, 
                    DNALength minPos, 
                    DNALength maxPos, 
                    int nBins);

template<typename T_Point>
int GraphPaper(vector<T_Point> &points, 
               int nRows, int nCols,
               FlatMatrix2D<int> &bins,
               FlatMatrix2D<int> &scoreMat,
               FlatMatrix2D<Arrow> &pathMat,
               vector<bool> &onOptPath);

template<typename T_Point>
void RemoveOffOpt(vector<T_Point> &points, vector<bool> &optPath);

#include "GraphPaperImpl.hpp"

#endif
