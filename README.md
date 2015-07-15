[![Build Status](https://travis-ci.org/PacificBiosciences/blasr_libcpp.svg?branch=master)](https://travis-ci.org/PacificBiosciences/blasr_libcpp)
#What is blasr_libcpp#

**Blasr_libcpp** is a *library* used by **blasr** and other executables such as samtoh5, loadPulses for analyzing PacBio sequences. This library contains three sub-directories, including pbdata, hdf and alignment.
+ pbdata  
   - contains source code for handling Pacbio sequences and can build lib ```libpbdata```.
+ hdf 
   - contains source code for handling Pacbio hdf5 files (e.g., *.pls.h5, *.rgn.h5, *.bas.h5) and builds ```libpbhdf```.
+ alignment 
   - contains source code for aligning Pacbio reads to target sequences used in blasr and builds ```libblasr```.

## Building
```
./configure.py
make -j all
```
By default, that will skip pbbam, and it will download HDF5 headers.

## configure.py
This is a WIP. It generates `defines.mk` based on the environment and command-line flags.
In theory, it will allow simpler configuration. We might soon have different executables for
different environments.

It also generates `pbdata/libconfig.h`.

By configuring up-front, we avoid race conditions, and we simplify the makefiles. For extra
simplicity, we use the same `defines.mk` for all 3 sub-dirs.

## unittest
There is at least one failing for now, and we cannot run them in Travis without installing HDF5. TODO.

(unittests mostly pass in Jenkins.)

##Appendix: Dependencies##
- libpbdata
   -  does **not** depend on ```libhdf5```
   -  should build without the ```pbbam``` library *for now*

- libpbihdf
   -  depends on the ```libpbdata``` and ```libhdf5``` libraries to build
   
- alignment
   -  depends on the ```libpbdata``` library to build
   -  can build either with or without the ```libpbihdf``` library
   -  can build either with or without the ```pbbam``` library
- hts
   - if you use pbbam, you will need [HTSLib](https://github.com/samtools/htslib)
