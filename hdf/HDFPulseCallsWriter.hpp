#ifndef _BLASR_HDF_PULSECALLS_WRITER_HPP_
#define _BLASR_HDF_PULSECALLS_WRITER_HPP_

#include "libconfig.h"
#ifdef USE_PBBAM
#include <memory>
#include <algorithm>
#include "HDFAtom.hpp"
#include "HDFWriterBase.hpp"
#include "HDFZMWWriter.hpp"

class HDFPulseCallsWriter: public HDFWriterBase {
    /// \name \{
public:
    /// \brief a vector of QVs in PulseCalls
    static const std::vector<PacBio::BAM::BaseFeature> ValidQVEnums;

    /// \brief Sanity check QVs to add. Remove QVs which are 
    ///        not included in file format specification, and
    ///        remove redundant QVs.
    /// \returns writable QVs that will be copied to PulseCalls
    static std::vector<PacBio::BAM::BaseFeature> 
        WritableQVs(const std::vector<PacBio::BAM::BaseFeature> & qvsToWrite);

public:
    HDFPulseCallsWriter(const std::string & filename,
                       HDFGroup & parentGroup,
                       const std::map<char, size_t> & baseMap,
                       const std::vector<PacBio::BAM::BaseFeature> & qvsToWrite = {});

    ~HDFPulseCallsWriter(void);

    /// \brief Write base caller version (changeListId)
    bool WriteBaseCallerVersion(const std::string & basecallerVersion);

    /// \brief Write a zmw read.
    bool WriteOneZmw(const SMRTSequence & read);

    /// \brief return a vector of QV name strings to write.
    const std::vector<std::string> & QVNamesToWrite(void) const;

    void Flush(void);

    void Close(void);

    std::vector<std::string> Errors(void) const;

public:
    /// \returns true if has PulseCall dataset and pulseCallArray_
    ///          has been initialized.
    inline bool HasPulseCall(void) const;
    inline bool HasIsPulse(void) const;
    inline bool HasLabelQV(void) const;
    inline bool HasPkmean(void) const;
    inline bool HasPulseMergeQV(void) const;
    inline bool HasPkmid(void) const;
    inline bool HasStartFrame(void) const;
    inline bool HasPulseCallWidth(void) const;
    inline bool HasAltLabel(void) const;
    inline bool HasAltLabelQV(void) const;

private:
    inline bool _HasQV(const PacBio::BAM::BaseFeature & qvToQuery) const;

    /// Write datasets
    bool _WritePulseCall(const PacBio::BAM::BamRecord & read);
    bool _WriteLabelQV(const PacBio::BAM::BamRecord & read);
    bool _WritePkmean(const PacBio::BAM::BamRecord & read);
    bool _WritePulseMergeQV(const PacBio::BAM::BamRecord & read);
    bool _WritePkmid(const PacBio::BAM::BamRecord & read);
    bool _WriteStartFrame(const PacBio::BAM::BamRecord & read);
    bool _WritePulseCallWidth(const PacBio::BAM::BamRecord & read);
    bool _WriteAltLabel(const PacBio::BAM::BamRecord & read);
    bool _WriteAltLabelQV(const PacBio::BAM::BamRecord & read);

