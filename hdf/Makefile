
include ../common.mk

PBDATA_INCLUDE := ../pbdata
PBBAM_INCLUDE := $(PBBAM)/include
HTSLIB_INCLUDE := $(PBBAM)/third-party/htslib

INCLUDES = -I$(PBDATA_INCLUDE)


ifeq ($(origin nopbbam), undefined)
    INCLUDES += -I$(PBBAM_INCLUDE) -I$(HTSLIB_INCLUDE) -I$(BOOST_INCLUDE)
endif

ifneq ($(ZLIB_ROOT), notfound)
	INCLUDES += -I$(ZLIB_ROOT)/include
endif

CXXOPTS := -std=c++11 -pedantic -MMD -MP
sources := $(wildcard *.cpp)
objects := $(sources:.cpp=.o)
dependencies := $(sources:.cpp=.d)

ifneq ($(HDF5_INC),)
HDF_HEADERS :=
INCLUDES += -I$(HDF5_INC)
else
HDF_HEADERS := hdf5-1.8.12-headers
INCLUDES += -I./$(HDF_HEADERS)/src -I./$(HDF_HEADERS)/c++/src
endif

all : CXXFLAGS ?= -O3

debug : CXXFLAGS ?= -g -ggdb -fno-inline

profile : CXXFLAGS ?= -Os -pg

g : CXXFLAGS ?= -g -ggdb -fno-inline -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -fno-omit-frame-pointer 

all debug profile g: $(HDF_HEADERS) libpbihdf.a

libpbihdf.a: $(objects)
	$(AR_pp) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX) $(CXXOPTS) $(CXXFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

$(HDF_HEADERS): 
	curl -L https://www.dropbox.com/s/8971bcyy5o42rxb/hdf5-1.8.12-headers.tar.bz2\?dl\=0 | tar xjf - 

# .INTERMEDIATE: $(objects)

clean: 
	@rm -f libpbihdf.a
	@rm -f $(objects) $(dependencies)

-include $(dependencies)
