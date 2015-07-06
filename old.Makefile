SHELL=/bin/bash

.PHONY: all debug profile gtest clean cleanall

subs:
	${MAKE} -C pbdata all
	${MAKE} -C hdf all
	${MAKE} -C alignment all

debug:
	${MAKE} subs

profile:
	${MAKE} subs

g:
	${MAKE} subs

gtest:
	${MAKE} -C unittest gtest

clean:
	@${MAKE} -C pbdata clean
	@${MAKE} -C hdf clean
	@${MAKE} -C alignment clean
	@${MAKE} -C unittest clean

cleanall: clean
