#include "libconfig.h"
#ifdef USE_PBBAM
#ifndef PBIFILTER_ZMWGROUPQUERY_H 
#define PBIFILTER_ZMWGROUPQUERY_H

#include "pbbam/internal/QueryBase.h"
#include "pbbam/PbiFilter.h"
#include <memory>

namespace PacBio {
namespace BAM {

/// This class operates on a name-sorted BAM file, with each iteration of the query
/// returning each contiguous block of records that share a name.
///
/// \note Iterate over zmws, return vector of subreads of a zmw each time.
///
class PBBAM_EXPORT PbiFilterZmwGroupQuery : public internal::IGroupQuery
{
public:
    PbiFilterZmwGroupQuery(const DataSet& dataset);
    PbiFilterZmwGroupQuery(const PbiFilter& filter, const DataSet& dataset);
    ~PbiFilterZmwGroupQuery(void);

public:
    bool GetNext(std::vector<BamRecord>& records);

private:
    struct PbiFilterZmwGroupQueryPrivate;
    std::unique_ptr<PbiFilterZmwGroupQueryPrivate> d_;
};

} // namespace BAM
} // namespace PacBio

#endif // PBIFILTER_ZMWGROUPQUERY_H
#endif
