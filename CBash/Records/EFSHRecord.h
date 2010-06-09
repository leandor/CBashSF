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

class EFSHRecord : public Record
    {
    private:
        enum EFSHRecordFields {
            eEDID = 0x44494445,
            eICON = 0x4E4F4349,
            eICO2 = 0x324F4349,
            eDATA = 0x41544144
            };
        struct EFSHDATA
            {
            unsigned char flags, unused1[3];
            unsigned int memSBlend, memBlendOp, memZFunc;
            GENCLR fill;
            float fillAIn, fillAFull, fillAOut, fillAPRatio, fillAAmp,
                fillAFreq, fillAnimSpdU, fillAnimSpdV, edgeOff;
            GENCLR edge;
            float edgeAIn, edgeAFull, edgeAOut, edgeAPRatio, edgeAAmp,
                edgeAFreq,  fillAFRatio, edgeAFRatio;
            unsigned int memDBlend, partSBlend, partBlendOp, partZFunc, partDBlend;
            float partBUp, partBFull, partBDown, partBFRatio, partBPRatio, partLTime,
                partLDelta, partNSpd, partNAcc, partVel1, partVel2, partVel3,
                partAcc1, partAcc2, partAcc3, partKey1, partKey2, partKey1Time,
                partKey2Time;
            GENCLR key1;
            GENCLR key2;
            GENCLR key3;
            float key1A, key2A, key3A, key1Time, key2Time, key3Time;
            EFSHDATA():flags(0),
                memSBlend(5), memBlendOp(1), memZFunc(3),
                fillAIn(0.0f), fillAFull(0.0f), fillAOut(0.0f),
                fillAPRatio(0.0f), fillAAmp(0.0f),  fillAFreq(1.0f),
                fillAnimSpdU(0.0f), fillAnimSpdV(0.0f), edgeOff(1.0f),
                edgeAIn(0.0f), edgeAFull(0.0f), edgeAOut(0.0f),
                edgeAPRatio(0.0f), edgeAAmp(0.0f), edgeAFreq(1.0f),
                fillAFRatio(1.0f), edgeAFRatio(1.0f),
                memDBlend(6), partSBlend(5), partBlendOp(1), partZFunc(4), partDBlend(6),
                partBUp(0.0f), partBFull(0.0f), partBDown(0.0f), partBFRatio(1.0f),
                partBPRatio(1.0f), partLTime(1.0f), partLDelta(0.0f),
                partNSpd(0.0f), partNAcc(0.0f), partVel1(0.0f),
                partVel2(0.0f), partVel3(0.0f), partAcc1(0.0f),
                partAcc2(0.0f), partAcc3(0.0f), partKey1(1.0f),
                partKey2(1.0f), partKey1Time(0.0f), partKey2Time(1.0f),
                key1(255, 255, 255, 0x00),
                key2(255, 255, 255, 0x00),
                key3(255, 255, 255, 0x00),
                key1A(1.0f), key2A(1.0f), key3A(1.0f), key1Time(0.0f),
                key2Time(0.5f), key3Time(1.0f)
                {
                memset(&unused1, 0xCD, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags        = %u\n", flags);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1      = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                        }
                    PrintIndent(indentation);
                    printf("memSBlend    = %u\n", memSBlend);
                    PrintIndent(indentation);
                    printf("memBlendOp   = %u\n", memBlendOp);
                    PrintIndent(indentation);
                    printf("memZFunc     = %u\n", memZFunc);
                    PrintIndent(indentation);
                    printf("fill:\n");
                    fill.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("fillAIn      = %f\n", fillAIn);
                    PrintIndent(indentation);
                    printf("fillAFull    = %f\n", fillAFull);
                    PrintIndent(indentation);
                    printf("fillAOut     = %f\n", fillAOut);
                    PrintIndent(indentation);
                    printf("fillAPRatio  = %f\n", fillAPRatio);
                    PrintIndent(indentation);
                    printf("fillAAmp     = %f\n", fillAAmp);
                    PrintIndent(indentation);
                    printf("fillAFreq    = %f\n", fillAFreq);
                    PrintIndent(indentation);
                    printf("fillAnimSpdU = %f\n", fillAnimSpdU);
                    PrintIndent(indentation);
                    printf("fillAnimSpdV = %f\n", fillAnimSpdV);
                    PrintIndent(indentation);
                    printf("edge:\n");
                    edge.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("edgeAIn      = %f\n", edgeAIn);
                    PrintIndent(indentation);
                    printf("edgeAFull    = %f\n", edgeAFull);
                    PrintIndent(indentation);
                    printf("edgeAOut     = %f\n", edgeAOut);
                    PrintIndent(indentation);
                    printf("edgeAPRatio  = %f\n", edgeAPRatio);
                    PrintIndent(indentation);
                    printf("edgeAAmp     = %f\n", edgeAAmp);
                    PrintIndent(indentation);
                    printf("edgeAFreq    = %f\n", edgeAFreq);
                    PrintIndent(indentation);
                    printf("fillAFRatio  = %f\n", fillAFRatio);
                    PrintIndent(indentation);
                    printf("edgeAFRatio  = %f\n", edgeAFRatio);
                    PrintIndent(indentation);
                    printf("memDBlend    = %u\n", memDBlend);
                    PrintIndent(indentation);
                    printf("partSBlend   = %u\n", partSBlend);
                    PrintIndent(indentation);
                    printf("partBlendOp  = %u\n", partBlendOp);
                    PrintIndent(indentation);
                    printf("partZFunc    = %u\n", partZFunc);
                    PrintIndent(indentation);
                    printf("partDBlend   = %u\n", partDBlend);
                    PrintIndent(indentation);
                    printf("partBUp      = %f\n", partBUp);
                    PrintIndent(indentation);
                    printf("partBFull    = %f\n", partBFull);
                    PrintIndent(indentation);
                    printf("partBDown    = %f\n", partBDown);
                    PrintIndent(indentation);
                    printf("partBFRatio  = %f\n", partBFRatio);
                    PrintIndent(indentation);
                    printf("partBPRatio  = %f\n", partBPRatio);
                    PrintIndent(indentation);
                    printf("partLTime    = %f\n", partLTime);
                    PrintIndent(indentation);
                    printf("partLDelta   = %f\n", partLDelta);
                    PrintIndent(indentation);
                    printf("partNSpd     = %f\n", partNSpd);
                    PrintIndent(indentation);
                    printf("partNAcc     = %f\n", partNAcc);
                    PrintIndent(indentation);
                    printf("partVel1     = %f\n", partVel1);
                    PrintIndent(indentation);
                    printf("partVel2     = %f\n", partVel2);
                    PrintIndent(indentation);
                    printf("partVel3     = %f\n", partVel3);
                    PrintIndent(indentation);
                    printf("partAcc1     = %f\n", partAcc1);
                    PrintIndent(indentation);
                    printf("partAcc2     = %f\n", partAcc2);
                    PrintIndent(indentation);
                    printf("partAcc3     = %f\n", partAcc3);
                    PrintIndent(indentation);
                    printf("partKey1     = %f\n", partKey1);
                    PrintIndent(indentation);
                    printf("partKey2     = %f\n", partKey2);
                    PrintIndent(indentation);
                    printf("partKey1Time = %f\n", partKey1Time);
                    PrintIndent(indentation);
                    printf("partKey2Time = %f\n", partKey2Time);
                    PrintIndent(indentation);
                    printf("key1:\n");
                    key1.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("key2:\n");
                    key2.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("key3:\n");
                    key3.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("key1A        = %f\n", key1A);
                    PrintIndent(indentation);
                    printf("key2A        = %f\n", key2A);
                    PrintIndent(indentation);
                    printf("key3A        = %f\n", key3A);
                    PrintIndent(indentation);
                    printf("key1Time     = %f\n", key1Time);
                    PrintIndent(indentation);
                    printf("key2Time     = %f\n", key2Time);
                    PrintIndent(indentation);
                    printf("key3Time     = %f\n", key3Time);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        enum flagsFlags
            {
            fIsNoMemShader  = 0x00000001,
            fIsNoPartShader = 0x00000008,
            fIsEdgeInverse  = 0x00000010,
            fIsMemSkinOnly  = 0x00000020
            };
        STRING EDID;
        STRING ICON;
        STRING ICO2;
        ReqRecordField<EFSHDATA> DATA;

        EFSHRecord(bool newRecord=false):Record(newRecord) {}
        EFSHRecord(const unsigned int &newFormID):Record(newFormID) {}
        EFSHRecord(EFSHRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            ICON = srcRecord->ICON;
            ICO2 = srcRecord->ICO2;
            DATA = srcRecord->DATA;
            return;
            }
        ~EFSHRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            ICON.Unload();
            ICO2.Unload();
            DATA.Unload();
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eEFSH;}
        char * GetStrType() {return "EFSH";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsNoMemShader()
            {
            return (DATA.value.flags & fIsNoMemShader) != 0;
            }
        void IsNoMemShader(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNoMemShader;
            else
                DATA.value.flags &= ~fIsNoMemShader;
            }
        bool IsNoMembraneShader()
            {
            return (DATA.value.flags & fIsNoMemShader) != 0;
            }
        void IsNoMembraneShader(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNoMemShader;
            else
                DATA.value.flags &= ~fIsNoMemShader;
            }
        bool IsNoPartShader()
            {
            return (DATA.value.flags & fIsNoPartShader) != 0;
            }
        void IsNoPartShader(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNoPartShader;
            else
                DATA.value.flags &= ~fIsNoPartShader;
            }
        bool IsNoParticleShader()
            {
            return (DATA.value.flags & fIsNoPartShader) != 0;
            }
        void IsNoParticleShader(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNoPartShader;
            else
                DATA.value.flags &= ~fIsNoPartShader;
            }
        bool IsEdgeInverse()
            {
            return (DATA.value.flags & fIsEdgeInverse) != 0;
            }
        void IsEdgeInverse(bool value)
            {
            if(value)
                DATA.value.flags |= fIsEdgeInverse;
            else
                DATA.value.flags &= ~fIsEdgeInverse;
            }
        bool IsEdgeEffectInverse()
            {
            return (DATA.value.flags & fIsEdgeInverse) != 0;
            }
        void IsEdgeEffectInverse(bool value)
            {
            if(value)
                DATA.value.flags |= fIsEdgeInverse;
            else
                DATA.value.flags &= ~fIsEdgeInverse;
            }
        bool IsMemSkinOnly()
            {
            return (DATA.value.flags & fIsMemSkinOnly) != 0;
            }
        void IsMemSkinOnly(bool value)
            {
            if(value)
                DATA.value.flags |= fIsMemSkinOnly;
            else
                DATA.value.flags &= ~fIsMemSkinOnly;
            }
        bool IsMembraneShaderSkinOnly()
            {
            return (DATA.value.flags & fIsMemSkinOnly) != 0;
            }
        void IsMembraneShaderSkinOnly(bool value)
            {
            if(value)
                DATA.value.flags |= fIsMemSkinOnly;
            else
                DATA.value.flags &= ~fIsMemSkinOnly;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            DATA.value.flags = Mask;
            }
    };
