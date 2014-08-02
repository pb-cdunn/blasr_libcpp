#ifndef _BLASR_TUPLE_LIST_HPP_
#define _BLASR_TUPLE_LIST_HPP_

#include <stdint.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Types.h"
#include "tuples/TupleMetrics.hpp"

template<typename T>
class TupleList {
    int listLength;
    TupleMetrics tm;
    public:
    typedef T Tuple;
    std::vector<T> tupleList;

    TupleList(); 

    void Reset(); 
    
    T &operator[](int index); 

    void GetTupleMetrics(TupleMetrics &ptm); 
    
    void SetTupleMetrics(TupleMetrics &ptm); 
    
    int size();
    
    int GetLength();
    
    int InitFromFile(std::string &fileName); 

    void clear(); 

    int WriteToFile(std::string &fileName); 

    //
    // Find one instance of a match.
    //
    int Find(T& tuple); 

    //
    // Find the boundaries of all instances of a match.
    //
    void FindAll(T &tuple, 
        typename std::vector<T>::const_iterator &firstPos, 
        typename std::vector<T>::const_iterator &endPos ); 

    void Append( T&tuple); 

    void Insert(T&tuple); 

    void Sort(); 

    void Print(); 
};

#include "TupleListImpl.hpp"
#endif // _BLASR_TUPLE_LIST_HPP_
