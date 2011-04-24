/*
GPL License and Copyright Notice ============================================
 This file is part of CBash.

 CBash is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 CBash is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with CBash; if not, write to the Free Software Foundation,
 Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

 CBash copyright (C) 2010 Waruddar
=============================================================================
*/
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class RACERecord : public Record //Race
    {
    private:
        struct RACESKILL
            {
            SINT8   value, boost;

            RACESKILL();
            ~RACESKILL();

            bool operator ==(const RACESKILL &other) const;
            bool operator !=(const RACESKILL &other) const;
            };

        struct RACEDATA
            {
            RACESKILL skills[7];
            UINT8   unused1[2];
            FLOAT32 maleHeight, femaleHeight, maleWeight, femaleWeight;
            UINT32  flags;

            RACEDATA();
            ~RACEDATA();

            bool operator ==(const RACEDATA &other) const;
            bool operator !=(const RACEDATA &other) const;
            };

        struct RACEPart // Head Part
            {
            OptSimpleSubRecord<UINT32> INDX; //Index
            OptSubRecord<FNVMODEL> MODL; //Model
            OptSubRecord<GENICON> ICON; //Icon Filenames

            bool operator ==(const RACEPart &other) const;
            bool operator !=(const RACEPart &other) const;
            };

        enum flagsFlags
            {
            fIsPlayable = 0x00000001,
            fIsChild    = 0x00000004
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord DESC; //Description
        std::vector<ReqSubRecord<FNVXNAM> *> XNAM;  //Relations
        OptSubRecord<RACEDATA> DATA; //Data
        OptSimpleSubRecord<FORMID> ONAM; //Older
        OptSimpleSubRecord<FORMID> YNAM; //Younger
        //OptSubRecord<GENNAM2> NAM2; //Unknown Marker (Empty)
        std::vector<FORMID> VTCK; //Voices
        std::vector<FORMID> DNAM; //Default Hair Styles
        std::vector<UINT8> CNAM; //Default Hair Colors
        OptSimpleSubRecord<FLOAT32> PNAM; //FaceGen - Main clamp
        OptSimpleSubRecord<FLOAT32> UNAM; //FaceGen - Face clamp
        RawRecord ATTR; //Unknown

        //OptSubRecord<GENNAM> NAM0; //Head Data Marker (Empty)
        //OptSubRecord<GENMNAM> MNAM; //Male Data Marker (Empty)
        std::vector<RACEPart *> MaleHeadParts; //Male Head Parts
        //OptSubRecord<GENFNAM> FNAM; //Female Data Marker (Empty)
        std::vector<RACEPart *> FemaleHeadParts; //Female Head Parts

        //OptSubRecord<GENNAM1> NAM1; //Body Data Marker (Empty)
        //OptSubRecord<GENMNAM> MNAM; //Male Data Marker (Empty)
        std::vector<RACEPart *> MaleBodyParts; //Male Head Parts
        //OptSubRecord<GENFNAM> FNAM; //Female Data Marker (Empty)
        std::vector<RACEPart *> FemaleBodyParts; //Female Head Parts

        std::vector<FORMID> HNAM; //Hairs
        std::vector<FORMID> ENAM; //Eyes

        //OptSubRecord<GENMNAM> MNAM; //Male Data Marker (Empty)
        RawRecord MaleFGGS; //FaceGen Geometry-Symmetric
        RawRecord MaleFGGA; //FaceGen Geometry-Asymmetric
        RawRecord MaleFGTS; //FaceGen Texture-Symmetric
        RawRecord MaleSNAM; //Unknown
        //OptSubRecord<GENFNAM> FNAM; //Female Data Marker (Empty)
        RawRecord FemaleFGGS; //FaceGen Geometry-Symmetric
        RawRecord FemaleFGGA; //FaceGen Geometry-Asymmetric
        RawRecord FemaleFGTS; //FaceGen Texture-Symmetric
        RawRecord FemaleSNAM; //Unknown

        RACERecord(unsigned char *_recData=NULL);
        RACERecord(RACERecord *srcRecord);
        ~RACERecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsPlayable();
        void   IsPlayable(bool value);
        bool   IsChild();
        void   IsChild(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(_FileHandler &SaveHandler);

        bool operator ==(const RACERecord &other) const;
        bool operator !=(const RACERecord &other) const;
    };
}