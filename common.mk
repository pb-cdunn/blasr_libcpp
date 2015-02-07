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

# handle HDF5_ROOT
ifeq ($(origin HDF5_ROOT), undefined)
	HDF5_ROOT := $(shell cd $(PREBUILT)/hdf5/hdf5-1.8.12/centos-5/artifact 2>/dev/null && pwd || echo -n notfound)
else
	HDF5_ROOT := $(shell cd $(HDF5_ROOT) 2>/dev/null && pwd || echo -n notfound)
endif

ifeq ($(HDF5_ROOT), notfound)
	HDF5_ROOT := $(shell cd $(THIRD_PARTY)/hdf5 2>/dev/null && pwd || echo -n notfound)
	ifeq ($(HDF5_ROOT), notfound)
		$(error please set HDF5_ROOT to a built source tree of hdf5.)
	endif
endif

# this is a magic string from our build system
OS_STRING2 ?= centos-5

# handle ZLIB_ROOT
ifeq ($(origin ZLIB_ROOT), undefined)
	ZLIB_ROOT := $(shell cd $(PREBUILT)/zlib/zlib-1.2.5/$(OS_STRING2) 2>/dev/null && pwd || echo -n notfound)
else
	ZLIB_ROOT := $(shell cd $(ZLIB_ROOT) 2>/dev/null && pwd || echo -n notfound)
endif

ifeq ($(ZLIB_ROOT), notfound)
	# we don't need a backup ZLIB_ROOT here, because almost everybody has one in their paths
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
