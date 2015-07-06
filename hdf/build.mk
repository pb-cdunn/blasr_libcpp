all:

include ../rules.mk
include ../defines.mk

CXXOPTS += -std=c++11 -pedantic -MMD -MP
all: libpbihdf.a

sources := $(wildcard *.cpp)
objects := $(sources:.cpp=.o)
shared_objects := $(sources:.cpp=.shared.o)
dependencies := $(objects:.o=.d) $(shared_objects:.o=.d)

libpbihdf.a: $(objects)
	$(AR) $(ARFLAGS) $@ $^

libpbihdf.so: $(shared_objects) $(DEP_LIBS)
	$(CXX) $(LD_SHAREDFLAGS) -o $@ $^

clean: 
	@rm -f libpbihdf.a libpbihdf.so
	@rm -f $(objects) $(shared_objects) $(dependencies)

-include $(dependencies)
