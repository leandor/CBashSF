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

class WATRRecord : public Record
    {
    private:
        struct WATRDATA
            {
            FLOAT32 windVelocity, windDirection, waveAmp, waveFreq, sunPower,
                    reflectAmt, fresnelAmt, xSpeed, ySpeed, fogNear, fogFar;
            GENCLR  shallow;
            GENCLR  deep;
            GENCLR  refl;
            UINT8   blend, unused1[3];
            FLOAT32 rainForce, rainVelocity, rainFalloff, rainDampner,
                    rainSize, dispForce, dispVelocity, dispFalloff,
                    dispDampner, dispSize;
            UINT16  damage;

            WATRDATA();
            ~WATRDATA();

            bool operator ==(const WATRDATA &other) const;
            bool operator !=(const WATRDATA &other) const;
            };

        struct WATRGNAM
            {
            FORMID  dayWater, nightWater, underWater;

            WATRGNAM();
            ~WATRGNAM();

            bool operator ==(const WATRGNAM &other) const;
            bool operator !=(const WATRGNAM &other) const;
            };

        enum flagsFlags
            {
            fIsCausesDamage = 0x00000001,
            fIsReflective   = 0x00000002
            };

    public:
        StringRecord EDID;
        StringRecord TNAM;
        ReqSimpleSubRecord<UINT8, 75> ANAM; // opacity
        ReqSimpleSubRecord<UINT8> FNAM;
        StringRecord MNAM;
        OptSimpleSubRecord<FORMID> SNAM;
        SemiOptSubRecord<WATRDATA> DATA;
        SemiOptSubRecord<WATRGNAM> GNAM;

        WATRRecord(unsigned char *_recData=NULL);
        WATRRecord(WATRRecord *srcRecord);
        ~WATRRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsCausesDmg();
        void   IsCausesDmg(bool value);
        bool   IsCausesDamage();
        void   IsCausesDamage(bool value);
        bool   IsReflective();
        void   IsReflective(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const WATRRecord &other) const;
        bool operator !=(const WATRRecord &other) const;
    };