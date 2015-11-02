#ifndef _BLASR_HDF_BASECALLS_WRITER_HPP_
#define _BLASR_HDF_BASECALLS_WRITER_HPP_

#include  "libconfig.h"
#ifdef USE_PBBAM
#include <memory>
#include <algorithm>
#include "HDFAtom.hpp"
#include "HDFWriterBase.hpp"
#include "HDFZMWWriter.hpp"
#include "HDFZMWMetricsWriter.hpp"

class HDFBaseCallsWriter: public HDFWriterBase {
    /// \name \{
public:
    /// \brief a vector of QVs in BaseCalls
    static const std::vector<PacBio::BAM::BaseFeature> ValidQVEnums;

    /// \brief Sanity check QVs to add. Remove QVs which are 
    ///        not included in file format specification, and
    ///        remove redundant QVs.
    /// \returns Writable QVs
    static std::vector<PacBio::BAM::BaseFeature>
    WritableQVs(const std::vector<PacBio::BAM::BaseFeature> & qvsToWrite);

public:
    HDFBaseCallsWriter(const std::string & filename,
                       HDFGroup & parentGroup,
                       const std::map<char, size_t> & baseMap,
                       const std::vector<PacBio::BAM::BaseFeature> & qvsToWrite = {},
                       const bool fakeQualityValue = true);

    ~HDFBaseCallsWriter(void);

    /// \brief Write base caller version (changeListId)
    bool WriteBaseCallerVersion(const std::string & basecallerVersion);

    /// \brief Write a zmw read.
    bool WriteOneZmw(const SMRTSequence & read);

    /// \brief return a vector of QV name strings to write.
    //const std::vector<std::string> & QVNamesToWrite(void) const;

    void Flush(void);

    void Close(void);

public:
    
    /// \returns true if FakeQualityValue() and qualityValueArray_ 
    ///          has been initialized
    inline bool HasQualityValue(void) const;

    /// \returns true if has DeletionQV dataset and deletionQVArray_
    ///          has been initialized.
    inline bool HasDeletionQV(void) const;
    inline bool HasDeletionTag(void) const;
    inline bool HasInsertionQV(void) const;
    inline bool HasSubstitutionTag(void) const;
    inline bool HasSubstitutionQV(void) const;
    inline bool HasMergeQV(void) const;
    inline bool HasIPD(void) const;
    inline bool HasPulseWidth(void) const;

    std::vector<std::string> Errors(void) const;

public: 
    /// \returns whether or not to fake QualityValue.
    bool FakeQualityValue() const;

private:
    bool fakeQualityValue_;


private:
    inline bool _HasQV(const PacBio::BAM::BaseFeature & qvToQuery) const;

    bool _WriteBasecall(const SMRTSequence & read);

    /// Write fake values to the 'QualityValue' dataset.
    bool _WriteQualityValue(const SMRTSequence & read);

    /// Write real data in the following.
    bool _WriteDeletionQV(const SMRTSequence & read);
    bool _WriteDeletionTag(const SMRTSequence & read);
    bool _WriteInsertionQV(const SMRTSequence & read);
    bool _WriteSubstitutionTag(const SMRTSequence & read);
    bool _WriteSubstitutionQV(const SMRTSequence & read);
    bool _WriteMergeQV(const SMRTSequence & read);
    bool _WriteIPD(const SMRTSequence & read);
    bool _WritePulseWidth(const SMRTSequence & read);

private:
    /// \brief Create and initialize QV groups.
    /// \returns Whether or not QV groups initialized successfully.
    bool InitializeQVGroups(void);

private:
    HDFGroup & parentGroup_;
    std::map<char, size_t> baseMap_;
    std::vector<PacBio::BAM::BaseFeature> qvsToWrite_;
    std::unique_ptr<HDFZMWWriter> zmwWriter_;
    std::unique_ptr<HDFZMWMetricsWriter> zmwMetricsWriter_;
	HDFGroup basecallsGroup_;

private:
	HDFAtom<string> changeListIDAtom_;

    /// BaseCalls/Basecall group
	BufferedHDFArray<unsigned char> basecallArray_;

    /// This is a mandatory dataset for 2.3, whose existence is 
    /// to ensure bam2bax to generate 2.3 compatible bax.h5 files.
	BufferedHDFArray<unsigned char> qualityValueArray_;

	/// \brief Define arrays for rich quality values.
    ///        DeletionQV         dq --> BaseCalls/DeletionQV
    ///        DeletionTag        dt --> BaseCalls/DeletionTag
    ///        InsertionQV        iq --> BaseCalls/InsertionQV
    ///        MergeQV            mq --> BaseCalls/MergeQV
    ///        SubstitutionQV     sq --> BaseCalls/SubstitutionQV
    ///        SubstitutionTag    st --> BaseCalls/SubstitutionTag
    ///        Ipd:Frames         ip --> BaseCalls/PreBaseFrames
    ///        PulseWidth:Frames  pw --> BaseCalls/WidthInFrames
	BufferedHDFArray<unsigned char> deletionQVArray_;
	BufferedHDFArray<unsigned char> deletionTagArray_;
	BufferedHDFArray<unsigned char> insertionQVArray_;
	BufferedHDFArray<unsigned char> mergeQVArray_;
	BufferedHDFArray<unsigned char> substitutionQVArray_;
	BufferedHDFArray<unsigned char> substitutionTagArray_;
	BufferedHDFArray<HalfWord> ipdArray_;
	BufferedHDFArray<HalfWord> pulseWidthArray_;

    /// \}
};

inline
bool HDFBaseCallsWriter::_HasQV(const PacBio::BAM::BaseFeature & qvToQuery) const {
    return (std::find(qvsToWrite_.begin(), qvsToWrite_.end(), qvToQuery) != qvsToWrite_.end());
}

inline
bool HDFBaseCallsWriter::HasQualityValue(void) const
{return (FakeQualityValue() and 
         qualityValueArray_.IsInitialized());}

inline
bool HDFBaseCallsWriter::HasDeletionQV(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::DELETION_QV) and 
         deletionQVArray_.IsInitialized());}

inline
bool HDFBaseCallsWriter::HasDeletionTag(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::DELETION_TAG) and
         deletionTagArray_.IsInitialized());}

inline
bool HDFBaseCallsWriter::HasInsertionQV(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::INSERTION_QV) and
         insertionQVArray_.IsInitialized());}

inline
bool HDFBaseCallsWriter::HasSubstitutionTag(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::SUBSTITUTION_TAG) and
         substitutionTagArray_.IsInitialized());}

inline
bool HDFBaseCallsWriter::HasSubstitutionQV(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::SUBSTITUTION_QV) and 
         substitutionQVArray_.IsInitialized());}

inline
bool HDFBaseCallsWriter::HasMergeQV(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::MERGE_QV) and 
         mergeQVArray_.IsInitialized());}

inline
bool HDFBaseCallsWriter::HasIPD(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::IPD) and
         ipdArray_.IsInitialized());}

inline
bool HDFBaseCallsWriter::HasPulseWidth(void) const
{return (_HasQV(PacBio::BAM::BaseFeature::PULSE_WIDTH) and
         pulseWidthArray_.IsInitialized());}

inline
bool HDFBaseCallsWriter::FakeQualityValue(void) const
{return this->fakeQualityValue_;}

#endif
#endif
