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
class DEBRRecord : public FNVRecord //Debris
    {
    private:
        struct DEBRModel
            {
            UINT8   percentage;
            STRING  modPath;
            UINT8   flags;

            RawRecord MODT;

            DEBRModel();
            ~DEBRModel();

            enum flagsFlags
                {
                fIsHasCollisionData = 0x01
                };

            bool   IsHasCollisionData();
            void   IsHasCollisionData(bool value);
            bool   IsFlagMask(UINT8 Mask, bool Exact=false);
            void   SetFlagMask(UINT8 Mask);

            bool   Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos);
            void   Write(FileWriter &writer);

            bool   operator ==(const DEBRModel &other) const;
            bool   operator !=(const DEBRModel &other) const;
            };

        struct DEBRModels
            {
            std::vector<DEBRModel *> MODS;

            DEBRModels();
            ~DEBRModels();

            bool IsLoaded() const;
            void Load();
            void Unload();

            void resize(UINT32 newSize);

            void Write(FileWriter &writer);

            DEBRModels& operator = (const DEBRModels &rhs);
            bool operator ==(const DEBRModels &other) const;
            bool operator !=(const DEBRModels &other) const;
            };

    public:
        StringRecord EDID; //Editor ID
        DEBRModels Models; //Models

        DEBRRecord(unsigned char *_recData=NULL);
        DEBRRecord(DEBRRecord *srcRecord);
        ~DEBRRecord();

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const DEBRRecord &other) const;
        bool operator !=(const DEBRRecord &other) const;
    };
}