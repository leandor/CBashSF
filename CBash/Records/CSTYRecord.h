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

class CSTYRecord : public Record
    {
    private:
        enum CSTYRecordFields {
            eEDID = 0x44494445,
            eCSTD = 0x44545343,
            eCSAD = 0x44415343
            };
        struct CSTYCSTD
            {
            unsigned char dodgeChance, lrChance, unused1[2];
            float lrTimerMin, lrTimerMax, forTimerMin, forTimerMax,
                backTimerMin, backTimerMax, idleTimerMin, idleTimerMax;
            unsigned char blkChance, atkChance, unused2[2];
            float atkBRecoil, atkBUnc, atkBh2h;
            unsigned char pAtkChance, unused3[3];
            float pAtkBRecoil, pAtkBUnc;
            unsigned char pAtkNormal, pAtkFor, pAtkBack, pAtkL, pAtkR, unused4[3];
            float holdTimerMin, holdTimerMax;
            unsigned char flagsA, acroDodge, unused5[2];
            float rMultOpt, rMultMax, mDistance, rDistance, buffStand, rStand, groupStand;
            unsigned char rushChance, unused6[3];
            float rushMult;
            unsigned int flagsB;
            CSTYCSTD():dodgeChance(75), lrChance(50),
                lrTimerMin(0.5f), lrTimerMax(1.5f), forTimerMin(0.5f), forTimerMax(1.0f),
                backTimerMin(0.25f), backTimerMax(0.75f), idleTimerMin(0.5f), idleTimerMax(1.5f),
                blkChance(30), atkChance(40),
                atkBRecoil(5.0f), atkBUnc(5.0f), atkBh2h(5.0f),
                pAtkChance(25),
                pAtkBRecoil(5.0f), pAtkBUnc(5.0f),
                pAtkNormal(20), pAtkFor(20), pAtkBack(20), pAtkL(20), pAtkR(20),
                holdTimerMin(0.5f), holdTimerMax(1.5f),
                flagsA(0), acroDodge(0),
                rMultOpt(1.0f), rMultMax(1.0f), mDistance(250.0f),
                rDistance(1000.0f), buffStand(325.0f), rStand(500.0f),
                groupStand(325.0f),
                rushChance(25), rushMult(1.0f), flagsB(0)
                {
                 memset(&unused1, 0xCD, 2);
                 memset(&unused2, 0xCD, 2);
                 memset(&unused3, 0xCD, 3);
                 memset(&unused4, 0xCD, 3);
                 memset(&unused5, 0xCD, 2);
                 memset(&unused6, 0xCD, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("dodgeChance  = %u\n", dodgeChance);
                    PrintIndent(indentation);
                    printf("lrChance     = %u\n", lrChance);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1      = %02X%02X\n", unused1[0], unused1[1]);
                        }
                    PrintIndent(indentation);
                    printf("lrTimerMin   = %f\n", lrTimerMin);
                    PrintIndent(indentation);
                    printf("lrTimerMax   = %f\n", lrTimerMax);
                    PrintIndent(indentation);
                    printf("forTimerMin  = %f\n", forTimerMin);
                    PrintIndent(indentation);
                    printf("forTimerMax  = %f\n", forTimerMax);
                    PrintIndent(indentation);
                    printf("backTimerMin = %f\n", backTimerMin);
                    PrintIndent(indentation);
                    printf("backTimerMax = %f\n", backTimerMax);
                    PrintIndent(indentation);
                    printf("idleTimerMin = %f\n", idleTimerMin);
                    PrintIndent(indentation);
                    printf("idleTimerMax = %f\n", idleTimerMax);
                    PrintIndent(indentation);
                    printf("blkChance    = %u\n", blkChance);
                    PrintIndent(indentation);
                    printf("atkChance    = %u\n", atkChance);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused2      = %02X%02X\n", unused2[0], unused2[1]);
                        }
                    PrintIndent(indentation);
                    printf("atkBRecoil   = %f\n", atkBRecoil);
                    PrintIndent(indentation);
                    printf("atkBUnc      = %f\n", atkBUnc);
                    PrintIndent(indentation);
                    printf("atkBh2h      = %f\n", atkBh2h);
                    PrintIndent(indentation);
                    printf("pAtkChance   = %u\n", pAtkChance);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused3      = %02X%02X%02X\n", unused3[0], unused3[1], unused3[2]);
                        }
                    PrintIndent(indentation);
                    printf("pAtkBRecoil  = %f\n", pAtkBRecoil);
                    PrintIndent(indentation);
                    printf("pAtkBUnc     = %f\n", pAtkBUnc);
                    PrintIndent(indentation);
                    printf("pAtkNormal   = %u\n", pAtkNormal);
                    PrintIndent(indentation);
                    printf("pAtkFor      = %u\n", pAtkFor);
                    PrintIndent(indentation);
                    printf("pAtkBack     = %u\n", pAtkBack);
                    PrintIndent(indentation);
                    printf("pAtkL        = %u\n", pAtkL);
                    PrintIndent(indentation);
                    printf("pAtkR        = %u\n", pAtkR);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused4      = %02X%02X%02X\n", unused4[0], unused4[1], unused4[2]);
                        }
                    PrintIndent(indentation);
                    printf("holdTimerMin = %f\n", holdTimerMin);
                    PrintIndent(indentation);
                    printf("holdTimerMax = %f\n", holdTimerMax);
                    PrintIndent(indentation);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flagsA       = %u\n", flagsA);
                        }
                    PrintIndent(indentation);
                    printf("acroDodge    = %u\n", acroDodge);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused5      = %02X%02X\n", unused5[0], unused5[1]);
                        }
                    PrintIndent(indentation);
                    printf("rMultOpt     = %f\n", rMultOpt);
                    PrintIndent(indentation);
                    printf("rMultMax     = %f\n", rMultMax);
                    PrintIndent(indentation);
                    printf("mDistance    = %f\n", mDistance);
                    PrintIndent(indentation);
                    printf("rDistance    = %f\n", rDistance);
                    PrintIndent(indentation);
                    printf("buffStand    = %f\n", buffStand);
                    PrintIndent(indentation);
                    printf("rStand       = %f\n", rStand);
                    PrintIndent(indentation);
                    printf("groupStand   = %f\n", groupStand);
                    PrintIndent(indentation);
                    printf("rushChance   = %u\n", rushChance);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused6      = %02X%02X%02X\n", unused6[0], unused6[1], unused6[2]);
                        }
                    PrintIndent(indentation);
                    printf("rushMult     = %f\n", rushMult);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flagsB       = %u\n", flagsB);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CSTYCSTD &other) const
                {
                return (dodgeChance == other.dodgeChance && 
                        lrChance == other.lrChance && 
                        AlmostEqual(lrTimerMin,other.lrTimerMin,2) && 
                        AlmostEqual(lrTimerMax,other.lrTimerMax,2) && 
                        AlmostEqual(forTimerMin,other.forTimerMin,2) && 
                        AlmostEqual(forTimerMax,other.forTimerMax,2) && 
                        AlmostEqual(backTimerMin,other.backTimerMin,2) &&                         
                        AlmostEqual(backTimerMax,other.backTimerMax,2) && 
                        AlmostEqual(idleTimerMin,other.idleTimerMin,2) && 
                        AlmostEqual(idleTimerMax,other.idleTimerMax,2) && 
                        blkChance == other.blkChance && 
                        atkChance == other.atkChance && 
                        AlmostEqual(atkBRecoil,other.atkBRecoil,2) && 
                        AlmostEqual(atkBUnc,other.atkBUnc,2) && 
                        AlmostEqual(atkBh2h,other.atkBh2h,2) && 
                        pAtkChance == other.pAtkChance && 
                        AlmostEqual(pAtkBRecoil,other.pAtkBRecoil,2) && 
                        AlmostEqual(pAtkBUnc,other.pAtkBUnc,2) && 
                        pAtkNormal == other.pAtkNormal && 
                        pAtkFor == other.pAtkFor && 
                        pAtkBack == other.pAtkBack && 
                        pAtkL == other.pAtkL && 
                        pAtkR == other.pAtkR && 
                        AlmostEqual(holdTimerMin,other.holdTimerMin,2) && 
                        AlmostEqual(holdTimerMax,other.holdTimerMax,2) && 
                        flagsA == other.flagsA && 
                        acroDodge == other.acroDodge && 
                        AlmostEqual(rMultOpt,other.rMultOpt,2) && 
                        AlmostEqual(rMultMax,other.rMultMax,2) && 
                        AlmostEqual(mDistance,other.mDistance,2) && 
                        AlmostEqual(rDistance,other.rDistance,2) && 
                        AlmostEqual(buffStand,other.buffStand,2) && 
                        AlmostEqual(rStand,other.rStand,2) && 
                        AlmostEqual(groupStand,other.groupStand,2) && 
                        rushChance == other.rushChance && 
                        AlmostEqual(rushMult,other.rushMult,2) && 
                        flagsB == other.flagsB);
                }
            bool operator !=(const CSTYCSTD &other) const
                {
                return !(*this == other);
                }
            };

        struct CSTYCSAD
            {
            float dodgeFMult, dodgeFBase, encSBase, encSMult, dodgeAtkMult,
                dodgeNAtkMult, dodgeBAtkMult, dodgeBNAtkMult,
                dodgeFAtkMult, dodgeFNAtkMult, blockMult, blockBase,
                blockAtkMult, blockNAtkMult, atkMult, atkBase, atkAtkMult,
                atkNAtkMult, atkBlockMult, pAtkFBase, pAtkFMult;
            CSTYCSAD():dodgeFMult(-20.0f), dodgeFBase(0.0f), encSBase(-110.0f), encSMult(1.0f),
                dodgeAtkMult(1.0f), dodgeNAtkMult(0.75f),
                dodgeBAtkMult(1.0f), dodgeBNAtkMult(0.7f),
                dodgeFAtkMult(1.0f), dodgeFNAtkMult(0.5f),
                blockMult(20.0f), blockBase(0.0f), blockAtkMult(2.0f),
                blockNAtkMult(1.0f), atkMult(20.0f), atkBase(0.0f),
                atkAtkMult(0.75f), atkNAtkMult(1.0f), atkBlockMult(0.5f),
                pAtkFBase(5.0f), pAtkFMult(-10.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("dodgeFMult     = %f\n", dodgeFMult);
                    PrintIndent(indentation);
                    printf("dodgeFBase     = %f\n", dodgeFBase);
                    PrintIndent(indentation);
                    printf("encSBase       = %f\n", encSBase);
                    PrintIndent(indentation);
                    printf("encSMult       = %f\n", encSMult);
                    PrintIndent(indentation);
                    printf("dodgeAtkMult   = %f\n", dodgeAtkMult);
                    PrintIndent(indentation);
                    printf("dodgeNAtkMult  = %f\n", dodgeNAtkMult);
                    PrintIndent(indentation);
                    printf("dodgeBAtkMult  = %f\n", dodgeBAtkMult);
                    PrintIndent(indentation);
                    printf("dodgeBNAtkMult = %f\n", dodgeBNAtkMult);
                    PrintIndent(indentation);
                    printf("dodgeFAtkMult  = %f\n", dodgeFAtkMult);
                    PrintIndent(indentation);
                    printf("dodgeFNAtkMult = %f\n", dodgeFNAtkMult);
                    PrintIndent(indentation);
                    printf("blockMult      = %f\n", blockMult);
                    PrintIndent(indentation);
                    printf("blockBase      = %f\n", blockBase);
                    PrintIndent(indentation);
                    printf("blockAtkMult   = %f\n", blockAtkMult);
                    PrintIndent(indentation);
                    printf("blockNAtkMult  = %f\n", blockNAtkMult);
                    PrintIndent(indentation);
                    printf("atkMult        = %f\n", atkMult);
                    PrintIndent(indentation);
                    printf("atkBase        = %f\n", atkBase);
                    PrintIndent(indentation);
                    printf("atkAtkMult     = %f\n", atkAtkMult);
                    PrintIndent(indentation);
                    printf("atkNAtkMult    = %f\n", atkNAtkMult);
                    PrintIndent(indentation);
                    printf("atkBlockMult   = %f\n", atkBlockMult);
                    PrintIndent(indentation);
                    printf("pAtkFBase      = %f\n", pAtkFBase);
                    PrintIndent(indentation);
                    printf("pAtkFMult      = %f\n", pAtkFMult);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CSTYCSAD &other) const
                {
                return (AlmostEqual(dodgeFMult,other.dodgeFMult,2) && 
                        AlmostEqual(dodgeFBase,other.dodgeFBase,2) && 
                        AlmostEqual(encSBase,other.encSBase,2) && 
                        AlmostEqual(encSMult,other.encSMult,2) && 
                        AlmostEqual(dodgeAtkMult,other.dodgeAtkMult,2) && 
                        
                        AlmostEqual(dodgeNAtkMult,other.dodgeNAtkMult,2) && 
                        AlmostEqual(dodgeBAtkMult,other.dodgeBAtkMult,2) && 
                        AlmostEqual(dodgeBNAtkMult,other.dodgeBNAtkMult,2) && 
                        
                        AlmostEqual(dodgeFAtkMult,other.dodgeFAtkMult,2) && 
                        AlmostEqual(dodgeFNAtkMult,other.dodgeFNAtkMult,2) && 
                        AlmostEqual(blockMult,other.blockMult,2) && 
                        AlmostEqual(blockBase,other.blockBase,2) && 
                        
                        AlmostEqual(blockAtkMult,other.blockAtkMult,2) && 
                        AlmostEqual(blockNAtkMult,other.blockNAtkMult,2) && 
                        AlmostEqual(atkMult,other.atkMult,2) && 
                        AlmostEqual(atkBase,other.atkBase,2) && 
                        AlmostEqual(atkAtkMult,other.atkAtkMult,2) && 
                        
                        AlmostEqual(atkNAtkMult,other.atkNAtkMult,2) && 
                        AlmostEqual(atkBlockMult,other.atkBlockMult,2) && 
                        AlmostEqual(pAtkFBase,other.pAtkFBase,2) && 
                        AlmostEqual(pAtkFMult,other.pAtkFMult,2));
                }
            bool operator !=(const CSTYCSAD &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum flagsAFlags
            {
            fIsUseAdvanced        = 0x00000001,
            fIsUseChanceForAttack = 0x00000002,
            fIsIgnoreAllies       = 0x00000004,
            fIsWillYield          = 0x00000008,
            fIsRejectsYields      = 0x00000010,
            fIsFleeingDisabled    = 0x00000020,
            fIsPrefersRanged      = 0x00000040,
            fIsMeleeAlertOK       = 0x00000080
            };
        enum flagsBFlags
            {
            fIsDoNotAcquire       = 0x00000001
            };
        STRING EDID;
        ReqRecordField<CSTYCSTD> CSTD;
        OptRecordField<CSTYCSAD> CSAD;
        CSTYRecord(bool newRecord=false):Record(newRecord) {}
        CSTYRecord(const unsigned int &newFormID):Record(newFormID) {}
        CSTYRecord(CSTYRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            CSTD = srcRecord->CSTD;
            CSAD = srcRecord->CSAD;
            return;
            }
        ~CSTYRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            CSTD.Unload();
            CSAD.Unload();
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
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eCSTY;}
        char * GetStrType() {return "CSTY";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsUseAdvanced()
            {
            return (CSTD.value.flagsA & fIsUseAdvanced) != 0;
            }
        void IsUseAdvanced(bool value)
            {
            if(value)
                CSTD.value.flagsA |= fIsUseAdvanced;
            else
                CSTD.value.flagsA &= ~fIsUseAdvanced;
            }
        bool IsUseChanceForAttack()
            {
            return (CSTD.value.flagsA & fIsUseChanceForAttack) != 0;
            }
        void IsUseChanceForAttack(bool value)
            {
            if(value)
                CSTD.value.flagsA |= fIsUseChanceForAttack;
            else
                CSTD.value.flagsA &= ~fIsUseChanceForAttack;
            }
        bool IsIgnoreAllies()
            {
            return (CSTD.value.flagsA & fIsIgnoreAllies) != 0;
            }
        void IsIgnoreAllies(bool value)
            {
            if(value)
                CSTD.value.flagsA |= fIsIgnoreAllies;
            else
                CSTD.value.flagsA &= ~fIsIgnoreAllies;
            }
        bool IsWillYield()
            {
            return (CSTD.value.flagsA & fIsWillYield) != 0;
            }
        void IsWillYield(bool value)
            {
            if(value)
                CSTD.value.flagsA |= fIsWillYield;
            else
                CSTD.value.flagsA &= ~fIsWillYield;
            }
        bool IsRejectsYields()
            {
            return (CSTD.value.flagsA & fIsRejectsYields) != 0;
            }
        void IsRejectsYields(bool value)
            {
            if(value)
                CSTD.value.flagsA |= fIsRejectsYields;
            else
                CSTD.value.flagsA &= ~fIsRejectsYields;
            }
        bool IsFleeingDisabled()
            {
            return (CSTD.value.flagsA & fIsFleeingDisabled) != 0;
            }
        void IsFleeingDisabled(bool value)
            {
            if(value)
                CSTD.value.flagsA |= fIsFleeingDisabled;
            else
                CSTD.value.flagsA &= ~fIsFleeingDisabled;
            }
        bool IsPrefersRanged()
            {
            return (CSTD.value.flagsA & fIsPrefersRanged) != 0;
            }
        void IsPrefersRanged(bool value)
            {
            if(value)
                CSTD.value.flagsA |= fIsPrefersRanged;
            else
                CSTD.value.flagsA &= ~fIsPrefersRanged;
            }
        bool IsMeleeAlertOK()
            {
            return (CSTD.value.flagsA & fIsMeleeAlertOK) != 0;
            }
        void IsMeleeAlertOK(bool value)
            {
            if(value)
                CSTD.value.flagsA |= fIsMeleeAlertOK;
            else
                CSTD.value.flagsA &= ~fIsMeleeAlertOK;
            }
        bool IsFlagAMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (CSTD.value.flagsA & Mask) == Mask;
            else
                return (CSTD.value.flagsA & Mask) != 0;
            }
        void SetFlagAMask(unsigned char Mask)
            {
            CSTD.value.flagsA = Mask;
            }
        bool IsDoNotAcquire()
            {
            return (CSTD.value.flagsB & fIsDoNotAcquire) != 0;
            }
        void IsDoNotAcquire(bool value)
            {
            if(value)
                CSTD.value.flagsB |= fIsDoNotAcquire;
            else
                CSTD.value.flagsB &= ~fIsDoNotAcquire;
            }
        bool IsFlagBMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (CSTD.value.flagsB & Mask) == Mask;
            else
                return (CSTD.value.flagsB & Mask) != 0;
            }
        void SetFlagBMask(unsigned char Mask)
            {
            CSTD.value.flagsB = Mask;
            }
    };
