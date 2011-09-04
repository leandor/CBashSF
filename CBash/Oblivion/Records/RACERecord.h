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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace Ob
{
class RACERecord : public Record //Race
    {
    private:
        struct RACEATTR
            {
            UINT8   maleStrength, maleIntelligence, maleWillpower,
                    maleAgility, maleSpeed, maleEndurance,
                    malePersonality, maleLuck;
            UINT8   femaleStrength, femaleIntelligence, femaleWillpower,
                    femaleAgility, femaleSpeed, femaleEndurance,
                    femalePersonality, femaleLuck;

            RACEATTR();
            ~RACEATTR();

            bool operator ==(const RACEATTR &other) const;
            bool operator !=(const RACEATTR &other) const;
            };

        struct RACEMODEL
            {
            ReqSimpleFloatSubRecord<flt_0> MODB;
            StringRecord MODL;
            RawRecord MODT;
            StringRecord ICON;

            void Write(FileWriter &writer);

            bool operator ==(const RACEMODEL &other) const;
            bool operator !=(const RACEMODEL &other) const;
            };

        enum flagsFlags
            {
            fIsPlayable = 0x00000001
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord DESC; //Description
        UnorderedSparseArray<FORMID> SPLO; //Spells
        OrderedSparseArray<GENXNAM *> XNAM; //Relations, not sure if record order matters
        ReqSubRecord<RACEDATA> DATA; //Data
        SubRecord<RACEVNAM> VNAM; //Voices
        SubRecord<RACEDNAM> DNAM; //Default Hair Styles
        ReqSimpleSubRecord<UINT8> CNAM; //Default Hair Color
        OptSimpleFloatSubRecord<flt_0> PNAM; //FaceGen - Main clamp
        OptSimpleFloatSubRecord<flt_0> UNAM; //FaceGen - Face clamp
        ReqSubRecord<RACEATTR> ATTR; //Base Attributes
        OptSubRecord<RACEMODEL> MOD0; //Head Model
        OptSubRecord<RACEMODEL> MOD1; //Male Ears Model
        OptSubRecord<RACEMODEL> MOD2; //Female Ears Model
        OptSubRecord<RACEMODEL> MOD3; //Mouth Model
        OptSubRecord<RACEMODEL> MOD4; //Lower Teeth Model
        OptSubRecord<RACEMODEL> MOD5; //Upper Teeth Model
        OptSubRecord<RACEMODEL> MOD6; //Tongue Model
        OptSubRecord<RACEMODEL> MOD7; //Left Eye Model
        OptSubRecord<RACEMODEL> MOD8; //Right Eye Model
        OptSubRecord<GENMODEL> MMODL; //Male Tail Model
        StringRecord MICON0; //Male Upper Body Texture
        StringRecord MICON1; //Male Lower Body Texture
        StringRecord MICON2; //Male Hand Texture
        StringRecord MICON3; //Male Foot Texture
        StringRecord MICON4; //Male Tail Texture
        OptSubRecord<GENMODEL> FMODL;//Female Tail Model
        StringRecord FICON0; //Female Upper Body Texture
        StringRecord FICON1; //Female Lower Body Texture
        StringRecord FICON2; //Female Hand Texture
        StringRecord FICON3; //Female Foot Texture
        StringRecord FICON4; //Female Tail Texture
        UnorderedPackedArray<FORMID> HNAM; //Hairs
        UnorderedPackedArray<FORMID> ENAM; //Eyes
        RawRecord FGGS; //FaceGen Geometry-Symmetric
        RawRecord FGGA; //FaceGen Geometry-Asymmetric
        RawRecord FGTS; //FaceGen Texture-Symmetric
        ReqSubRecord<RACESNAM> SNAM; //Unknown

        RACERecord(unsigned char *_recData=NULL);
        RACERecord(RACERecord *srcRecord);
        ~RACERecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsPlayable();
        void   IsPlayable(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const RACERecord &other) const;
        bool operator !=(const RACERecord &other) const;
        bool equals(Record *other);
    };
}