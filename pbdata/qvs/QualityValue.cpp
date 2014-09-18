#include <math.h>
#include "defs.h"
#include <assert.h>
#include "QualityValue.hpp"

QualityValue 
ProbabilityToQualityValue(QualityProbability pErr, QVScale qvScale) {
    if (qvScale == POverOneMinusP) {
        QualityProbability pe;
        QualityProbability maxReportedErrorProb = 0.499;
        pe = MIN(pErr, maxReportedErrorProb);
        return MIN(255, -100*log10(pe/(1-pe)));
    }
    else if (qvScale == PHRED) {
        return -10*log10(pErr);
    } else {
        assert(false);
    }
}

QualityValue 
PacBioQVToPhred(QualityValue pbQV) {
    // yanked from Aaron's code.
    return (unsigned char) floor( 10.0 * log10( 1.0 + pow(10.0, pbQV / 100.0) ) + 0.5 );
}

QualityValue 
ToPhred(QualityValue qv, QVScale qvScale) {
    // 
    // Nothing to do when the quality is already in phred.
    //
    if (qvScale == PHRED) {
        return qv;
    }
    else {
        return PacBioQVToPhred(qv);
    }
}


QualityProbability 
QualityValueToProbability(QualityValue qv, QVScale qvScale) {
    if (qvScale == POverOneMinusP) {
        QualityProbability pp;
        pp = pow(10, qv/-100.0);
        return pp/(1+pp);
    }
    else if (qvScale == PHRED) {
        return pow(10, qv/-10.0);
    } else {
        assert(false);
    }
}

QVScale DetermineQVScaleFromChangeListID(ChangeListID &cl) {
    ChangeListID phredCL;
    phredCL.intVer.resize(3);
    phredCL.intVer[0] = 1; phredCL.intVer[1] = 2; phredCL.intVer[2] = 2;
    if (cl.LessThan(phredCL)) {
        return POverOneMinusP;
    }
    else {
        return PHRED;
    }
}