    /// \returns If record has Tag PulseBlockSize and PulseBlockSize 
    ///          equals qvLength. Otherwise, add error message and 
    ///          return false.
    bool _CheckRead(const PacBio::BAM::BamRecord & record, 
                    const uint32_t qvLength,
                    const std::string & qvName);

private:
    /// \brief Create and initialize QV groups.
    /// \returns Whether or not QV groups initialized successfully.
    bool InitializeQVGroups(void);

private:
    HDFGroup & parentGroup_;
    std::map<char, size_t> baseMap_;
    std::vector<PacBio::BAM::BaseFeature> qvsToWrite_;
    std::unique_ptr<HDFZMWWriter> zmwWriter_;
	HDFGroup pulsecallsGroup_;
	HDFAtom<string> changeListIDAtom_;

private:
	/// \brief Datasets which exist in both PulseCalls and BAM.
    ///  PulseCall   pc --> PulseCalls/Channel --> type Z
    //                  --> e.g., GaAT --> PulseCall
    //                  --> lower case indicate that the base was squashed by P2B
    ///  IsPulse     pc --> Must be infered from pc
    ///  LabelQV     pq --> PulseCalls/MergeQV --> e.g., 20,20,12,20
    ///  Pkmean      pa --> PulseCalls/MeanSignal
    ///  PulseMergeQV
    ///              pg --> PulseCalls/MergeQV
    ///  Pkmid       pm --> PulseCalls/MidSignal
    ///  StartFrame
    ///              pd --> PulseCalls/StartFrame
    ///                 --> Note that BaseCalls/PreBaseFrames is defined as 'ip' in BAM
    ///  PulseCallWidth
    ///              px --> PulseCalls/WidthInFrames
    ///                 --> Note that BaseCalls/WidthInFrames is defined as 'pw' in BAM
    ///
    /// \brief Datasets which exist in BAM but not defined in PulseCalls
    ///  AltLabel    pt  --> Z, e.g., ---C, second best label, '-' if not alternative applicable
    ///  AltLableQV  pv  --> B,C, e.g., 0,0,0,3, 
    ///
    /// \brief Datasets which are included in PulseCalls but not in BAM
    ///  Chi2, MaxSignal, MidStdDev, ClassifierQV
    ///
	BufferedHDFArray<unsigned char> pulseCallArray_;
	BufferedHDFArray<unsigned char> isPulseArray_;
	BufferedHDFArray<unsigned char> labelQVArray_; 
    // FIXME: pkmean is 2D array (one value per pulse per channel) in H5,
    // while is 1D array (one value per pulse) in BAM.
	BufferedHDFArray<HalfWord>      pkmeanArray_;
	BufferedHDFArray<unsigned char> pulseMergeQVArray_;
	BufferedHDFArray<HalfWord>      pkmidArray_;
	BufferedHDFArray<uint32_t>      startFrameArray_;
	BufferedHDFArray<HalfWord>      pulseCallWidthArray_;
	BufferedHDFArray<unsigned char> altLabelArray_;
	BufferedHDFArray<unsigned char> altLabelQVArray_;

    /// \}
};

inline
bool HDFPulseCallsWriter::_HasQV(const PacBio::BAM::BaseFeature & qvToQuery) const {
    return (std::find(qvsToWrite_.begin(), qvsToWrite_.end(), qvToQuery) != qvsToWrite_.end());
}

inline
bool HDFPulseCallsWriter::HasPulseCall(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::PULSE_CALL) and
         pulseCallArray_.IsInitialized());}

inline
bool HDFPulseCallsWriter::HasIsPulse(void) const
// IsPulse is inferred from PulseCall
{return (_HasQV(PacBio::BAM::BaseFeature::PULSE_CALL) and 
         isPulseArray_.IsInitialized());}

inline
bool HDFPulseCallsWriter::HasLabelQV(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::LABEL_QV) and
         labelQVArray_.IsInitialized());}

inline
bool HDFPulseCallsWriter::HasPkmean(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::PKMEAN) and
         pkmeanArray_.IsInitialized());}

inline
bool HDFPulseCallsWriter::HasPulseMergeQV(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::PULSE_MERGE_QV) and
         pulseMergeQVArray_.IsInitialized());}

inline
bool HDFPulseCallsWriter::HasPkmid(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::PKMID) and 
         pkmidArray_.IsInitialized());}

inline
bool HDFPulseCallsWriter::HasStartFrame(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::START_FRAME) and 
         startFrameArray_.IsInitialized());}

inline
bool HDFPulseCallsWriter::HasPulseCallWidth(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::PULSE_CALL_WIDTH) and
         pulseCallWidthArray_.IsInitialized());}

inline
bool HDFPulseCallsWriter::HasAltLabel(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::ALT_LABEL) and
         altLabelArray_.IsInitialized());}

inline
bool HDFPulseCallsWriter::HasAltLabelQV(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::ALT_LABEL_QV) and
         altLabelQVArray_.IsInitialized());}

#endif // end of #ifdef USE_PBBAM
#endif // end of #ifdef _BLASR_HDF_PULSECALLS_WRITER_HPP_
