#include "libconfig.h"
#ifdef USE_PBBAM
#include "HDFPulseCallsWriter.hpp"
#include <ctype.h>

const std::vector<PacBio::BAM::BaseFeature>  HDFPulseCallsWriter::ValidQVEnums = 
{     PacBio::BAM::BaseFeature::PULSE_CALL
    , PacBio::BAM::BaseFeature::LABEL_QV
    , PacBio::BAM::BaseFeature::PKMID
    , PacBio::BAM::BaseFeature::PKMEAN
    , PacBio::BAM::BaseFeature::PULSE_MERGE_QV
    , PacBio::BAM::BaseFeature::ALT_LABEL
    , PacBio::BAM::BaseFeature::ALT_LABEL_QV
    , PacBio::BAM::BaseFeature::START_FRAME
    , PacBio::BAM::BaseFeature::PULSE_CALL_WIDTH 
};

std::vector<PacBio::BAM::BaseFeature> 
HDFPulseCallsWriter::WritableQVs(const std::vector<PacBio::BAM::BaseFeature> & qvsToWrite) {
    std::vector<PacBio::BAM::BaseFeature> ret;
    for(auto qv : qvsToWrite) {
        // Filter qvs which are not in format specification.
        if (std::find(ValidQVEnums.begin(), ValidQVEnums.end(), qv) != ValidQVEnums.end()) {
            if (std::find(ret.begin(), ret.end(), qv) == ret.end()) ret.push_back(qv); 
        }
    }
    return ret;
}

HDFPulseCallsWriter::HDFPulseCallsWriter(const std::string & filename,
                                         HDFGroup & parentGroup,
                                         const std::map<char, size_t> & baseMap,
                                         const std::vector<PacBio::BAM::BaseFeature> & qvsToWrite)
    : HDFWriterBase(filename)
    , parentGroup_(parentGroup)
    , baseMap_(baseMap)
    , qvsToWrite_({}) // Input qvsToWrite must be checked.
    , zmwWriter_(nullptr)
{
    // Add PulseCalls as a child group to the parent group.
    AddChildGroup(parentGroup_, pulsecallsGroup_, PacBio::GroupNames::pulsecalls);

    this->qvsToWrite_ = WritableQVs(qvsToWrite);

    // Any QVs to write?
    if (qvsToWrite_.size() == 0) {
        AddErrorMessage("No QVs to write.");
        return;
    }

    // Initialize QV groups
    if (not InitializeQVGroups()) {
        AddErrorMessage("Failed to initialize QV Groups.");
        return;
    }

    // Create a zmwWriter.
    zmwWriter_.reset(new HDFZMWWriter(Filename(), pulsecallsGroup_, true, baseMap));

    // Note: ignore /PulseCalls/ZMWMetrics none of its metrics exist in BAM.
}

std::vector<std::string> HDFPulseCallsWriter::Errors(void) const {
    std::vector<std::string> retErrors = this->errors_;
    if (zmwWriter_) {
        const std::vector<std::string> & zmwErrors = zmwWriter_->Errors();
        retErrors.insert(retErrors.end(), zmwErrors.begin(), zmwErrors.end());
    }
    return retErrors;
}

HDFPulseCallsWriter::~HDFPulseCallsWriter(void) {
    this->Close();
}

bool HDFPulseCallsWriter::InitializeQVGroups(void) {
    int ret = 1;
    if (_HasQV(PacBio::BAM::BaseFeature::PULSE_CALL)) 
        ret *= pulseCallArray_.Initialize(pulsecallsGroup_,      PacBio::GroupNames::channel);
        ret *= isPulseArray_.Initialize(pulsecallsGroup_,        PacBio::GroupNames::ispulse);
    if (_HasQV(PacBio::BAM::BaseFeature::LABEL_QV))
        ret *= labelQVArray_.Initialize(pulsecallsGroup_,        PacBio::GroupNames::labelqv);
    if (_HasQV(PacBio::BAM::BaseFeature::PKMEAN))
        ret *= pkmeanArray_.Initialize(pulsecallsGroup_,         PacBio::GroupNames::meansignal);
    if (_HasQV(PacBio::BAM::BaseFeature::PULSE_MERGE_QV))
        ret *= pulseMergeQVArray_.Initialize(pulsecallsGroup_,   PacBio::GroupNames::mergeqv);
    if (_HasQV(PacBio::BAM::BaseFeature::PKMID))
        ret *= pkmidArray_.Initialize(pulsecallsGroup_,          PacBio::GroupNames::midsignal);
    if (_HasQV(PacBio::BAM::BaseFeature::START_FRAME))
        ret *= startFrameArray_.Initialize(pulsecallsGroup_,     PacBio::GroupNames::startframe);
    if (_HasQV(PacBio::BAM::BaseFeature::PULSE_CALL_WIDTH))
        ret *= pulseCallWidthArray_.Initialize(pulsecallsGroup_, PacBio::GroupNames::widthinframes);
    if (_HasQV(PacBio::BAM::BaseFeature::ALT_LABEL))
        ret *= altLabelArray_.Initialize(pulsecallsGroup_,       PacBio::GroupNames::altlabel);
    if (_HasQV(PacBio::BAM::BaseFeature::ALT_LABEL_QV))
        ret *= altLabelQVArray_.Initialize(pulsecallsGroup_,     PacBio::GroupNames::altlabelqv);
    return (ret != 0);
}


