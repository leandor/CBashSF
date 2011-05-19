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
class EXPLRecord : public FNVRecord //Explosion
    {
    private:
        struct EXPLDATA
            {
            FLOAT32 force, damage, radius;
            FORMID  light, sound1;
            UINT32  flags;
            FLOAT32 ISRadius;
            FORMID  impactDataSet, sound2;
            FLOAT32 radLevel, radTime, radRadius;
            UINT32  soundLevel;

            EXPLDATA();
            ~EXPLDATA();

            bool operator ==(const EXPLDATA &other) const;
            bool operator !=(const EXPLDATA &other) const;
            };

        enum flagsFlags
            {
            fIsUnknown1                   = 0x00000001,
            fIsAlwaysUsesWorldOrientation = 0x00000002,
            fIsAlwaysKnockDown            = 0x00000004,
            fIsFormulaKnockDown           = 0x00000008,
            fIsIgnoreLOS                  = 0x00000010,
            fIsPushExplosionSourceRefOnly = 0x00000020,
            fIsIgnoreImageSpaceSwap       = 0x00000040
            };

        enum soundLevelTypes
            {
            eLoud = 0,
            eNormal,
            eSilent
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSimpleSubRecord<FORMID> EITM; //Object Effect
        OptSimpleSubRecord<FORMID> MNAM; //Image Space Modifier
        ReqSubRecord<EXPLDATA> DATA; //Data
        OptSimpleSubRecord<FORMID> INAM; //Placed Impact Object

        EXPLRecord(unsigned char *_recData=NULL);
        EXPLRecord(EXPLRecord *srcRecord);
        ~EXPLRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsUnknown1();
        void   IsUnknown1(bool value);
        bool   IsAlwaysUsesWorldOrientation();
        void   IsAlwaysUsesWorldOrientation(bool value);
        bool   IsAlwaysKnockDown();
        void   IsAlwaysKnockDown(bool value);
        bool   IsFormulaKnockDown();
        void   IsFormulaKnockDown(bool value);
        bool   IsIgnoreLOS();
        void   IsIgnoreLOS(bool value);
        bool   IsPushExplosionSourceRefOnly();
        void   IsPushExplosionSourceRefOnly(bool value);
        bool   IsIgnoreImageSpaceSwap();
        void   IsIgnoreImageSpaceSwap(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsLoud();
        void   IsLoud(bool value);
        bool   IsNormal();
        void   IsNormal(bool value);
        bool   IsSilent();
        void   IsSilent(bool value);
        bool   IsSoundLevelType(UINT8 Type);
        void   SetSoundLevelType(UINT8 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const EXPLRecord &other) const;
        bool operator !=(const EXPLRecord &other) const;
    };
}