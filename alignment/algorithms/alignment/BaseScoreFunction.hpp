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

        BaseScoreFunction();

        BaseScoreFunction(int insP, int delP, int subPriorP, 
            int delPriorP, int affineExtensionP, int affineOpenP); 
};

#endif // _BLASR_BASE_SCORE_FUNCTION_HPP_`
