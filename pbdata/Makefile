#LEGACY := -I../../../../assembly/cpp/common
CXXOPTS := -I . -pedantic -c -fmessage-length=0 -MMD -MP
INCLUDE := -I matrix -I reads -I qvs -I metagenome -I saf -I utils -I alignment

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

all : GCCOPTS = -O3

debug : GCCOPTS = -g -ggdb -fno-inline

profile : GCCOPTS = -Os -pg

all debug profile: libpbdata.a

libpbdata.a: libpbdata.a($(objects))
	$(AR) $(ARFLAGS)s $@ $%

%.o: %.cpp
	$(CXX) $(GCCOPTS) $(CXXOPTS) $(INCLUDE) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -o $@ $<

.INTERMEDIATE: $(objects)

clean: 
	rm -f libpbdata.a
	rm -f $(objects) $(dependencies)

-include $(dependencies)
