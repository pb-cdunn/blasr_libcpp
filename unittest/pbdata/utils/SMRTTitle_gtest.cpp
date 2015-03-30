#include "gtest/gtest.h"
#include "utils/SMRTTitle.hpp"


TEST(SMRTTitleTest, test1) {
    SMRTTitle title("1");
    EXPECT_EQ(title.isSMRTTitle, false);
    EXPECT_EQ(title.ToString(), "");
}

TEST(SMRTTitleTest, test2) {
    SMRTTitle title("1/2");
    EXPECT_EQ(title.isSMRTTitle, false);
    EXPECT_EQ(title.ToString(), "");
}

TEST(SMRTTitleTest, test3) {
    SMRTTitle title("m/1/3_4");
    EXPECT_EQ(title.isSMRTTitle, true);
    EXPECT_EQ(title.ToString(), "m/1/3_4");
}

TEST(SMRTTitleTest, test4) {
    SMRTTitle title("m/1/10_20/3_7");
    EXPECT_EQ(title.isSMRTTitle, true);
    EXPECT_EQ(title.ToString(), "m/1/13_17");
}

