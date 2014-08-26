#include <iostream>
#include "HDFCmpExperimentGroup.hpp"

using namespace std;

bool HDFCmpExperimentGroup::Create(HDFGroup &parent, 
    string experimentGroupName) {

    parent.AddGroup(experimentGroupName);
    if (experimentGroup.Initialize(parent.group, experimentGroupName) == 0) { return 0; }
    alignmentArray.Create(experimentGroup, "AlnArray");
    return true;
}


void HDFCmpExperimentGroup::AddAlignment(std::vector<unsigned char> &alignment, 
    unsigned int &offsetBegin, unsigned int &offsetEnd) {

    int curNRows = alignmentArray.size();
    offsetBegin = offsetEnd = 0;
    if (alignment.size() == 0 ) {
        // 
        // Do not increment anything.
        //
        return;
    }

    // Make a copy of alignment.
    vector<unsigned char> paddedAlignment = alignment;
    // Pad '0' to the end of the alignment.
    paddedAlignment.push_back(0);

    offsetBegin = alignmentArray.size(); // 0 based, inclusive
    offsetEnd   = offsetBegin + alignment.size(); // 0 based, exclusive
    // alignmentArray[offsetEnd] is not a part of the real alignment, it is the padded 0.
    alignmentArray.Write(&paddedAlignment[0], paddedAlignment.size());
}

//template<typename T>
//void HDFCmpExperimentGroup::AddQualityValues(const std::vector<T> &qualityValues,
//                                             const std::string &fieldName,
//                                             unsigned int *offsetBegin,
//                                             unsigned int *offsetEnd) {
//
//  std::vector<T> paddedQualityValues = qualityValues;
//  paddedQualityValues.push_back(0);
//  HDFArray<T> *arrayPtr = NULL;
//  
//  // This seems to be how we do it 
//  if (fieldName == "DeletionQV") {
//      arrayPtr = &deletionQV;
//  } else if (fieldName == "InsertionQV") {
//      arrayPtr = &insertionQV;
//  } else if (fieldName == "MergeQV") {
//      arrayPtr = &mergeQV;
//  } else if (fieldName == "SubstitutionQV") {
//      arrayPtr = &substitutionQV;
//  } else if (fieldName == "DeletionTag") {
//      arrayPtr = &deletionTag;
//  } else if (fieldName == "SubstitutionTag") {
//      arrayPtr = &substitutionTag;
//  } else {
//      assert(false);
//  }
//
//  *offsetBegin = arrayPtr->size();
//  *offsetEnd = arrayPtr->size() + qualityValues.size();
//  
//  arrayPtr->Write(&paddedQualityValues[0], paddedQualityValues.size());
//}
//
//// One for tags, one for QVs
//template void HDFCmpExperimentGroup::AddQualityValues<char>(
//        const std::vector<char>&, const std::string&,
//        unsigned int*, unsigned int*);
//
//template void HDFCmpExperimentGroup::AddQualityValues<UChar>(
//        const std::vector<UChar>&, const std::string&,
//        unsigned int*, unsigned int*);
//
int HDFCmpExperimentGroup::Initialize(HDFGroup &refGroup, 
    string experimentGroupName, set<string> &fieldNames) {
    //
    // Normal initialization that prepares for reading alignments
    //
    Initialize(refGroup, experimentGroupName);

    //
    // Field initialization for reading in pulse/quality information.
    //
    set<string>::iterator fieldNameIt, fieldEnd;
    fieldEnd = fieldNames.end();
    for (fieldNameIt = fieldNames.begin(); fieldNameIt != fieldEnd; ++fieldNameIt) {
        if (supportedFields.find(*fieldNameIt) != supportedFields.end() and
                experimentGroup.ContainsObject(*fieldNameIt)) {
            fields[*fieldNameIt]->Initialize(experimentGroup, *fieldNameIt);
        }
        else {
            cout << "Unable to initialize requested field " << *fieldNameIt << " in experiment group " << experimentGroupName << endl;
        }
    }
    return 1;
}

