#ifndef _BLASR_CLUSTER_PROBABILITY_HPP_
#define _BLASR_CLUSTER_PROBABILITY_HPP_

float ComputeAnchorProbability(float pMatch, int minAnchorLength);

float ComputeExpectedAnchorLength(float pMatch, int minAnchorLength, 
    float pAnchor);

float AnchorBasesPerRead(int readLength, float pAnchor);

float AnchorBasesPerReadSigma(float expAnchorBasesPerRead);

#endif
