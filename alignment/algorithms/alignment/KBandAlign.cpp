#include "algorithms/alignment/KBandAlign.hpp"

DefaultGuide::DefaultGuide() {}

int DefaultGuide::operator()(int i) {
    return i;
}

void SetKBoundedLengths(DNALength tLength, DNALength qLength, DNALength k, DNALength &tLen, DNALength &qLen) {
	//
	// Determine how much of each read to align.   If the query is
	// shorter than target - k, then it is impossible to align all the
	// way to the end of the target.  Similar if the query is longer
	// than the target.
	//
	if (tLength < qLength) {
		tLen = tLength;
		qLen = MIN(qLength, tLength + k);
	}
	else if (qLength < tLength) {
		qLen = qLength;
		tLen = MIN(tLength, qLength + k);
	}
	else {
		// They are the same length, the diagonal will definitely fit the two.
		qLen = qLength;
		tLen = tLength;
	}
}

