/*
 * =====================================================================================
 *
 *       Filename:  ScanData_gtest.cpp
 *
 *    Description:  Test pbdata/reads/ScanData.hpp
 *
 *        Version:  1.0
 *        Created:  11/29/2012 03:55:46 PM
 *       Revision:  08/20/2014
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * =====================================================================================
 */

#include "gtest/gtest.h"
#include "reads/ScanData.hpp"

TEST(ScanDataTest, GetMovieName) {
    ScanData sd;
    EXPECT_EQ(sd.platformId, NoPlatform);
    EXPECT_EQ(sd.frameRate, 0);
    EXPECT_EQ(sd.numFrames, 0);
    EXPECT_EQ(sd.movieName.size(), 0);
    EXPECT_EQ(sd.runCode.size(), 0);
    EXPECT_EQ(sd.whenStarted.size(), 0);
    EXPECT_EQ(sd.baseMap.size(), 0);
}
