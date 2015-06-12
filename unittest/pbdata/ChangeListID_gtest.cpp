/*
 * =====================================================================================
 *
 *       Filename:  ChangeListID_gtest.cpp
 *
 *    Description:  Test pbdata/ChangeListID.hpp
 *
 *        Version:  1.0
 *        Created:  02/26/2015 06:01:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan Li (yli), yli@pacificbiosciences.com
 *        Company:  Pacific Biosciences
 *
 * =====================================================================================
 */

#include "gtest/gtest.h"
#include "ChangeListID.hpp"

using namespace std;

// Test ChangeListID.GetVersion().
TEST(ChangeListID, GetVersion) {
    string str = "2.3.0.143354";
    ChangeListID change = ChangeListID(str);
    EXPECT_EQ(change.GetVersion(), "2.3");

    str = "";
    change = ChangeListID(str);
    EXPECT_EQ(change.GetVersion(), "");
} 

