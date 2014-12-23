include ../common.mk

INCDIRS    = -I.. \
             -I$(PBINCROOT)/pbdata \
             -I$(PBINCROOT)/hdf \
             -I$(GTEST_ROOT) \
             -I$(HDF5_ROOT)/src \
             -I$(HDF5_ROOT)/c++/src

LIBDIRS    = -L$(PBINCROOT)/pbdata \
             -L$(PBINCROOT)/hdf \
             -L$(HDF5_ROOT)/src/.libs \
             -L$(HDF5_ROOT)/c++/src/.libs

LDFLAGS   := -lpbihdf -lpbdata -lhdf5_cpp -lhdf5 -lpthread -lz -ldl
# The order of -l{lib} matters

SOURCES    = $(wildcard *.cpp) 
OBJECTS    = $(SOURCES:.cpp=.o)

EXE := test-runner

all debug profile: $(EXE)

libpbihdf_gtest.a: $(OBJECTS)
	$(AR) $(ARFLAGS)c $@ $^

$(EXE): $(OBJECTS)
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $^ $(GTEST_SRC) -o $@ -I$(GTEST_ROOT) $(LIBDIRS) $(LDFLAGS)

$(OBJECTS): %.o: %.cpp
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) -c $< -o $@ $(INCDIRS)

gtest: $(EXE)
	./$< --gtest_output=xml:../xml/hdf.xml

clean:
	@find . -type f -name \*.o -delete
	@find . -type f -name \*.d -delete
	@rm -f libpbihdf_gtest.a $(EXE) ../xml/hdf.xml
