#include <stdint.h>
#include "TupleMask.h"
#include "TupleMetrics.hpp"

TupleMetrics::TupleMetrics() {
    tupleSize = tupleMask = 0;
}

void TupleMetrics::InitializeMask() {
    tupleMask = TupleMask[tupleSize];
}

void TupleMetrics::Initialize(int pTupleSize) {
    tupleSize = pTupleSize;
    InitializeMask();
}
