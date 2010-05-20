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

class LVSPRecord : public Record
    {
    protected:
        enum LVSPRecordFields {
            eEDID = 0x44494445,

            eLVLD = 0x444C564C,
            eLVLF = 0x464C564C,
            eLVLO = 0x4F4C564C
            };
        struct LVLLVLD
            {
            unsigned char chanceNone;
            LVLLVLD():chanceNone(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
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
            };
        struct LVLLVLO
            {
            short level;
            unsigned char unused1[2];
            unsigned int listId;
            short count;
            unsigned char unused2[2];
            LVLLVLO():level(0), listId(NULL), count(1)
                {
                memset(&unused1, 0x00, 2);
                memset(&unused2, 0x00, 2);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
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
            };
    public:
        enum flagsFlags
            {
            fCalcFromAllLevels    = 0x00000001,
            fCalcForEachItem      = 0x00000002,
            fUseAllSpells         = 0x00000004,
            fAltCalcFromAllLevels = 0x00000080
            };
        STRING EDID;
        RecordField<LVLLVLD> LVLD;
        RecordField<GENFLAG> LVLF;
        std::vector<ReqRecordField<LVLLVLO> *> Entries;

        LVSPRecord(bool newRecord=false):Record(newRecord) {}
        LVSPRecord(const unsigned int &newFormID):Record(newFormID) {}
        LVSPRecord(LVSPRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            LVLD = srcRecord->LVLD;
            LVLF = srcRecord->LVLF;
            Entries.clear();
            Entries.resize(srcRecord->Entries.size());
            for(unsigned int x = 0; x < srcRecord->Entries.size(); x++)
                {
                Entries[x] = new ReqRecordField<LVLLVLO>;
                *Entries[x] = *srcRecord->Entries[x];
                }
            return;
            }
        ~LVSPRecord()
            {
            for(unsigned int x = 0; x < Entries.size(); x++)
                delete Entries[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            LVLD.Unload();
            LVLF.Unload();
            for(unsigned int x = 0; x < Entries.size(); x++)
                delete Entries[x];
            Entries.clear();
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < Entries.size(); x++)
                FormIDHandler.ExpandFormID(Entries[x]->value.listId);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < Entries.size(); x++)
                FormIDHandler.CollapseFormID(Entries[x]->value.listId);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eLVSP;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);

        bool IsCalcFromAllLevels()
            {
            if(!LVLF.IsLoaded())
                if(!LVLD.IsLoaded())
                    return false;
                else
                    return (LVLD.value.chanceNone & fAltCalcFromAllLevels) != 0;
            else
                if(!LVLD.IsLoaded())
                    return (LVLF.value.flags & fCalcFromAllLevels) != 0;
                else
                    return ((LVLF.value.flags & fCalcFromAllLevels) != 0) || ((LVLD.value.chanceNone & fAltCalcFromAllLevels) != 0);
            }
        void IsCalcFromAllLevels(bool value)
            {
            if(!LVLF.IsLoaded())
                if(!LVLD.IsLoaded())
                    return;
                else
                    if(value)
                        LVLD.value.chanceNone |= fAltCalcFromAllLevels;
                    else
                        LVLD.value.chanceNone &= ~fAltCalcFromAllLevels;
            else
                if(!LVLD.IsLoaded())
                    if(value)
                        LVLF.value.flags |= fCalcFromAllLevels;
                    else
                        LVLF.value.flags &= ~fCalcFromAllLevels;
                else
                    if(value)
                        {
                        LVLF.value.flags |= fCalcFromAllLevels;
                        LVLD.value.chanceNone &= ~fAltCalcFromAllLevels;
                        }
                    else
                        {
                        LVLF.value.flags &= ~fCalcFromAllLevels;
                        LVLD.value.chanceNone &= ~fAltCalcFromAllLevels;
                        }
            }
        bool IsCalcForEachItem()
            {
            return (LVLF.value.flags & fCalcForEachItem) != 0;
            }
        void IsCalcForEachItem(bool value)
            {
            if(value)
                LVLF.value.flags |= fCalcForEachItem;
            else
                LVLF.value.flags &= ~fCalcForEachItem;
            }
        bool IsUseAllSpells()
            {
            return (LVLF.value.flags & fUseAllSpells) != 0;
            }
        void IsUseAllSpells(bool value)
            {
            if(value)
                LVLF.value.flags |= fUseAllSpells;
            else
                LVLF.value.flags &= ~fUseAllSpells;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (LVLF.value.flags & Mask) == Mask;
            else
                return (LVLF.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            LVLF.value.flags = Mask;
            }
    };
