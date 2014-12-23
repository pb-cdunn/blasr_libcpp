#ifndef _BLASR_BASE_SCORE_FUNCTION_HPP_
#define _BLASR_BASE_SCORE_FUNCTION_HPP_

class BaseScoreFunction {
    public:
        int ins;
        int del;
        int substitutionPrior;
        int globalDeletionPrior;
        int affineExtend;
        int affineOpen;

        BaseScoreFunction(int insP = 0, int delP = 0, int subPriorP = 0, 
            int delPriorP = 0, int affineExtensionP = 0, int affineOpenP = 0); 
};

#endif // _BLASR_BASE_SCORE_FUNCTION_HPP_`
