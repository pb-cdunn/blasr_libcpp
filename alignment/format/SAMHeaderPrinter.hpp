#ifndef _BLASR_FILE_SAM_HEADER_PRINTER_
#define _BLASR_FILE_SAM_HEADER_PRINTER_

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include "Types.h"
#include "Enumerations.h"
#include "StringUtils.hpp"
#include "files/BaseSequenceIO.hpp"
#include "files/ReaderAgglomerate.hpp"
#include "datastructures/alignmentset/SAMSupplementalQVList.hpp"

/// This is a simple implementation for generating SAM Headers. 
/// It is provided such that libblasr can compile with and without
/// linking to lib PBBAM.
/// * When compiled without linking to lib PBBAM, blasr should be 
///   able to produce SAM output.
/// * When compiled with lib PBBAM, blasr should be able to produce
///   SAM and BAM output. If input is one or more than one BAM files,
///   @PG and @CO info will be kept.

#define REQUEST_PBBAM_ERROR() \
    assert("libblasr must be compiled with lib PBBAM to consume bam files." == 0)

class SAMHeaderItem {
/// SAM Header Item: key=value
public:
    SAMHeaderItem(const std::string & key, const std::string & val)
    :_key(key), _val(val) {}

    SAMHeaderItem(const std::string & fromString);

    std::string ToString();

private:
    std::string _key;
    std::string _val;
};

std::vector<SAMHeaderItem> MakeSAMHeaderItems(const std::string & fromString);

class SAMHeaderTag {
public:
    SAMHeaderTag() {} 

    /// ID:12345
    SAMHeaderTag(const std::string & tagName, const std::string & tagValue)
    :_tagName(tagName), _tagValue(tagValue) {}

    /// DS:READTYPE=SUBREAD;BINDKINGKIT=123456
    SAMHeaderTag(const std::string & tagName, const std::vector<SAMHeaderItem> & tagItems)
    :_tagName(tagName), _tagItems(tagItems) {}

    SAMHeaderTag(const std::string & fromString);

public:
    std::string ToString();

    std::string TagName() const;

    void AddItem(SAMHeaderItem & item); 

    void AddItem(const std::string & fromString);

    void AddItems(const std::string & fromString);

private:
    std::string _tagName;
    std::string _tagValue;
    std::vector<SAMHeaderItem> _tagItems;
};

typedef std::vector<SAMHeaderTag> SAMHeaderTags;

class SAMHeaderGroup {
public:
    SAMHeaderGroup() {}

    SAMHeaderGroup(const std::string & groupName, const SAMHeaderTags & tags)
    :_groupName(groupName), _tags(tags) {}

    SAMHeaderGroup(const std::string & fromString); 

    std::string ToString();

    /// returns true if this SAMHeaderGroup contains a tag tagName.
    bool HasTag(std::string tagName);

    /// returns value of a tag if it exists, otherwise, return an empty string. 
    std::string Tag(const std::string & tagName);

protected:
    std::string _groupName;

    SAMHeaderTags _tags; 
};

class SAMHeaderGroupWithID : public SAMHeaderGroup {
public:
    SAMHeaderGroupWithID() {}

    SAMHeaderGroupWithID(const std::string & fromString); 

    std::string ID() const;

protected:
    std::string _id;
};

std::ostream & operator << (std::ostream& os, SAMHeaderGroup & g);

class SAMHeaderRG : public SAMHeaderGroupWithID {
    /// SAM Header @RG entry, containing ID, PL, PU, DS tags.
    /// ID: Read group Id Tag, which must be unique for read groups.
    /// PL: PacBio platform Tag, e.g., PacBio.
    /// PU: PacBio platform unit Tag, e.g., m1473.....p0
    /// DS: Description Items for this @RG entry, including READTYPE, BINDKINGKIT, 
    ///     SEQUENCEKIT, BASECALLERVERSION. 
    /// The following is an example: 
    /// @RG ID:abcdefgh PL:PacBio   PU:m1473...p0   DS:READTYPE=SUBREAD;BINDINGKIT=123456;SEQUENCINGKIT=123456;BASECALLERVERSION=2.3
public:
    SAMHeaderRG(const std::string & id, const std::string & pl, const std::string & pu, const std::vector<SAMHeaderItem> & dsItems);

