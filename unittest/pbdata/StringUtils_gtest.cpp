/*
 * ==================================================================
 *
 *       Filename:  StringUtils_gtest.cpp
 *
 *    Description:  Test pbdata/StringUtils.hpp
 *
 *        Version:  1.0
 *        Created:  03/28/2015 03:54:55 PM
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * ==================================================================
 */
#include "gtest/gtest.h"
#include "reads/ReadType.hpp"
#include "StringUtils.hpp"

using namespace std;


TEST(StringUtilTest, MakeReadGroupId) {

    string movieName = "m140905_042212_sidney_c100564852550000001823085912221377_s1_X0";
    ReadType::ReadTypeEnum readType = ReadType::SUBREAD;
    string expectedReadGroupId = "05aecfc9";

    EXPECT_EQ(MakeReadGroupId(movieName, readType), expectedReadGroupId);
}


