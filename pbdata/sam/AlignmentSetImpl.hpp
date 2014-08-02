#include "AlignmentSet.hpp"

template<typename T_ReferenceSequence, typename T_ReadGroup, typename T_Alignment>
void AlignmentSet<T_ReferenceSequence, T_ReadGroup, T_Alignment>::RearrangeReferences(std::vector<FASTASequence> &fastaReferences) {
    int i = 0;
    std::map<std::string, int> fastaRefToIndex;
    std::map<std::string, int>::iterator it;
    for (i = 0; i<fastaReferences.size(); i++) {
        it = fastaRefToIndex.find(fastaReferences[i].GetName());
        if (it != fastaRefToIndex.end()) {
            std::cout<<"Error, reference with name \""<<fastaReferences[i].GetName()
                <<"\" in the reference genome is not unique"<<std::endl;
            exit(1);
        }
        fastaRefToIndex[fastaReferences[i].GetName()] = i;
    }
    std::vector<T_ReferenceSequence> newreferences;
    for (i = 0; i < references.size(); i++) {
        newreferences.push_back(T_ReferenceSequence());
    }
    for (i = 0; i < references.size(); i++) {
        it = fastaRefToIndex.find(references[i].sequenceName);
        if (it == fastaRefToIndex.end()) {
            std::cout<<"Error, can not find reference name "<<references[i].sequenceName
                <<" in the reference genome."<<std::endl;
            exit(1);
        }
        newreferences[(*it).second] = references[i];
    }
    references = newreferences;
}
