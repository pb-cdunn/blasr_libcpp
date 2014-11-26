
HDF5_INC = ../../../../../assembly/seymour/dist/common/include

INCLUDES = -I$(HDF_INC) \
		   -I../pbdata
CXXOPTS := -std=c++0x -pedantic -c -fmessage-length=0 -MMD -MP
sources := $(wildcard *.cpp)
objects := $(sources:.cpp=.o)
dependencies := $(sources:.cpp=.d)

all : GCCOPTS = -O3

debug : GCCOPTS = -g -ggdb -fno-inline

profile : GCCOPTS = -Os -pg

all debug profile: libpbihdf.a

libpbihdf.a: libpbihdf.a($(objects))
	$(AR) $(ARFLAGS)s $@ $%

%.o: %.cpp
	$(CXX) $(GCCOPTS) $(CXXOPTS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o) $(@:%.o=%.d)" -o $@ $<

.INTERMEDIATE: $(objects)

clean: 
	rm -f libpbihdf.a
	rm -f $(objects) $(dependencies)

-include $(dependencies)
