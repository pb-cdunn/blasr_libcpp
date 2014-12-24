
include ../common.mk

INCLUDES = -I$(HDF5_ROOT)/src \
		   -I$(HDF5_ROOT)/c++/src \
		   -I../pbdata

ifneq ($(ZLIB_ROOT), notfound)
	INCLUDES += -I$(ZLIB_ROOT)/include
endif

CXXOPTS := -std=c++0x -pedantic -MMD -MP
sources := $(wildcard *.cpp)
objects := $(sources:.cpp=.o)
dependencies := $(sources:.cpp=.d)

all : CXXFLAGS ?= -O3

debug : CXXFLAGS ?= -g -ggdb -fno-inline

profile : CXXFLAGS ?= -Os -pg

all debug profile: libpbihdf.a

libpbihdf.a: $(objects)
	$(AR_pp) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

# .INTERMEDIATE: $(objects)

clean: 
	@rm -f libpbihdf.a
	@rm -f $(objects) $(dependencies)

-include $(dependencies)
