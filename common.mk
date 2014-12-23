SHELL=bash

#
# Definitions common to all make files for library code.
# All paths are relative from inside the subdirectories, not this file
#

THIRD_PARTY_PREFIX ?= ../..

# git layout vs p4 layout automagic
THIRD_PARTY ?= $(shell cd $(abspath $(THIRD_PARTY_PREFIX)/third-party) 2>/dev/null && pwd || echo -n notfound)
ifeq ($(THIRD_PARTY), notfound)
	THIRD_PARTY := $(shell cd $(abspath $(THIRD_PARTY_PREFIX)/../third-party/cpp) 2>/dev/null && pwd || echo -n notfound)
	ifeq ($(THIRD_PARTY), notfound)
		$(error cannot find third-party libraries!)
	endif
endif

PREBUILT ?= ../../../../prebuilt.out

# this is a magic string from our build system
OS_STRING2 ?= centos-5

HDF5_ROOT := $(shell cd $(PREBUILT)/hdf5/hdf5-1.8.12/$(OS_STRING2)/artifact 2>/dev/null && pwd || echo -n notfound)
ifeq ($(HDF5_ROOT), notfound)
	HDF5_ROOT := $(shell cd $(THIRD_PARTY)/hdf5 2>/dev/null && pwd || echo -n notfound)
	ifeq ($(HDF5_ROOT), notfound)
		$(error please set HDF5_ROOT to a built source tree of hdf5.)
	endif
endif

# magic for non-verbose builds
V ?= 0

CXX_0 = @echo "  CXX	$@"; $(CXX)
CXX_1 = $(CXX)
CXX_pp = $(CXX_$(V))

AR_0 = @echo "  AR	$@"; $(AR)
AR_1 = $(AR)
AR_pp = $(AR_$(V))

ARFLAGS := rc
