include ../common.mk

INCDIRS    = -I.. \
             -I$(PBINCROOT)/alignment \
             -I$(PBINCROOT)/pbdata \
             -I$(PBINCROOT)/hdf \
             -I$(GTEST_ROOT) \
             -I$(HDF5_ROOT)/include 

LIBDIRS    = -L$(PBINCROOT)/alignment \
             -L$(PBINCROOT)/pbdata \
             -L$(PBINCROOT)/hdf \
             -L$(HDF5_ROOT)/lib 

LDFLAGS1 := -lblasr -lpbihdf -lpbdata 

ifeq ($(origin nopbbam), undefined)
	INCDIRS += -I$(PBBAM)/include -I$(PBBAM)/third-party/htslib/htslib
	LIBDIRS += -L$(PBBAM)/lib -L$(PBBAM)/third-party/htslib
	LDFLAGS1 += -lpbbam -lhts
endif

ifneq ($(ZLIB_ROOT), notfound)
	INCDIRS += -I$(ZLIB_ROOT)/include
	LIBDIRS += -L$(ZLIB_ROOT)/lib
endif

ifneq ($(wildcard "$(HDF5_ROOT)/lib/libhdf5_cpp.a"),"")
    LDFLAGS   := $(LDFLAGS1) $(HDF5_ROOT)/lib/libhdf5_cpp.a $(HDF5_ROOT)/lib/libhdf5.a -lpthread -lz -ldl
else
    LDFLAGS   := $(LDFLAGS1) -lhdf5_cpp -lhdf5 -lpthread -lz -ldl
endif

SOURCES    = $(wildcard *.cpp) \
		     $(wildcard utils/*.cpp) \
		     $(wildcard datastructures/alignment/*.cpp) \
		     $(wildcard files/*.cpp) \
		     $(wildcard format/*.cpp) 

ifneq ($(origin nopbbam), undefined)
	SOURCES := $(filter-out format/SAMHeaderPrinter_gtest.cpp $(SOURCES))
endif

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
