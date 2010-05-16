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

class LTEXRecord : public Record
    {
    private:
        enum LTEXRecordFields {
            eEDID = 0x44494445,
            eICON = 0x4E4F4349,
            eHNAM = 0x4D414E48,
            eSNAM = 0x4D414E53,
            eGNAM = 0x4D414E47
            };
        struct LTEXHNAM
            {
            unsigned char flags, friction, restitution;
            LTEXHNAM():flags(0), friction(0), restitution(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags       = %u\n", flags);
                        }
                    PrintIndent(indentation);
                    printf("friction    = %u\n", friction);
                    PrintIndent(indentation);
                    printf("restitution = %u\n", restitution);
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct LTEXSNAM
            {
            unsigned char specular;
            LTEXSNAM():specular(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("specular = %u\n", specular);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        enum flagsFlags
            {
            fIsStone      = 0x00000001,
            fIsCloth      = 0x00000002,
            fIsDirt       = 0x00000004,
            fIsGlass      = 0x00000008,
            fIsGrass      = 0x00000010,
            fIsMetal      = 0x00000020,
            fIsOrganic    = 0x00000040,
            fIsSkin       = 0x00000080,
            fIsWater      = 0x00000100,
            fIsWood       = 0x00000200,
            fIsHeavyStone = 0x00000400,
            fIsHeavyMetal = 0x00000800,
            fIsHeavyWood  = 0x00001000,
            fIsChain      = 0x00002000,
            fIsSnow       = 0x00004000
            };
        STRING EDID;
        STRING ICON;
        RecordField<LTEXHNAM> HNAM;
        RecordField<LTEXSNAM> SNAM;
        std::vector<unsigned int *> GNAM;
        LTEXRecord(bool newRecord=false):Record(newRecord) {}
        LTEXRecord(const unsigned int &newFormID):Record(newFormID) {}
        LTEXRecord(LTEXRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            ICON = srcRecord->ICON;
            HNAM = srcRecord->HNAM;
            SNAM = srcRecord->SNAM;

            GNAM.clear();
            GNAM.resize(srcRecord->GNAM.size());
            for(unsigned int x = 0; x < srcRecord->GNAM.size(); x++)
                GNAM[x] = new unsigned int(*srcRecord->GNAM[x]);
            return;
            }
        ~LTEXRecord()
            {
            for(unsigned int x = 0; x < GNAM.size(); x++)
                delete GNAM[x];
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < GNAM.size(); x++)
                FormIDHandler.ExpandFormID(GNAM[x]);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < GNAM.size(); x++)
                FormIDHandler.CollapseFormID(GNAM[x]);
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
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eLTEX;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
        bool IsStone()
            {
            return (HNAM.value.flags & fIsStone) != 0;
            }
        void IsStone(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsStone;
            else
                HNAM.value.flags &= ~fIsStone;
            }
        bool IsCloth()
            {
            return (HNAM.value.flags & fIsCloth) != 0;
            }
        void IsCloth(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsCloth;
            else
                HNAM.value.flags &= ~fIsCloth;
            }
        bool IsDirt()
            {
            return (HNAM.value.flags & fIsDirt) != 0;
            }
        void IsDirt(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsDirt;
            else
                HNAM.value.flags &= ~fIsDirt;
            }
        bool IsGlass()
            {
            return (HNAM.value.flags & fIsGlass) != 0;
            }
        void IsGlass(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsGlass;
            else
                HNAM.value.flags &= ~fIsGlass;
            }
        bool IsGrass()
            {
            return (HNAM.value.flags & fIsGrass) != 0;
            }
        void IsGrass(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsGrass;
            else
                HNAM.value.flags &= ~fIsGrass;
            }
        bool IsMetal()
            {
            return (HNAM.value.flags & fIsMetal) != 0;
            }
        void IsMetal(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsMetal;
            else
                HNAM.value.flags &= ~fIsMetal;
            }
        bool IsOrganic()
            {
            return (HNAM.value.flags & fIsOrganic) != 0;
            }
        void IsOrganic(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsOrganic;
            else
                HNAM.value.flags &= ~fIsOrganic;
            }
        bool IsSkin()
            {
            return (HNAM.value.flags & fIsSkin) != 0;
            }
        void IsSkin(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsSkin;
            else
                HNAM.value.flags &= ~fIsSkin;
            }
        bool IsWater()
            {
            return (HNAM.value.flags & fIsWater) != 0;
            }
        void IsWater(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsWater;
            else
                HNAM.value.flags &= ~fIsWater;
            }
        bool IsWood()
            {
            return (HNAM.value.flags & fIsWood) != 0;
            }
        void IsWood(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsWood;
            else
                HNAM.value.flags &= ~fIsWood;
            }
        bool IsHeavyStone()
            {
            return (HNAM.value.flags & fIsHeavyStone) != 0;
            }
        void IsHeavyStone(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsHeavyStone;
            else
                HNAM.value.flags &= ~fIsHeavyStone;
            }
        bool IsHeavyMetal()
            {
            return (HNAM.value.flags & fIsHeavyMetal) != 0;
            }
        void IsHeavyMetal(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsHeavyMetal;
            else
                HNAM.value.flags &= ~fIsHeavyMetal;
            }
        bool IsHeavyWood()
            {
            return (HNAM.value.flags & fIsHeavyWood) != 0;
            }
        void IsHeavyWood(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsHeavyWood;
            else
                HNAM.value.flags &= ~fIsHeavyWood;
            }
        bool IsChain()
            {
            return (HNAM.value.flags & fIsChain) != 0;
            }
        void IsChain(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsChain;
            else
                HNAM.value.flags &= ~fIsChain;
            }
        bool IsSnow()
            {
            return (HNAM.value.flags & fIsSnow) != 0;
            }
        void IsSnow(bool value)
            {
            if(value)
                HNAM.value.flags |= fIsSnow;
            else
                HNAM.value.flags &= ~fIsSnow;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (HNAM.value.flags & Mask) == Mask;
            else
                return (HNAM.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            HNAM.value.flags = Mask;
            }
    };
