
include ../common.mk

INCLUDES = -I$(HDF5_ROOT)/include \
	   -I../pbdata

ifeq ($(origin nopbbam), undefined)
    INCLUDES += -I$(PBBAM)/include -I$(PBBAM)/third-party/htslib -I../../../../prebuilt.out/boost/boost_1_55_0
endif

ifneq ($(ZLIB_ROOT), notfound)
	INCLUDES += -I$(ZLIB_ROOT)/include
endif

CXXOPTS := -std=c++11 -pedantic -MMD -MP
sources := $(wildcard *.cpp)
objects := $(sources:.cpp=.o)
dependencies := $(sources:.cpp=.d)

all : CXXFLAGS ?= -O3

debug : CXXFLAGS ?= -g -ggdb -fno-inline

profile : CXXFLAGS ?= -Os -pg

g : CXXFLAGS ?= -g -ggdb -fno-inline -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -fno-omit-frame-pointer 

all debug profile g: libpbihdf.a

libpbihdf.a: $(objects)
	$(AR_pp) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

# .INTERMEDIATE: $(objects)

clean: 
	@rm -f libpbihdf.a
	@rm -f $(objects) $(dependencies)

-include $(dependencies)
