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

class LVLIRecord : public Record
    {
    protected:
        enum LVLISubRecords {
            eEDID = 0x44494445,

            eLVLD = 0x444C564C,
            eLVLF = 0x464C564C,
            eLVLO = 0x4F4C564C,
            eDATA = 0x41544144
            };
        struct LVLLVLD
            {
            unsigned char chanceNone;
            LVLLVLD():chanceNone(0) {}
            #ifdef _DEBUG
            void Debug(signed long debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("chanceNone = %u\n", chanceNone);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const LVLLVLD &other) const
                {
                return (chanceNone == other.chanceNone);
                }
            bool operator !=(const LVLLVLD &other) const
                {
                return !(*this == other);
                }
            };
        struct LVLLVLO
            {
            short level;
            unsigned char unused1[2];
            unsigned long listId;
            short count;
            unsigned char unused2[2];
            LVLLVLO():level(0), listId(NULL), count(1)
                {
                memset(&unused1, 0x00, 2);
                memset(&unused2, 0x00, 2);
                }
            #ifdef _DEBUG
            void Debug(signed long debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("level   = %i\n", level);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1 = %02X%02X\n", unused1[0], unused1[1]);
                        }
                    PrintIndent(indentation);
                    printf("listId  = %s\n", PrintFormID(listId));
                    PrintIndent(indentation);
                    printf("count   = %i\n", count);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused2 = %02X%02X\n", unused2[0], unused2[1]);
                        }
                    indentation -= 2;
                    }
                else
                    {
                    PrintIndent(indentation);
                    printf("LVLO\n");
                    }
                }
            #endif
            bool operator ==(const LVLLVLO &other) const
                {
                return (level == other.level &&
                        listId == other.listId &&
                        count == other.count);
                }
            bool operator !=(const LVLLVLO &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum flagsFlags
            {
            fCalcFromAllLevels    = 0x00000001,
            fCalcForEachItem      = 0x00000002,
            fUseAllSpells         = 0x00000004,
            fAltCalcFromAllLevels = 0x00000080
            };
        StringRecord EDID;
        ReqSubRecord<LVLLVLD> LVLD;
        SemiOptSubRecord<GENFLAG> LVLF;
        std::vector<ReqSubRecord<LVLLVLO> *> Entries;
        //RawRecord DATA; //Older version of LVLF. Auto-updated to newer format.

        LVLIRecord(bool newRecord=false):Record(newRecord) {}
        LVLIRecord(LVLIRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eLVLI)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            LVLD = srcRecord->LVLD;
            LVLF = srcRecord->LVLF;
            Entries.clear();
            Entries.resize(srcRecord->Entries.size());
            for(unsigned long x = 0; x < srcRecord->Entries.size(); x++)
                {
                Entries[x] = new ReqSubRecord<LVLLVLO>;
                *Entries[x] = *srcRecord->Entries[x];
                }
            //DATA = srcRecord->DATA;
            return;
            }
        ~LVLIRecord()
            {
            for(unsigned long x = 0; x < Entries.size(); x++)
                delete Entries[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            LVLD.Unload();
            LVLF.Unload();
            for(unsigned long x = 0; x < Entries.size(); x++)
                delete Entries[x];
            Entries.clear();
            //DATA.Unload();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            for(unsigned long x = 0; x < Entries.size(); x++)
                op.Accept(Entries[x]->value.listId);

            return op.Stop();
            }

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long CreateListElement(const unsigned long subField);
        signed long DeleteListElement(const unsigned long subField);
        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        signed long GetListFieldType(const unsigned long subField, const unsigned long listField);
        unsigned long GetListSize(const unsigned long Field);
        unsigned long GetListArraySize(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void GetListArray(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues);
        void * GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void SetField(const unsigned long Field, char *FieldValue);
        void SetField(const unsigned long Field, unsigned char FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, short FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char *FieldValue, unsigned long nSize);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue);

        signed long DeleteField(const unsigned long Field);
        signed long DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eLVLI;}
        char *GetStrType() {return "LVLI";}
        signed long WriteRecord(_FileHandler &SaveHandler);

        bool IsCalcFromAllLevels()
            {
            if(!LVLF.IsLoaded()) return false;
            return (LVLF->flags & fCalcFromAllLevels) != 0;
            }
        void IsCalcFromAllLevels(bool value)
            {
            if(!LVLF.IsLoaded()) return;
            if(value)
                LVLF->flags |= fCalcFromAllLevels;
            else
                LVLF->flags &= ~fCalcFromAllLevels;
            }
        bool IsCalcForEachItem()
            {
            if(!LVLF.IsLoaded()) return false;
            return (LVLF->flags & fCalcForEachItem) != 0;
            }
        void IsCalcForEachItem(bool value)
            {
            if(!LVLF.IsLoaded()) return;
            if(value)
                LVLF->flags |= fCalcForEachItem;
            else
                LVLF->flags &= ~fCalcForEachItem;
            }
        bool IsUseAllSpells()
            {
            if(!LVLF.IsLoaded()) return false;
            return (LVLF->flags & fUseAllSpells) != 0;
            }
        void IsUseAllSpells(bool value)
            {
            if(!LVLF.IsLoaded()) return;
            if(value)
                LVLF->flags |= fUseAllSpells;
            else
                LVLF->flags &= ~fUseAllSpells;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(!LVLF.IsLoaded()) return false;
            if(Exact)
                return (LVLF->flags & Mask) == Mask;
            else
                return (LVLF->flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            LVLF.Load();
            LVLF->flags = Mask;
            }
    };
