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
class CELLRecord : public Record //Cell
    {
    private:
        struct CELLXCLC
            {
            SINT32  posX, posY;
            UINT32  flags;

            CELLXCLC();
            ~CELLXCLC();

            bool operator ==(const CELLXCLC &other) const;
            bool operator !=(const CELLXCLC &other) const;
            };

        struct CELLXCLL
            {
            GENCLR  ambient; //Ambient Color
            GENCLR  directional; //Directional Color
            GENCLR  fog; //Fog Color
            FLOAT32 fogNear, fogFar; //Fog Near, Fog Far
            SINT32  directionalXY, directionalZ; //Directional Rotation XY, Directional Rotation Z
            FLOAT32 directionalFade, fogClip, fogPower; //Directional Fade, Fog Clip Dist, Fog Power

            CELLXCLL();
            ~CELLXCLL();

            bool operator ==(const CELLXCLL &other) const;
            bool operator !=(const CELLXCLL &other) const;
            };

        struct CELLLTMP //Light Template
            {
            OptSubRecord<GENFID> LTMP; //Template
            OptSubRecord<GENU32> LNAM; //Inherit Flags

            enum flagsFlags
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

            bool   IsAmbientInherited();
            void   IsAmbientInherited(bool value);
            bool   IsDirectionalColorInherited();
            void   IsDirectionalColorInherited(bool value);
            bool   IsFogColorInherited();
            void   IsFogColorInherited(bool value);
            bool   IsFogNearInherited();
            void   IsFogNearInherited(bool value);
            bool   IsFogFarInherited();
            void   IsFogFarInherited(bool value);
            bool   IsDirectionalRotationInherited();
            void   IsDirectionalRotationInherited(bool value);
            bool   IsDirectionalFadeInherited();
            void   IsDirectionalFadeInherited(bool value);
            bool   IsFogClipInherited();
            void   IsFogClipInherited(bool value);
            bool   IsFogPowerInherited();
            void   IsFogPowerInherited(bool value);
            bool   IsFlagMask(UINT32 Mask, bool Exact=false);
            void   SetFlagMask(UINT32 Mask);

            bool operator ==(const CELLLTMP &other) const;
            bool operator !=(const CELLLTMP &other) const;
            };

        struct CELLXCLW
            {
            FLOAT32 waterHeight;

            CELLXCLW();
            ~CELLXCLW();

            bool operator ==(const CELLXCLW &other) const;
            bool operator !=(const CELLXCLW &other) const;
            };

        enum flagsFlags
            {
            fIsInterior         = 0x00000001,
            fHasWater           = 0x00000002,
            fInvertFastTravel   = 0x00000004,
            fForceHideLand      = 0x00000008, //Exterior Cells
            fIsOblivionInterior = 0x00000008, //From OBSE, unconfirmed
            fPublicPlace        = 0x00000020,
            fHandChanged        = 0x00000040,
            fBehaveLikeExterior = 0x00000080
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
        OptSubRecord<GENU8> DATA; //Flags
        OptSubRecord<CELLXCLC> XCLC; //Grid
        OptSubRecord<CELLXCLL> XCLL; //Lighting
        std::vector<StringRecord> IMPF; //Footstep Materials
        OptSubRecord<CELLLTMP> LTMP; //Light Template
        OptSubRecord<CELLXCLW> XCLW; //Water Height
        StringRecord XNAM; //Water Noise Texture
        std::vector<FORMID> XCLR; //Regions
        OptSubRecord<GENFID> XCIM; //Image Space
        RawRecord XCET; //Unknown
        OptSubRecord<GENFID> XEZN; //Encounter Zone
        OptSubRecord<GENFID> XCCM; //Climate
        OptSubRecord<GENFID> XCWT; //Water
        OptSubRecord<FNVXOWN> Ownership; //Owner
        OptSubRecord<GENFID> XCAS; //Acoustic Space
        RawRecord XCMT; //Unused
        OptSubRecord<GENFID> XCMO; //Music Type
        std::vector<Record *> ACHR;
        std::vector<Record *> ACRE;
        std::vector<Record *> REFR;
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
        bool   HasWater();
        void   HasWater(bool value);
        bool   InvertFastTravel();
        void   InvertFastTravel(bool value);
        bool   ForceHideLand();
        void   ForceHideLand(bool value);
        bool   IsOblivionInterior();
        void   IsOblivionInterior(bool value);
        bool   PublicPlace();
        void   PublicPlace(bool value);
        bool   HandChanged();
        void   HandChanged(bool value);
        bool   BehaveLikeExterior();
        void   BehaveLikeExterior(bool value);
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
        bool   IsHiddenFlagMask(UINT8 Mask, bool Exact=false);
        void   SetHiddenFlagMask(UINT8 Mask);

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

        bool operator ==(const CELLRecord &other) const;
        bool operator !=(const CELLRecord &other) const;
    };
}