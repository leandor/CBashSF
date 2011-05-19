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
class CELLRecord : public FNVRecord //Cell
    {
    private:
        struct CELLXCLC
            {
            SINT32  posX, posY;
            UINT32  flags; //Not always present in chunk

            CELLXCLC();
            ~CELLXCLC();

            bool operator ==(const CELLXCLC &other) const;
            bool operator !=(const CELLXCLC &other) const;
            };

        enum flagsFlags
            {
            fIsInterior         = 0x00000001,
            fHasWater           = 0x00000002,
            fInvertFastTravel   = 0x00000004,
            fForceHideLand      = 0x00000008, //Exterior Cells
            fIsOblivionInterior = 0x00000008, //Interior Cells
            fPublicPlace        = 0x00000020,
            fHandChanged        = 0x00000040,
            fBehaveLikeExterior = 0x00000080
            };


        enum lightFlags
            {
            fIsAmbientInherited             = 0x00000001,
            fIsDirectionalColorInherited    = 0x00000002,
            fIsFogColorInherited            = 0x00000004,
            fIsFogNearInherited             = 0x00000008,
            fIsFogFarInherited              = 0x00000010,
            fIsDirectionalRotationInherited = 0x00000020,
            fIsDirectionalFadeInherited     = 0x00000040,
            fIsFogClipInherited             = 0x00000080,
            fIsFogPowerInherited            = 0x00000100
            };

        enum xclcFlags
            {
            fIsQuad1ForceHidden = 0x00000001,
            fIsQuad2ForceHidden = 0x00000002,
            fIsQuad3ForceHidden = 0x00000004,
            fIsQuad4ForceHidden = 0x00000008
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<UINT8> DATA; //Flags
        OptSubRecord<CELLXCLC> XCLC; //Grid
        OptSubRecord<FNVLIGHT> XCLL; //Lighting
        UnorderedSparseArray<GENIMPS *> IMPS; //Swapped Impact
        OptSubRecord<GENIMPF> IMPF; //Footstep Materials
        ReqSimpleSubRecord<FORMID> LTMP; //Light Template
        ReqSimpleSubRecord<UINT32> LNAM; //Light Inherit Flags
        SimpleFloatSubRecord<flt_max> XCLW; //waterHeight
        StringRecord XNAM; //Water Noise Texture
        UnorderedPackedArray<FORMID> XCLR; //Regions
        OptSimpleSubRecord<FORMID> XCIM; //Image Space
        RawRecord XCET; //Unknown
        OptSimpleSubRecord<FORMID> XEZN; //Encounter Zone
        OptSimpleSubRecord<FORMID> XCCM; //Climate
        OptSimpleSubRecord<FORMID> XCWT; //Water
        OptSubRecord<FNVXOWN> Ownership; //Owner
        OptSimpleSubRecord<FORMID> XCAS; //Acoustic Space
        RawRecord XCMT; //Unused
        OptSimpleSubRecord<FORMID> XCMO; //Music Type
        std::vector<Record *> ACHR;
        std::vector<Record *> ACRE;
        std::vector<Record *> REFR;
        std::vector<Record *> PGRE;
        std::vector<Record *> PMIS;
        std::vector<Record *> PBEA;
        std::vector<Record *> PFLA;
        std::vector<Record *> PCBE;
        std::vector<Record *> NAVM;
        Record *LAND;

        Record *Parent;

        CELLRecord(unsigned char *_recData=NULL);
        CELLRecord(CELLRecord *srcRecord);
        ~CELLRecord();

        bool   HasSubRecords();
        bool   VisitSubRecords(const UINT32 &RecordType, RecordOp &op);
        bool   VisitFormIDs(FormIDOp &op);

        bool   IsInterior();
        void   IsInterior(bool value);
        bool   IsHasWater();
        void   IsHasWater(bool value);
        bool   IsInvertFastTravel();
        void   IsInvertFastTravel(bool value);
        bool   IsForceHideLand();
        void   IsForceHideLand(bool value);
        bool   IsOblivionInterior();
        void   IsOblivionInterior(bool value);
        bool   IsPublicPlace();
        void   IsPublicPlace(bool value);
        bool   IsHandChanged();
        void   IsHandChanged(bool value);
        bool   IsBehaveLikeExterior();
        void   IsBehaveLikeExterior(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsQuad1ForceHidden();
        void   IsQuad1ForceHidden(bool value);
        bool   IsQuad2ForceHidden();
        void   IsQuad2ForceHidden(bool value);
        bool   IsQuad3ForceHidden();
        void   IsQuad3ForceHidden(bool value);
        bool   IsQuad4ForceHidden();
        void   IsQuad4ForceHidden(bool value);
        bool   IsQuadFlagMask(UINT32 Mask, bool Exact=false);
        void   SetQuadFlagMask(UINT32 Mask);

        bool   IsLightAmbientInherited();
        void   IsLightAmbientInherited(bool value);
        bool   IsLightDirectionalColorInherited();
        void   IsLightDirectionalColorInherited(bool value);
        bool   IsLightFogColorInherited();
        void   IsLightFogColorInherited(bool value);
        bool   IsLightFogNearInherited();
        void   IsLightFogNearInherited(bool value);
        bool   IsLightFogFarInherited();
        void   IsLightFogFarInherited(bool value);
        bool   IsLightDirectionalRotationInherited();
        void   IsLightDirectionalRotationInherited(bool value);
        bool   IsLightDirectionalFadeInherited();
        void   IsLightDirectionalFadeInherited(bool value);
        bool   IsLightFogClipInherited();
        void   IsLightFogClipInherited(bool value);
        bool   IsLightFogPowerInherited();
        void   IsLightFogPowerInherited(bool value);
        bool   IsLightFlagMask(UINT32 Mask, bool Exact=false);
        void   SetLightFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();
        UINT32 GetParentType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CELLRecord &other) const;
        bool operator !=(const CELLRecord &other) const;
    };
}