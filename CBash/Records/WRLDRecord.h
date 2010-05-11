# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
#pragma once
#include "..\Common.h"
#include "..\BaseRecord.h"
#include "CELLRecord.h"
#include "ROADRecord.h"
#include <vector>

class WRLDRecord : public Record
    {
    private:
        enum WRLDRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eWNAM = 0x4D414E57,
            eCNAM = 0x4D414E43,
            eNAM2 = 0x324D414E,

            eICON = 0x4E4F4349,

            eMNAM = 0x4D414E4D,
            eDATA = 0x41544144,
            eNAM0 = 0x304D414E,
            eNAM9 = 0x394D414E,
            eSNAM = 0x4D414E53,

            eOFST = 0x5453464F
            };

        struct WRLDMNAM
            {
            int dimX, dimY;
            short NWCellX, NWCellY, SECellX, SECellY;
            WRLDMNAM():dimX(0), dimY(0), NWCellX(0), NWCellY(0), SECellX(0), SECellY(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("dimX    = %i\n", dimX);
                    PrintIndent(indentation);
                    printf("dimY    = %i\n", dimY);
                    PrintIndent(indentation);
                    printf("NWCellX = %i\n", NWCellX);
                    PrintIndent(indentation);
                    printf("NWCellY = %i\n", NWCellY);
                    PrintIndent(indentation);
                    printf("SECellX = %i\n", SECellX);
                    PrintIndent(indentation);
                    printf("SECellY = %i\n", SECellY);
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct WRLDUNK
            {
            float unk1, unk2;
            WRLDUNK():unk1(0.0f), unk2(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 5)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("unk1 = %f\n", unk1);
                    PrintIndent(indentation);
                    printf("unk2 = %f\n", unk2);
                    indentation -= 2;
                    }
                }
            #endif
            };

    public:
        enum flagsFlags
            {
            fSmallWorld         = 0x00000001,
            fNoFastTravel       = 0x00000002,
            fOblivionWorldspace = 0x00000004,
            fNoLODWater         = 0x00000010
            };
        enum eSNAMType
            {
            eDefault,
            ePublic,
            eDungeon
            };
        STRING EDID;
        STRING FULL;

        OptRecordField<GENFID> WNAM;
        OptRecordField<GENFID> CNAM;
        OptRecordField<GENFID> NAM2;

        STRING ICON;

        OptRecordField<WRLDMNAM> MNAM;
        ReqRecordField<GENFLAG> DATA;

        ReqRecordField<WRLDUNK> NAM0;
        ReqRecordField<WRLDUNK> NAM9;

        OptRecordField<GENUFLAG> SNAM;
        RAWBYTES OFST;
        ROADRecord *ROAD;
        CELLRecord *CELL;
        std::vector<CELLRecord *> CELLS;
        WRLDRecord(bool newRecord=false):Record(newRecord), ROAD(NULL), CELL(NULL) {}
        WRLDRecord(const unsigned int &newFormID):Record(newFormID), ROAD(NULL), CELL(NULL) {}
        WRLDRecord(WRLDRecord *srcRecord):Record(true), ROAD(NULL), CELL(NULL)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            WNAM = srcRecord->WNAM;
            CNAM = srcRecord->CNAM;
            NAM2 = srcRecord->NAM2;
            ICON = srcRecord->ICON;
            MNAM = srcRecord->MNAM;
            DATA = srcRecord->DATA;
            NAM0 = srcRecord->NAM0;
            NAM9 = srcRecord->NAM9;
            SNAM = srcRecord->SNAM;
            OFST = srcRecord->OFST;
            return;
            }
        ~WRLDRecord()
            {
            delete ROAD;
            delete CELL;
            for(unsigned int x = 0; x < CELLS.size(); ++x)
                delete CELLS[x];
            }
        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            if(WNAM.IsLoaded())
                FormIDHandler.ExpandFormID(WNAM->fid);
            if(CNAM.IsLoaded())
                FormIDHandler.ExpandFormID(CNAM->fid);
            if(NAM2.IsLoaded())
                FormIDHandler.ExpandFormID(NAM2->fid);
            }
        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            if(WNAM.IsLoaded())
                FormIDHandler.CollapseFormID(WNAM->fid);
            if(CNAM.IsLoaded())
                FormIDHandler.CollapseFormID(CNAM->fid);
            if(NAM2.IsLoaded())
                FormIDHandler.CollapseFormID(NAM2->fid);
            }
        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, short FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eWRLD;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);

        bool IsSmallWorld()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fSmallWorld) != 0;
            }
        void IsSmallWorld(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fSmallWorld;
            else
                DATA.value.flags &= ~fSmallWorld;
            }
        bool IsNoFastTravel()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fNoFastTravel) != 0;
            }
        void IsNoFastTravel(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fNoFastTravel;
            else
                DATA.value.flags &= ~fNoFastTravel;
            }
        bool IsOblivionWorldspace()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fOblivionWorldspace) != 0;
            }
        void IsOblivionWorldspace(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fOblivionWorldspace;
            else
                DATA.value.flags &= ~fOblivionWorldspace;
            }
        bool IsNoLODWater()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fNoLODWater) != 0;
            }
        void IsNoLODWater(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fNoLODWater;
            else
                DATA.value.flags &= ~fNoLODWater;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(!DATA.IsLoaded()) return false;
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            if(!DATA.IsLoaded()) return;
            DATA.value.flags = Mask;
            }
        bool IsDefaultMusic()
            {
            if(!SNAM.IsLoaded()) return false;
            return (SNAM->flags == eDefault);
            }
        void IsDefaultMusic(bool value)
            {
            if(!SNAM.IsLoaded()) return;
            if(value)
                SNAM->flags = eDefault;
            else if(IsDefaultMusic())
                SNAM->flags = ePublic;
            }
        bool IsPublicMusic()
            {
            if(!SNAM.IsLoaded()) return false;
            return (SNAM->flags == ePublic);
            }
        void IsPublicMusic(bool value)
            {
            if(!SNAM.IsLoaded()) return;
            if(value)
                SNAM->flags = ePublic;
            else if(IsPublicMusic())
                SNAM->flags = eDefault;
            }
        bool IsDungeonMusic()
            {
            if(!SNAM.IsLoaded()) return false;
            return (SNAM->flags == eDungeon);
            }
        void IsDungeonMusic(bool value)
            {
            if(!SNAM.IsLoaded()) return;
            if(value)
                SNAM->flags = eDungeon;
            else if(IsDungeonMusic())
                SNAM->flags = eDefault;
            }
        bool IsMusicType(unsigned int Type)
            {
            if(!SNAM.IsLoaded()) return false;
            return (SNAM->flags == Type);
            }
        void SetMusicType(unsigned int Type)
            {
            if(!SNAM.IsLoaded()) return;
            SNAM->flags = Type;
            }
    };

struct sortBlocks
    {
     bool operator()(const unsigned int &l, const unsigned int &r) const
        {
        return l < r;
        }
    };

struct WritableSubBlock
    {
    unsigned int size;
    std::vector<WritableCell> WritableRecords;
    };
struct WritableBlock
    {
    unsigned int size;
    std::map<unsigned int, WritableSubBlock, sortBlocks> SubBlock;
    };

struct WritableWorld
    {
    unsigned int WorldGRUPSize;
    unsigned int WorldSize;
    unsigned int RoadSize;
    unsigned int CellSize;
    unsigned int ChildrenSize;
    unsigned int PersistentSize;
    std::vector<Record *> Persistent;
    std::vector<unsigned int> PersistentSizes;
    std::map<unsigned int, WritableBlock, sortBlocks> Block;
    };

