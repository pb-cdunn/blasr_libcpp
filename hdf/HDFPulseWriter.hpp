#ifndef _BLASR_HDF_PULSE_WRITER_HPP_
#define _BLASR_HDF_PULSE_WRITER_HPP_
#include "libconfig.h"
#ifdef USE_PBBAM

#include <sstream>
#include <memory>
#include "Enumerations.h"
#include "SMRTSequence.hpp"
#include "HDFFile.hpp"
#include "HDFWriterBase.hpp"
#include "HDFScanDataWriter.hpp"
#include "HDFBaseCallsWriter.hpp"
#include "HDFPulseCallsWriter.hpp"
#include "HDFRegionsWriter.hpp"

using namespace H5;
using namespace std;

class HDFPulseWriter : public HDFWriterBase {
public:

    /// \name Constructor & Related Methods
    /// \{
    /// \brief Sets output h5 file name, scan data, base caller version
    ///        QVs to write, and h5 file access property list.
    /// \note Set /PulseData/Regions
    /// \param[in] filename output h5 file name.
    /// \param[in] ScanData meta data string, must contain bindingKit and sequencingKit.
    /// \param[in] basecallerVersion meta data string
    /// \param[in] qvsToWrite Quality values to include in output h5 file. 
    /// \param[in] regionTypes, regionTypes as /Regions/RegionTypes
    /// \param[in] fileAccPropList H5 file access property list
    HDFPulseWriter(const std::string & filename,
                   const ScanData & sd,
                   const std::string & basecallerVersion,
                   const std::vector<PacBio::BAM::BaseFeature> & qvsToWrite,
                   const std::vector<std::string> & regionTypes,
                   const H5::FileAccPropList & fileAccPropList = H5::FileAccPropList::DEFAULT);

    /// \note No /PulseData/Regions
    HDFPulseWriter(const std::string & filename,
                   const ScanData & sd,
                   const std::string & basecallerVersion,
                   const std::vector<PacBio::BAM::BaseFeature> & qvsToWrite,
                   const H5::FileAccPropList & fileAccPropList = H5::FileAccPropList::DEFAULT);

	~HDFPulseWriter(void);

    /// \brief Write one zmw sequence to output h5 file. 
    /// \param[in] seq, the SMRTSequence to write
    bool WriteOneZmw(const SMRTSequence & seq);

    /// \brief Write one zmw sequence and its region table to output h5 file. 
    /// \param[in] seq, the SMRTSequence to write
    /// \param[in] regions, region annotations of this zmw.
    bool WriteOneZmw(const SMRTSequence & seq, 
                     const std::vector<RegionAnnotation> & regions);

    inline bool HasRegions(void) const;

    /// \brief Flushes buffered data.
    void Flush(void);

    /// \returns all errors from all writers.
    std::vector<std::string> Errors(void);

    /// \}

private:
    /// \name Private Variables
    /// \{
	HDFFile outfile_;  ///< HDFFile file handler

    H5::FileAccPropList fileaccproplist_; ///< H5 file access property list

	HDFGroup pulseDataGroup_; ///< /PulseData group

private:
    /// Points to scan data writer.
    std::unique_ptr<HDFScanDataWriter>  scandataWriter_;
    /// Points to base caller writer.
    std::unique_ptr<HDFBaseCallsWriter> basecallsWriter_;
    /// Points to pulse calls writer.
    std::unique_ptr<HDFPulseCallsWriter> pulsecallsWriter_;
    /// Points to region table writer.
    std::unique_ptr<HDFRegionsWriter>   regionsWriter_;
    /// \}

private:
    /// \name Private Methods.
    /// \{
    /// \brief Checks whether chemistry triple, including
    ///        binding kit, sequencing kit and base caller version
    ///        are set. 
    ///        If not, add error messages.
    bool SanityCheckChemistry(const std::string & bindingKit,
                              const std::string & sequencingKit,
                              const std::string & basecallerVersion);

    /// \brief Closes HDFPulseWriter.
    void Close(void);
    /// \}
};

inline bool HDFPulseWriter::HasRegions(void) const
{ return bool(regionsWriter_); }

#endif
#endif
