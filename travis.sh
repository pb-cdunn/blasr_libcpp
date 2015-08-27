#!/bin/bash
ls /usr/include/hdf*
ls /usr/lib/libhdf*
set -ex
NOPBBAM=1 ./configure.py
make -j4 all
# make -j4 gtest
