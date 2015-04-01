include ../common.mk

INCDIRS    = -I.. \
             -I$(PBINCROOT)/pbdata \
             -I$(PBINCROOT)/hdf \
             -I$(GTEST_ROOT) \
             -I$(HDF5_INC)

LIBDIRS    = -L$(PBINCROOT)/pbdata \
             -L$(PBINCROOT)/hdf \
             -L$(HDF5_LIB)

LDFLAGS1 := -lpbihdf -lpbdata 

ifeq ($(origin nopbbam), undefined)
	INCDIRS += -I$(PBBAM)/include -I$(PBBAM)/third-party/htslib/htslib
	LIBDIRS += -L$(PBBAM)/lib -L$(PBBAM)/third-party/htslib
	LDFLAGS1 += -lpbbam -lhts
endif


ifneq ($(ZLIB_ROOT), notfound)
	INCDIRS += -I$(ZLIB_ROOT)/include
	LIBDIRS += -L$(ZLIB_ROOT)/lib
endif

ifneq ($(wildcard "$(HDF5_LIB)/libhdf5_cpp.a"),"")
    LDFLAGS   := $(LDFLAGS1) $(HDF5_LIB)/libhdf5_cpp.a $(HDF5_LIB)/libhdf5.a -lpthread -lz -ldl
else
    LDFLAGS   := $(LDFLAGS1) -lhdf5_cpp -lhdf5 -lpthread -lz -ldl
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
