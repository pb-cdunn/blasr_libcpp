include ../common.mk

INCDIRS    = -I.. \
             -I$(PBINCROOT)/pbdata \
             -I$(PBINCROOT)/hdf \
             -I$(GTEST_ROOT) \
             -I$(HDF5_ROOT)/include

LIBDIRS    = -L$(PBINCROOT)/pbdata \
             -L$(PBINCROOT)/hdf \
             -L$(HDF5_ROOT)/lib

ifneq ($(ZLIB_ROOT), notfound)
	INCDIRS += -I$(ZLIB_ROOT)/include
	LIBDIRS += -L$(ZLIB_ROOT)/lib
endif

ifneq ($(wildcard "$(HDF5_ROOT)/lib/libhdf5_cpp.a"),"")
    LDFLAGS   := -lpbihdf -lpbdata $(HDF5_ROOT)/lib/libhdf5_cpp.a $(HDF5_ROOT)/lib/libhdf5.a -lpthread -lz -ldl
else
    LDFLAGS   := -lpbihdf -lpbdata -lhdf5_cpp -lhdf5 -lpthread -lz -ldl
endif
# The order of -l{lib} matters

SOURCES    = $(wildcard *.cpp) 
OBJECTS    = $(SOURCES:.cpp=.o)

EXE := test-runner

all debug profile: $(EXE)

libpbihdf_gtest.a: $(OBJECTS)
	$(AR_pp) $(ARFLAGS)c $@ $^

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
