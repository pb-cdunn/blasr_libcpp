
include ../common.mk

INCLUDES = -I$(HDF5_ROOT)/include \
           -I../pbdata \
           -I../hdf \
	   -I.

ifneq ($(ZLIB_ROOT), notfound)
	INCLUDES += -I$(ZLIB_ROOT)/include
endif

CXXOPTS := -std=c++0x -pedantic -Wno-long-long -MMD -MP

sources := $(wildcard algorithms/alignment/*.cpp) \
		   $(wildcard algorithms/alignment/sdp/*.cpp) \
		   $(wildcard algorithms/anchoring/*.cpp) \
		   $(wildcard algorithms/compare/*.cpp) \
		   $(wildcard algorithms/sorting/*.cpp) \
		   $(wildcard datastructures/alignment/*.cpp) \
		   $(wildcard datastructures/alignmentset/*.cpp) \
		   $(wildcard datastructures/anchoring/*.cpp) \
		   $(wildcard datastructures/tuplelists/*.cpp) \
		   $(wildcard suffixarray/*.cpp) \
		   $(wildcard qvs/*.cpp) \
		   $(wildcard statistics/*.cpp) \
		   $(wildcard tuples/*.cpp) \
		   $(wildcard utils/*.cpp) \
		   $(wildcard files/*.cpp) \
		   $(wildcard format/*.cpp) \
		   $(wildcard simulator/*.cpp) \
		   $(wildcard *.cpp) 

ifdef nohdf
sources := $(filter-out files/% utils/FileOfFileNames.cpp, $(sources))
endif

objects := $(sources:.cpp=.o)
dependencies := $(sources:.cpp=.d)

all : CXXFLAGS ?= -O3

debug : CXXFLAGS ?= -g -ggdb -fno-inline

profile : CXXFLAGS ?= -Os -pg

g: CXXFLAGS = -g -ggdb -fno-inline -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -fno-omit-frame-pointer 

all debug profile g: libblasr.a

libblasr.a: $(objects)
	$(AR_pp) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $(LEGACY) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

# .INTERMEDIATE: $(objects)

clean: 
	@rm -f libblasr.a
	@find . -type f -name \*.o -delete
	@find . -type f -name \*.d -delete


-include $(dependencies)
