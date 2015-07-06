PBINCROOT?=..
#THIRD_PARTY_PREFIX ?= ../../..

#include $(PBINCROOT)/common.mk


HDF_HEADERS:=hdf5-1.8.12-headers
HDF5:=/home/UNIXHOME/cdunn/repo/pb/smrtanalysis-client/smrtanalysis/prebuilt.out/hdf5/hdf5-1.8.12/ubuntu-1404
HDF5_INC?=../hdf/${HDF_HEADERS}/src
HDF5_LIB?=${HDF5}/lib
INCLUDES+=-I${PBINCROOT}/hdf/${HDF_HEADERS}/src -I${PBINCROOT}/hdf/${HDF_HEADERS}/c++/src
#INCLUDES+=-I../pbdata -I../hdf -I.

#OS := $(shell uname)

#ifeq ($(OS), Darwin)
#	LD_WHOLE_ARCHIVE := -all_load
#	LD_NO_WHOLE_ARCHIVE := -noall_load
#else
#	LD_WHOLE_ARCHIVE := --whole-archive
#	LD_NO_WHOLE_ARCHIVE := --no-whole-archive
#endif

LD_WHOLE_ARCHIVE := --whole-archive
LD_NO_WHOLE_ARCHIVE := --no-whole-archive

# All Google Test headers.  Usually you shouldn't change this.
#GTEST_ROOT := $(THIRD_PARTY)/gtest/fused-src
GTEST_ROOT:=/home/UNIXHOME/cdunn/repo/gh/blasr_libcpp/../pbdagcon/test/cpp/gtest-1.7.0/fused-src
GTEST_SRC  := $(GTEST_ROOT)/gtest/gtest-all.cc \
              $(GTEST_ROOT)/gtest/gtest_main.cc

# INCLUDE DIRS
INCDIRS    = -I$(PBINCROOT)/alignment \
             -I$(PBINCROOT)/hdf \
             -I$(PBINCROOT)/pbdata \
			 -I$(PBINCROOT)/unittest \
             -I$(GTEST_ROOT)
INCDIRS+=${INCLUDES}

# LIB DIRS
LIBDIRS    = -L$(PBINCROOT)/alignment \
             -L$(PBINCROOT)/hdf \
             -L$(PBINCROOT)/pbdata \
             -L$(HDF5_LIB) 

LDFLAGS1 := -lblasr -lpbihdf -lpbdata 
# The order of -l{lib} matters

#LDFLAGS   := $(LDFLAGS1) -lhdf5_cpp -lhdf5 -lpthread -lz -ldl
LDFLAGS   := $(LDFLAGS1) $(HDF5_LIB)/libhdf5_cpp.a $(HDF5_LIB)/libhdf5.a -lpthread -lz -ldl

CXXOPTS := -std=c++11 -Wno-div-by-zero
CXXFLAGS := -O3
