include ../common.mk

CXXOPTS := -std=c++11 -pedantic -MMD -MP
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

all debug profile g: mklibconfig libpbdata.a

mklibconfig:
ifeq ($(origin nopbbam), undefined)
	ls $(PBBAM)/lib/libpbbam.a 2>/dev/null || (rm -rf $(PBBAM)/build && mkdir $(PBBAM)/build && cd $(PBBAM)/build && cmake ../ && make)
	@grep "USE_PBBAM" libconfig.h > /dev/null || echo "#define USE_PBBAM" > libconfig.h
    INCLUDES += -I$(PBBAM)/include -I$(PBBAM)/third-party/htslib/htslib 
else
	@rm -f libconfig.h && echo "" > libconfig.h && echo "no use libpbbam"
endif

libpbdata.a: $(objects)
	$(AR_pp) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -c $< -o $@

# .INTERMEDIATE: $(objects)

clean: 
	@rm -f libpbdata.a
	@rm -f $(objects) $(dependencies)

-include $(dependencies)
