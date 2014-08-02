#ifndef _BLASR_FASTQ_SEQUENCE_HPP_
#define _BLASR_FASTQ_SEQUENCE_HPP_

#include "DNASequence.hpp"
#include "FASTASequence.hpp"
#include "qvs/QualityValue.hpp"
#include "qvs/QualityValueVector.hpp"
#include "matrix/Matrix.hpp"
#include "reads/ZMWGroupEntry.hpp"


class FASTQSequence : public FASTASequence {
public:
    static int charToQuality;
    QualityValueVector<QualityValue> qual;
    QualityValueVector<QualityValue> deletionQV;
    QualityValueVector<QualityValue> preBaseDeletionQV;
    QualityValueVector<QualityValue> insertionQV;
    QualityValueVector<QualityValue> substitutionQV;
    QualityValueVector<QualityValue> mergeQV;
    Nucleotide *deletionTag;
    Nucleotide *substitutionTag;
    int subreadStart, subreadEnd;
    QualityValue deletionQVPrior, insertionQVPrior, substitutionQVPrior, preBaseDeletionQVPrior;

    QVScale qvScale;

    QVScale GetQVScale(); 

    void SetQVScale(QVScale qvScaleP); 

    QualityValueVector<QualityValue>* GetQVPointerByIndex(int index);

    int GetStorageSize(); 

    FASTQSequence();

    QualityValue GetDeletionQV(DNALength pos); 

    QualityValue GetMergeQV(DNALength pos); 

    Nucleotide GetSubstitutionTag(DNALength pos); 

    Nucleotide GetDeletionTag(DNALength pos); 

    QualityValue GetInsertionQV(DNALength pos); 

    QualityValue GetSubstitutionQV(DNALength pos); 

    QualityValue GetPreBaseDeletionQV(DNALength pos, Nucleotide nuc); 

    void ShallowCopy(const FASTQSequence &rhs); 

    void ReferenceSubstring(const FASTQSequence &rhs); 

    void ReferenceSubstring(const FASTQSequence &rhs, DNALength pos);

    void ReferenceSubstring(const FASTQSequence &rhs, DNALength pos, DNALength substrLength); 

    void ClearAndNull(QualityValue *value); 

    void CopyQualityValues(const FASTQSequence &rhs);

    void AllocateQualitySpace(DNALength qualLength); 

    void AllocateDeletionQVSpace(DNALength qualLength); 

    void AllocateMergeQVSpace(DNALength len);

    void AllocateDeletionTagSpace(DNALength qualLength); 

    void AllocatePreBaseDeletionQVSpace(DNALength qualLength); 

    void AllocateInsertionQVSpace(DNALength qualLength); 

    void AllocateSubstitutionQVSpace(DNALength qualLength );

    void AllocateSubstitutionTagSpace(DNALength qualLength );

    void AllocateRichQualityValues(DNALength qualLength); 

    void Copy(const FASTQSequence &rhs); 

    FASTQSequence& operator=(const FASTQSequence &rhs); 

    FASTQSequence(const FASTQSequence &rhs); 

    void Assign(FASTQSequence &rhs); 

    void PrintFastq(std::ostream &out, int lineLength=50); 

    void PrintFastqQuality(std::ostream &out, int lineLength=50); 

    void PrintAsciiRichQuality(std::ostream &out, int whichQuality, int lineLength=50);

    void PrintAsciiQual(std::ostream &out, int lineLength=50) ;

    void PrintQual(std::ostream &out, int lineLength = 50); 

    void PrintQualSeq(std::ostream &out, int lineLength = 50);

    void MakeRC(FASTQSequence &rc); 

    void Free(); 

    void LowerCaseMask(int qThreshold); 

    float GetAverageQuality(); 
};


#endif // _BLASR_FASTQ_SEQUENCE_HPP_
