# Let common.mk know that that the third party checks should be ignored
COMMON_NO_THIRD_PARTY_REQD := true

include ../common.mk

CXXOPTS := -std=c++11 -pedantic -MMD -MP
INCLUDES := -I. -Imatrix -Ireads -Iqvs -Imetagenome -Isaf -Iutils -Ialignment

# To enable building a shared library, invoke as "make SHARED_LIB=true ..."
ifneq ($(SHARED_LIB),)
    # Generating shared library
    CXX_SHAREDFLAGS := -fPIC
    LD_SHAREDFLAGS  := -shared -fPIC
    TARGET_LIB      := libpbdata.so
    # Developers should set these to appropriate defaults (other systems 
    # will override these on the command line):
    PBBAM_LIB      := ../../../staging/PostPrimary/pbbam/_output/install-build/lib/libpbbam.so
    HTSLIB_LIB       := ../../../staging/PostPrimary/htslib/_output/install-build/lib/libhts.so
else
    # Generating static library
    CXX_SHAREDFLAGS :=
    TARGET_LIB      := libpbdata.a
    LD_SHAREDFLAGS  :=
    HTSLIB_LIB      :=
    PBBAM_LIB       := 
endif

DEP_LIBS := $(HTSLIB_LIB) $(PBBAM_LIB)

PBBAM_INCLUDE := $(PBBAM)/include
HTSLIB_INCLUDE ?= $(HTSLIB)

sources := $(wildcard *.cpp) \
	       $(wildcard matrix/*.cpp) \
	       $(wildcard reads/*.cpp) \
	       $(wildcard metagenome/*.cpp) \
	       $(wildcard qvs/*.cpp) \
	       $(wildcard saf/*.cpp) \
	       $(wildcard utils/*.cpp) \
	       $(wildcard loadpulses/*.cpp) \
	       $(wildcard alignment/*.cpp) \
	       $(wildcard amos/*.cpp) \
	       $(wildcard sam/*.cpp) 

objects := $(sources:.cpp=.o)
shared_objects := $(sources:.cpp=.shared.o)
dependencies := $(objects:.o=.d) $(shared_objects:.o=.d)

all : CXXFLAGS ?= -O3

debug : CXXFLAGS ?= -g -ggdb -fno-inline

profile : CXXFLAGS ?= -Os -pg

g: CXXFLAGS = -g -ggdb -fno-inline -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -fno-omit-frame-pointer 

all debug profile g: mklibconfig $(TARGET_LIB)

ifeq ($(origin nopbbam), undefined)
    INCLUDES += -I$(PBBAM_INCLUDE) -I$(HTSLIB_INCLUDE) -I$(BOOST_INCLUDE)
    USE_PBBAM:=YES
else
    USE_PBBAM:=NO
endif

mklibconfig:
	./mklibconfig.sh libconfig.h ${USE_PBBAM}

libpbdata.a: $(objects)
	$(AR_pp) $(ARFLAGS) $@ $^

libpbdata.so: $(shared_objects) $(DEP_LIBS)
	$(CXX_pp) $(LD_SHAREDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

%.shared.o: %.cpp
	$(CXX_pp) $(CXX_SHAREDFLAGS) $(CXXOPTS) $(CXXFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

# .INTERMEDIATE: $(objects)

clean: 
	@rm -f libpbdata.a  libpbdata.so
	@rm -f $(objects) $(shared_objects) $(dependencies)

-include $(dependencies)
