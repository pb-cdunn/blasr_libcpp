SHELL=/bin/bash

.PHONY: all debug profile gtest clean cleanall

# $Change: 140182 $ 

all:
	make -C pbdata all
	make -C hdf all
	make -C alignment all

debug:
	make -C pbdata debug
	make -C hdf debug
	make -C alignment debug

profile:
	make -C pbdata profile
	make -C hdf profile
	make -C alignment profile

gtest:
	make -C unittest gtest

clean:
	make -C pbdata clean
	make -C hdf clean
	make -C alignment clean
	make -C unittest clean

cleanall: clean
