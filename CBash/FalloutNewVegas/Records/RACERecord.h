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
class RACERecord : public FNVRecord //Race
    {
    private:
        struct RACEPart // Part
            {
            OptSubRecord<FNVMODEL> MODL; //Model
            StringRecord ICON; //Large Icon Filename
            StringRecord MICO; //Small Icon Filename

            void Write(UINT32 index, FileWriter &writer);
            void WriteIconsFirst(UINT32 index, FileWriter &writer);

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
        OrderedSparseArray<FNVXNAM *> XNAM; //Relations, not sure if record order matters
        ReqSubRecord<RACEDATA> DATA; //Data
        OptSimpleSubRecord<FORMID> ONAM; //Older
        OptSimpleSubRecord<FORMID> YNAM; //Younger
        //OptSubRecord<GENNAM2> NAM2; //Unknown Marker (Empty)
        SubRecord<RACEVNAM> VTCK; //Voices
        SubRecord<RACEDNAM> DNAM; //Default Hair Styles
        SubRecord<RACECNAM> CNAM; //Default Hair Colors
        OptSimpleSubRecord<FLOAT32> PNAM; //FaceGen - Main clamp
        OptSimpleSubRecord<FLOAT32> UNAM; //FaceGen - Face clamp
        RawRecord ATTR; //Unknown

        //OptSubRecord<GENNAM> NAM0; //Head Data Marker (Empty)
        //OptSubRecord<GENMNAM> MNAM; //Male Data Marker (Empty)
        //Male Head Parts
        RACEPart MHMOD0; //Head
        RACEPart MHMOD1; //Ears
        RACEPart MHMOD2; //Mouth
        RACEPart MHMOD3; //Teeth Lower
        RACEPart MHMOD4; //Teeth Upper
        RACEPart MHMOD5; //Tongue
        RACEPart MHMOD6; //Left Eye
        RACEPart MHMOD7; //Right Eye

        //OptSubRecord<GENFNAM> FNAM; //Female Data Marker (Empty)
        //Female Head Parts
        RACEPart FHMOD0; //Head
        RACEPart FHMOD1; //Ears
        RACEPart FHMOD2; //Mouth
        RACEPart FHMOD3; //Teeth Lower
        RACEPart FHMOD4; //Teeth Upper
        RACEPart FHMOD5; //Tongue
        RACEPart FHMOD6; //Left Eye
        RACEPart FHMOD7; //Right Eye

        //OptSubRecord<GENNAM1> NAM1; //Body Data Marker (Empty)
        //OptSubRecord<GENMNAM> MNAM; //Male Data Marker (Empty)
        //Male Body Parts
        RACEPart MBMOD0; //Upper Body
        RACEPart MBMOD1; //Left Hand
        RACEPart MBMOD2; //Right Hand
        RACEPart MBMOD3; //Upper Body Texture

        //OptSubRecord<GENFNAM> FNAM; //Female Data Marker (Empty)
        //Female Body Parts
        RACEPart FBMOD0; //Upper Body
        RACEPart FBMOD1; //Left Hand
        RACEPart FBMOD2; //Right Hand
        RACEPart FBMOD3; //Upper Body Texture

        UnorderedPackedArray<FORMID> HNAM; //Hairs
        UnorderedPackedArray<FORMID> ENAM; //Eyes

        //OptSubRecord<GENMNAM> MNAM; //Male Data Marker (Empty)
        RawRecord MaleFGGS; //FaceGen Geometry-Symmetric
        RawRecord MaleFGGA; //FaceGen Geometry-Asymmetric
        RawRecord MaleFGTS; //FaceGen Texture-Symmetric
        ReqSubRecord<RACESNAM> MaleSNAM; //Unknown
        //OptSubRecord<GENFNAM> FNAM; //Female Data Marker (Empty)
        RawRecord FemaleFGGS; //FaceGen Geometry-Symmetric
        RawRecord FemaleFGGA; //FaceGen Geometry-Asymmetric
        RawRecord FemaleFGTS; //FaceGen Texture-Symmetric
        ReqSubRecord<RACESNAM> FemaleSNAM; //Unknown

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

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const RACERecord &other) const;
        bool operator !=(const RACERecord &other) const;
    };
}