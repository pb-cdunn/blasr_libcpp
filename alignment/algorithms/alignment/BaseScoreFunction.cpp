#include "BaseScoreFunction.hpp"

BaseScoreFunction::BaseScoreFunction() {
    ins = del = substitutionPrior = globalDeletionPrior = 0;
    affineOpen = affineExtend = 0;
}

BaseScoreFunction::BaseScoreFunction(int insP, int delP, int subPriorP, 
        int delPriorP, int affineExtensionP, int affineOpenP)  {
    ins = insP;
    del = delP;
    substitutionPrior = subPriorP;
    globalDeletionPrior = delPriorP;
    affineExtend = affineExtensionP;
    affineOpen = affineOpenP;
}