int HDFCmpExperimentGroup::Initialize(HDFGroup &refGroup, string experimentGroupName) {

    if (experimentGroup.Initialize(refGroup.group, experimentGroupName) == 0) { return 0; }
    if (alignmentArray.Initialize(experimentGroup, "AlnArray") == 0) { return 0; }
    return 1;
}


HDFCmpExperimentGroup::HDFCmpExperimentGroup() {
    fields["StartTimeOffset"] = &this->startTimeOffset;
    fields["QualityValue"] = &this->qualityValue;
    fields["IPD"] = &this->ipd;
    fields["PreBaseFrames"] = &this->preBaseFrames;
    fields["DeletionQV"] = &this->deletionQV;
    fields["InsertionQV"] = &this->insertionQV;
    fields["ClassifierQV"] = &this->classifierQV;
    fields["SubstitutionQV"] = &this->substitutionQV;
    fields["Light"] = &this->light;
    fields["WidthInFrames"] = &this->widthInFrames;
    fields["PulseWidth"] = &this->pulseWidth;
    fields["StartFrame"] = &this->startTime;
    // StartFrame computed from Pulse metrics and Base metrics
    fields["StartFramePulse"] = &this->startTimePulse;
    fields["StartFrameBase"] = &this->startTimeBase;

    fields["pkmid"] = &this->pkmid;
    fields["pkmax"] = &this->pkmax;
    fields["pkmean"] = &this->pkmean;
    fields["DeletionTag"] = &this->deletionTag;
    fields["SubstitutionTag"] = &this->substitutionTag;
    fields["PulseIndex"] = &this->pulseIndex;
    fields["MergeQV"] = &this->mergeQV;
}

// Return reference alignment AlnArray size in KB.
UInt HDFCmpExperimentGroup::GetAlnArraySize() {
    return alignmentArray.arrayLength / 1024 * sizeof (unsigned char);
}

void HDFCmpExperimentGroup::AddQVs(const std::vector<UChar> &qualityValues,
                                   const std::string &fieldName,
                                   unsigned int *offsetBegin,
                                   unsigned int *offsetEnd) {
    std::vector<UChar> paddedQualityValues = qualityValues;
    paddedQualityValues.push_back(0);
    HDFArray<UChar> *arrayPtr = NULL;
    
    // This seems to be how we do it 
    if (fieldName == "DeletionQV") {
        arrayPtr = &deletionQV;
    } else if (fieldName == "InsertionQV") {
        arrayPtr = &insertionQV;
    } else if (fieldName == "MergeQV") {
        arrayPtr = &mergeQV;
    } else if (fieldName == "SubstitutionQV") {
        arrayPtr = &substitutionQV;
    } else {
        assert(false);
    }
    
    if (!arrayPtr->isInitialized) arrayPtr->Initialize(experimentGroup, fieldName);
    *offsetBegin = arrayPtr->size();
    *offsetEnd = arrayPtr->size() + qualityValues.size();
    
    arrayPtr->Write(&paddedQualityValues[0], paddedQualityValues.size());
}

void HDFCmpExperimentGroup::AddTags(const std::vector<char> &qualityValues,
                                    const std::string &fieldName,
                                    unsigned int *offsetBegin,
                                    unsigned int *offsetEnd) {
    std::vector<char> paddedQualityValues = qualityValues;
    paddedQualityValues.push_back(0);
    HDFArray<char> *arrayPtr = NULL;
    
    if (fieldName == "DeletionTag") {
        arrayPtr = &deletionTag;
    } else if (fieldName == "SubstitutionTag") {
        arrayPtr = &substitutionTag;
    } else {
        assert(false);
    }

    if (!arrayPtr->isInitialized) arrayPtr->Initialize(experimentGroup, fieldName);
    *offsetBegin = arrayPtr->size();
    *offsetEnd = arrayPtr->size() + qualityValues.size();
    
    arrayPtr->Write(&paddedQualityValues[0], paddedQualityValues.size());
}

