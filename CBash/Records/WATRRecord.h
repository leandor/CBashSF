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

class WATRRecord : public Record
    {
    private:
        enum WATRSubRecords {
            eEDID = 0x44494445,
            eTNAM = 0x4D414E54,
            eANAM = 0x4D414E41,
            eFNAM = 0x4D414E46,
            eMNAM = 0x4D414E4D,
            eSNAM = 0x4D414E53,
            eDATA = 0x41544144,
            eGNAM = 0x4D414E47
            };
        struct WATRANAM
            {
            unsigned char opacity;
            WATRANAM():opacity(75) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("opacity  = %u\n", opacity);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const WATRANAM &other) const
                {
                return (opacity == other.opacity);
                }
            bool operator !=(const WATRANAM &other) const
                {
                return !(*this == other);
                }
            };
        struct WATRDATA
            {
            float windVelocity, windDirection, waveAmp, waveFreq, sunPower,
                reflectAmt, fresnelAmt, xSpeed, ySpeed, fogNear, fogFar;
            GENCLR shallow;
            GENCLR deep;
            GENCLR refl;

            unsigned char blend, unused1[3];
            float rainForce, rainVelocity, rainFalloff, rainDampner,
                rainSize, dispForce, dispVelocity, dispFalloff,
                dispDampner, dispSize;
            unsigned short damage;
            WATRDATA():windVelocity(0.1f), windDirection(90.0f), waveAmp(0.5f),
                waveFreq(1.0f), sunPower(50.0f),
                reflectAmt(0.5f), fresnelAmt(0.025f), xSpeed(0.0f), ySpeed(0.0f),
                fogNear(27852.801f), fogFar(163840.0f),
                shallow(0, 128, 128, 0),
                deep(0, 0, 25, 0),
                refl(255, 255, 255, 0),
                blend(50),
                rainForce(0.1f), rainVelocity(0.6f), rainFalloff(0.985f), rainDampner(2.0f),
                rainSize(0.01f), dispForce(0.4f), dispVelocity(0.6f), dispFalloff(0.985f),
                dispDampner(10.0f), dispSize(0.05f), damage(0)
                {
                memset(&unused1, 0xCD, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("windVelocity  = %f\n", windVelocity);
                    PrintIndent(indentation);
                    printf("windDirection = %f\n", windDirection);
                    PrintIndent(indentation);
                    printf("waveAmp       = %f\n", waveAmp);
                    PrintIndent(indentation);
                    printf("waveFreq      = %f\n", waveFreq);
                    PrintIndent(indentation);
                    printf("sunPower      = %f\n", sunPower);
                    PrintIndent(indentation);
                    printf("reflectAmt    = %f\n", reflectAmt);
                    PrintIndent(indentation);
                    printf("fresnelAmt    = %f\n", fresnelAmt);
                    PrintIndent(indentation);
                    printf("xSpeed        = %f\n", xSpeed);
                    PrintIndent(indentation);
                    printf("ySpeed        = %f\n", ySpeed);
                    PrintIndent(indentation);
                    printf("fogNear       = %f\n", fogNear);
                    PrintIndent(indentation);
                    printf("fogFar        = %f\n", fogFar);
                    PrintIndent(indentation);
                    printf("shallow:\n");
                    shallow.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("deep:\n");
                    deep.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("refl:\n");
                    refl.Debug(debugLevel, indentation);

                    PrintIndent(indentation);
                    printf("blend         = %u\n", blend);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1       = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                        }
                    PrintIndent(indentation);
                    printf("rainForce     = %f\n", rainForce);
                    PrintIndent(indentation);
                    printf("rainVelocity  = %f\n", rainVelocity);
                    PrintIndent(indentation);
                    printf("rainFalloff   = %f\n", rainFalloff);
                    PrintIndent(indentation);
                    printf("rainDampner   = %f\n", rainDampner);
                    PrintIndent(indentation);
                    printf("rainSize      = %f\n", rainSize);
                    PrintIndent(indentation);
                    printf("dispForce     = %f\n", dispForce);
                    PrintIndent(indentation);
                    printf("dispVelocity  = %f\n", dispVelocity);
                    PrintIndent(indentation);
                    printf("dispFalloff   = %f\n", dispFalloff);
                    PrintIndent(indentation);
                    printf("dispDampner   = %f\n", dispDampner);
                    PrintIndent(indentation);
                    printf("dispSize      = %f\n", dispSize);
                    PrintIndent(indentation);
                    printf("damage        = %u\n", damage);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const WATRDATA &other) const
                {
                return (AlmostEqual(windVelocity,other.windVelocity,2) &&
                        AlmostEqual(windDirection,other.windDirection,2) &&
                        AlmostEqual(waveAmp,other.waveAmp,2) &&
                        AlmostEqual(waveFreq,other.waveFreq,2) &&
                        AlmostEqual(sunPower,other.sunPower,2) &&
                        AlmostEqual(reflectAmt,other.reflectAmt,2) &&
                        AlmostEqual(fresnelAmt,other.fresnelAmt,2) &&
                        AlmostEqual(xSpeed,other.xSpeed,2) &&
                        AlmostEqual(ySpeed,other.ySpeed,2) &&
                        AlmostEqual(fogNear,other.fogNear,2) &&
                        AlmostEqual(fogFar,other.fogFar,2) &&
                        shallow == other.shallow &&
                        deep == other.deep &&
                        refl == other.refl &&
                        blend == other.blend &&
                        AlmostEqual(rainForce,other.rainForce,2) &&
                        AlmostEqual(rainVelocity,other.rainVelocity,2) &&
                        AlmostEqual(rainFalloff,other.rainFalloff,2) &&
                        AlmostEqual(rainDampner,other.rainDampner,2) &&
                        AlmostEqual(rainSize,other.rainSize,2) &&
                        AlmostEqual(dispForce,other.dispForce,2) &&
                        AlmostEqual(dispVelocity,other.dispVelocity,2) &&
                        AlmostEqual(dispFalloff,other.dispFalloff,2) &&
                        AlmostEqual(dispDampner,other.dispDampner,2) &&
                        AlmostEqual(dispSize,other.dispSize,2) &&
                        damage == other.damage);
                }
            bool operator !=(const WATRDATA &other) const
                {
                return !(*this == other);
                }
            };
        struct WATRGNAM
            {
            unsigned int dayWater, nightWater, underWater;
            WATRGNAM():dayWater(0), nightWater(0), underWater(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("dayWater   = %s\n", PrintFormID(dayWater));
                    PrintIndent(indentation);
                    printf("nightWater = %s\n", PrintFormID(nightWater));
                    PrintIndent(indentation);
                    printf("underWater = %s\n", PrintFormID(underWater));
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const WATRGNAM &other) const
                {
                return (dayWater == other.dayWater &&
                        nightWater == other.nightWater &&
                        underWater == other.underWater);
                }
            bool operator !=(const WATRGNAM &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum flagsFlags
            {
            fIsCausesDmg  = 0x00000001,
            fIsReflective = 0x00000002
            };
        STRING EDID;
        ISTRING TNAM;
        ReqSubRecord<WATRANAM> ANAM;
        ReqSubRecord<GENFLAG> FNAM;
        ISTRING MNAM;
        OptSubRecord<GENFID> SNAM;
        OptSubRecord<WATRDATA> DATA;
        OptSubRecord<WATRGNAM> GNAM;

        WATRRecord(bool newRecord=false):Record(newRecord) {}
        WATRRecord(const unsigned int &newFormID):Record(newFormID) {}
        WATRRecord(WATRRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            TNAM = srcRecord->TNAM;
            ANAM = srcRecord->ANAM;
            FNAM = srcRecord->FNAM;
            MNAM = srcRecord->MNAM;
            SNAM = srcRecord->SNAM;
            DATA = srcRecord->DATA;
            GNAM = srcRecord->GNAM;
            return;
            }
        ~WATRRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            TNAM.Unload();
            ANAM.Unload();
            FNAM.Unload();
            MNAM.Unload();
            SNAM.Unload();
            DATA.Unload();
            GNAM.Unload();
            }

        void VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return;
            if(SNAM.IsLoaded())
                op.Accept(SNAM->fid);
            if(GNAM.IsLoaded())
                {
                op.Accept(GNAM->dayWater);
                op.Accept(GNAM->nightWater);
                op.Accept(GNAM->underWater);
                }
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(const unsigned int Field, char *FieldValue);
        void SetField(const unsigned int Field, unsigned char FieldValue);
        void SetOtherField(const unsigned int Field, unsigned int FieldValue);
        void SetField(const unsigned int Field, float FieldValue);
        void SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(const unsigned int Field, unsigned short FieldValue);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eWATR;}
        char * GetStrType() {return "WATR";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsCausesDmg()
            {
            return (FNAM.value.flags & fIsCausesDmg) != 0;
            }
        void IsCausesDmg(bool value)
            {
            if(value)
                FNAM.value.flags |= fIsCausesDmg;
            else
                FNAM.value.flags &= ~fIsCausesDmg;
            }
        bool IsCausesDamage()
            {
            return (FNAM.value.flags & fIsCausesDmg) != 0;
            }
        void IsCausesDamage(bool value)
            {
            if(value)
                FNAM.value.flags |= fIsCausesDmg;
            else
                FNAM.value.flags &= ~fIsCausesDmg;
            }
        bool IsReflective()
            {
            return (FNAM.value.flags & fIsReflective) != 0;
            }
        void IsReflective(bool value)
            {
            if(value)
                FNAM.value.flags |= fIsReflective;
            else
                FNAM.value.flags &= ~fIsReflective;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (FNAM.value.flags & Mask) == Mask;
            else
                return (FNAM.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            FNAM.value.flags = Mask;
            }
    };