    SAMHeaderRG(const std::string & fromString);
};

class SAMHeaderPG: public SAMHeaderGroupWithID {
public:
    SAMHeaderPG(const std::string & id, const std::string & progName, const std::string & progVersion, const std::string & commandLine);

    SAMHeaderPG(const std::string & fromString);
};

class SAMHeaderSQ:  public SAMHeaderGroup {
public:
    SAMHeaderSQ(const std::string & sn, const DNALength & ln, const std::string & md5);

    SAMHeaderSQ(const std::string & sn, const string & ln, const std::string & md5);

    SAMHeaderSQ(const std::string & fromString);
};

template <class T>
class SAMHeaderGroups {
public:
    SAMHeaderGroups() {}

    // Add a SAM Header group regardless
    void Add(const T & group);
   
    void Append(const std::vector<T> & groups);

    std::string ToString();
   
protected:
    std::vector<T> _groups;
};

template <class T>
class SAMHeaderGroupsWithID : public SAMHeaderGroups<T> {
public:
    SAMHeaderGroupsWithID(): SAMHeaderGroups<T>() {}

    /// Add a SAM Header group with unique ID if it does not exist.
    void Add(const T & g) ;

    /// Check whether a group already exists or not.
    /// \returns true if g.ID() already exists in _groups, otherwise false.
    bool Contain(const T & g);
};

typedef SAMHeaderGroupsWithID<SAMHeaderRG> SAMHeaderRGs;
// FIXME: @PG groups should have unique IDs according to SAM spec v1.5,
// However, PacBio tools such as blasr and bax2bam use prog name as prog id.
typedef SAMHeaderGroups<SAMHeaderPG> SAMHeaderPGs;
typedef SAMHeaderGroups<SAMHeaderSQ> SAMHeaderSQs;
typedef SAMHeaderGroups<std::string> SAMHeaderCOs;

class SAMHeaderPrinter {
public:
    /// SAMHeaderPrinter constructor  
    /// \param[in] sortingOrder - sorting order of alignments. 
    /// \param[in] seqdb - database of target sequences.
    /// \param[in] readsFiles - input reads files, file format
    /// can be FASTA, FASTQ, BAS.H5, BAX.H5, BAM.
    /// \param[in] samQVs - samQVs that will be printed.
    /// \param[in] readType - read type, must be either SUBREAD or CCS or UNKNOWN
    /// \param[in] progName - program which calls SMAHeaderPrinter
    /// \param[in] progVersion - program version. 
    /// \param[in] commandLine - command line to call program. 
    SAMHeaderPrinter(const std::string & sortingOrder,
                     SequenceIndexDatabase<FASTASequence> & seqdb,
                     const std::vector<std::string> & readsFiles,
                     const ReadType::ReadTypeEnum & readType,
                     const SupplementalQVList & samQVs,
                     const std::string & progName, 
                     const std::string & progVersion,
                     const std::string & commandLine);

    /// \returns SAM header in string.
    std::string ToString();
        
public:
#ifdef USE_PBBAM
    /// Converts this SAMHeader to PacBio::BAM::BamHeader, must be compiled with pbbam
    /// \returns a shared pointer to PacBio::BAM::BamHeader. 
    std::shared_ptr<PacBio::BAM::BamHeader> ToBamHeader();
#endif

    /// Add a SAM Header @RG entry, including the following tags:
    /// ID (identifier), PL (platform), PU (platform unit), 
    /// DS (description, which may have many items)
    SAMHeaderPrinter & AddRG(std::string & id, std::string & pl, std::string & pu, std::string & ds);

