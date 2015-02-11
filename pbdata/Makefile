
include ../common.mk

CXXOPTS := -std=c++0x -pedantic -MMD -MP
INCLUDES := -I. -Imatrix -Ireads -Iqvs -Imetagenome -Isaf -Iutils -Ialignment

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
dependencies := $(sources:.cpp=.d)

all : CXXFLAGS ?= -O3

debug : CXXFLAGS ?= -g -ggdb -fno-inline

profile : CXXFLAGS ?= -Os -pg

g: CXXFLAGS = -g -ggdb -fno-inline -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -fno-omit-frame-pointer 

all debug profile g: libpbdata.a

libpbdata.a: $(objects)
	$(AR_pp) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

# .INTERMEDIATE: $(objects)

clean: 
	@rm -f libpbdata.a
	@rm -f $(objects) $(dependencies)

-include $(dependencies)
