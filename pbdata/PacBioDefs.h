// Copyright (c) 2014-2015, Pacific Biosciences of California, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the
// disclaimer below) provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//  * Neither the name of Pacific Biosciences nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
// GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY PACIFIC
// BIOSCIENCES AND ITS CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL PACIFIC BIOSCIENCES OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
// USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// Author: Yuan Li

#ifndef _PBDATA_PACBIO_DEFS_H_
#define _PBDATA_PACBIO_DEFS_H_
#include <string>
#include <vector>

namespace PacBio {
namespace GroupNames {
    ///PulseData
    static const std::string pulsedata        = "PulseData";

    ///PulseData/BaseCalls
    static const std::string basecalls        = "BaseCalls";
    ///PulseData/Regions
    static const std::string regions          = "Regions";

    ///PulseData/BaseCalls/BaseCall
    static const std::string basecall         = "Basecall";
    static const std::string deletionqv       = "DeletionQV";
    static const std::string deletiontag      = "DeletionTag";
    static const std::string insertionqv      = "InsertionQV";
    static const std::string mergeqv          = "MergeQV";
    static const std::string substitutionqv   = "SubstitutionQV";
    static const std::string substitutiontag  = "SubstitutionTag";
    static const std::string prebaseframes    = "PreBaseFrames";
    static const std::string widthinframes    = "WidthInFrames";

    ///PulseData/BaseCalls/ZMW
    static const std::string zmw              = "ZMW";
    static const std::string zmwmetrics       = "ZMWMetrics";

    ///PulseData/BaseCalls/ZMW/HoleNumber
    static const std::string holenumber       = "HoleNumber";
    static const std::string holestatus       = "HoleStatus";
    static const std::string holexy           = "HoleXY";
    static const std::string numevent         = "NumEvent";

    ///PulseData/BaseCalls/ZMWMetrics/HQRegionSNR
    static const std::string hqregionsnr      = "HQRegionSNR";
    static const std::string readscore        = "ReadScore";
    static const std::string productivity     = "Productivity";

    static const std::vector<std::string> BaxQVNames ({
            deletionqv, 
            deletiontag, 
            insertionqv,
            mergeqv,
            substitutionqv,
            substitutiontag,
            prebaseframes,
            widthinframes,
            hqregionsnr,
            readscore});
} // namespace GroupNames

namespace AttributeNames {
    namespace Common {
        static const std::string changelistid       = "ChangeListID";
        static const std::string description        = "Description";
    } // Common

    namespace ZMW {
        namespace HoleStatus {
            static const std::string lookuptable    = "LookupTable";
        }
    }

    namespace Regions {
        static const std::string columnnames        = "ColumnNames";
        static const std::string regiontypes        = "RegionTypes";
        static const std::string regiondescriptions = "RegionDescriptions";
        static const std::string regionsources      = "RegionSources";
    } // Regions

    namespace ScanData {
        namespace DyeSet {
            static const std::string basemap        = "BaseMap";
        }
    } // ScanData


} // namespace AttributeNames 

namespace AttributeValues {

    namespace ZMW {
        namespace HoleNumber {
            static const std::string description     = "Hole number on chip array";
        } //namespace HoleNumber

        namespace HoleStatus {
            static const std::string description     = "Type of data coming from ZMW";
            static const std::vector<std::string> lookuptable    =
            {"SEQUENCING", "ANTIHOLE", "FIDUCIAL", "SUSPECT", 
             "ANTIMIRROR", "FDZMW",    "FBZMW",    "ANTIBEAMLET", "OUTSIDEFOV"};

            static const unsigned char sequencingzmw = 0; // not '0'
            static const unsigned char outsidefov    = 8; // not '8'
        } // namespace HoleStatus

        namespace HoleXY {
            static const std::string description     = "Coordinates of ZMW on Chip";
        } // namespace HoleXY

    } // namespace ZMW

    namespace Regions {
        static const std::vector<std::string> columnnames        =
        {"HoleNumber", "Region type index", "Region start in bases",
         "Region end in bases", "Region score"};
        static const std::vector<std::string> regiontypes        =
        {"Adapter", "Insert", "HQRegion"};
        static const std::vector<std::string> regiondescriptions =
        {"Adapter Hit", "Insert Region",
         "High Quality bases region. Score is 1000 * predicted accuracy, where predicted accuary is 0 to 1.0"};
        static const std::vector<std::string> regionsources      =
        {"AdapterFinding", "AdapterFinding", "PulseToBase Region classifer"};
    }

    namespace ZMWMetrics {
        namespace HQRegionSNR {
            static const std::string description = "HQRegion average signal to noise ratio";
        }
        namespace ReadScore {
            static const std::string description = "Read raw accuracy prediction";
        }
        namespace Productivity {
            static const std::string description = "ZMW productivity classification";
        }
    } // ZMWMetrics

    namespace ScanData {
        namespace DyeSet {
            static const std::string basemap = "ACGT"; // default, order matters!
        }
    } // ScanData

} // namespace AttributeValues 

} // namespace PacBio 

#endif