    /// Add a SAM Header @RG entry from string, which may contain arbitary tags.
    SAMHeaderPrinter & AddRG(const std::string & fromString);
   
    /// Add a SAM Header @PG entry, including the following tags:
    /// ID, progName, progVersion, commandLine. @PG must have unique ID.
    SAMHeaderPrinter & AddPG(std::string & id, std::string & progName, std::string & progVersion, std::string & commandLine);

    /// Add a SAM Header @PG entry from string, which may contain arbitary tags.
    SAMHeaderPrinter & AddPG(const std::string & fromString);

    /// Add a SAM Header @CO entry from string.
    SAMHeaderPrinter & AddCO(const std::string & fromString);

private:
    const std::string & _sortingOrder;
    const std::vector<std::string> & _readsFiles;
    SequenceIndexDatabase<FASTASequence> & _seqdb;
    FileType fileType;

    SAMHeaderGroup _hd; //@HD VN:? SO:? pb:?
    SAMHeaderSQs _sqs;  //@SQ SN:? LN:? M5:?
    SAMHeaderRGs _rgs;  //@RG ID:? PU:? PL:? DS:key=val;key=val;key=val
    SAMHeaderPGs _pgs;  //@PG VN:? CL:?
    SAMHeaderCOs _cos;  //@CO

private:
    /// \returns SAMHeaderGroup @HD
    static SAMHeaderGroup MakeHD(const std::string & sortingOrder);

    /// \returns SAMHeaderSQs, SAM Header @SQ groups
    SAMHeaderSQs MakeSQs(SequenceIndexDatabase<FASTASequence> & seqdb);

    /// \returns SAMHeaderRGs @RG groups
    /// \param[in] readsFiles - incoming reads files in BAM or other formats
    /// \param[in] readType - read type, must be either SUBREAD or CCS or UNKNOWN
    /// \param[in] samQVs - SupplementalQVList, an object that handles which 
    ///                      QVs to print in SAM/BAM file.
    SAMHeaderRGs MakeRGs(const std::vector<std::string> & readsFiles,
        const ReadType::ReadTypeEnum & readType,
        const SupplementalQVList & samQVs); 

    /// \returns SAMHeaderPGs @PG groups
    /// \param[in] readsFiles - incoming reads files in BAM or other formats
    /// \param[in] progName - program which calls SMAHeaderPrinter
    /// \param[in] progVersion - program version. 
    /// \param[in] commandLine - command line to call program. 
    SAMHeaderPGs MakePGs(const std::vector<std::string> & readsFiles, 
        const std::string & progName, const std::string & progVersion, 
        const std::string & commandLine);

    /// \returns SAMHeaderPGs @CO groups
    /// \param[in] readsFiles - incoming reads files in BAM or other formats
    SAMHeaderCOs MakeCOs(const std::vector<std::string> & readsFiles); 
};

// template<class T> SAMHeaderGroups
template<class T>
void SAMHeaderGroups<T>::Add(const T & group) {
    this->_groups.push_back(group);
}

template<class T>
void SAMHeaderGroups<T>::Append(const std::vector<T> & groups) {
    for(int i = 0; i < groups.size(); i++) {
        this->Add(groups[i]);
    }
}

template<class T>
std::string SAMHeaderGroups<T>::ToString() {
    std::stringstream ss;
    for (int i = 0; i < this->_groups.size(); i++) {
        ss << this->_groups[i] << std::endl;
    }
    return ss.str();
}

// template<class T> SAMHeaderGroupsWithID
template <class T>
void SAMHeaderGroupsWithID<T>::Add(const T & g) {
    if (not this->Contain(g)) {this->_groups.push_back(g);}
}

template <class T>
bool SAMHeaderGroupsWithID<T>::Contain(const T & g) {
    typename std::vector<T>::iterator it;
    for(it = this->_groups.begin(); it < this->_groups.end(); it++) {
        if ((*it).ID() == g.ID()) {
            return true;
        }
    }
    return false;
}
#endif
