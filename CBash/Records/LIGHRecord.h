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

class LIGHRecord : public Record
    {
    private:
        enum LIGHRecordFields {
            eEDID = 0x44494445,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eSCRI = 0x49524353,
            eFULL = 0x4C4C5546,
            eICON = 0x4E4F4349,
            eDATA = 0x41544144,

            eFNAM = 0x4D414E46,
            eSNAM = 0x4D414E53
            };
        struct LIGHDATA
            {
            int duration;
            unsigned int radius;
            GENCLR color;
            unsigned int flags;
            float falloff, fov;
            unsigned int value;
            float weight;
            LIGHDATA():duration(0), radius(0),
                flags(0), falloff(0.0f), fov(0.0f),
                value(0), weight(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("duration = %i\n", duration);
                    PrintIndent(indentation);
                    printf("radius   = %u\n", radius);
                    PrintIndent(indentation);
                    printf("color:\n");
                    color.Debug(debugLevel, indentation);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags    = %u\n", flags);
                        }
                    PrintIndent(indentation);
                    printf("falloff  = %f\n", falloff);
                    PrintIndent(indentation);
                    printf("fov      = %f\n", fov);
                    PrintIndent(indentation);
                    printf("value    = %u\n", value);
                    PrintIndent(indentation);
                    printf("weight   = %f\n", weight);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct LIGHFNAM
            {
            float fade;
            LIGHFNAM():fade(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("fade = %f\n", fade);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        enum flagsFlags
            {
            fIsDynamic      = 0x00000001,
            fIsCanTake      = 0x00000002,
            fIsNegative     = 0x00000004,
            fIsFlickers     = 0x00000008,
            fIsOffByDefault = 0x00000020,
            fIsFlickerSlow  = 0x00000040,
            fIsPulse        = 0x00000080,
            fIsPulseSlow    = 0x00000100,
            fIsSpotLight    = 0x00000200,
            fIsSpotShadow   = 0x00000400
            };
        STRING EDID;
        GENMODEL MODL;
        OptRecordField<GENFID> SCRI;
        STRING FULL;
        STRING ICON;
        ReqRecordField<LIGHDATA> DATA;
        OptRecordField<LIGHFNAM> FNAM;
        OptRecordField<GENFID> SNAM;

        LIGHRecord(bool newRecord=false):Record(newRecord) {}
        LIGHRecord(const unsigned int &newFormID):Record(newFormID) {}
        LIGHRecord(LIGHRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
            SCRI = srcRecord->SCRI;
            FULL = srcRecord->FULL;
            ICON = srcRecord->ICON;
            DATA = srcRecord->DATA;
            FNAM = srcRecord->FNAM;
            SNAM = srcRecord->SNAM;
            return;
            }
        ~LIGHRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            MODL.MODB.Unload();
            MODL.MODL.Unload();
            MODL.MODT.Unload();
            SCRI.Unload();
            FULL.Unload();
            ICON.Unload();
            DATA.Unload();
            FNAM.Unload();
            SNAM.Unload();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(SCRI.IsLoaded())
                FormIDs.push_back(&SCRI->fid);
            if(SNAM.IsLoaded())
                FormIDs.push_back(&SNAM->fid);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eLIGH;}
        char * GetStrType() {return "LIGH";}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
        bool IsDynamic()
            {
            return (DATA.value.flags & fIsDynamic) != 0;
            }
        void IsDynamic(bool value)
            {
            if(value)
                DATA.value.flags |= fIsDynamic;
            else
                DATA.value.flags &= ~fIsDynamic;
            }
        bool IsCanTake()
            {
            return (DATA.value.flags & fIsCanTake) != 0;
            }
        void IsCanTake(bool value)
            {
            if(value)
                DATA.value.flags |= fIsCanTake;
            else
                DATA.value.flags &= ~fIsCanTake;
            }
        bool IsTakeable()
            {
            return (DATA.value.flags & fIsCanTake) != 0;
            }
        void IsTakeable(bool value)
            {
            if(value)
                DATA.value.flags |= fIsCanTake;
            else
                DATA.value.flags &= ~fIsCanTake;
            }
        bool IsNegative()
            {
            return (DATA.value.flags & fIsNegative) != 0;
            }
        void IsNegative(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNegative;
            else
                DATA.value.flags &= ~fIsNegative;
            }
        bool IsFlickers()
            {
            return (DATA.value.flags & fIsFlickers) != 0;
            }
        void IsFlickers(bool value)
            {
            if(value)
                DATA.value.flags |= fIsFlickers;
            else
                DATA.value.flags &= ~fIsFlickers;
            }
        bool IsOffByDefault()
            {
            return (DATA.value.flags & fIsOffByDefault) != 0;
            }
        void IsOffByDefault(bool value)
            {
            if(value)
                DATA.value.flags |= fIsOffByDefault;
            else
                DATA.value.flags &= ~fIsOffByDefault;
            }
        bool IsFlickerSlow()
            {
            return (DATA.value.flags & fIsFlickerSlow) != 0;
            }
        void IsFlickerSlow(bool value)
            {
            if(value)
                DATA.value.flags |= fIsFlickerSlow;
            else
                DATA.value.flags &= ~fIsFlickerSlow;
            }
        bool IsPulse()
            {
            return (DATA.value.flags & fIsPulse) != 0;
            }
        void IsPulse(bool value)
            {
            if(value)
                DATA.value.flags |= fIsPulse;
            else
                DATA.value.flags &= ~fIsPulse;
            }
        bool IsPulseSlow()
            {
            return (DATA.value.flags & fIsPulseSlow) != 0;
            }
        void IsPulseSlow(bool value)
            {
            if(value)
                DATA.value.flags |= fIsPulseSlow;
            else
                DATA.value.flags &= ~fIsPulseSlow;
            }
        bool IsSpotLight()
            {
            return (DATA.value.flags & fIsSpotLight) != 0;
            }
        void IsSpotLight(bool value)
            {
            if(value)
                DATA.value.flags |= fIsSpotLight;
            else
                DATA.value.flags &= ~fIsSpotLight;
            }
        bool IsSpotShadow()
            {
            return (DATA.value.flags & fIsSpotShadow) != 0;
            }
        void IsSpotShadow(bool value)
            {
            if(value)
                DATA.value.flags |= fIsSpotShadow;
            else
                DATA.value.flags &= ~fIsSpotShadow;
            }
        bool IsFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned int Mask)
            {
            DATA.value.flags = Mask;
            }
    };
