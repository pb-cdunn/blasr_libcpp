/*
 * =====================================================================================
 *
 *       Filename:  ReaderAgglomerate_gtest.cpp
 *
 *    Description:  Test alignment/files/ReaderAgglomerate.hpp
 *
 *        Version:  1.0
 *        Created:  02/25/2015 04:51:29 PM
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * =====================================================================================
 */

#include "files/ReaderAgglomerate.hpp"
#include "pbdata/testdata.h"
#include <gtest/gtest.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

class ReaderAgglomerateTest: public testing::Test {
public:
    void SetUp() {
        reader = new ReaderAgglomerate();
    }

    void TearDown() {
        if (reader) {
            delete reader;
            reader = NULL;
        }
    }
    ReaderAgglomerate * reader;
};

#define INIT_READER(INFILE) \
    fn = INFILE; \
    reader->SetReadFileName(fn); \
    EXPECT_EQ(reader->Initialize(), 1);

TEST_F(ReaderAgglomerateTest, Initialize) {
    string fn;
    INIT_READER(fastaFile1)
    reader->Close();

    INIT_READER(baxFile1)
    reader->Close();

    INIT_READER(baxFile3)
    reader->Close();
}


#define SIMPLE(INFILE, SEQ) \
    INIT_READER(INFILE) \
    for(int i = 0; i < 10; i++) {\
        reader->GetNext(SEQ);\
    }\
    reader->Close();

TEST_F(ReaderAgglomerateTest, Simple) {
    string fn;

    // Fasta
    FASTASequence fastaSeq;
    SIMPLE(fastaFile1, fastaSeq)
    
    // Bax
    SMRTSequence smrtSeq;
    SIMPLE(baxFile1, smrtSeq)
    SIMPLE(baxFile3, smrtSeq)
}

#define GET_MOVIE_NAME(INFILE) \
    INIT_READER(INFILE) \
    reader->GetMovieName(movieName); \
    reader->Close();

TEST_F(ReaderAgglomerateTest, GetMovieName) {
    string fn;
    string movieName = "";
    // Fasta
    GET_MOVIE_NAME(fastaFile1)
    EXPECT_EQ(movieName, "/mnt/secondary-siv/testdata/BlasrTestData/utest/data/read.fasta");

    // Bax
    GET_MOVIE_NAME(baxFile1)
    EXPECT_EQ(movieName, "m130220_114643_42129_c100471902550000001823071906131347_s1_p0");

    GET_MOVIE_NAME(baxFile3)
    EXPECT_EQ(movieName, "m150223_190837_42175_c100735112550000001823160806051530_s1_p0");
}

#define GET_CHEMISTRY_TRIPLE(INFILE, A, B, C) \
    INIT_READER(INFILE) \
    bindingKit = sequencingKit = version; \
    reader->GetChemistryTriple(bindingKit, sequencingKit, version); \
    reader->Close(); \
    EXPECT_EQ(bindingKit, A); \
    EXPECT_EQ(sequencingKit, B); \
    EXPECT_EQ(version, C);

TEST_F(ReaderAgglomerateTest, GetChemistryTriple) {
    string fn;
    string bindingKit, sequencingKit, version;

    GET_CHEMISTRY_TRIPLE(baxFile3, "100356300", "100356200", "2.3")
} 

TEST_F(ReaderAgglomerateTest, ReadFromBam) {
    string fn (bamFile1);
    reader->SetReadFileName(fn);
    EXPECT_EQ(reader->Initialize(), 1);

    SMRTSequence seq;
    int count=0;
    while (true) {
        int ret = reader->GetNext(seq);
        if (ret == 0) break;
        count++;
    }

    EXPECT_EQ(count, 117);

    reader->Close();
}

TEST_F(ReaderAgglomerateTest, ReadsFromBam) {
    string fn (bamFile1);
    reader->SetReadFileName(fn);
    EXPECT_EQ(reader->Initialize(), 1);

    vector<SMRTSequence> seqs;
    vector<size_t> counts;
    size_t count=0;

    while (true) {
        int ret = reader->GetNext(seqs);
        if (ret == 0) break;
        count += seqs.size();
        counts.push_back(seqs.size());
    }
    vector<size_t> expected({2, 2, 10, 2, 3, 1, 2, 2, 3, 4, 1, 3, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 3, 8, 1, 3, 2, 1, 15, 2, 1, 3, 1, 2, 2, 1, 3, 3, 2, 2, 1, 2, 2, 1, 1, 1});

    EXPECT_EQ(count, 117);
    EXPECT_EQ(counts, expected);

    reader->Close();
}

TEST_F(ReaderAgglomerateTest, ReadFromXml) {
    string fn (xmlFile1);
    reader->SetReadFileName(fn);
    EXPECT_EQ(reader->Initialize(), 1);

    SMRTSequence seq;
    size_t count=0;

    while (true) {
        int ret = reader->GetNext(seq);
        if (ret == 0) break;
        count ++;
    }

    EXPECT_EQ(count, 150);
    reader->Close();
}

TEST_F(ReaderAgglomerateTest, ReadByZmwFromXml) {
    string fn (xmlFile1);
    reader->SetReadFileName(fn);
    EXPECT_EQ(reader->Initialize(), 1);

    vector<SMRTSequence> seqs;
    vector<size_t> counts;
    while (true) {
        int ret = reader->GetNext(seqs);
        if (ret == 0) break;
        counts.push_back(seqs.size());
    }

    // The filter in dataset xml must be honored.
    vector<size_t> expected({2,21,13,1,5,13,1,34,12,2,20,5,3,7,11});
    EXPECT_EQ(counts, expected);

    reader->Close();
}

TEST_F(ReaderAgglomerateTest, ReadByZmwFromXmlNoFilter) {
    string fn (xmlFile2);
    reader->SetReadFileName(fn);
    EXPECT_EQ(reader->Initialize(), 1);

    vector<SMRTSequence> seqs;
    vector<size_t> counts;
    while (true) {
        int ret = reader->GetNext(seqs);
        if (ret == 0) break;
        counts.push_back(seqs.size());
    }

    // no filter in dataset.xml, all bam records should pass
    vector<size_t> expected({2,21,13,1,5,13,1,34,12,2,20,5,3,7,11,14,6,8,23,53,17,21,7,5,35,3,26,6,21,37,26,59,2,6,30,34,32,2,14,3,24,1,15,1,12,26,6,3,1,9,3,21,12,10,24,3,6,1,6,17,34,11,24,4,11,1,10,8,10,20,3,4,6,27,5,2,21,3,14,1,9,5,30,37,6,1,26,7,7,32});

    EXPECT_EQ(counts, expected);

    reader->Close();
}
