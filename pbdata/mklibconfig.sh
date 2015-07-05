#!/bin/bash
fn=$1
use_pbbam=$2
# If $fn exists, then guarantee its contents are correct.
# If not, write the proper contents.
# This way, 'make' will not have to re-create a perfectly fine file,
# which would cause all other targets to be remade.

use0=$(cat <<'EOF'
EOF
)

use1=$(cat <<'EOF'
#define USE_PBBAM
EOF
)

if [ "${use_pbbam}" == "YES" ]; then
    wanted=$use1
else
    wanted=$use0
fi

if [ -r $fn ]; then
    actual=$(<"${fn}")
else
    actual="EMPTY"
fi

if [ "$wanted" != "$actual" ]; then
    echo "$wanted" > $fn
fi
