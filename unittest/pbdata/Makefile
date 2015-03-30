include ../common.mk

INCDIRS    = -I.. \
             -I$(PBINCROOT)/pbdata \
             -I$(GTEST_ROOT) 

LIBDIRS    = -L$(PBINCROOT)/pbdata \
             -L$(HDF5_ROOT)/lib

LDFLAGS1 := -lpbdata 

ifeq ($(origin nopbbam), undefined)
	INCDIRS += -I$(PBBAM)/include -I$(PBBAM)/third-party/htslib/htslib
	LIBDIRS += -L$(PBBAM)/lib -L$(PBBAM)/third-party/htslib
	LDFLAGS1 += -lpbbam -lhts
endif


ifneq ($(ZLIB_ROOT), notfound)
	INCDIRS += -I$(ZLIB_ROOT)/include
	LIBDIRS += -L$(ZLIB_ROOT)/lib
endif

LDFLAGS   := $(LDFLAGS1) -lpthread -lz -ldl

SOURCES    = $(wildcard *.cpp) \
		     $(wildcard utils/*.cpp) \
		     $(wildcard metagenome/*.cpp) \
		     $(wildcard saf/*.cpp) \
		     $(wildcard reads/*.cpp) \
		     $(wildcard qvs/*.cpp) 
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
