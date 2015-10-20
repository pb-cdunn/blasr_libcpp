#include "pbdata/testdata.h"
#include <gtest/gtest.h>
#include "query/SequentialZmwGroupQuery.h"
#include <string>
using namespace PacBio;
using namespace PacBio::BAM;
using namespace std;

static const string testChunking = xmlFile1;
static const string testNoFilter = xmlFile2;

static
void TestSequentialZmwGroupQuery(const string& fn, 
                                 const vector<int>& expected)
{
    EXPECT_NO_THROW(
    {
        vector<int> counts;
        SequentialZmwGroupQuery qQuery(fn);
        for (const vector<BamRecord>& records : qQuery)
        {
            counts.push_back(records.size());
            EXPECT_GT(records.size(), 0);
            string movieName = records[0].MovieName();
            uint32_t holeNumber = records[0].HoleNumber();
            for (const BamRecord & record: records) {
                EXPECT_EQ(holeNumber, record.HoleNumber());
                EXPECT_EQ(movieName, record.MovieName());
            }
        }
        EXPECT_EQ(expected, counts);
    });
}

static
void TestNoneConstSequentialZmwGroupQuery(const string& fn, 
                                          const vector<int>& expected)
{
    EXPECT_NO_THROW(
    {
        vector<int> counts;
        SequentialZmwGroupQuery qQuery(fn);
        for (vector<BamRecord>& records : qQuery) {
            counts.push_back(records.size());
            EXPECT_GT(records.size(), 0);
            string movieName = records[0].MovieName();
            uint32_t holeNumber = records[0].HoleNumber();
            for (BamRecord & record: records) {
                EXPECT_EQ(holeNumber, record.HoleNumber());
                EXPECT_EQ(movieName, record.MovieName());
            }
        }
        EXPECT_EQ(expected, counts);
    });
}

TEST(SequentialZmwGroupQueryTest, CountQSizes)
{
    string fn = bamFile1;
    vector<int> expected({2, 2, 10, 2, 3, 1, 2, 2, 3, 4, 1, 3, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 3, 8, 1, 3, 2, 1, 15, 2, 1, 3, 1, 2, 2, 1, 3, 3, 2, 2, 1, 2, 2, 1, 1, 1});
    TestSequentialZmwGroupQuery(fn, expected);
    TestNoneConstSequentialZmwGroupQuery(fn, expected);
} 

TEST(SequentialZmwGroupQueryTest, Chunking)
{
    string fn = testChunking;
    vector<int> expected({2,21,13,1,5,13,1,34,12,2,20,5,3,7,11,14,6,8,23,53,17,21,7,5,35,3,26,6,21,37,26,59,2,6,30,34,32,2,14,3,24,1,15,1,12,26,6,3,1,9,3,21,12,10,24,3,6,1,6,17,34,11,24,4,11,1,10,8,10,20,3,4,6,27,5,2,21,3,14,1,9,5,30,37,6,1,26,7,7,32});
    TestSequentialZmwGroupQuery(fn, expected);
}
