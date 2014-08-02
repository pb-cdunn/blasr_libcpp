#ifndef _BLASR_MAPPING_METRICS_HPP_
#define _BLASR_MAPPING_METRICS_HPP_

#include <iostream>
#include <time.h>
#include <map>
#include <vector>
//In order to use clock_gettime in LINUX, add -lrt 
#ifdef __APPLE__
#pragma weak clock_gettime
#include <mach/mach.h>
#include <mach/clock.h>
#include <mach/mach_time.h>
#include <errno.h>

typedef enum {
    CLOCK_REALTIME,
    CLOCK_MONOTONIC,
    CLOCK_PROCESS_CPUTIME_ID,
    CLOCK_THREAD_CPUTIME_ID
} clockid_t;
static mach_timebase_info_data_t __clock_gettime_inf;

int clock_gettime(clockid_t clk_id, struct timespec *tp); 
#endif // __APPLE__

class Timer {
public:
    bool keepHistogram, keepList;
    timespec cpuclock[2];
    int elapsedClockMsec;
    float   elapsedTime;
    std::map<int,int> histogram;
    std::vector<int> msecList;
    long long totalElapsedClock;
    std::string header;


    Timer(std::string _header=""); 

    int ListSize(); 

    void PrintHeader(std::ostream &out); 

    void PrintListValue(std::ostream &out, int index); 

    void Tick(); 

    void SetStoreElapsedTime(bool value); 

    void SetStoreHistgram(bool value); 

    void Tock(); 

    void Add(const Timer &rhs); 

    void SetHeader(std::string _header); 

};


class MappingClocks {
public:
    Timer total;
    Timer findAnchors;
    Timer mapToGenome;
    Timer sortMatchPosList;
    Timer findMaxIncreasingInterval;
    Timer alignIntervals;           
    std::vector<int> nCellsPerSample;
    std::vector<int> nBasesPerSample;

    void AddCells(int nCells); 

    void AddBases(int nBases); 

    int  GetSize(); 

    MappingClocks(); 

    void PrintHeader(std::ostream &out); 

    void PrintList(std::ostream &out, int index); 

    void SetStoreList(bool value=true); 

    void AddClockTime(const MappingClocks &rhs); 
};


class MappingMetrics {
public:
    MappingClocks clocks;
    int numReads;
    int numMappedReads;
    int numMappedBases;
    std::vector<int> mappedBases;
    std::vector<int> cellsPerAlignment;
    std::vector<int> anchorsPerAlignment;
    std::vector<int> sdpAnchors, sdpBases, sdpClock;
    long totalAnchors;
    int anchorsPerRead;
    long totalAnchorsForMappedReads;

    MappingMetrics(); 

    void StoreSDPPoint(int nBases, int nSDPAnchors, int nClock); 

    void SetStoreList(bool value=true); 

    void PrintSeconds(std::ostream &out, long sec);

    void PrintFraction(std::ostream &out, float frac); 

    void RecordNumAlignedBases(int nBases); 

    void RecordNumCells(int nCells); 

    void Collect(MappingMetrics &rhs); 

    void CollectSDPMetrics(MappingMetrics &rhs); 

    void PrintSDPMetrics(std::ostream &out); 

    void PrintFullList(std::ostream &out); 

    void PrintSummary(std::ostream &out); 

    void AddClock(MappingClocks &clocks); 
};



#endif // _BLASR_MAPPING_METRICS_HPP_
