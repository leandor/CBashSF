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
#include "..\Common.h"
#include "..\BaseRecord.h"
#include <vector>

class WTHRRecord : public Record
    {
    private:
        enum WTHRRecordFields {
            eEDID = 0x44494445,
            eCNAM = 0x4D414E43,
            eDNAM = 0x4D414E44,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eNAM0 = 0x304D414E,
            eFNAM = 0x4D414E46,
            eHNAM = 0x4D414E48,
            eDATA = 0x41544144,
            eSNAM = 0x4D414E53
            };
        struct WTHRColors
            {
            GENCLR rise;
            GENCLR day;
            GENCLR set;
            GENCLR night;
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("rise:\n");
                    rise.Debug(debugLevel, indentation);
                    printf("day:\n");
                    day.Debug(debugLevel, indentation);
                    printf("set:\n");
                    set.Debug(debugLevel, indentation);
                    printf("night:\n");
                    night.Debug(debugLevel, indentation);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct WTHRNAM0
            {
            WTHRColors upperSky;
            WTHRColors fog;
            WTHRColors lowerClouds;
            WTHRColors ambient;
            WTHRColors sunlight;
            WTHRColors sun;
            WTHRColors stars;
            WTHRColors lowerSky;
            WTHRColors horizon;
            WTHRColors upperClouds;
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("Type = upperSky\n");
                    upperSky.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("Type = fog\n");
                    fog.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("Type = lowerClouds\n");
                    lowerClouds.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("Type = ambient\n");
                    ambient.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("Type = sunlight\n");
                    sunlight.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("Type = sun\n");
                    sun.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("Type = stars\n");
                    stars.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("Type = lowerSky\n");
                    lowerSky.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("Type = horizon\n");
                    horizon.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("Type = upperClouds\n");
                    upperClouds.Debug(debugLevel, indentation);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct WTHRFNAM
            {
            float fogDayNear, fogDayFar, fogNightNear, fogNightFar;
            WTHRFNAM():fogDayNear(0.0f), fogDayFar(0.0f), fogNightNear(0.0f), fogNightFar(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("fogDayNear   = %f\n", fogDayNear);
                    PrintIndent(indentation);
                    printf("fogDayFar    = %f\n", fogDayFar);
                    PrintIndent(indentation);
                    printf("fogNightNear = %f\n", fogNightNear);
                    PrintIndent(indentation);
                    printf("fogNightFar  = %f\n", fogNightFar);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct WTHRHNAM
            {
            float eyeAdaptSpeed, blurRadius, blurPasses, emissiveMult,
                targetLum, upperLumClamp, brightScale, brightClamp,
                lumRampNoTex, lumRampMin, lumRampMax, sunlightDimmer,
                grassDimmer, treeDimmer;
            WTHRHNAM():eyeAdaptSpeed(0.0f), blurRadius(0.0f), blurPasses(0.0f), emissiveMult(0.0f),
                targetLum(0.0f), upperLumClamp(0.0f), brightScale(0.0f), brightClamp(0.0f),
                lumRampNoTex(0.0f), lumRampMin(0.0f), lumRampMax(0.0f), sunlightDimmer(0.0f),
                grassDimmer(0.0f), treeDimmer(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("eyeAdaptSpeed  = %f\n", eyeAdaptSpeed);
                    PrintIndent(indentation);
                    printf("blurRadius     = %f\n", blurRadius);
                    PrintIndent(indentation);
                    printf("blurPasses     = %f\n", blurPasses);
                    PrintIndent(indentation);
                    printf("emissiveMult   = %f\n", emissiveMult);
                    PrintIndent(indentation);
                    printf("targetLum      = %f\n", targetLum);
                    PrintIndent(indentation);
                    printf("upperLumClamp  = %f\n", upperLumClamp);
                    PrintIndent(indentation);
                    printf("brightScale    = %f\n", brightScale);
                    PrintIndent(indentation);
                    printf("brightClamp    = %f\n", brightClamp);
                    PrintIndent(indentation);
                    printf("lumRampNoTex   = %f\n", lumRampNoTex);
                    PrintIndent(indentation);
                    printf("lumRampMin     = %f\n", lumRampMin);
                    PrintIndent(indentation);
                    printf("lumRampMax     = %f\n", lumRampMax);
                    PrintIndent(indentation);
                    printf("sunlightDimmer = %f\n", sunlightDimmer);
                    PrintIndent(indentation);
                    printf("grassDimmer    = %f\n", grassDimmer);
                    PrintIndent(indentation);
                    printf("treeDimmer     = %f\n", treeDimmer);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct WTHRDATA
            {
            unsigned char windSpeed, lowerCloudSpeed, upperCloudSpeed,
                transDelta, sunGlare, sunDamage, rainFadeIn,
                rainFadeOut, boltFadeIn, boltFadeOut, boltFrequency,
                weatherType, boltRed, boltGreen, boltBlue;
            WTHRDATA():windSpeed(0), lowerCloudSpeed(0), upperCloudSpeed(0),
                transDelta(0), sunGlare(0), sunDamage(0), rainFadeIn(0),
                rainFadeOut(0), boltFadeIn(0), boltFadeOut(0), boltFrequency(0),
                weatherType(0), boltRed(0), boltGreen(0), boltBlue(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("windSpeed       = %u\n", windSpeed);
                    PrintIndent(indentation);
                    printf("lowerCloudSpeed = %u\n", lowerCloudSpeed);
                    PrintIndent(indentation);
                    printf("upperCloudSpeed = %u\n", upperCloudSpeed);
                    PrintIndent(indentation);
                    printf("transDelta      = %u\n", transDelta);
                    PrintIndent(indentation);
                    printf("sunGlare        = %u\n", sunGlare);
                    PrintIndent(indentation);
                    printf("sunDamage       = %u\n", sunDamage);
                    PrintIndent(indentation);
                    printf("rainFadeIn      = %u\n", rainFadeIn);
                    PrintIndent(indentation);
                    printf("rainFadeOut     = %u\n", rainFadeOut);
                    PrintIndent(indentation);
                    printf("boltFadeIn      = %u\n", boltFadeIn);
                    PrintIndent(indentation);
                    printf("boltFadeOut     = %u\n", boltFadeOut);
                    PrintIndent(indentation);
                    printf("boltFrequency   = %u\n", boltFrequency);
                    PrintIndent(indentation);
                    printf("weatherType     = %u\n", weatherType);
                    PrintIndent(indentation);
                    printf("boltRed         = %u\n", boltRed);
                    PrintIndent(indentation);
                    printf("boltGreen       = %u\n", boltGreen);
                    PrintIndent(indentation);
                    printf("boltBlue        = %u\n", boltBlue);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct WTHRSNAM
            {
            unsigned int sound;
            unsigned int type;
            WTHRSNAM():sound(0), type(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("sound = %s\n", PrintFormID(sound));
                    PrintIndent(indentation);
                    printf("type  = %u\n", type);
                    indentation -= 2;
                    }
                else
                    printf("      SNAM\n");
                }
            #endif
            enum eSoundType
                {
                eDefault,
                ePrecip,
                eWind,
                eThunder
                };
            bool IsDefault()
                {
                return (type == eDefault);
                }
            void IsDefault(bool value)
                {
                if(value)
                    type = eDefault;
                else if(IsDefault())
                    type = ePrecip;
                }
            bool IsPrecip()
                {
                return (type == ePrecip);
                }
            void IsPrecip(bool value)
                {
                if(value)
                    type = ePrecip;
                else if(IsPrecip())
                    type = eDefault;
                }
            bool IsPrecipitation()
                {
                return (type == ePrecip);
                }
            void IsPrecipitation(bool value)
                {
                if(value)
                    type = ePrecip;
                else if(IsPrecipitation())
                    type = eDefault;
                }
            bool IsWind()
                {
                return (type == eWind);
                }
            void IsWind(bool value)
                {
                if(value)
                    type = eWind;
                else if(IsWind())
                    type = eDefault;
                }
            bool IsThunder()
                {
                return (type == eThunder);
                }
            void IsThunder(bool value)
                {
                if(value)
                    type = eThunder;
                else if(IsThunder())
                    type = eDefault;
                }
            bool IsType(unsigned int Type)
                {
                return (type == Type);
                }
            void SetType(unsigned int Type)
                {
                type = Type;
                }
            };
    public:
        enum eWeatherType //actually flags, but all are exclusive(except unknowns)...so like a Type
            { //Manual hackery will make the CS think it is multiple types. It isn't known how the game would react.
            eNone     = 0x00000000,
            ePleasant = 0x00000001,
            eCloudy   = 0x00000002,
            eRainy    = 0x00000004,
            eSnow     = 0x00000008,
            fUnk1     = 0x01000000,
            fUnk2     = 0x10000000
            };
        STRING EDID;
        STRING CNAM;
        STRING DNAM;
        GENMODEL MODL;
        ReqRecordField<WTHRNAM0> NAM0;
        ReqRecordField<WTHRFNAM> FNAM;
        ReqRecordField<WTHRHNAM> HNAM;
        ReqRecordField<WTHRDATA> DATA;
        std::vector<ReqRecordField<WTHRSNAM> *> Sounds;

        WTHRRecord(bool newRecord=false):Record(newRecord) {}
        WTHRRecord(const unsigned int &newFormID):Record(newFormID) {}
        WTHRRecord(WTHRRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            CNAM = srcRecord->CNAM;
            DNAM = srcRecord->DNAM;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
            NAM0 = srcRecord->NAM0;
            FNAM = srcRecord->FNAM;
            HNAM = srcRecord->HNAM;
            DATA = srcRecord->DATA;
            Sounds.clear();
            Sounds.resize(srcRecord->Sounds.size());
            for(unsigned int x = 0; x < srcRecord->Sounds.size(); x++)
                {
                Sounds[x] = new ReqRecordField<WTHRSNAM>;
                *Sounds[x] = *srcRecord->Sounds[x];
                }
            return;
            }
        ~WTHRRecord()
            {
            for(unsigned int x = 0; x < Sounds.size(); x++)
                delete Sounds[x];
            }
        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < Sounds.size(); x++)
                FormIDHandler.ExpandFormID(Sounds[x]->value.sound);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < Sounds.size(); x++)
                FormIDHandler.CollapseFormID(Sounds[x]->value.sound);
            }
        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eWTHR;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
        
        bool IsPleasant()
            {
            return (DATA.value.weatherType & ePleasant) != 0;
            }
        void IsPleasant(bool value)
            {
            if(value)
                {
                DATA.value.weatherType |= ePleasant;
                DATA.value.weatherType &= ~eCloudy;
                DATA.value.weatherType &= ~eRainy;
                DATA.value.weatherType &= ~eSnow;
                }
            else if(IsPleasant())
                {
                DATA.value.weatherType &= ~ePleasant;
                DATA.value.weatherType &= ~eCloudy;
                DATA.value.weatherType &= ~eRainy;
                DATA.value.weatherType &= ~eSnow;
                }
            }
        bool IsCloudy()
            {
            return (DATA.value.weatherType & eCloudy) != 0;
            }
        void IsCloudy(bool value)
            {
            if(value)
                {
                DATA.value.weatherType &= ~ePleasant;
                DATA.value.weatherType |= eCloudy;
                DATA.value.weatherType &= ~eRainy;
                DATA.value.weatherType &= ~eSnow;
                }
            else if(IsCloudy())
                {
                DATA.value.weatherType &= ~ePleasant;
                DATA.value.weatherType &= ~eCloudy;
                DATA.value.weatherType &= ~eRainy;
                DATA.value.weatherType &= ~eSnow;
                }
            }
        bool IsRainy()
            {
            return (DATA.value.weatherType & eRainy) != 0;
            }
        void IsRainy(bool value)
            {
            if(value)
                {
                DATA.value.weatherType &= ~ePleasant;
                DATA.value.weatherType &= ~eCloudy;
                DATA.value.weatherType |= eRainy;
                DATA.value.weatherType &= ~eSnow;
                }
            else if(IsRainy())
                {
                DATA.value.weatherType &= ~ePleasant;
                DATA.value.weatherType &= ~eCloudy;
                DATA.value.weatherType &= ~eRainy;
                DATA.value.weatherType &= ~eSnow;
                }
            }
        bool IsSnow()
            {
            return (DATA.value.weatherType & eSnow) != 0;
            }
        void IsSnow(bool value)
            {
            if(value)
                {
                DATA.value.weatherType &= ~ePleasant;
                DATA.value.weatherType &= ~eCloudy;
                DATA.value.weatherType &= ~eRainy;
                DATA.value.weatherType |= eSnow;
                }
            else if(IsSnow())
                {
                DATA.value.weatherType &= ~ePleasant;
                DATA.value.weatherType &= ~eCloudy;
                DATA.value.weatherType &= ~eRainy;
                DATA.value.weatherType &= ~eSnow;
                }
            }
        bool IsNone()
            {
            return IsPleasant() == false && IsCloudy() == false && IsRainy() == false && IsSnow() == false;
            }
        void IsNone(bool value)
            {
            if(value)
                {
                DATA.value.weatherType &= ~ePleasant;
                DATA.value.weatherType &= ~eCloudy;
                DATA.value.weatherType &= ~eRainy;
                DATA.value.weatherType &= ~eSnow;
                }
            else if(IsNone())
                {
                DATA.value.weatherType |= ePleasant;
                DATA.value.weatherType &= ~eCloudy;
                DATA.value.weatherType &= ~eRainy;
                DATA.value.weatherType &= ~eSnow;
                }
            }
        bool IsUnk1()
            {
            return (DATA.value.weatherType & fUnk1) != 0;
            }
        void IsUnk1(bool value)
            {
            if(value)
                DATA.value.weatherType |= fUnk1;
            else
                DATA.value.weatherType &= ~fUnk1;
            }
        bool IsUnk2()
            {
            return (DATA.value.weatherType & fUnk2) != 0;
            }
        void IsUnk2(bool value)
            {
            if(value)
                DATA.value.weatherType |= fUnk2;
            else
                DATA.value.weatherType &= ~fUnk2;
            }
        bool IsType(unsigned char Type)
            {
            return (DATA.value.weatherType == Type);
            }
        void SetType(unsigned char Type)
            {
            DATA.value.weatherType = Type;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (DATA.value.weatherType & Mask) == Mask;
            else
                return (DATA.value.weatherType & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            DATA.value.weatherType = Mask;
            }

    };
