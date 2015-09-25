/*
 * ============================================================================
 *
 *       Filename:  HDFPlsReader_gtest.cpp
 *
 *    Description:  Test hdf/HDFPlsReader.hpp
 *
 *        Version:  1.0
 *        Created:  08/23/2013 11:13:34 AM
 *       Revision:  08/20/2014 
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * ============================================================================
 */

#include "HDFPlsReader.hpp"
#include "gtest/gtest.h"
#include "pbdata/testdata.h"

using namespace std;
using namespace H5;

class HDFPlsReaderTEST : public ::testing::Test {
public:
    virtual void SetUp() {
        fileName = plsFile1;
        ASSERT_EQ(reader.Initialize(fileName), 1);
    }
    virtual void TearDown() {
        reader.Close();
    }
    string fileName;
    HDFPlsReader reader; 
};

TEST_F(HDFPlsReaderTEST, ReadToPulseFile) {
    PulseFile  pulseFile;
    reader.IncludeField("NumEvent");
    reader.IncludeField("StartFrame");
    reader.ReadPulseFileInit(pulseFile);
    reader.ReadPulseFile(pulseFile);
    //Astro = 1, Springfield = 2
    ASSERT_EQ(pulseFile.platformId, 2);
    ASSERT_EQ(pulseFile.startFrame.size(), 197626964);
}


