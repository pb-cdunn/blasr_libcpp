#include "FASTASequence.hpp"

using namespace std;

FASTASequence::FASTASequence() : DNASequence() {
    title =NULL;
    titleLength = 0;
}

void FASTASequence::PrintSeq(ostream &out, int lineLength, char delim) {
    out << delim << title <<endl;
    ((DNASequence*)this)->PrintSeq(out, lineLength);
}
int FASTASequence::GetStorageSize() {
    if (!title) 
        return DNASequence::GetStorageSize();
    return strlen(title) + DNASequence::GetStorageSize();
}

string FASTASequence::GetName() {
    string name;
    int i;
    for (i = 0; i < titleLength; i++) {
        if (title[i] != ' ' and
                title[i] != '\t' and
                title[i] != '\n' and
                title[i] != '\r') {
            name.push_back(title[i]);
        }
        else {
            break;
        }
    }
    return name;
}

//
// Define  some no-ops to satisfy instantiating templates that
// expect these to exist.
//
bool FASTASequence::StoreHoleNumber(int holeNumber) {return false;}
bool FASTASequence::StoreHoleStatus(unsigned char holeStatus) {return false;}
bool FASTASequence::StorePlatformId(PlatformId platformId) { return false;}
bool FASTASequence::StoreZMWData(ZMWGroupEntry &data) { return false;}
bool GetHoleNumber (int &holeNumberP) {
    //
    // There is no notion of a hole number for a fasta sequence.
    //
    return false;
}

bool FASTASequence::StoreXY(int16_t xy[]) {return false;}

bool FASTASequence::GetXY(int xyP[]) {
    //
    // Although the xyP is stored in the fasta title for astro reads
    // this class is more general than an astro read, so do not assume 
    // that it may be found in the title.
    //
    // So, this function is effectively a noop.
    //
    xyP[0] = xyP[1] = 0;
    return false;
}


void FASTASequence::ShallowCopy(const FASTASequence &rhs) {
    // Be careful when using ShallowCopy(), because 
    // title may double free. 
    title = rhs.title;
    titleLength = rhs.titleLength;
    ((DNASequence*)this)->ShallowCopy(rhs);
}

string FASTASequence::GetTitle() const {
    return string(title);
}

void FASTASequence::CopyTitle(const char* str, int strlen) {
    if (title != NULL) {
        delete[] title;
    }
    title = new char[strlen+1];
    memcpy(title, str, strlen);
    titleLength = strlen;
    title[titleLength] = '\0';
}

void FASTASequence::CopyTitle(string str) {
    CopyTitle(str.c_str(), str.size());
}

void FASTASequence::GetFASTATitle(string& fastaTitle) {
    // look for the first space, and return the string until there.
    int i;
    for (i = 0; i < titleLength; i++ ){
        if (title[i] == ' ' or
                title[i] == '\t') {
            break;
        }
    }
    fastaTitle.assign(title, i);
}


void FASTASequence::CopySubsequence(FASTASequence &rhs, int readStart, int readEnd) {
    if (readEnd == -1) {
        readEnd = rhs.length;
    }
    else if (readEnd > readStart) {
        seq = new Nucleotide[readEnd-readStart];
        memcpy(seq, &rhs.seq[readStart], readEnd - readStart);
    }
    else {
        seq = NULL;
    }
    length = readEnd - readStart;
    CopyTitle(rhs.title);
}

void FASTASequence::AppendToTitle(string str) {
    int newLength = titleLength + str.size() + 1;
    if ( newLength == 0) {
        title = NULL;
        return;
    }

    char *tmpTitle = new char[newLength];
    memcpy(tmpTitle, title, titleLength);
    memcpy(&tmpTitle[titleLength], str.c_str(), str.size());
    tmpTitle[newLength-1] = '\0';
    delete[] title;
    title = tmpTitle;
    titleLength = newLength;
}
void FASTASequence::Assign(FASTASequence &rhs) {
    *this = rhs;
}

void FASTASequence::MakeRC(FASTASequence &rhs, DNALength rhsPos, DNALength rhsLength) {
    DNASequence::MakeRC((DNASequence&) rhs, rhsPos, rhsLength);
    if (title != NULL) {
        rhs.CopyTitle(title);
    }
}

void FASTASequence::ReverseComplementSelf() {
    DNALength i;
    for (i = 0; i < length/2 + length % 2; i++) {
        char c = seq[i];
        seq[i] = ReverseComplementNuc[seq[length - i - 1]];
        seq[length - i - 1] = ReverseComplementNuc[c];
    }
}

void FASTASequence::operator=(const FASTASequence &rhs) {
    CopyTitle(rhs.title, rhs.titleLength);
    ((DNASequence*)this)->Copy((DNASequence&)rhs);
}

void FASTASequence::Copy(const FASTASequence &rhs) {
    *this = rhs;
}

void FASTASequence::Free() {
    DNASequence::Free();
    if (title != NULL) {
        delete[] title;
        title = NULL;
        titleLength = 0;
    }
}

template DNALength ResizeSequence<FASTASequence>(FASTASequence &, DNALength);
