/*
 * =====================================================================================
 *
 *       Filename:  QualityValueVector_gtest.cpp
 *
 *    Description:  Test pbdata/qvs/QualityValueVector.hpp
 *
 *        Version:  1.0
 *        Created:  03/28/2015 05:21:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * =====================================================================================
 */
#include "gtest/gtest.h"
#include "qvs/QualityValue.hpp"
#include "qvs/QualityValueVector.hpp"

using namespace std;

const string qvstr = "!#$%0123:;ABab{|}~";
vector<uint8_t> data = {0,2,3,4,15,16,17,18,25,26,32,33,64,65,90,91,92,93};

TEST(QualityValueVectorTest, Copy){
    EXPECT_EQ(qvstr.size(), data.size());

    QualityValueVector<QualityValue> qual;
    EXPECT_TRUE(qual.Empty());

    // Copy qvs from a string
    qual.Copy(qvstr);
    EXPECT_FALSE(qual.Empty());
    for(size_t i = 0; i < qvstr.size(); i++) {
        EXPECT_EQ(static_cast<uint8_t>(qual.data[i]), data[i]);
    }
}

TEST(QualityValueVectorTest, ToString){
    QualityValueVector<QualityValue> qual;
    qual.Copy(qvstr);

    // Test ToString()
    EXPECT_EQ(qual.ToString(), qvstr);

    EXPECT_EQ(static_cast<size_t>(qual.Length()), qvstr.size());
}

