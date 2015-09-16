#include "ContextSet.hpp"

ContextSampleMap::ContextSampleMap() {
    contextLength = 0;
}

void ContextSampleMap::Write(std::ofstream &out) {
    T_ContextSampleMap::iterator mapIt, mapEnd;
    int mapSize = this->size();
    out.write((char*)&contextLength, sizeof(contextLength));
    out.write((char*)&mapSize, sizeof(mapSize));
    mapEnd = this->end();
    for(mapIt = this->begin(); mapIt != mapEnd; ++mapIt) {
        out.write(mapIt->first.c_str(), contextLength);
        mapIt->second->Write(out);
    }
}

void ContextSampleMap::Read(std::ifstream &in) {
    in.read((char*)&contextLength, sizeof(contextLength));
    int numContext;
    in.read((char*)&numContext, sizeof(numContext));
    int i;
    char *context = ProtectedNew<char>(contextLength+1);
    context[contextLength] = '\0';
    for (i = 0; i < numContext; i++) {
        in.read(context, contextLength);
        std::string contextString = context;
        // Allocate the context
        (*this)[contextString] = ProtectedNew<ContextSample>();
        (*this)[contextString]->Read(in);
    }
    delete[] context;
}

