#changelist 137921
#LEGACY := -I../../../../assembly/cpp/common
INCLUDES = -I../../../../assembly/seymour/dist/common/include \
		   -I../pbdata \
		   -I../hdf

CXXOPTS := -I . -I../hdf/ -pedantic -c -Wno-long-long -MMD -MP -std=c++0x

sources := $(wildcard algorithms/alignment/*.cpp) \
		   $(wildcard algorithms/alignment/sdp/*.cpp) \
		   $(wildcard algorithms/anchoring/*.cpp) \
		   $(wildcard algorithms/compare/*.cpp) \
		   $(wildcard algorithms/sorting/*.cpp) \
		   $(wildcard datastructures/alignment/*.cpp) \
		   $(wildcard datastructures/alignmentset/*.cpp) \
		   $(wildcard datastructures/anchoring/*.cpp) \
		   $(wildcard datastructures/tuplelists/*.cpp) \
		   $(wildcard qvs/*.cpp) \
		   $(wildcard statistics/*.cpp) \
		   $(wildcard tuples/*.cpp) \
		   $(wildcard utils/*.cpp) \
		   $(wildcard files/*.cpp) \
		   $(wildcard format/*.cpp) \
		   $(wildcard *.cpp) \

objects := $(sources:.cpp=.o)
dependencies := $(sources:.cpp=.d)

all : GCCOPTS = -O3

debug : GCCOPTS = -g -ggdb

profile : GCCOPTS = -Os -pg

all debug profile: libblasr.a

libblasr.a: libblasr.a($(objects))
	$(AR) $(ARFLAGS)s $@ $%

%.o: %.cpp
	$(CXX) $(GCCOPTS) $(CXXOPTS) $(LEGACY) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -o $@ $<

.INTERMEDIATE: $(objects)

clean: 
	rm -f libblasr.a
	find . -type f -name \*.o -delete
	find . -type f -name \*.d -delete


-include $(dependencies)
