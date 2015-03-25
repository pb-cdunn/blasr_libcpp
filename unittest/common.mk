SHELL=bash

.PHONY: all debug profile clean

#
# Definitions common to all make files for unit tests.
# All paths are relative from inside the subdirectories, not this file
#

PBINCROOT 		   ?= ../..
PREBUILT    	   ?= ../../../../../prebuilt.out
THIRD_PARTY_PREFIX ?= ../../..

include $(PBINCROOT)/common.mk

# All Google Test headers.  Usually you shouldn't change this.
GTEST_ROOT := $(THIRD_PARTY)/gtest/fused-src
GTEST_SRC  := $(GTEST_ROOT)/gtest/gtest-all.cc \
              $(GTEST_ROOT)/gtest/gtest_main.cc

CXX := g++
CXXOPTS := -std=c++11 -Wno-div-by-zero 

all : CXXFLAGS ?= -O3

debug : CXXFLAGS ?= -g -ggdb -fno-inline

profile : CXXFLAGS ?= -Os -pg
