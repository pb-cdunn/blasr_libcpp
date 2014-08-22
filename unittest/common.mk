#
# Definitions common to all make files for unit tests.
#

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_DIR = /mnt/secondary-siv/third_party_source/gtest-1.6.0
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_MAINA   = $(GTEST_DIR)/make/gtest_main.a  
GTESTINCDIRS  = -I$(GTEST_DIR) \
				-I$(GTEST_DIR)/include \

PBINCROOT ?= ../..
HDFINC    ?= ../../../../../assembly/seymour/dist/common/include 
HDFLIB    ?= ../../../../../assembly/seymour/dist/common/lib 


#LDFLAGS := -lblasr -lpbdata -lpbihdf -lhdf5_cpp -lhdf5 -lz -lpthread -lrt -ldl

CCOPTS := -O3 

CCFLAGS := -std=c++0x -Wno-div-by-zero 

CXX = g++
