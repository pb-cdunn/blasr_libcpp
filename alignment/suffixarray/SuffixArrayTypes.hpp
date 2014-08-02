#ifndef _BLASR_SUFFIX_ARRAY_TYPES_HPP_
#define _BLASR_SUFFIX_ARRAY_TYPES_HPP_

#include <vector>
#include "SuffixArray.hpp"
#include "SharedSuffixArray.hpp"

#include "CompressedSequence.hpp"
#include "Compare4BitCompressed.hpp"
#include "FASTASequence.hpp"

typedef SuffixArray<Nucleotide, std::vector<int> > DNASuffixArray;
typedef SuffixArray<Nucleotide, std::vector<int>, 
	                  Compare4BitCompressed<Nucleotide>,
	                  CompressedDNATuple<FASTASequence> >       CompressedDNASuffixArray;

#endif // _BLASR_SUFFIX_ARRAY_TYPES_HPP_
