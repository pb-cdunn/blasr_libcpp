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

TEST(ReadTypeTest, ParseReadType) {

    string standard   = "Standard";
    string ccs        = "CCS";
    string rccs       = "RCCS";
    string noreadtype = "standard";

    EXPECT_EQ(ReadType::ParseReadType(standard), ReadType::Standard);
    EXPECT_EQ(ReadType::ParseReadType(ccs),      ReadType::CCS);
    EXPECT_EQ(ReadType::ParseReadType(rccs),     ReadType::RCCS);
    EXPECT_EQ(ReadType::ParseReadType(noreadtype), ReadType::NoReadType);
}
