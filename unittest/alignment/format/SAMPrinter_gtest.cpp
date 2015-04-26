/*
 * =====================================================================================
 *
 *       Filename:  SAMHeaderPrinter_gtest.cpp
 *
 *    Description:  Test alignment/format/SAMHeaderPrinter.hpp
 *
 *        Version:  1.0
 *        Created:  03/24/2015 04:51:29 PM
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * =====================================================================================
 */

#define private public
#define protected public

#include <algorithm>
#include <stdio.h>
#include <string.h>
#include "format/SAMPrinter.hpp"
#include <gtest/gtest.h>
using namespace std;

TEST(SAMPrinterTest, AddMatchBlockCigarOps) {
    DNASequence qSeq; qSeq.Copy("XXXXXAAAAAGGGGGCCCCC");
    DNASequence tSeq; tSeq.Copy(     "AAAAANGGGGCCCCC");
    blasr::Block b; 
    b.qPos = 5;
    b.tPos = 0;
    b.length=15;
    vector<int> opSize;
    vector<char> opChar;

    const vector<int>  expOpSize = {5  , 1  , 9  };
    const vector<char> expOpChar = {'=', 'X', '='};

    AddMatchBlockCigarOps(qSeq, tSeq, b, opSize, opChar);

    EXPECT_EQ(opSize, expOpSize);
    EXPECT_EQ(opChar, expOpChar);
}
