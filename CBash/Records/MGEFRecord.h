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

class MGEFRecord : public Record
    {
    private:
        enum MGEFRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,
            eDESC = 0x43534544,
            eICON = 0x4E4F4349,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eDATA = 0x41544144,
            eESCE = 0x45435345
            };
        struct MGEFDATA
            {
            unsigned int flags;
            float baseCost;
            unsigned int associated;
            int school, resistValue;
            unsigned short unk1;
            unsigned char unused1[2];
            unsigned int light;
            float projectileSpeed;
            unsigned int effectShader, enchantEffect, castingSound, boltSound, hitSound, areaSound;
            float cefEnchantment, cefBarter;
            MGEFDATA():flags(0), baseCost(0.0f), associated(0),
                school(0), resistValue(0), unk1(0),
                light(0), projectileSpeed(0.0f),
                effectShader(0), enchantEffect(0),
                castingSound(0), boltSound(0),
                hitSound(0), areaSound(0),
                cefEnchantment(0.0f),cefBarter(0.0f)
                {
                memset(&unused1, 0x00, 2);
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
                        printf("flags           = %u\n", flags);
                        }
                    PrintIndent(indentation);
                    printf("baseCost        = %f\n", baseCost);
                    PrintIndent(indentation);
                    printf("associated      = %s\n", PrintFormID(associated));
                    PrintIndent(indentation);
                    printf("school          = %i\n", school);
                    PrintIndent(indentation);
                    printf("resistValue     = %i\n", resistValue);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("unk1            = %i\n", unk1);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1         = %02X%02X\n", unused1[0], unused1[1]);
                        }
                    PrintIndent(indentation);
                    printf("light           = %s\n", PrintFormID(light));
                    PrintIndent(indentation);
                    printf("projectileSpeed = %f\n", projectileSpeed);
                    PrintIndent(indentation);
                    printf("effectShader    = %s\n", PrintFormID(effectShader));
                    PrintIndent(indentation);
                    printf("enchantEffect   = %s\n", PrintFormID(enchantEffect));
                    PrintIndent(indentation);
                    printf("castingSound    = %s\n", PrintFormID(castingSound));
                    PrintIndent(indentation);
                    printf("boltSound       = %s\n", PrintFormID(boltSound));
                    PrintIndent(indentation);
                    printf("hitSound        = %s\n", PrintFormID(hitSound));
                    PrintIndent(indentation);
                    printf("areaSound       = %s\n", PrintFormID(areaSound));
                    PrintIndent(indentation);
                    printf("cefEnchantment  = %f\n", baseCost);
                    PrintIndent(indentation);
                    printf("cefBarter       = %f\n", baseCost);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const MGEFDATA &other) const
                {
                return (flags == other.flags && 
                        AlmostEqual(baseCost,other.baseCost,2) && 
                        associated == other.associated && 
                        school == other.school && 
                        resistValue == other.resistValue && 
                        light == other.light && 
                        AlmostEqual(projectileSpeed,other.projectileSpeed,2) && 
                        effectShader == other.effectShader && 
                        enchantEffect == other.enchantEffect && 
                        castingSound == other.castingSound && 
                        boltSound == other.boltSound && 
                        hitSound == other.hitSound && 
                        areaSound == other.areaSound && 
                        AlmostEqual(cefEnchantment,other.cefEnchantment,2) && 
                        AlmostEqual(cefBarter,other.cefBarter,2));
                }
            bool operator !=(const MGEFDATA &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum flagsFlags
            {
            fIsHostile      = 0x00000001,
            fIsRecover      = 0x00000002,
            fIsDetrimental  = 0x00000004,
            fIsMagnitude    = 0x00000008,
            fIsSelf         = 0x00000010,
            fIsTouch        = 0x00000020,
            fIsTarget       = 0x00000040,
            fIsNoDuration   = 0x00000080,
            fIsNoMagnitude  = 0x00000100,
            fIsNoArea       = 0x00000200,
            fIsFXPersist    = 0x00000400,
            fIsSpellmaking  = 0x00000800,
            fIsEnchanting   = 0x00001000,
            fIsNoIngredient = 0x00002000,
            fIsUseWeapon    = 0x00010000,
            fIsUseArmor     = 0x00020000,
            fIsUseCreature  = 0x00040000,
            fIsUseSkill     = 0x00080000,
            fIsUseAttr      = 0x00100000,
            fIsUseAV        = 0x01000000,
            fIsSprayType    = 0x02000000,
            fIsBoltType     = 0x04000000,
            fIsFogType      = 0x06000000,
            fIsNoHitEffect  = 0x08000000
            };
        STRING EDID;
        STRING FULL;
        STRING DESC;
        STRING ICON;
        OptRecordField<GENMODEL> MODL;
        ReqRecordField<MGEFDATA> DATA;
        std::vector<unsigned int> ESCE;
        MGEFRecord(bool newRecord=false):Record(newRecord) {}
        MGEFRecord(const unsigned int &newFormID):Record(newFormID) {}
        MGEFRecord(MGEFRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            DESC = srcRecord->DESC;
            ICON = srcRecord->ICON;
            if(srcRecord->MODL.IsLoaded())
                {
                MODL.Load();
                MODL->MODB = srcRecord->MODL->MODB;
                MODL->MODL = srcRecord->MODL->MODL;
                MODL->MODT = srcRecord->MODL->MODT;
                }
            DATA = srcRecord->DATA;
            ESCE = srcRecord->ESCE;
            }
        ~MGEFRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            DESC.Unload();
            ICON.Unload();
            MODL.Unload();
            DATA.Unload();
            ESCE.clear();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            FormIDs.push_back(&DATA.value.associated);
            FormIDs.push_back(&DATA.value.light);
            FormIDs.push_back(&DATA.value.effectShader);
            FormIDs.push_back(&DATA.value.enchantEffect);
            FormIDs.push_back(&DATA.value.castingSound);
            FormIDs.push_back(&DATA.value.boltSound);
            FormIDs.push_back(&DATA.value.hitSound);
            FormIDs.push_back(&DATA.value.areaSound);
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
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eMGEF;}
        char * GetStrType() {return "MGEF";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsHostile()
            {
            return (DATA.value.flags & fIsHostile) != 0;
            }
        bool IsRecover()
            {
            return (DATA.value.flags & fIsRecover) != 0;
            }
        bool IsDetrimental()
            {
            return (DATA.value.flags & fIsDetrimental) != 0;
            }
        bool IsMagnitude()
            {
            return (DATA.value.flags & fIsMagnitude) != 0;
            }
        bool IsSelf()
            {
            return (DATA.value.flags & fIsSelf) != 0;
            }
        bool IsTouch()
            {
            return (DATA.value.flags & fIsTouch) != 0;
            }
        bool IsTarget()
            {
            return (DATA.value.flags & fIsTarget) != 0;
            }
        bool IsNoDuration()
            {
            return (DATA.value.flags & fIsNoDuration) != 0;
            }
        bool IsNoMagnitude()
            {
            return (DATA.value.flags & fIsNoMagnitude) != 0;
            }
        bool IsNoArea()
            {
            return (DATA.value.flags & fIsNoArea) != 0;
            }
        bool IsFXPersist()
            {
            return (DATA.value.flags & fIsFXPersist) != 0;
            }
        void IsFXPersist(bool value)
            {
            if(value)
                DATA.value.flags |= fIsFXPersist;
            else
                DATA.value.flags &= ~fIsFXPersist;
            }
        bool IsSpellmaking()
            {
            return (DATA.value.flags & fIsSpellmaking) != 0;
            }
        void IsSpellmaking(bool value)
            {
            if(value)
                DATA.value.flags |= fIsSpellmaking;
            else
                DATA.value.flags &= ~fIsSpellmaking;
            }
        bool IsEnchanting()
            {
            return (DATA.value.flags & fIsEnchanting) != 0;
            }
        void IsEnchanting(bool value)
            {
            if(value)
                DATA.value.flags |= fIsEnchanting;
            else
                DATA.value.flags &= ~fIsEnchanting;
            }
        bool IsNoIngredient()
            {
            return (DATA.value.flags & fIsNoIngredient) != 0;
            }
        void IsNoIngredient(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNoIngredient;
            else
                DATA.value.flags &= ~fIsNoIngredient;
            }
        bool IsUseWeapon()
            {
            return (DATA.value.flags & fIsUseWeapon) != 0;
            }
        bool IsUseArmor()
            {
            return (DATA.value.flags & fIsUseArmor) != 0;
            }
        bool IsUseCreature()
            {
            return (DATA.value.flags & fIsUseCreature) != 0;
            }
        bool IsUseSkill()
            {
            return (DATA.value.flags & fIsUseSkill) != 0;
            }
        bool IsUseAttribute()
            {
            return (DATA.value.flags & fIsUseAttr) != 0;
            }
        bool IsUseAttr()
            {
            return (DATA.value.flags & fIsUseAttr) != 0;
            }
        bool IsUseActorValue()
            {
            return (DATA.value.flags & fIsUseAV) != 0;
            }
        void IsUseActorValue(bool value)
            {
            if(value)
                DATA.value.flags |= fIsUseAV;
            else
                DATA.value.flags &= ~fIsUseAV;
            }
        bool IsUseAV()
            {
            return (DATA.value.flags & fIsUseAV) != 0;
            }
        void IsUseAV(bool value)
            {
            if(value)
                DATA.value.flags |= fIsUseAV;
            else
                DATA.value.flags &= ~fIsUseAV;
            }
        bool IsSprayType()
            {
            return ((DATA.value.flags & fIsSprayType) != 0) && ((DATA.value.flags & fIsBoltType) == 0);
            }
        void IsSprayType(bool value)
            {
            if(value)
                {
                DATA.value.flags &= ~fIsFogType;
                DATA.value.flags |= fIsSprayType;
                }
            else if(IsSprayType())
                IsBallType(true);
            }
        bool IsBoltType()
            {
            return ((DATA.value.flags & fIsBoltType) != 0) && ((DATA.value.flags & fIsSprayType) == 0);
            }
        void IsBoltType(bool value)
            {
            if(value)
                {
                DATA.value.flags &= ~fIsFogType;
                DATA.value.flags |= fIsBoltType;
                }
            else if(IsBoltType())
                IsBallType(true);
            }
        bool IsFogType()
            {
            return (DATA.value.flags & fIsFogType) == fIsFogType;
            }
        void IsFogType(bool value)
            {
            if(value)
                DATA.value.flags |= fIsFogType;
            else if(IsFogType())
                IsBallType(true);
            }
        bool IsBallType()
            {
            return (DATA.value.flags & fIsFogType) == 0;
            }
        void IsBallType(bool value)
            {
            if(value)
                DATA.value.flags &= ~fIsFogType;
            else if(IsBallType())
                IsBoltType(true);
            }
        bool IsNoHitEffect()
            {
            return (DATA.value.flags & fIsNoHitEffect) != 0;
            }
        void IsNoHitEffect(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNoHitEffect;
            else
                DATA.value.flags &= ~fIsNoHitEffect;
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
