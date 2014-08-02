#ifndef _BLASR_DATASET_COLLECTION_IMPL_HPP_
#define _BLASR_DATASET_COLLECTION_IMPL_HPP_

template <typename T_Dataset>
bool DatasetCollection::InitializeDataset(HDFGroup &group, 
    T_Dataset &dataset, std::string datasetName) {

    //
    // Perform initialization of the dataset in a way that keep track
    // of which datasets in the collection are present.
    //
    if (includedFields[datasetName]) {
        if (dataset.Initialize(group, datasetName) == false) {
            if (requiredFields[datasetName]) {
                return false;
            }
            else {
                //
                // This field was supposed to be included but it either does
                // not exist or there was a problem otherwise in creating
                // it.  Don't try and read from it later on.
                //
                includedFields[datasetName] = false;
            }
        }
    }
    return true;
}
#endif
