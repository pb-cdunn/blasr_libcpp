#include "libconfig.h"
#ifdef USE_PBBAM
#ifndef SEQUENTIAL_ZMWGROUPQUERY_H
#define SEQUENTIAL_ZMWGROUPQUERY_H

#include "pbbam/internal/QueryBase.h"
#include <memory>

namespace PacBio {
namespace BAM {

/// This class operates on a name-sorted BAM file, with each iteration of the query
/// returning each contiguous block of records that share a name.
///
/// \note Iterate over zmws, return vector of subreads of a zmw each time.
///
class PBBAM_EXPORT SequentialZmwGroupQuery : public internal::IGroupQuery
{
public:
    SequentialZmwGroupQuery(const DataSet& dataset);
    ~SequentialZmwGroupQuery(void);

public:
    bool GetNext(std::vector<BamRecord>& records);

private:
    struct SequentialZmwGroupQueryPrivate;
    std::unique_ptr<SequentialZmwGroupQueryPrivate> d_;
};

} // namespace BAM
} // namespace PacBio

#endif // SEQUENTIAL_ZMWGROUPQUERY_H
#endif
