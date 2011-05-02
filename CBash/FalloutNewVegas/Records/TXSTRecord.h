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
class TXSTRecord : public FNVRecord //Texture Set
    {
    private:
        enum flagsFlags
            {
            fIsNoSpecularMap = 0x00000001
            };

        enum DODTFlags
            {
            fIsParallax      = 0x00000001,
            fIsAlphaBlending = 0x00000002,
            fIsAlphaTesting  = 0x00000004
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        //Textures (RGB/A)
        StringRecord TX00; //Base Image / Transparency
        StringRecord TX01; //Normal Map / Specular
        StringRecord TX02; //Environment Map Mask / ?
        StringRecord TX03; //Glow Map / Unused
        StringRecord TX04; //Parallax Map / Unused
        StringRecord TX05; //Environment Map / Unused
        OptSubRecord<GENDODT> DODT; //Decal Data
        ReqSimpleSubRecord<UINT16> DNAM; //Flags

        TXSTRecord(unsigned char *_recData=NULL);
        TXSTRecord(TXSTRecord *srcRecord);
        ~TXSTRecord();

        bool   IsNoSpecularMap();
        void   IsNoSpecularMap(bool value);
        bool   IsFlagMask(UINT16 Mask, bool Exact=false);
        void   SetFlagMask(UINT16 Mask);

        bool   IsObjectParallax();
        void   IsObjectParallax(bool value);
        bool   IsObjectAlphaBlending();
        void   IsObjectAlphaBlending(bool value);
        bool   IsObjectAlphaTesting();
        void   IsObjectAlphaTesting(bool value);
        bool   IsObjectFlagMask(UINT8 Mask, bool Exact=false);
        void   SetObjectFlagMask(UINT8 Mask);

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

        bool operator ==(const TXSTRecord &other) const;
        bool operator !=(const TXSTRecord &other) const;
    };
}