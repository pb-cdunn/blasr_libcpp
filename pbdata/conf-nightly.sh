#!/bin/bash
set -v

fn=$1
cat <<EOF >| tmp.${fn}
INCLUDES+=-I${PBBAM_INCLUDE} -I${HTSLIB_INCLUDE} -I${BOOST_INCLUDE}
LDLIBS+=${PBBAM_LIB} ${HTSLIB_LIB}
EOF

diff -q tmp.${fn} ${fn}
diffs=$?
if [ ${diffs} -eq 0 ]; then
    rm tmp.${fn}
else
    mv tmp.${fn} ${fn}
fi

