#include "DatasetCollection.hpp"

void DatasetCollection::MakeFieldRequired(std::string &fieldName) {
    includedFields[fieldName] = true;
    requiredFields[fieldName] = true;
}

void DatasetCollection::MakeFieldOptional(std::string &fieldName) {
    includedFields[fieldName] = true;
    requiredFields[fieldName] = false;
}

void DatasetCollection::InitializeAllFields(bool value) {
    int f;
    for (f = 0; f < fieldNames.size(); f++ ) {
        includedFields[fieldNames[f]] = value;
    }
}

void DatasetCollection::InitializeFields(std::vector<std::string> &fieldList) {
    int i;
    for (i = 0; i < fieldList.size(); i++) {
        includedFields[fieldList[i]] = true;
    }
}

void DatasetCollection::InitializeFields(std::vector<char*> &fieldList) {
    int i;
    InitializeAllFields(false);
    for (i = 0; i < fieldList.size(); i++) {
        includedFields[fieldList[i]] = true;
    }
}

int DatasetCollection::IncludeField(std::string fieldName) {
    if (includedFields.find(fieldName) == includedFields.end()) {
        return 0;
    }	
    else {
        includedFields[fieldName] = true;
    }
    return 1;
}

bool DatasetCollection::FieldIsIncluded(std::string fieldName) {
    if (includedFields.find(fieldName) == includedFields.end()) {
        return false;
    }
    else {
        return includedFields[fieldName];
    }
}

bool DatasetCollection::ContainsField(std::string fieldName) {
    int f;
    for (f = 0; f < fieldNames.size(); f++) {
        if (fieldNames[f] == fieldName) return true;
    }
    return false;
}

