#!/bin/bash
set -ex
NOPBBAM=1 ./configure.py
make -j4 all
# make -j4 gtest
