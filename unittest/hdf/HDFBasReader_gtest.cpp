/*
 * ============================================================================
 *
 *       Filename:  HDFBasReader_gtest.cpp
 *
 *    Description:  Test hdf/HDFBasReader.hpp
 *
 *        Version:  1.0
 *        Created:  08/23/2013 10:17:14 AM
 *       Revision:  08/20/2014 
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * ============================================================================
 */

#include "gtest/gtest.h"
#include "HDFBasReader.hpp"
#include "pbdata/testdata.h"

using namespace std;
using namespace H5;

class HDFBasReaderTEST : public ::testing::Test {
public:
    virtual void SetUp() {
        fileName = baxFile3;
        reader.InitializeDefaultIncludedFields();
        ASSERT_EQ(reader.Initialize(fileName), 1);
    }
    virtual void TearDown() {
        reader.Close();
    }
    string fileName;
    T_HDFBasReader<SMRTSequence> reader; 
};

TEST_F(HDFBasReaderTEST, ReadBaseFromBaseCalls) {
    ASSERT_EQ(reader.GetMovieName(), 
            "m150223_190837_42175_c100735112550000001823160806051530_s1_p0");
    SMRTSequence seq;

    for(int i=0; i < 1000; i++) {
        reader.GetNext(seq);
    }
}

TEST_F(HDFBasReaderTEST, GetChemistryTriple) {
    string bindingKit, sequencingKit, version;
    reader.GetChemistryTriple(bindingKit, sequencingKit, version);
    EXPECT_EQ(bindingKit, "100356300");
    EXPECT_EQ(sequencingKit, "100356200");
    EXPECT_EQ(version, "2.3.0.0.140018");
}
