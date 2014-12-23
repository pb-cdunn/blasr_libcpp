include ../common.mk

INCDIRS    = -I.. \
             -I$(PBINCROOT)/pbdata \
             -I$(GTEST_ROOT) \
             -I$(HDF5_ROOT)/src \
             -I$(HDF5_ROOT)/c++/src

LIBDIRS    = -L$(PBINCROOT)/pbdata \
             -L$(HDF5_ROOT)/src/.libs \
             -L$(HDF5_ROOT)/c++/src/.libs

LDFLAGS   := -lpbdata -lpthread -lz -ldl

SOURCES    = $(wildcard *.cpp) \
		     $(wildcard utils/*.cpp) \
		     $(wildcard metagenome/*.cpp) \
		     $(wildcard saf/*.cpp)
OBJECTS    = $(SOURCES:.cpp=.o)

EXE := test-runner

all debug profile: $(EXE)

libpbdata_gtest.a: $(OBJECTS)
	$(AR_pp) $(ARFLAGS)c $@ $^

$(EXE): $(OBJECTS)
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $^ $(GTEST_SRC) -o $@ -I$(GTEST_ROOT) $(LIBDIRS) $(LDFLAGS)

$(OBJECTS): %.o: %.cpp
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) -c $< -o $@ $(INCDIRS)

gtest: $(EXE)
	./$< --gtest_output=xml:../xml/pbdata.xml

clean:
	@find . -type f -name \*.o -delete
	@find . -type f -name \*.d -delete
	@rm -f libpbdata_gtest.a $(EXE) ../xml/pbdata.xml
