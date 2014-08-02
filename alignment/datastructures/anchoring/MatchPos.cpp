#include "MatchPos.hpp"


MatchPos::MatchPos(const MatchPos &rhs) {
    (*this) = rhs;
}

int MatchPos::GetMultiplicity() const {
    return m;
}

MatchWeight MatchPos::GetWeight() const {
    if (m > 0) {
        return (1.0*l)/m;
    } else {
        return 0;
    }
}

UInt MatchPos::GetT() {
    return t;
}

UInt MatchPos::GetQ() {
    return (UInt) q;
}

UInt MatchPos::GetW() {
    return w;
}

std::ostream& operator<<(std::ostream & out, MatchPos &p) {
    out << p.q << "\t" << p.t <<"\t"<< p.l << "\t"<< p.m;
    return out;
}


ChainedMatchPos::ChainedMatchPos(DNALength pt, DNALength pq, DNALength pl, int pm) : MatchPos(pt, pq, pl, pm) {
    score = 0; 
    chainPrev = NULL;
}

ChainedMatchPos::ChainedMatchPos() : MatchPos() {
    score = 0;
    chainPrev = NULL;
}

int ChainedMatchPos::SetScore(int _score) {
    return (score = _score);
}

ChainedMatchPos* ChainedMatchPos::SetChainPrev(ChainedMatchPos *_chainPrev) {
    return (chainPrev = _chainPrev);
}

std::ostream& operator<<(std::ostream & out, ChainedMatchPos &p) {
    out << p.q << "\t" << p.t <<"\t"<< p.l << "\t"<< p.m;
    return out;
}
