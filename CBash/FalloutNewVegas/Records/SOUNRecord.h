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
class SOUNRecord : public FNVRecord //Sound
    {
    private:
        struct SOUNSNDD
            {
            UINT8   minDistance, maxDistance;
            SINT8   freqAdjustment;
            UINT8   unused1;
            UINT32  flags;
            SINT16  staticAtten;
            UINT8   stopTime, startTime;
            //Below are only on SNDD, and not SNDX
            SINT16  attenCurve[5], reverb;
            SINT32  priority, x, y;

            SOUNSNDD();
            ~SOUNSNDD();

            bool operator ==(const SOUNSNDD &other) const;
            bool operator !=(const SOUNSNDD &other) const;
            };

        enum flagsFlags
            {
            fIsRandomFrequencyShift = 0x00000001,
            fIsPlayAtRandom         = 0x00000002,
            fIsEnvironmentIgnored   = 0x00000004,
            fIsRandomLocation       = 0x00000008,
            fIsLoop                 = 0x00000010,
            fIsMenuSound            = 0x00000020,
            fIs2D                   = 0x00000040,
            fIs360LFE               = 0x00000080,
            fIsDialogueSound        = 0x00000100,
            fIsEnvelopeFast         = 0x00000200,
            fIsEnvelopeSlow         = 0x00000400,
            fIs2DRadius             = 0x00000800,
            fIsMuteWhenSubmerged    = 0x00001000
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FNAM; //Sound Filename
        SemiOptSimpleSubRecord<UINT8> RNAM; //Random Chance %
        ReqSubRecord<SOUNSNDD> SNDD; // Sound Data (May be SNDX format, so auto-update on read)

        //OptSubRecord<GENANAM> ANAM; //Attenuation Curve (Read into SNDD)
        //OptSimpleSubRecord<SINT16> GNAM; //Reverb Attenuation Control (Read into SNDD)
        //OptSimpleSubRecord<SINT32> HNAM; //Priority (Read into SNDD)

        SOUNRecord(unsigned char *_recData=NULL);
        SOUNRecord(SOUNRecord *srcRecord);
        ~SOUNRecord();

        bool   IsRandomFrequencyShift();
        void   IsRandomFrequencyShift(bool value);
        bool   IsPlayAtRandom();
        void   IsPlayAtRandom(bool value);
        bool   IsEnvironmentIgnored();
        void   IsEnvironmentIgnored(bool value);
        bool   IsRandomLocation();
        void   IsRandomLocation(bool value);
        bool   IsLoop();
        void   IsLoop(bool value);
        bool   IsMenuSound();
        void   IsMenuSound(bool value);
        bool   Is2D();
        void   Is2D(bool value);
        bool   Is360LFE();
        void   Is360LFE(bool value);
        bool   IsDialogueSound();
        void   IsDialogueSound(bool value);
        bool   IsEnvelopeFast();
        void   IsEnvelopeFast(bool value);
        bool   IsEnvelopeSlow();
        void   IsEnvelopeSlow(bool value);
        bool   Is2DRadius();
        void   Is2DRadius(bool value);
        bool   IsMuteWhenSubmerged();
        void   IsMuteWhenSubmerged(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const SOUNRecord &other) const;
        bool operator !=(const SOUNRecord &other) const;
    };
}