/*
 * ==================================================================
 *
 *       Filename:  ReadType_gtest.cpp
 *
 *    Description:  Test pbdata/reads/ReadType.hpp
 *
 *        Version:  1.0
 *        Created:  11/29/2012 03:54:55 PM
 *       Revision:  08/20/2014 
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * ==================================================================
 */
#include "gtest/gtest.h"
#include "reads/ReadType.hpp"

using namespace std;

string standard   = "Standard";
string ccs        = "CCS";
string rccs       = "RCCS";
string noreadtype = "standard";

string subread    = "SUBREAD";
string polymerase = "POLYMERASE";
string hqregion   = "HQREGION";
string scarp      = "SCARP";
string unknown    = "UNKNOWN";

TEST(ReadTypeTest, ParseReadType) {
    EXPECT_EQ(ReadType::ParseReadType(standard), ReadType::Standard);
    EXPECT_EQ(ReadType::ParseReadType(ccs),      ReadType::CCS);
    EXPECT_EQ(ReadType::ParseReadType(rccs),     ReadType::RCCS);
    EXPECT_EQ(ReadType::ParseReadType(noreadtype), ReadType::NoReadType);

    EXPECT_EQ(ReadType::ParseReadType(subread), ReadType::SUBREAD);
    EXPECT_EQ(ReadType::ParseReadType(hqregion), ReadType::HQREGION);
    EXPECT_EQ(ReadType::ParseReadType(polymerase), ReadType::POLYMERASE);
    EXPECT_EQ(ReadType::ParseReadType(unknown), ReadType::UNKNOWN);
}


TEST(ReadTypeTest, ToString) {
    EXPECT_EQ(ReadType::ToString(ReadType::Standard), standard);
    EXPECT_EQ(ReadType::ToString(ReadType::CCS), ccs);
    EXPECT_EQ(ReadType::ToString(ReadType::RCCS), rccs);
    EXPECT_EQ(ReadType::ToString(ReadType::NoReadType), "NoReadType");

    EXPECT_EQ(ReadType::ToString(ReadType::SUBREAD), subread);
    EXPECT_EQ(ReadType::ToString(ReadType::HQREGION), hqregion);
    EXPECT_EQ(ReadType::ToString(ReadType::POLYMERASE), polymerase);
    EXPECT_EQ(ReadType::ToString(ReadType::UNKNOWN), unknown);
}
