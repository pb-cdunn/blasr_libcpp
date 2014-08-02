
template<typename T>
TupleList<T>::TupleList() {
    listLength = 0;
}

template<typename T>
void TupleList<T>::Reset() {
    std::vector<T>().swap(tupleList);
}

template<typename T>
T& TupleList<T>::operator[](int index) {
    return tupleList[index];
}

template<typename T>
void TupleList<T>::GetTupleMetrics(TupleMetrics &ptm) {
    ptm = tm;
}

template<typename T>
void TupleList<T>::SetTupleMetrics(TupleMetrics &ptm) {
    tm = ptm;
}

template<typename T>
int TupleList<T>::size() {
    return tupleList.size();
}

template<typename T>
int TupleList<T>::GetLength() {
    return tupleList.size();
}

template<typename T>
int TupleList<T>::InitFromFile(std::string &fileName) {
    std::ifstream listIn;
    listIn.open(fileName.c_str(), std::ios_base::binary);
    if (!listIn)
        return 0;
    listIn.read((char*) &listLength, sizeof(int));
    listIn.read((char*) &tm.tupleSize, sizeof(int));
    tm.InitializeMask();
    //list = new T[listLength];
    tupleList.resize(listLength);
    listIn.read((char*) &tupleList[0], sizeof(T) * listLength);
    return 1;
}

template<typename T>
void TupleList<T>::clear() {
    tupleList.clear();
    listLength = 0;
}

template<typename T>
int TupleList<T>::WriteToFile(std::string &fileName) {
    std::ofstream listOut;
    listOut.open(fileName.c_str(), std::ios_base::binary);
    if (!listOut)
        return 0;
    listLength = tupleList.size();
    std::cout << "writing tuple lis of length " << listLength << std::endl;
    listOut.write((char*) &listLength, sizeof(int));
    listOut.write((char*) &tm.tupleSize, sizeof(int));
    listOut.write((char*) &tupleList[0], sizeof(T)*listLength);
    return 1;
}

//
// Find one instance of a match.
//
template<typename T>
int TupleList<T>::Find( T& tuple)  {
    typename std::vector<T>::const_iterator begin, end, matchIt;
    begin = tupleList.begin();
    end   = tupleList.end();
    matchIt = lower_bound(begin, end, tuple);
    if (*matchIt != tuple) {
        return -1;
    }
    else {
        return matchIt - tupleList.begin();
    }
}

//
// Find the boundaries of all instances of a match.
//
template<typename T>
void TupleList<T>::FindAll(T &tuple, 
    typename std::vector<T>::const_iterator &firstPos, 
    typename std::vector<T>::const_iterator &endPos ) {
    firstPos = lower_bound(tupleList.begin(), tupleList.end(), tuple);
    typename std::vector<T>::const_iterator firstPos2;
    endPos = tupleList.end();
    endPos = upper_bound(firstPos, endPos, tuple);
    while (endPos != tupleList.end()) {
        if (*endPos != tuple) {
            return;
        }
        else {
            endPos++;
        }
    }
}

template<typename T>
void TupleList<T>::Append( T&tuple) {
    tupleList.push_back(tuple);
}

template<typename T>
void TupleList<T>::Insert(T&tuple) {
    // insert and maintain order.
    typename std::vector<T>::iterator pos;
    pos = std::lower_bound(tupleList.begin(), tupleList.end(), tuple);
    tupleList.insert(pos, tuple);
}

template<typename T>
void TupleList<T>::Sort() {
    sort(tupleList.begin(), tupleList.end());
}

template<typename T>
void TupleList<T>::Print() {
    int i;
    for (i = 0; i< tupleList.size(); i++) {
        std::cout << tupleList[i].tuple << std::endl;
    }
}
