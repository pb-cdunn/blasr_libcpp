#include "ReferenceSequence.hpp"

const char* SAMReferenceSequence::SAMReferenceSequenceFieldNames[] = {"SN", "LN"};

void SAMReferenceSequence::StoreValues(std::vector<SAMKeywordValuePair> &kvPairs, int lineNumber) {
  int i;
  std::vector<bool> usedFields;
  usedFields.resize(SQ_LN);
  std::fill(usedFields.begin(), usedFields.end(), false);
  for (i = 0; i < kvPairs.size(); i++) {
    if (kvPairs[i].key == "SN") {
      sequenceName = kvPairs[i].value;
      usedFields[SQ_SN] = true;
    }
    else if (kvPairs[i].key == "LN") {
      StoreValue(kvPairs[i].value, length);
      usedFields[SQ_SN] = true;
    }
  }
  for (i = 0; i < usedFields.size(); i++) {
    if (usedFields[i] == false) {
      std::cout << "SQ specifier missing " << SAMReferenceSequenceFieldNames[i] << std::endl;
   }
  }
}

const char* SAMFullReferenceSequence::SAMFullReferenceSequenceFieldNames[] = {"AS", "M5", "SP", "UR"};

void SAMFullReferenceSequence::StoreValues(std::vector<SAMKeywordValuePair> &kvPairs,
                                           int lineNumber) {
  SAMReferenceSequence::StoreValues(kvPairs, lineNumber);
  int i;
  for (i = 0; i < kvPairs.size(); i++ ){
    if (kvPairs[i].key == "AS") {
      genomeAssembly = kvPairs[i].value;
    }
    else if (kvPairs[i].key == "M5") {
      md5 = kvPairs[i].value;
    }
    else if (kvPairs[i].key == "SP") {
      species = kvPairs[i].value;
    }
    else if (kvPairs[i].key == "UR") {
      uri = kvPairs[i].value;
    }
  }
}
