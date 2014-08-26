#ifndef _BLASR_ALIGNMENT_SET_TO_CMPH5_ADAPTER_HPP_
#define _BLASR_ALIGNMENT_SET_TO_CMPH5_ADAPTER_HPP_

#include "utils/SMRTReadUtils.hpp"
#include "HDFCmpFile.hpp"
#include "sam/AlignmentSet.hpp"
#include "datastructures/alignment/AlignmentCandidate.hpp"
#include "datastructures/alignment/ByteAlignment.h"
#include "algorithms/alignment/DistanceMatrixScoreFunction.hpp"

class RefGroupNameId {
 public:
  std::string name;
  unsigned int id;
  RefGroupNameId() {
    id = 0;
    name = "";
  }

  RefGroupNameId(std::string n, unsigned int i) {
    name = n; id = i;
  }

  RefGroupNameId(const RefGroupNameId &rhs) {
    name = rhs.name;
    id   = rhs.id;
  }
};

template<typename T_CmpFile>
class AlignmentSetToCmpH5Adapter {
public:
  // Map reference name to reference group (/RefGroup) name and ID.
  std::map<std::string, RefGroupNameId> refNameToRefGroupNameandId;
  std::map<std::string, unsigned int> knownMovies;
  std::map<std::string, unsigned int> knownPaths;
  unsigned int numAlignments;
  std::map<std::string, int> refNameToRefInfoIndex;
 
  void Initialize() {
      numAlignments = 0;
  }

  template<typename T_Reference>
  void StoreReferenceInfo(std::vector<T_Reference> &references,
                          T_CmpFile &cmpFile);

  unsigned int StoreMovieInfo(std::string movieName, T_CmpFile &cmpFile);


  // Given a reference name, find whether there exists a refGroup 
  // (e.g. /ref000001) associated with it. 
  // If not, create a refGroup and update refNameToRefGroupNameandId. 
  // Finally, return its associated refGroup ID.
  unsigned int StoreRefGroup(std::string refName, T_CmpFile & cmpFile);

  unsigned int StorePath(std::string & path, T_CmpFile &cmpFile);

  void RemoveGapsAtEndOfAlignment(AlignmentCandidate<> &alignment);

  void StoreAlignmentCandidate(AlignmentCandidate<> &alignment, 
                               int alnSegment,
                               T_CmpFile &cmpFile,
                               int moleculeNumber = -1,
                               bool copyQVs=false);

  void StoreAlignmentCandidateList(std::vector<AlignmentCandidate<> > &alignments,
                                   T_CmpFile &cmpFile,
                                   int moleculeNumber=-1,
                                   bool copyQVs=false);

  void StoreAlignmentCandidate(AlignmentCandidate<> alignment, 
                               T_CmpFile &cmpFile) {
    StoreAlignmentCandidate(alignment, 0, cmpFile);
  }

};

#include "AlignmentSetToCmpH5AdapterImpl.hpp"

#endif
