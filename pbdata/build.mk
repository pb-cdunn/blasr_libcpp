all:

include ../rules.mk
include ../defines.mk

CXXOPTS += -std=c++11 -pedantic -MMD -MP
INCLUDES += -I. -Imatrix -Ireads -Iqvs -Imetagenome -Isaf -Iutils -Ialignment

all: libpbdata.a

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

libpbdata.a: $(objects)
	$(AR) $(ARFLAGS) $@ $^

libpbdata.so: $(shared_objects) $(DEP_LIBS)
	$(CXX) $(LD_SHAREDFLAGS) -o $@ $^

clean: 
	@rm -f libpbdata.a  libpbdata.so
	@rm -f $(objects) $(shared_objects) $(dependencies)

-include $(dependencies)
