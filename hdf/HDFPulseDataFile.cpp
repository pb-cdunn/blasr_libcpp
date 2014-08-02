#include "HDFPulseDataFile.hpp"

using namespace std;

int HDFPulseDataFile::GetAllReadLengths(vector<DNALength> &readLengths) {
    nReads = zmwReader.numEventArray.arrayLength;
    readLengths.resize(nReads);
    zmwReader.numEventArray.Read(0,nReads, (int*) &readLengths[0]);
    return readLengths.size();
}

void HDFPulseDataFile::CheckMemoryAllocation(long allocSize, long allocLimit, const char *fieldName) {
    if (allocSize > allocLimit) {
        if (fieldName == NULL) {
            cout << "Allocating too large of memory" << endl;
        }
        else {
            cout << "Allocate size " << allocSize << " > allocate limit " << allocLimit << endl;
            cout << "ERROR! Reading the dataset " << fieldName << " will use too much memory." << endl;
            cout << "The pls/bas file is too large, exiting." << endl;
        }
        exit(1);
    }
}

HDFPulseDataFile::HDFPulseDataFile() {
    pulseDataGroupName = "PulseData";
    nReads             = 0;
    useScanData        = false;
    closeFileOnExit    = false;
    maxAllocNElements  = INT_MAX;
    preparedForRandomAccess = false;
    rootGroupPtr       = NULL;
}

void HDFPulseDataFile::PrepareForRandomAccess() {
    GetAllReadLengths(eventOffset);
    int i;
    int curOffset = 0;
    for (i = 0; i < eventOffset.size(); i++) {
        int curLength = eventOffset[i];
        eventOffset[i] = curOffset;
        curOffset = curOffset + curLength;
    }
    nReads = eventOffset.size();
    preparedForRandomAccess = true;
}


int HDFPulseDataFile::OpenHDFFile(string fileName, 
    const H5::FileAccPropList & fileAccPropList) {

    try {
        H5::FileAccPropList propList = fileAccPropList;
        H5::Exception::dontPrint();
        hdfBasFile.openFile(fileName.c_str(), H5F_ACC_RDONLY, propList);	
    }
    catch (H5::Exception &e) {
        cout << "ERROR, could not open hdf file" << fileName << ", exiting." << endl;
        exit(1);
    }
    closeFileOnExit = true;
    return 1;
}

//
// All pulse data files contain the "PulseData" group name.
// 
//
int HDFPulseDataFile::InitializePulseDataFile(string fileName, 
    const H5::FileAccPropList & fileAccPropList) {

    if (OpenHDFFile(fileName, fileAccPropList) == 0) return 0;
    return 1;
}

int HDFPulseDataFile::Initialize(string fileName, 
    const H5::FileAccPropList & fileAccPropList) {

    if (InitializePulseDataFile(fileName, fileAccPropList) == 0) {
        return 0;
    }
    //
    // The pulse group is contained directly below the root group.
    //
    if (rootGroup.Initialize(hdfBasFile, "/") == 0) {
        return 0;
    }
    rootGroupPtr = &rootGroup;
    return Initialize();
}

//
// Initialize inside another open group.
//
int HDFPulseDataFile::Initialize(HDFGroup *rootGroupP) {
    rootGroupPtr = rootGroupP;
    return Initialize();
}

//
// Initialize all fields 
//
int HDFPulseDataFile::Initialize() {
    preparedForRandomAccess = false;		
    if (InitializePulseGroup() == 0) return 0;
    if (rootGroupPtr->ContainsObject("ScanData")) {
        if (scanDataReader.Initialize(rootGroupPtr) == 0) {
            return 0;
        }
        else {
            useScanData = true;
        }
    }
    return 1;
}

int HDFPulseDataFile::InitializePulseGroup() {
    if (pulseDataGroup.Initialize(rootGroupPtr->group, pulseDataGroupName) == 0) return 0;
    return 1;
}

int HDFPulseDataFile::GetAllHoleNumbers(vector<unsigned int> &holeNumbers) {
    CheckMemoryAllocation(zmwReader.holeNumberArray.arrayLength, maxAllocNElements, "HoleNumbers (base)");
    holeNumbers.resize(nReads);
    zmwReader.holeNumberArray.Read(0,nReads, (unsigned int*)&holeNumbers[0]);
    return holeNumbers.size();
}	

void HDFPulseDataFile::Close() {
    if (useScanData) {
        scanDataReader.Close();
    }

    pulseDataGroup.Close();
    if (rootGroupPtr == &rootGroup) {
        rootGroup.Close();
    }
    /*
       cout << "there are " <<  hdfBasFile.getObjCount(H5F_OBJ_FILE) << " open files upon closing." <<endl;
       cout << "there are " <<  hdfBasFile.getObjCount(H5F_OBJ_DATASET) << " open datasets upon closing." <<endl;
       cout << "there are " <<  hdfBasFile.getObjCount(H5F_OBJ_GROUP) << " open groups upon closing." <<endl;
       cout << "there are " <<  hdfBasFile.getObjCount(H5F_OBJ_DATATYPE) << " open datatypes upon closing." <<endl;
       cout << "there are " <<  hdfBasFile.getObjCount(H5F_OBJ_ATTR) << " open attributes upon closing." <<endl;
       */
    if (closeFileOnExit) {
        hdfBasFile.close();
    }


}
