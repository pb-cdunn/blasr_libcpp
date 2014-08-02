#ifndef _BLASR_PRIORITY_SEARCH_TREE_HPP_
#define _BLASR_PRIORITY_SEARCH_TREE_HPP_

#include <vector>
#include "algorithms/anchoring/BasicEndpoint.hpp"

/*
 * Define a priority search tree on a point that implements 
 * the following interface:
 *
 * int T_point::GetIndex()
 *    - Return the index of the point in a list of points.
 * int T_point::GetKey()
 *    - Return the key value that the points are sorted by (x-value in a 2D query)
 * int T_point::GetValue()
 *    - Return the value of a point.
 * int T_point::SetValue(int value)
 *    - sets the value of a point.
 *
 * This class implements a query FindMax(key), which returns
 * the index of the point with greatest value of all points with key [0...key).
 *
 * 
 */
template<typename T_Point>
class PSTVertex {
public: 
    unsigned int leftChildIndex;
    unsigned int rightChildIndex;
    unsigned int isALeaf;
    KeyType medianKey;
    KeyType maxKey;
    unsigned int pointIndex;
    int maxScoreNode;
    PSTVertex();
};

template<typename T_Point>
class PrioritySearchTree {
private:
    std::vector<PSTVertex<T_Point> > tree;
    std::vector<PSTVertex<T_Point> > * treePtr;
	int GetMedianIndex(int start, int end);

	inline KeyType CreateTree(std::vector<T_Point> &points, 
        int start, int end, unsigned int &iterativeIndex);

	int FindIndexOfMaxPoint(int curVertexIndex, std::vector<T_Point> &points, 
        KeyType maxKey, int &maxPointValue, 
        int &maxPointIndex);

public:
    PrioritySearchTree();

	void CreateTree(std::vector<T_Point> &points, 
        std::vector<PSTVertex<T_Point> > *bufTreePtr=NULL);

	int FindPoint(KeyType pointKey, 
        int curVertexIndex, int &pointVertexIndex);

	void Activate(std::vector<T_Point> &points, int pointIndex);

	int FindIndexOfMaxPoint(std::vector<T_Point> &points, 
        KeyType maxPointKey, int &maxPointIndex);
};

#include "algorithms/anchoring/PrioritySearchTreeImpl.hpp"

#endif
