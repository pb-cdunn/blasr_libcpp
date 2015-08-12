SHELL=bash

V  := 0
V@ := @
ifeq ($(V),$(filter $(V),1))
    # Enable verbose mode if V=1 or V= specified on command ine
    V@ :=
endif

MKDIR := mkdir

null :=
space := $(null) $(null)



OUTDIR := _output

GTEST_SRCDIR       := __UNSET__

LIBBLASR_INCLUDE   := __UNSET__
LIBPBIHDF_INCLUDE  := __UNSET__
LIBPBDATA_INCLUDE  := __UNSET__
PBBAM_INCLUDE      := __UNSET__
HTSLIB_INCLUDE     := __UNSET__
HDF5_INCLUDE       := __UNSET__
BOOST_INCLUDE      := __UNSET__
GTEST_INCLUDE      := __UNSET__

LIBBLASR_LIB       := __UNSET__
LIBPBIHDF_LIB      := __UNSET__
LIBPBDATA_LIB      := __UNSET__
PBBAM_LIB          := __UNSET__
HTSLIB_LIB         := __UNSET__
HDF5_LIB           := __UNSET__
ZLIB_LIB           := __UNSET__



broken_test_sources := \
	alignment/files/ReaderAgglomerate_gtest.cpp \
	alignment/format/SAMHeaderPrinter_gtest.cpp \
	alignment/format/SAMPrinter_gtest.cpp \
	alignment/utils/FileUtils_gtest.cpp \
	$(null)


gtest_sources  := $(GTEST_SRCDIR)/gtest/gtest-all.cc \
                  $(GTEST_SRCDIR)/gtest/gtest_main.cc \
		  $(null)

test_sources   := $(wildcard pbdata/*.cpp) \
                  $(wildcard pbdata/utils/*.cpp) \
                  $(wildcard pbdata/metagenome/*.cpp) \
                  $(wildcard pbdata/saf/*.cpp) \
                  $(wildcard pbdata/reads/*.cpp) \
                  $(wildcard pbdata/qvs/*.cpp)  \
                  \
                  $(wildcard hdf/*.cpp) \
                  \
                  $(wildcard alignment/*.cpp) \
                  $(wildcard alignment/utils/*.cpp) \
                  $(wildcard alignment/datastructures/alignment/*.cpp) \
                  $(wildcard alignment/files/*.cpp) \
                  $(wildcard alignment/format/*.cpp) \
                  $(null)

# Remove broken tests from the test_sources list
test_sources   := $(filter-out $(broken_test_sources),$(test_sources))


sources   := $(gtest_sources) $(test_sources)
objects   := $(patsubst %.cc,$(OUTDIR)/%.o,$(filter %.cc,$(sources))) \
             $(patsubst %.cpp,$(OUTDIR)/%.o,$(filter %.cpp,$(sources))) \
             $(null)
depfiles  := $(objects:%.o=%.d)


includes := \
    -I. \
    -I$(GTEST_INCLUDE) \
    -I$(LIBBLASR_INCLUDE) \
    -I$(LIBPBIHDF_INCLUDE) \
    -I$(LIBPBDATA_INCLUDE) \
    -I$(PBBAM_INCLUDE) \
    -I$(HTSLIB_INCLUDE) \
    -I$(HDF5_INCLUDE) \
    -I$(BOOST_INCLUDE) \
    $(null)

libs := \
    $(LIBBLASR_LIB) \
    $(LIBPBIHDF_LIB) \
    $(LIBPBDATA_LIB) \
    $(PBBAM_LIB) \
    $(HTSLIB_LIB) \
    $(HDF5_LIB) \
    $(HDF5_CPP_LIB) \
    $(ZLIB_LIB) \
    $(null)


sys_ldflags := -lpthread -ldl -lrt


cxxopts := -std=c++11 -Wno-div-by-zero 
cxxflags := -O3
ldflags := $(libs) $(sys_ldflags)



CPPFLAGS := $(includes) $(EXTRA_CPPFLAGS)
CXXFLAGS := $(cxxflags) $(cxxopts) $(EXTRA_CXXFLAGS)
LDLIBS   := $(ldflags) $(EXTRA_LDLIBS)

OUTPUT_OPTION = -o $@
COMPILE.cpp   = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cc    = $(COMPILE.cpp)
LINK.o        = $(CXX) $(LDFLAGS) $(TARGET_ARCH)


all: test-runner

test-runner: $(objects)
	$(V@)$(LINK.o) $^ $(LDLIBS) $(OUTPUT_OPTION)

gtest: test-runner
	$(V@)LD_LIBRARY_PATH=$(subst $(space),:,$(strip $(dir $(libs)))) ./$< --gtest_output=xml:$(OUTDIR)/xml/all.xml

# Build objects
$(OUTDIR)/%.o: %.cpp
	@echo "  CXX    $@"
	$(V@)$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(OUTDIR)/%.o: %.cc
	@echo "  CXX    $@"
	$(V@)$(COMPILE.cc) $(OUTPUT_OPTION) $<

# Make all directories of object files 'order-only' dependencies of all objects
# This will make all the output directories we need before building any objects
$(objects): | $(dir $(objects))

# Create any output directories
$(OUTDIR)/%/:
	$(V@)$(MKDIR) -p "$@"


clean:
	$(V@)$(RM) -r $(OUTDIR)

-include ${depfiles}
