#include "SAMHeader.hpp"

void SAMHeader::StoreValues(std::vector<SAMKeywordValuePair> &kvPairs,
                            int lineNumber) {
  int i;
  for ( i = 0; i < kvPairs.size(); i++) {
    if (kvPairs[i].key == "VN") {
      formatVersion = kvPairs[i].value;
    }
    else if (kvPairs[i].key == "SO") {
      if (kvPairs[i].value == "unknown" ||
          kvPairs[i].value == "unsorted") {
        sortingOrder = unknown;
      }
      else if (kvPairs[i].value == "sorted") {
        sortingOrder = sorted;
      }
      else if (kvPairs[i].value == "queryname") {
        sortingOrder =queryname;
      }
      else if (kvPairs[i].value == "coordinate") {
        sortingOrder = coordinate;
      }
      else {
        std::cout << "Invalid sorting order " << kvPairs[i].value << " at line " << lineNumber;
      }
    }
  }
}
