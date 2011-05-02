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
class IMGSRecord : public FNVRecord //Image Space
    {
    private:
        struct IMGSDNAM
            {
            //HDR
            FLOAT32 hdrEyeAdaptSpeed, hdrBlurRadius, hdrBlurPasses,
                    hdrEmissiveMult, hdrTargetLUM, hdrUpperLUMClamp,
                    hdrBrightScale, hdrBrightClamp, hdrLUMRampNoTex,
                    hdrLUMRampMin, hdrLUMRampMax, hdrSunlightDimmer,
                    hdrGrassDimmer, hdrTreeDimmer, hdrSkinDimmer;

            //Bloom
            FLOAT32 bloomBlurRadius, bloomAlphaMultInterior, bloomAlphaMultExterior;

            //Get Hit
            FLOAT32 hitBlurRadius, hitBlurDampingConstant, hitDampingConstant;

            //Night Eye
            FLOAT32 neRed, neGreen, neBlue, neBrightness;

            //Cinematic
            FLOAT32 saturation, contrastAvgLUMValue, contrastValue,
                    brightnessValue, cineRed, cineGreen, cineBlue,
                    cineValue;

            UINT8   unused1[4], unused2[4], unused3[4], unused4[4];
            UINT8   flags, unused5[3];

            IMGSDNAM();
            ~IMGSDNAM();

            bool operator ==(const IMGSDNAM &other) const;
            bool operator !=(const IMGSDNAM &other) const;
            };

        enum flagsFlags
            {
            fIsSaturation = 0x00000001,
            fIsContrast   = 0x00000002,
            fIsTint       = 0x00000004,
            fIsBrightness = 0x00000008
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<IMGSDNAM> DNAM; //IMGS Data

        IMGSRecord(unsigned char *_recData=NULL);
        IMGSRecord(IMGSRecord *srcRecord);
        ~IMGSRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsSaturation();
        void   IsSaturation(bool value);
        bool   IsContrast();
        void   IsContrast(bool value);
        bool   IsTint();
        void   IsTint(bool value);
        bool   IsBrightness();
        void   IsBrightness(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);


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

        bool operator ==(const IMGSRecord &other) const;
        bool operator !=(const IMGSRecord &other) const;
    };
}