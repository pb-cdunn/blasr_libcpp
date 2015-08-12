#!/bin/bash
set -ex
( cd pbdata; NOPBBAM=1 ../configure.py; )
( cd hdf; NOPBBAM=1 ../configure.py; )
( cd alignment; NOPBBAM=1 ../configure.py; )
make -j4 all
# make -j4 gtest
