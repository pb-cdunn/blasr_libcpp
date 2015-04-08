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
#include "FASTAReader.hpp"
#include "format/SAMHeaderPrinter.hpp"
#include "pbdata/testdata.h"
#include <gtest/gtest.h>
using namespace std;

class SAMHeaderPrinterTest: public testing::Test {
public:
    void SetUp() {
        samQVs.SetDefaultQV(); 
        so = "UNKNOWN";
        readType = ReadType::SUBREAD;

        int rand;
        string fastaFn(fastaFile1);
        reader.computeMD5 = true;
        EXPECT_TRUE(reader.Init(fastaFn));
        reader.ReadAllSequencesIntoOne(sequence, &seqdb);
    }

    void TearDown() {
        if (printer) {
            delete printer;
            printer = NULL;
        }
    }

    SAMHeaderPrinter * printer;
    SupplementalQVList samQVs;
    string so;
    ReadType::ReadTypeEnum readType;
    FASTAReader reader;
    FASTASequence sequence;
    SequenceIndexDatabase<FASTASequence> seqdb;
};


const string bax1ExpectedHeader = 
"PU:PACBIO\tPL:m130220_114643_42129_c100471902550000001823071906131347_s1_p0\tDS:READTYPE=SUBREAD;BINDINGKIT=;SEQUENCINGKIT=;BASECALLERVERSION=2.0.0.0.120374;InsertionQV=iq;DeletionQV=dq;SubstitutionQV=sq;MergeQV=mq;DeletionTag=dt";
const string bax3ExpectedHeader = 
"PU:PACBIO\tPL:m150223_190837_42175_c100735112550000001823160806051530_s1_p0\tDS:READTYPE=SUBREAD;BINDINGKIT=100356300;SEQUENCINGKIT=100356200;BASECALLERVERSION=2.3.0.0.140018;InsertionQV=iq;DeletionQV=dq;SubstitutionQV=sq;MergeQV=mq;DeletionTag=dt";
const string pls1ExpectedHeader = 
"PU:PACBIO\tPL:m121215_065521_richard_c100425710150000001823055001121371_s1_p0\tDS:READTYPE=SUBREAD;BINDINGKIT=;SEQUENCINGKIT=;BASECALLERVERSION=1.3.3.11.117366;InsertionQV=iq;DeletionQV=dq;SubstitutionQV=sq;MergeQV=mq;DeletionTag=dt";

TEST_F(SAMHeaderPrinterTest, BAX_ONE_MOVIE_IN) {
    // Read from two bax files of the same movie.
    EXPECT_EQ(readType, ReadType::ReadTypeEnum::SUBREAD);
    vector<string> readsFiles = {baxFile1, baxFile2};
    printer = new SAMHeaderPrinter(so, seqdb, readsFiles, readType, samQVs, "blasr", "1.3.2", "blasr a b c");

    EXPECT_EQ(printer->_hd.ToString().find("@HD\tVN:1.5\tSO:UNKNOWN\tpb:3.0b"), 0);
    EXPECT_EQ(printer->_sqs._groups.size(), 12);
    EXPECT_EQ(printer->_sqs._groups[0].ToString().find ("@SQ\tSN:read1\tLN:100\tM5:"), 0);
    EXPECT_EQ(printer->_sqs._groups[11].ToString().find ("@SQ\tSN:read2x\tLN:100\tM5:"), 0);
    
    // Expect exactly one read group 
    EXPECT_EQ(printer->_rgs._groups.size(), 1);
    EXPECT_NE(printer->_rgs._groups[0].ToString().find(bax1ExpectedHeader), string::npos);

    EXPECT_EQ(printer->_pgs._groups.size(), 1);
    EXPECT_EQ(printer->_cos._groups.size(), 0);
}

TEST_F(SAMHeaderPrinterTest, BAX_MULTI_MOVIE_IN) {
    // Read subread from more than one movies
    vector<string> readsFiles = {baxFile1, baxFile2, baxFile3, plsFile1};
    printer = new SAMHeaderPrinter(so, seqdb, readsFiles, readType, samQVs, "blasr", "1.3.2", "blasr a b c");

    EXPECT_EQ(printer->_hd.ToString().find("@HD\tVN:1.5\tSO:UNKNOWN\tpb:3.0b"), 0);
    EXPECT_EQ(printer->_sqs._groups.size(), 12);
    EXPECT_EQ(printer->_sqs._groups[0].ToString().find ("@SQ\tSN:read1\tLN:100\tM5:"), 0);
    EXPECT_EQ(printer->_sqs._groups[11].ToString().find ("@SQ\tSN:read2x\tLN:100\tM5:"), 0);
    
    // Expect three read groups because baxFile1 and baxFile2 contains reads of the same movie.
    EXPECT_EQ(printer->_rgs._groups.size(), 3);

    EXPECT_NE(printer->_rgs._groups[0].ToString().find(bax1ExpectedHeader), string::npos);
    EXPECT_NE(printer->_rgs._groups[1].ToString().find(bax3ExpectedHeader), string::npos);
    EXPECT_NE(printer->_rgs._groups[2].ToString().find(pls1ExpectedHeader), string::npos);

    EXPECT_EQ(printer->_pgs._groups.size(), 1);
    EXPECT_EQ(printer->_cos._groups.size(), 0);
}


const string bam1ExpectedHeader = 
"@RG\tID:b89a4406\tPL:PACBIO\tDS:READTYPE=SUBREAD;DeletionQV=dq;DeletionTag=dt;InsertionQV=iq;MergeQV=mq;SubstitutionQV=sq;Ipd=ip;BINDINGKIT=100356300;SEQUENCINGKIT=100356200;BASECALLERVERSION=2.3.0.0.140018\tPU:m140905_042212_sidney_c100564852550000001823085912221377_s1_X0";
const string bam2ExpectedHeader = 
"PL:PACBIO\tDS:READTYPE=SUBREAD;DeletionQV=dq;DeletionTag=dt;InsertionQV=iq;MergeQV=mq;SubstitutionQV=sq;Ipd=ip;BINDINGKIT=100236500;SEQUENCINGKIT=001558034;BASECALLERVERSION=2.3.0.1.142990\tPU:m150325_224749_42269_c100795290850000001823159309091522_s1_p0";

TEST_F(SAMHeaderPrinterTest, ONE_BAM_IN) {
    // Read the same file twice in order to test uniqueness of @RG
    vector<string> readsFiles = {bamFile1, bamFile1}; 
    printer = new SAMHeaderPrinter(so, seqdb, readsFiles, readType, samQVs, "blasr", "1.3.2", "blasr a b c");

    EXPECT_EQ(printer->_rgs._groups.size(), 1);
    EXPECT_EQ(printer->_rgs._groups[0].ToString(), bam1ExpectedHeader);

    EXPECT_EQ(printer->_pgs._groups.size(), 3);
}

TEST_F(SAMHeaderPrinterTest, TWO_BAM_IN) {
    // Read multiple bam files 
    vector<string> readsFiles = {bamFile1, bamFile2}; 
    printer = new SAMHeaderPrinter(so, seqdb, readsFiles, readType, samQVs, "blasr", "1.3.2", "blasr a b c");

    EXPECT_EQ(printer->_rgs._groups.size(), 2);
    EXPECT_NE(printer->_rgs._groups[0].ToString().find(bam1ExpectedHeader), string::npos);
    EXPECT_NE(printer->_rgs._groups[1].ToString().find(bam2ExpectedHeader), string::npos);

    EXPECT_EQ(printer->_pgs._groups.size(), 3);
}

