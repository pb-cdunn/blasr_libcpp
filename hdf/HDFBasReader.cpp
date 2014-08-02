#include "HDFBasReader.hpp"

//
// Below is sample code for using the bas reader to read in sequences
// from a .bas.h5 or .pls.h5 file.  
// One may select which quality value fields to read.  By default,
// none are read in.  To read in the rich quality values (insertionQV,
// deletionQV, substitutionQV, mergeQV, substitutionTag, deletionTag),
// call InitializeDefaultIncludedFields() BEFORE initializing the
// reader on the file name.
//
//#include "data/hdf/HDFBasReader.h"
//#include "SMRTSequence.h"
//#include <string>
//
//int main(int argc, char* argv[]) {
//	
//	string basFile = argv[1];
//
//	HDFBasReader reader;
//  reader.InitializeDefaultIncludedFields();
//	reader.Initialize(basFile);
//
//	SMRTSequence read;
//
//	while(reader.GetNext(read)) {
//		read.PrintQualSeq(cout);
//	}
//
//
//	return 0;
//}
//
// * If you wanted to read only fasta sequences and not fastq, use:
// 
// FASTASequence read;
// while (reader.GetNext(read) {
//   read.PritnSeq(cout);
// }
//

int HDFSmrtReader::Advance(int nSteps) {
	int retVal;
	retVal = ((T_HDFBasReader<FASTQSequence>*)this)->Advance(nSteps);
	return retVal;
}
