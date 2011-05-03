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
class WATRRecord : public FNVRecord //Water
    {
    private:
        struct WATRANAM
            {
            UINT8   opacity;

            WATRANAM();
            ~WATRANAM();

            bool operator ==(const WATRANAM &other) const;
            bool operator !=(const WATRANAM &other) const;
            };

        struct WATRDNAM
            {
            FLOAT32 unknown1, unknown2, unknown3, unknown4,
                    sunPower, reflectAmt, fresnelAmt;
            UINT8   unused1[4];
            FLOAT32 fogNear, fogFar;
            GENCLR  shallow;
            GENCLR  deep;
            GENCLR  refl;
            UINT8   unused2[4];
            FLOAT32 rainForce, rainVelocity, rainFalloff, rainDampner,
                    dispSize, dispForce, dispVelocity, dispFalloff,
                    dispDampner, rainSize, noiseScale, noise1Direction,
                    noise2Direction, noise3Direction, noise1Speed,
                    noise2Speed, noise3Speed, noiseFalloffStart,
                    noiseFalloffEnd, underFogAmt, uvScale, underFogAmt,
                    underFogNear, underFogFar, distAmt, shininess,
                    hdrMult, lightRadius, lightBright, noise1UVScale,
                    noise2UVScale, noise3UVScale;

            //Missing in old format (DATA, not DNAM)
            FLOAT32 noise1AmpScale, noise2AmpScale, noise3AmpScale;
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
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord NNAM; //Noise Map
        OptSubRecord<WATRANAM> ANAM; //Opacity
        OptSimpleSubRecord<UINT8> FNAM; //Flags
        StringRecord MNAM; //Material ID
        OptSimpleSubRecord<FORMID> SNAM; //Sound
        OptSimpleSubRecord<FORMID> XNAM; //Actor Effect
        OptSimpleSubRecord<UINT16> DATA; //Damage
        OptSubRecord<WATRDNAM> DNAM; //Visual Data (May be listed as DATA in old format, auto upgrade to DNAM on read)
        OptSubRecord<WATRGNAM> GNAM; //Related Waters (Unused)

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
}