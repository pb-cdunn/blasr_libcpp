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
