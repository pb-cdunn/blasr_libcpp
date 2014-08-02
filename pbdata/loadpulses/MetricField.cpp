#include "MetricField.hpp"

Field::Field(std::string n, FieldType t) {
    name = n;
    type = t;
}

bool Field::operator==(const Field &another) const {
    return (name == another.name && 
            type == another.type);
}

FieldsRequirement::FieldsRequirement(const std::string & m) {
    metric = m;
    if (metric == "QualityValue"   ||  metric == "InsertionQV"     ||
        metric == "MergeQV"        ||  metric == "DeletionQV"      ||
        metric == "DeletionTag"    ||  metric == "SubstitutionTag" ||
        metric == "SubstitutionQV" ||  metric == "PreBaseFrames"   ||
        metric == "PulseIndex"     ||  metric == "Basecall") {
        fieldsUseBasFile.push_back(Field (metric         , BasField));

    } else if (metric == "ClassifierQV") {
        fieldsUsePlsFile.push_back(Field (metric         , PlsField));
        fieldsUsePlsFile.push_back(Field ("NumEvent"     , PlsField));
        fieldsUsePlsFile.push_back(Field ("PulseIndex"   , BasField));

    } else if (metric == "StartTimeOffset") {
        fieldsUsePlsFile.push_back(Field ("StartFrame"   , PlsField));
        fieldsUsePlsFile.push_back(Field ("NumEvent"     , PlsField));
        fieldsUsePlsFile.push_back(Field ("PulseIndex"   , BasField));

    } else if (metric == "StartFramePulse") {// Compute StartFrame from PulseCalls only
        fieldsUsePlsFile.push_back(Field ("StartFrame"   , PlsField));
        fieldsUsePlsFile.push_back(Field ("NumEvent"     , PlsField));
        fieldsUsePlsFile.push_back(Field ("PulseIndex"   , BasField));

    } else if (metric == "StartFrameBase") {// Compute StartFrame from BaseCalls only
        fieldsUseBasFile.push_back(Field ("PreBaseFrames", BasField));
        fieldsUseBasFile.push_back(Field ("WidthInFrames", BasField));

    } else if (metric == "WhenStarted") {
        // WhenStarted does not require any field because it only requires an attribute
    
    } else if (metric == "pkmid") {
        fieldsUsePlsFile.push_back(Field ("MidSignal"    , PlsField));
        fieldsUsePlsFile.push_back(Field ("NumEvent"     , PlsField));
        fieldsUsePlsFile.push_back(Field ("PulseIndex"   , BasField));

    } else if (metric == "Light") {
        fieldsUsePlsFile.push_back(Field ("WidthInFrames", PlsField));
        fieldsUsePlsFile.push_back(Field ("MeanSignal"   , PlsField));
        fieldsUsePlsFile.push_back(Field ("NumEvent"     , PlsField));
        fieldsUsePlsFile.push_back(Field ("PulseIndex"   , BasField));

    } else if (metric == "PulseWidth"     ||  metric == "WidthInFrames") {
        // Both metrics require a field "WidthInFrames", which can be read from 
        // either bas.h5 or pls.h5.
        fieldsUseBasFile.push_back(Field ("WidthInFrames", BasField));

        fieldsUsePlsFile.push_back(Field ("WidthInFrames", PlsField));
        fieldsUsePlsFile.push_back(Field ("NumEvent"     , PlsField));
        fieldsUsePlsFile.push_back(Field ("PulseIndex"   , BasField));

    } else if (metric == "StartFrame") { 
        // Compute StartFrame from either PulseCalls or BaseCalls
        fieldsUseBasFile.push_back(Field ("PreBaseFrames", BasField));
        fieldsUseBasFile.push_back(Field ("WidthInFrames", BasField));

        fieldsUsePlsFile.push_back(Field ("StartFrame"   , PlsField));
        fieldsUsePlsFile.push_back(Field ("NumEvent"     , PlsField));
        fieldsUsePlsFile.push_back(Field ("PulseIndex"   , BasField));
    } else if (metric == "IPD") {
        // IPD can be obtained from basFile.PreBaseFrames or computed from 
        // plsFile.WidthInFrames and plsFile.StartFrame. Use the second method if possible
        fieldsUseBasFile.push_back(Field ("PreBaseFrames", BasField));

        fieldsUsePlsFile.push_back(Field ("StartFrame"   , PlsField));
        fieldsUsePlsFile.push_back(Field ("WidthInFrames", PlsField));
        fieldsUsePlsFile.push_back(Field ("NumEvent"     , PlsField));
        fieldsUsePlsFile.push_back(Field ("PulseIndex"   , BasField));
    } else if (metric == "") {
        // No metric, no required fields.
    } else {
        std::cout << "ERROR, metric [" << metric << "] is not supported." << std::endl;
        exit(1);
    }
}
