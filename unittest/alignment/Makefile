include ../common.mk

INCDIRS    = -I.. \
             -I$(PBINCROOT)/alignment \
             -I$(PBINCROOT)/pbdata \
             -I$(PBINCROOT)/hdf \
             -I$(GTEST_ROOT) \
             -I$(HDF5_ROOT)/src \
             -I$(HDF5_ROOT)/c++/src

LIBDIRS    = -L$(PBINCROOT)/alignment \
             -L$(PBINCROOT)/pbdata \
             -L$(PBINCROOT)/hdf \
             -L$(HDF5_ROOT)/src/.libs \
             -L$(HDF5_ROOT)/c++/src/.libs 

LDFLAGS   := -lblasr -lpbihdf -lpbdata -lhdf5_cpp -lhdf5 -lpthread -lz -ldl
# The order of -l{lib} matters

SOURCES    = $(wildcard *.cpp) \
		     $(wildcard utils/*.cpp) \
		     $(wildcard datastructures/alignment/*.cpp) \
		     $(wildcard files/*.cpp) 
OBJECTS    = $(SOURCES:.cpp=.o)

EXE := test-runner

all debug profile: $(EXE)

libblasr_gtest.a: $(OBJECTS)
	$(AR_pp) $(ARFLAGS)c $@ $^

$(EXE): $(OBJECTS)
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) $^ $(GTEST_SRC) -o $@ -I$(GTEST_ROOT) $(LIBDIRS) $(LDFLAGS)

$(OBJECTS): %.o: %.cpp
	$(CXX_pp) $(CXXOPTS) $(CXXFLAGS) -c $< -o $@ $(INCDIRS)

gtest: $(EXE)
	./$< --gtest_output=xml:../xml/alignment.xml

clean:
	@find . -type f -name \*.o -delete
	@find . -type f -name \*.d -delete
	@rm -f libblasr_gtest.a $(EXE) ../xml/alignment.xml
