SHELL=bash

.PHONY: all debug profile clean

#
# Definitions common to all make files for unit tests.
# All paths are relative from inside the subdirectories, not this file
#

PBINCROOT 	   ?= $(realpath ../..)
PREBUILT    	   ?= $(realpath ../../../../../prebuilt.out)
THIRD_PARTY_PREFIX ?= ../../..

include $(PBINCROOT)/common.mk

# All Google Test headers.  Usually you shouldn't change this.
GTEST_ROOT := $(THIRD_PARTY)/gtest/fused-src
GTEST_SRC  := $(GTEST_ROOT)/gtest/gtest-all.cc \
              $(GTEST_ROOT)/gtest/gtest_main.cc

# INCLUDE DIRS
INCDIRS    = -I$(PBINCROOT)/alignment \
             -I$(PBINCROOT)/hdf \
             -I$(PBINCROOT)/pbdata \
			 -I$(PBINCROOT)/unittest \
             -I$(GTEST_ROOT) \
             -I$(HDF5_INC)

# LIB DIRS
LIBDIRS    = -L$(PBINCROOT)/alignment \
             -L$(PBINCROOT)/hdf \
             -L$(PBINCROOT)/pbdata \
             -L$(HDF5_LIB) 

LDFLAGS1 := -lblasr -lpbihdf -lpbdata 
# The order of -l{lib} matters

ifeq ($(origin nopbbam), undefined)
	INCDIRS += -I$(PBBAM)/include -I$(PBBAM)/third-party/htslib
	LIBDIRS += -L$(PBBAM)/lib -L$(PBBAM)/third-party/htslib
	LDFLAGS1 += -lpbbam
# Use libhts.a built with pbbam
ifneq ($(wildcard "$(PBBAM)/third-party/htslib/libhts.a"), "")
	LDFLAGS1 += $(PBBAM)/third-party/htslib/libhts.a 
else
    LDFLAGS1 += lhts
endif
endif

ifneq ($(ZLIB_ROOT), notfound)
	INCDIRS += -I$(ZLIB_ROOT)/include
	LIBDIRS += -L$(ZLIB_ROOT)/lib
endif

ifneq ($(wildcard "$(HDF5_LIB)/libhdf5_cpp.a"),"")
    LDFLAGS   := $(LDFLAGS1) $(HDF5_LIB)/libhdf5_cpp.a $(HDF5_LIB)/libhdf5.a -lpthread -lz -ldl
else
    LDFLAGS   := $(LDFLAGS1) -lhdf5_cpp -lhdf5 -lpthread -lz -ldl
endif


CXX := g++
CXXOPTS := -std=c++11 -Wno-div-by-zero 

all : CXXFLAGS ?= -O3

debug : CXXFLAGS ?= -g -ggdb -fno-inline

profile : CXXFLAGS ?= -Os -pg


