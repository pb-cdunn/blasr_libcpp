#!/bin/bash
set -x
( cd pbdata; NOPBBAM=1 ../configure.py; )
( cd hdf; NOPBBAM=1 ../configure.py; )
( cd alignment; NOPBBAM=1 ../configure.py; )
make -j all
# make -j gtest
