#ifndef _BLASR_READER_AGGLOMERATE_HPP_
#define _BLASR_READER_AGGLOMERATE_HPP_

#include <cstdlib>

#include "Enumerations.h"
#include "files/BaseSequenceIO.hpp"

#include "FASTAReader.hpp"
#include "FASTQReader.hpp"
#include "CCSSequence.hpp"
#include "SMRTSequence.hpp"
#include "StringUtils.hpp"

#include "HDFBasReader.hpp"
#include "HDFCCSReader.hpp"

class ReaderAgglomerate : public BaseSequenceIO {
  FASTAReader fastaReader;
  FASTQReader fastqReader;
  int readQuality;
  int stride;
  int start;
  float subsample;
  bool useRegionTable;
  bool ignoreCCS;
public:
  //
  // Create interfaces for reading hdf 
  //
  T_HDFBasReader<SMRTSequence>  hdfBasReader;
  HDFCCSReader<CCSSequence>     hdfCcsReader;
  vector<SMRTSequence>          readBuffer;
  vector<CCSSequence>           ccsBuffer;
  string readGroupId;

  void SetToUpper();

  void InitializeParameters();
  ReaderAgglomerate();

  ReaderAgglomerate(float _subsample);

  ReaderAgglomerate(int _stride);

  ReaderAgglomerate(int _start, int _stride);

  void GetMovieName(string &movieName);

  bool FileHasZMWInformation();

  void SkipReadQuality();

  void IgnoreCCS();

  void UseCCS();

  int Initialize(string &pFileName);

  bool SetReadFileName(string &pFileName);

  int Initialize(FileType &pFileType, string &pFileName);

  bool HasRegionTable();

  int Initialize();

  ReaderAgglomerate &operator=(ReaderAgglomerate &rhs);

  bool Subsample(float rate);

  int GetNext(FASTASequence &seq);
  int GetNext(FASTQSequence &seq);
  int GetNext(SMRTSequence &seq);
  int GetNext(CCSSequence &seq);

  template<typename T_Sequence>
      int GetNext(T_Sequence & seq, int & randNum);

  int GetNextBases(SMRTSequence & seq, bool readQVs);

  int Advance(int nSteps);

  void Close();
};


template<typename T_Sequence>
int ReadChunkByNReads(ReaderAgglomerate &reader, vector<T_Sequence> &reads, int maxNReads);

template<typename T_Sequence>
int ReadChunkBySize (ReaderAgglomerate &reader, vector<T_Sequence> &reads, int maxMemorySize);

#include "files/ReaderAgglomerateImpl.hpp"

#endif
