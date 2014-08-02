#include "StatUtils.hpp" 

void InitializeRandomGenerator(int value) {
  srandom((unsigned) value);
}


unsigned int RandomUnsignedInt(unsigned int randMax) {
 // 
 //  step 1, pack an unsigned integer with a random value, this 
 //
 unsigned int randVal = RAND_MAX * (1.0*random())/RAND_MAX;

 // step 2, 
 unsigned int lastBit = random() % 2;
 lastBit = lastBit << ( __WORDSIZE/2-1);
 // This should never overflow, add a 31-bit number into a 32.
 randVal+= lastBit; 
 double fpRandVal = 1.0*randVal;
 return (randMax * fpRandVal / UINT_MAX);
}
	
unsigned int RandomInt(int randMax) {
  int randVal = (randMax * ((1.0*random()) / RAND_MAX));
  return std::min(randMax-1, randVal);
}

unsigned int RandomInt(unsigned int min, unsigned int max) {
	return RandomInt(max - min) + min;
}

float Random() {
	return (RandomInt(0,RAND_MAX)*1.0)/RAND_MAX;
}

bool FindQNorm(float prob, float & nStdDev) {
    if (prob < 0.5 or prob > 1.0) {
        return false;
    }
    else {
        nStdDev = qnorm[(int)((prob - 0.50) * 500)];
        return true;
    }
}

