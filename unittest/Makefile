SHELL=bash

PBINCROOT   := ..
PREBUILT    := ../../../../prebuilt.out
THIRD_PARTY := $(abspath ../../../third-party/cpp)

include ./common.mk

LIBDIRS := -L$(PBINCROOT)/alignment \
           -L$(PBINCROOT)/pbdata \
           -L$(PBINCROOT)/hdf \
           -L$(HDF5_ROOT)/src/.libs \
           -L$(HDF5_ROOT)/c++/src/.libs

ifneq ($(ZLIB_ROOT), notfound)
	LIBDIRS += -L$(ZLIB_ROOT)/lib
endif

LDFLAGS := -lblasr -lpbihdf -lpbdata -lhdf5_cpp -lhdf5 -lpthread -lz -ldl

OS := $(shell uname)

ifeq ($(OS), Darwin)
	LD_WHOLE_ARCHIVE := -all_load
	LD_NO_WHOLE_ARCHIVE := -noall_load
else
	LD_WHOLE_ARCHIVE := --whole-archive
	LD_NO_WHOLE_ARCHIVE := --no-whole-archive
endif

EXE := test-runner

all: $(EXE)
	
gtest: $(EXE)
	./$< --gtest_output=xml:./xml/all.xml

LIBS := alignment/libblasr_gtest.a \
		hdf/libpbihdf_gtest.a \
		pbdata/libpbdata_gtest.a

$(EXE): $(LIBS)
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $(GTEST_SRC) -Wl,$(LD_WHOLE_ARCHIVE) $^ -Wl,$(LD_NO_WHOLE_ARCHVIE) -o $@ -I$(GTEST_ROOT) $(LIBDIRS) $(LDFLAGS)

$(LIBS):
	make -C $(dir $@) $(notdir $@)

clean:
	@make -C alignment clean
	@make -C hdf clean
	@make -C pbdata clean
	@rm -fr $(EXE) xml

