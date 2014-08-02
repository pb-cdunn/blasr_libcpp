#include "HDFCmpSupportedFields.hpp"

HDFCmpSupportedFields::HDFCmpSupportedFields() {
    this->insert("StartTimeOffset");
    this->insert("QualityValue");
    this->insert("IPD");
    this->insert("PreBaseFrames");
    this->insert("DeletionQV");
    this->insert("InsertionQV");
    this->insert("ClassifierQV");
    this->insert("SubstitutionQV");
    this->insert("MergeQV");
    this->insert("Light");
    this->insert("WidthInFrames");
    this->insert("PulseWidth");
    this->insert("StartTime");
    this->insert("pkmid");
    this->insert("pkmax");
    this->insert("pkmean");
    this->insert("pkmean");
    this->insert("SubstitutionTag");
    this->insert("DeletionTag");
    this->insert("PulseIndex");

}
