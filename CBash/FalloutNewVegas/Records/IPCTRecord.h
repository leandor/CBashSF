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
class IPCTRecord : public FNVRecord //Impact
    {
    private:
        struct IPCTDATA
            {
            FLOAT32 duration; // Effect - Duration
            UINT32  orientation; // Effect - Orientation
            FLOAT32 angleThreshold, placementRadius; // Angle Threshold, Placement Radius
            UINT32  soundLevel, flags; // Sound Level, Flags

            IPCTDATA();
            ~IPCTDATA();

            bool operator ==(const IPCTDATA &other) const;
            bool operator !=(const IPCTDATA &other) const;
            };

        enum flagsFlags
            {
            fIsNoDecalData = 0x00000001
            };

        enum DODTFlags
            {
            fIsParallax      = 0x00000001,
            fIsAlphaBlending = 0x00000002,
            fIsAlphaTesting  = 0x00000004
            };

        enum soundLevelTypes
            {
            eLoud = 0,
            eNormal,
            eSilent
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<IPCTDATA> DATA; //Data
        OptSubRecord<GENDODT> DODT; //Decal Data
        OptSimpleSubRecord<FORMID> DNAM; //Texture Set
        OptSimpleSubRecord<FORMID> SNAM; //Sound 1
        OptSimpleSubRecord<FORMID> NAM1; //Sound 2

        IPCTRecord(unsigned char *_recData=NULL);
        IPCTRecord(IPCTRecord *srcRecord);
        ~IPCTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNoDecalData();
        void   IsNoDecalData(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsObjectParallax();
        void   IsObjectParallax(bool value);
        bool   IsObjectAlphaBlending();
        void   IsObjectAlphaBlending(bool value);
        bool   IsObjectAlphaTesting();
        void   IsObjectAlphaTesting(bool value);
        bool   IsObjectFlagMask(UINT8 Mask, bool Exact=false);
        void   SetObjectFlagMask(UINT8 Mask);

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

        bool operator ==(const IPCTRecord &other) const;
        bool operator !=(const IPCTRecord &other) const;
    };
}