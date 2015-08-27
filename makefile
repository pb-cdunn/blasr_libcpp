SHELL=/bin/bash

THISDIR:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))

.PHONY: all libpbdata libhdf libblasr gtest clean cleanall

all:
	${MAKE} libpbdata
	${MAKE} libhdf
	${MAKE} libblasr
libpbdata:
	${MAKE} -C ${THISDIR}/pbdata all
libhdf:
	${MAKE} -C ${THISDIR}/hdf all
libblasr:
	${MAKE} -C ${THISDIR}/alignment all
gtest:
	${MAKE} -C ${THISDIR}/unittest gtest
clean:
	${MAKE} -C ${THISDIR}/pbdata clean
	${MAKE} -C ${THISDIR}/hdf clean
	${MAKE} -C ${THISDIR}/alignment clean
	#@${MAKE} -C ${THISDIR}/unittest clean
cleanall: clean

# Note: hdf/ will not build if nohdf=1 is configured.
