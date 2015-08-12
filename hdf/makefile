all:

THISDIR:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
-include ${CURDIR}/defines.mk
include ${THISDIR}/../rules.mk

CXXOPTS  += -std=c++11 -pedantic -MMD -MP
INCLUDES += ${LIBPBDATA_INC} ${HDF5_INC} ${PBBAM_INC} ${HTSLIB_INC} ${BOOST_INC}
LIBS     += ${LIBPBDATA_LIB} ${HDF5_LIB} ${PBBAM_LIB} ${HTSLIB_LIB} ${ZLIB_LIB}
LDFLAGS  += $(patsubst %,-L%,${LIBS})

all: libpbihdf.a libpbihdf${SH_LIB_EXT}

paths := ${THISDIR}
sources := $(wildcard ${THISDIR}*.cpp)
objects := $(sources:.cpp=.o)
shared_objects := $(sources:.cpp=.shared.o)
dependencies := $(objects:.o=.d) $(shared_objects:.o=.d)

vpath %.cpp ${paths}

libpbihdf.a: $(objects)
	$(AR) $(ARFLAGS) $@ $^

libpbihdf.so: $(shared_objects)

clean: 
	rm -f libpbihdf.a libpbihdf.so *.o *.d

-include $(dependencies)