bool HDFPulseCallsWriter::WriteBaseCallerVersion(const std::string & basecallerVersion) {
    if (basecallerVersion.empty()) {
        AddErrorMessage("BaseCallerVersion must not be empty!");
        return false;
    }
    changeListIDAtom_.Create(pulsecallsGroup_.group, 
                             PacBio::AttributeNames::Common::changelistid,
                             basecallerVersion);
    return true;
}

bool HDFPulseCallsWriter::WriteOneZmw(const SMRTSequence & read) {
    const PacBio::BAM::BamRecord & record = read.bamRecord;

    if (zmwWriter_) 
        zmwWriter_->WriteOneZmw(record);

    _WritePulseCall(record); // Write PulseCall and IsPulse
    _WriteLabelQV(record);
    _WritePkmean(record);
    _WritePulseMergeQV(record);
    _WritePkmid(record);
    _WriteStartFrame(record);
    _WritePulseCallWidth(record);
    _WriteAltLabel(record);
    _WriteAltLabelQV(record);

    return Errors().empty();
}

bool HDFPulseCallsWriter::_CheckRead(const PacBio::BAM::BamRecord & read, 
                                     const uint32_t qvLength,
                                     const std::string & qvName) {
    // Tag 'pb' will not be available until 3.0.1, bug 29486
    return true;
    /*
    // FIXME: pbbam should provide HasPulseBlockSize() and PulseBlockSize().
    if (read.Impl().HasTag("pb")) {
        if (qvLength != read.Impl().TagValue("pb").ToUInt32()) {
            AddErrorMessage(std::string(qvName) + "'s size does not match PulseBlockSize in read " + read.FullName());
            return false;
        } else {
            return true;
        }
    } else {
        AddErrorMessage(std::string("Tag PulseBlockSize is absent in read ") + read.FullName());
        return false;
    }
    */
}

bool HDFPulseCallsWriter::_WritePulseCall(const PacBio::BAM::BamRecord & read) {
    if (HasPulseCall()) {
        if (read.HasPulseCall()) {
            // Write both PulseCall (i.e., Channel) and IsPulse
            const std::string & pulsecall = read.PulseCall();
            const unsigned int length = pulsecall.size();
            _CheckRead(read, length, "PulseCall");
            std::vector<uint8_t> channel; channel.resize(length);
            uint32_t num_bases = 0;
            for (size_t i = 0; i < length; i++) {
                const char base = pulsecall[i];
                if (base == 'A' or base == 'C' or base == 'G' or base == 'T') {
                    channel[i] = static_cast<uint8_t>(baseMap_[std::toupper(base)]);
                    num_bases += 1;
                } else if (base == 'a' or base == 'c' or base == 'g' or base == 't') {
                    channel[i] = static_cast<uint8_t>(baseMap_[std::toupper(base)]);
                } else {
                    AddErrorMessage(std::string("Unrecognizable base in PulseCall of " + read.FullName()));
                }
            }
            if (num_bases != read.Sequence().size()) {
                AddErrorMessage(std::string("Number of bases in PulseCall does not match BaseCall in read ") + read.FullName());
            }
            pulseCallArray_.Write(&channel[0], length);

            std::vector<uint8_t> ispulse(length, 1); // all pulses in BAM are real pulses
            isPulseArray_.Write(&ispulse[0], length);
        } else {
            AddErrorMessage(std::string("PulseCall is absent in read " + read.FullName()));
        }
    }
    return Errors().empty();
}

bool HDFPulseCallsWriter::_WriteLabelQV(const PacBio::BAM::BamRecord & read) {
    if (HasLabelQV()) {
        if (read.HasLabelQV()) {
            const PacBio::BAM::QualityValues & qvs = read.LabelQV();
            std::vector<uint8_t> data(qvs.cbegin(), qvs.cend());
            _CheckRead(read, data.size(), "LabelQV");
            labelQVArray_.Write(&data[0], data.size());
        } else {
            AddErrorMessage(std::string("LabelQV is absent in read " + read.FullName()));
        }
    }
    return Errors().empty();
}

bool HDFPulseCallsWriter::_WritePkmean(const PacBio::BAM::BamRecord & read) {
    if (HasPkmean()) {
        if (read.HasPkmean()) {
            const std::vector<float> & qvs = read.Pkmean();
            _CheckRead(read, qvs.size(), "Pkmean");
            std::vector<HalfWord> data(qvs.begin(), qvs.end());
            pkmeanArray_.Write(&data[0], qvs.size());
        } else {
            AddErrorMessage(std::string("Pkmean is absent in read " + read.FullName()));
        }
    }
    return Errors().empty();
}

