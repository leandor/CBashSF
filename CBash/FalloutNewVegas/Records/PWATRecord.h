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
class PWATRecord : public FNVRecord //Placeable Water
    {
    private:
        struct PWATDNAM
            {
            UINT32  flags;
            FORMID  water;

            CREADATA();
            ~CREADATA();

            bool operator ==(const CREADATA &other) const;
            bool operator !=(const CREADATA &other) const;
            };

        enum flagsFlags
            {
            fIsReflects                 = 0x00000001,
            fIsReflectsActors           = 0x00000002,
            fIsReflectsLand             = 0x00000004
            fIsReflectsLODLand          = 0x00000008,
            fIsReflectsLODBuildings     = 0x00000010,
            fIsReflectsTrees            = 0x00000020,
            fIsReflectsSky              = 0x00000040,
            fIsReflectsDynamicObjects   = 0x00000080,
            fIsReflectsDeadBodies       = 0x00000100,
            fIsRefracts                 = 0x00000200,
            fIsRefractsActors           = 0x00000400,
            fIsRefractsDeadBodies       = 0x00000800,
            fIsRefractsDynamicObjects   = 0x00010000,
            fIsRefractsDeadBodies       = 0x00020000,
            fIsSilhouetteReflections    = 0x00040000,
            fIsDepth                    = 0x10000000,
            fIsObjectTextureCoordinates = 0x20000000,
            fIsNoUnderwaterFog          = 0x80000000
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<PWATDNAM> DNAM; //Data

        PWATRecord(unsigned char *_recData=NULL);
        PWATRecord(PWATRecord *srcRecord);
        ~PWATRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsReflects();
        void   IsReflects(bool value);
        bool   IsReflectsActors();
        void   IsReflectsActors(bool value);
        bool   IsReflectsLand();
        void   IsReflectsLand(bool value);
        bool   IsReflectsLODLand();
        void   IsReflectsLODLand(bool value);
        bool   IsReflectsLODBuildings();
        void   IsReflectsLODBuildings(bool value);
        bool   IsReflectsTrees();
        void   IsReflectsTrees(bool value);
        bool   IsReflectsSky();
        void   IsReflectsSky(bool value);
        bool   IsReflectsDynamicObjects();
        void   IsReflectsDynamicObjects(bool value);
        bool   IsReflectsDeadBodies();
        void   IsReflectsDeadBodies(bool value);
        bool   IsRefracts();
        void   IsRefracts(bool value);
        bool   IsRefractsActors();
        void   IsRefractsActors(bool value);
        bool   IsRefractsDeadBodies();
        void   IsRefractsDeadBodies(bool value);
        bool   IsRefractsDynamicObjects();
        void   IsRefractsDynamicObjects(bool value);
        bool   IsRefractsDeadBodies();
        void   IsRefractsDeadBodies(bool value);
        bool   IsSilhouetteReflections();
        void   IsSilhouetteReflections(bool value);
        bool   IsDepth();
        void   IsDepth(bool value);
        bool   IsObjectTextureCoordinates();
        void   IsObjectTextureCoordinates(bool value);
        bool   IsNoUnderwaterFog();
        void   IsNoUnderwaterFog(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);



        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        //UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const PWATRecord &other) const;
        bool operator !=(const PWATRecord &other) const;
    };
}