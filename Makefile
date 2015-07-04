SHELL=/bin/bash

.PHONY: all debug profile gtest clean cleanall

# $Change: 140182 $ 

all:
	${MAKE} -C pbdata all
	${MAKE} -C hdf all
	${MAKE} -C alignment all

debug:
	${MAKE} -C pbdata debug
	${MAKE} -C hdf debug
	${MAKE} -C alignment debug

profile:
	${MAKE} -C pbdata profile
	${MAKE} -C hdf profile
	${MAKE} -C alignment profile

g:
	${MAKE} -C pbdata g
	${MAKE} -C hdf g
	${MAKE} -C alignment g

gtest:
	${MAKE} -C unittest gtest

clean:
	@${MAKE} -C pbdata clean
	@${MAKE} -C hdf clean
	@${MAKE} -C alignment clean
	@${MAKE} -C unittest clean

cleanall: clean
