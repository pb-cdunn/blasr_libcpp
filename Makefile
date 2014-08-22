.PHONY: all debug profile gtest clean

# $Change: 139398 $ 

all:
	cd pbdata;\
	make all
	cd hdf;\
	make all
	cd alignment;\
	make all

debug:
	cd pbdata;\
	make debug 
	cd hdf;\
	make debug 
	cd alignment;\
	make debug 

profile:
	cd pbdata;\
	make profile 
	cd hdf;\
	make profile 
	cd alignment;\
	make profile 

gtest:
	cd unittest;\
	make gtest

clean: 
	cd pbdata;\
	make clean
	cd hdf;\
	make clean
	cd alignment;\
	make clean
	cd unittest;\
	make clean


