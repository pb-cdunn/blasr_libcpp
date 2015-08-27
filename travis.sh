#!/bin/bash
ls /usr/include/hdf*
ls /usr/lib/libhdf*
set -ex
NOHDF=1 NOPBBAM=1 ./configure.py
make -j4 libpbdata
make -j4 libblasr

# Test compilation of ./hdf using our own HDF5 headers, for now.
# (This fails on Darwin b/c our HDF5_HEADERS were configured for Linux.)
NOPBBAM=1 ./configure.py
make -j4 -C ./hdf libpbihdf.a

# make -j4 gtest
