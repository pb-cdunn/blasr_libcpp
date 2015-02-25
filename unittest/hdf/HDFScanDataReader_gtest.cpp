#include "gtest/gtest.h"
#include "HDFScanDataReader.hpp"
#include "pbdata/testdata.h"

using namespace std;
using namespace H5;

class HDFScanDataReaderTEST : public ::testing::Test {
public:
    virtual void SetUp() {
        fileName = scanDataFile1;
        try{
            hdfFile.openFile(fileName.c_str(), H5F_ACC_RDONLY);
            ASSERT_EQ(rootGroup.Initialize(hdfFile, "/"), 1);
            ASSERT_EQ(reader.Initialize(dynamic_cast<HDFGroup*>(&rootGroup)), 1);
        } catch(H5::Exception & e) {
            cerr << "Failed to open " << fileName << endl;
            ASSERT_FALSE(true);
        }
    }

    virtual void TearDown() {
        reader.Close();
        hdfFile.close();
    }

    string fileName;
    H5::H5File hdfFile;
    HDFGroup rootGroup;
    HDFScanDataReader reader;
};

TEST_F(HDFScanDataReaderTEST, ReadBindingKit) {
    string bindingKit;
    EXPECT_EQ(reader.ReadBindingKit(bindingKit), 1);
    EXPECT_EQ(bindingKit, "100356300");
}

TEST_F(HDFScanDataReaderTEST, ReadSequencingKit) {
    string sequencingKit;
    EXPECT_EQ(reader.ReadSequencingKit(sequencingKit), 1);
    EXPECT_EQ(sequencingKit, "100356200");
}

