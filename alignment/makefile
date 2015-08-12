all:

include ../rules.mk
include ../defines.mk

CXXOPTS  := -std=c++11 -pedantic -MMD -MP -Wno-long-long
INCLUDES += . ${LIBPBDATA_INC} ${LIBPBIHDF_INC} ${HDF5_INC} ${PBBAM_INC} ${HTSLIB_INC} ${BOOST_INC}
LIBS     += ${LIBPBDATA_LIB} ${HDF5_LIB} ${PBBAM_LIB} ${HTSLIB_LIB} ${ZLIB_LIB}
LDFLAGS  += $(patsubst %,-L%,${LIBS})

all: libblasr.a libblasr${SH_LIB_EXT}

sources := $(wildcard algorithms/alignment/*.cpp) \
		   $(wildcard algorithms/alignment/sdp/*.cpp) \
		   $(wildcard algorithms/anchoring/*.cpp) \
		   $(wildcard algorithms/compare/*.cpp) \
		   $(wildcard algorithms/sorting/*.cpp) \
		   $(wildcard datastructures/alignment/*.cpp) \
		   $(wildcard datastructures/alignmentset/*.cpp) \
		   $(wildcard datastructures/anchoring/*.cpp) \
		   $(wildcard datastructures/tuplelists/*.cpp) \
		   $(wildcard suffixarray/*.cpp) \
		   $(wildcard qvs/*.cpp) \
		   $(wildcard statistics/*.cpp) \
		   $(wildcard tuples/*.cpp) \
		   $(wildcard utils/*.cpp) \
		   $(wildcard files/*.cpp) \
		   $(wildcard format/*.cpp) \
		   $(wildcard simulator/*.cpp) \
		   $(wildcard *.cpp) 

ifdef nohdf
sources := $(filter-out files/% utils/FileOfFileNames.cpp format/SAMHeaderPrinter.cpp, $(sources))
endif

objects := $(sources:.cpp=.o)
shared_objects := $(sources:.cpp=.shared.o)
dependencies := $(objects:.o=.d) $(shared_objects:.o=.d)

libblasr.a: $(objects)
	$(AR) $(ARFLAGS) $@ $^

libblasr.so: $(shared_objects)

clean: 
	@rm -f libblasr.a libblasr.so
	@rm -f $(objects) $(shared_objects) $(dependencies)
	@find . -type f -name \*.o -delete
	@find . -type f -name \*.d -delete

-include $(dependencies)