bool HDFPulseCallsWriter::_WritePulseMergeQV(const PacBio::BAM::BamRecord & read) {
    if (HasPulseMergeQV()) {
        if (read.HasPulseMergeQV()) {
            const PacBio::BAM::QualityValues & qvs = read.PulseMergeQV();
            std::vector<uint8_t> data(qvs.cbegin(), qvs.cend());
            _CheckRead(read, data.size(), "PulseMergeQV");
            pulseMergeQVArray_.Write(&data[0], data.size());
        } else {
            AddErrorMessage(std::string("PulseMergeQV is absent in read " + read.FullName()));
        }
    }
    return Errors().empty();
}

bool HDFPulseCallsWriter::_WritePkmid(const PacBio::BAM::BamRecord & read) {
    if (HasPkmid()) {
        if (read.HasPkmid()) {
            const std::vector<float> & qvs = read.Pkmid();
            std::vector<HalfWord> data(qvs.begin(), qvs.end());
            _CheckRead(read, data.size(), "Pkmid");
            pkmidArray_.Write(&data[0], qvs.size());
        } else {
            AddErrorMessage(std::string("Pkmid is absent in read " + read.FullName()));
        }
    }
    return Errors().empty();
}

bool HDFPulseCallsWriter::_WriteStartFrame(const PacBio::BAM::BamRecord & read) {
    if (HasStartFrame()) {
        if (read.HasStartFrame()) {
            const std::vector<uint32_t> data = read.StartFrame();
            _CheckRead(read, data.size(), "StartFrame");
            startFrameArray_.Write(&data[0], data.size());
        } else {
            AddErrorMessage(std::string("StartFrame is absent in read " + read.FullName()));
        }
    }
    return Errors().empty();
}

bool HDFPulseCallsWriter::_WritePulseCallWidth(const PacBio::BAM::BamRecord & read) {
    if (HasPulseCallWidth()) {
        if (read.HasPulseCallWidth()) {
            //FIXME: pbbam PulseCallWidth().Data() returns incorrect vector (e.g., size)
            const PacBio::BAM::Tag & tag = read.Impl().TagValue("px");
            std::vector<uint16_t> data = tag.ToUInt16Array();
            _CheckRead(read, data.size(), "PulseCallWidth");
            pulseCallWidthArray_.Write(&data[0], data.size());
        } else {
            AddErrorMessage(std::string("PulseCallWidth is absent in read " + read.FullName()));
        }
    }
    return Errors().empty();
}

bool HDFPulseCallsWriter::_WriteAltLabel(const PacBio::BAM::BamRecord & read) {
    if (HasAltLabel()) {
        if (read.HasAltLabelTag()) {
            const std::string & tags = read.AltLabelTag();
            std::vector<unsigned char> data(tags.begin(), tags.end());
            _CheckRead(read, data.size(), "AltLabel");
            altLabelArray_.Write(&data[0], tags.size());
        } else {
            AddErrorMessage(std::string("AltLabel is absent in read " + read.FullName()));
        }
    }
    return Errors().empty();
}

bool HDFPulseCallsWriter::_WriteAltLabelQV(const PacBio::BAM::BamRecord & read) {
    if (HasAltLabelQV()) {
        if (read.HasAltLabelQV()) {
            const PacBio::BAM::QualityValues & qvs = read.AltLabelQV();
            std::vector<uint8_t> data(qvs.begin(), qvs.end());
            _CheckRead(read, data.size(), "AltLabelQV");
            altLabelQVArray_.Write(&data[0], data.size());
        } else {
            AddErrorMessage(std::string("AltLabelQV is absent in read " + read.FullName()));
        }
    }
    return Errors().empty();
}

void HDFPulseCallsWriter::Flush(void) {
    if (HasPulseCall())      pulseCallArray_.Flush();
    if (HasIsPulse())        isPulseArray_.Flush();
    if (HasLabelQV())        labelQVArray_.Flush();
    if (HasPkmean())         pkmeanArray_.Flush();
    if (HasPulseMergeQV())   pulseMergeQVArray_.Flush();
    if (HasPkmid())          pkmidArray_.Flush();
    if (HasStartFrame())     startFrameArray_.Flush();
    if (HasPulseCallWidth()) pulseCallWidthArray_.Flush();
    if (HasAltLabel())       altLabelArray_.Flush();
    if (HasAltLabelQV())     altLabelQVArray_.Flush();

    if (zmwWriter_)          zmwWriter_->Flush();
}

void HDFPulseCallsWriter::Close(void) {
    this->Flush();
    if (HasPulseCall())      pulseCallArray_.Close();
    if (HasIsPulse())        isPulseArray_.Close();
    if (HasLabelQV())        labelQVArray_.Close();
    if (HasPkmean())         pkmeanArray_.Close();
    if (HasPulseMergeQV())   pulseMergeQVArray_.Close();
    if (HasPkmid())          pkmidArray_.Close();
    if (HasStartFrame())     startFrameArray_.Close();
    if (HasPulseCallWidth()) pulseCallWidthArray_.Close();
    if (HasAltLabel())       altLabelArray_.Close();
    if (HasAltLabelQV())     altLabelQVArray_.Close();
}

#endif
