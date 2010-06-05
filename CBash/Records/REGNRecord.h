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

class REGNRecord : public Record
    {
    private:
        enum REGNRecordFields {
            eEDID = 0x44494445,
            eICON = 0x4E4F4349,
            eRCLR = 0x524C4352,
            eWNAM = 0x4D414E57,
            eRPLI = 0x494C5052,
            eRPLD = 0x444C5052,
            eRDAT = 0x54414452,
            eRDOT = 0x544F4452,
            eRDMP = 0x504D4452,
            eRDGS = 0x53474452,
            eRDMD = 0x444D4452,
            eRDSD = 0x44534452,
            eRDWT = 0x54574452
            };
        struct REGNRPLD
            {
            float posX, posY;
            REGNRPLD():posX(0.0f), posY(0.0f){}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("posX = %f\n", posX);
                    PrintIndent(indentation);
                    printf("posY = %f\n", posY);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct REGNRPLI
            {
            unsigned int edgeFalloff;
            REGNRPLI():edgeFalloff(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("edgeFalloff = %u\n", edgeFalloff);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct REGNArea
            {
            ReqRecordField<REGNRPLI> RPLI;
            std::vector<REGNRPLD> RPLD;
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    RPLI.Debug("RPLI", debugLevel, indentation);
                    if(RPLD.size())
                        {
                        PrintIndent(indentation);
                        printf("RPLD:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < RPLD.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            RPLD[p].Debug(debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    indentation -= 2;
                    }
                else
                    {
                    indentation += 2;
                    RPLI.Debug("RPLI", debugLevel, indentation);
                    if(RPLD.size())
                        {
                        PrintIndent(indentation);
                        printf("RPLD:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < RPLD.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            RPLD[p].Debug(debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct REGNRDWT
            {
            unsigned int weather;
            unsigned int chance;
            REGNRDWT():weather(0), chance(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("weather = %s\n", PrintFormID(weather));
                    PrintIndent(indentation);
                    printf("chance  = %u\n", chance);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct REGNRDSD
            {
            unsigned int sound;
            unsigned int flags, chance;
            REGNRDSD():sound(0), flags(0), chance(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("sound  = %s\n", PrintFormID(sound));
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags  = %u\n", flags);
                        }
                    PrintIndent(indentation);
                    printf("chance = %f\n", chance);
                    indentation -= 2;
                    }
                }
            #endif
            enum RDSDFlags
                {
                fIsPleasant = 0x00000001,
                fIsCloudy   = 0x00000002,
                fIsRainy    = 0x00000004,
                fIsSnowy    = 0x00000008
                };
            bool IsPleasant()
                {
                return (flags & fIsPleasant) != 0;
                }
            void IsPleasant(bool value)
                {
                if(value)
                    flags |= fIsPleasant;
                else
                    flags &= ~fIsPleasant;
                }
            bool IsCloudy()
                {
                return (flags & fIsCloudy) != 0;
                }
            void IsCloudy(bool value)
                {
                if(value)
                    flags |= fIsCloudy;
                else
                    flags &= ~fIsCloudy;
                }
            bool IsRainy()
                {
                return (flags & fIsRainy) != 0;
                }
            void IsRainy(bool value)
                {
                if(value)
                    flags |= fIsRainy;
                else
                    flags &= ~fIsRainy;
                }
            bool IsSnowy()
                {
                return (flags & fIsSnowy) != 0;
                }
            void IsSnowy(bool value)
                {
                if(value)
                    flags |= fIsSnowy;
                else
                    flags &= ~fIsSnowy;
                }
            bool IsFlagMask(unsigned int Mask, bool Exact=false)
                {
                if(Exact)
                    return (flags & Mask) == Mask;
                else
                    return (flags & Mask) != 0;
                }
            void SetFlagMask(unsigned int Mask)
                {
                flags = Mask;
                }
            };
        struct REGNRDMD
            {
            unsigned int type;
            REGNRDMD():type(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("type = %u\n", type);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct REGNRDGS
            {
            unsigned int grass;
            unsigned char unk1[4];
            REGNRDGS():grass(0)
                {
                memset(&unk1, 0x00, 4);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("grass = %s\n", PrintFormID(grass));
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("unk1  = %02X%02X%02X%02X\n", unk1[0], unk1[1], unk1[2], unk1[3]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct REGNRDOT
            {
            unsigned int objectId;
            unsigned short parentIndex;
            unsigned char unused1[2];
            float density;
            unsigned char clustering, minSlope, maxSlope, flags;
            unsigned short radiusWRTParent, radius;
            unsigned char unk1[4];
            float maxHeight, sink, sinkVar, sizeVar;
            unsigned short angleVarX, angleVarY, angleVarZ;
            unsigned char unused2[2], unk2[4];

            REGNRDOT():objectId(0), parentIndex(0), density(0.0f),
                clustering(0), minSlope(0), maxSlope(0), flags(0),
                radiusWRTParent(0), radius(0),
                maxHeight(0.0f), sink(0.0f), sinkVar(0.0f), sizeVar(0.0f),
                angleVarX(0) ,angleVarY(0), angleVarZ(0)
                {
                memset(&unused1, 0x00, 2);
                memset(&unk1, 0x00, 4);
                memset(&unused2, 0x00, 2);
                memset(&unk2, 0x00, 4);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("objectId        = %s\n", PrintFormID(objectId));
                    PrintIndent(indentation);
                    printf("parentIndex     = %u\n", parentIndex);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1         = %02X%02X\n", unused1[0], unused1[1]);
                        }
                    PrintIndent(indentation);
                    printf("density         = %f\n", density);
                    PrintIndent(indentation);
                    printf("clustering      = %u\n", clustering);
                    PrintIndent(indentation);
                    printf("minSlope        = %u\n", minSlope);
                    PrintIndent(indentation);
                    printf("maxSlope        = %u\n", maxSlope);
                    PrintIndent(indentation);
                    printf("flags           = %u\n", flags);
                    PrintIndent(indentation);
                    printf("radiusWRTParent = %u\n", radiusWRTParent);
                    PrintIndent(indentation);
                    printf("radius          = %u\n", radius);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("unk1            = %02X%02X%02X%02X\n", unk1[0], unk1[1], unk1[2], unk1[3]);
                        }
                    PrintIndent(indentation);
                    printf("maxHeight       = %f\n", maxHeight);
                    PrintIndent(indentation);
                    printf("sink            = %f\n", sink);
                    PrintIndent(indentation);
                    printf("sinkVar         = %f\n", sinkVar);
                    PrintIndent(indentation);
                    printf("sizeVar         = %f\n", sizeVar);
                    PrintIndent(indentation);
                    printf("angleVarX       = %u\n", angleVarX);
                    PrintIndent(indentation);
                    printf("angleVarY       = %u\n", angleVarY);
                    PrintIndent(indentation);
                    printf("angleVarZ       = %u\n", angleVarZ);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused2         = %02X%02X\n", unused2[0], unused2[1]);
                        }
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("unk2            = %02X%02X%02X%02X\n", unk2[0], unk2[1], unk2[2], unk2[3]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            enum RDOTFlags
                {
                fIsConformToSlope = 0x00000001,
                fIsPaintVertices  = 0x00000002,
                fIsSizeVariance   = 0x00000004,
                fIsXVariance      = 0x00000008,
                fIsYVariance      = 0x00000010,
                fIsZVariance      = 0x00000020,
                fIsTree           = 0x00000040,
                fIsHugeRock       = 0x00000080
                };
            bool IsConformToSlope()
                {
                return (flags & fIsConformToSlope) != 0;
                }
            void IsConformToSlope(bool value)
                {
                if(value)
                    flags |= fIsConformToSlope;
                else
                    flags &= ~fIsConformToSlope;
                }
            bool IsPaintVertices()
                {
                return (flags & fIsPaintVertices) != 0;
                }
            void IsPaintVertices(bool value)
                {
                if(value)
                    flags |= fIsPaintVertices;
                else
                    flags &= ~fIsPaintVertices;
                }
            bool IsSizeVariance()
                {
                return (flags & fIsSizeVariance) != 0;
                }
            void IsSizeVariance(bool value)
                {
                if(value)
                    flags |= fIsSizeVariance;
                else
                    flags &= ~fIsSizeVariance;
                }
            bool IsXVariance()
                {
                return (flags & fIsXVariance) != 0;
                }
            void IsXVariance(bool value)
                {
                if(value)
                    flags |= fIsXVariance;
                else
                    flags &= ~fIsXVariance;
                }
            bool IsYVariance()
                {
                return (flags & fIsYVariance) != 0;
                }
            void IsYVariance(bool value)
                {
                if(value)
                    flags |= fIsYVariance;
                else
                    flags &= ~fIsYVariance;
                }
            bool IsZVariance()
                {
                return (flags & fIsZVariance) != 0;
                }
            void IsZVariance(bool value)
                {
                if(value)
                    flags |= fIsZVariance;
                else
                    flags &= ~fIsZVariance;
                }
            bool IsTree()
                {
                return (flags & fIsTree) != 0;
                }
            void IsTree(bool value)
                {
                if(value)
                    flags |= fIsTree;
                else
                    flags &= ~fIsTree;
                }
            bool IsHugeRock()
                {
                return (flags & fIsHugeRock) != 0;
                }
            void IsHugeRock(bool value)
                {
                if(value)
                    flags |= fIsHugeRock;
                else
                    flags &= ~fIsHugeRock;
                }
            bool IsFlagMask(unsigned char Mask, bool Exact=false)
                {
                if(Exact)
                    return (flags & Mask) == Mask;
                else
                    return (flags & Mask) != 0;
                }
            void SetFlagMask(unsigned char Mask)
                {
                flags = Mask;
                }
            };
        struct REGNRDAT
            {
            unsigned int entryType;
            unsigned char flags, priority, unused1[2];
            REGNRDAT():entryType(0), flags(0), priority(0)
                {
                memset(&unused1, 0x00, 2);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("entryType = %u\n", entryType);
                    PrintIndent(indentation);
                    printf("flags     = %u\n", flags);
                    PrintIndent(indentation);
                    printf("priority  = %u\n", priority);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1   = %02X%02X\n", unused1[0], unused1[1]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct REGNEntry
            {
            ReqRecordField<REGNRDAT> RDAT;
            std::vector<REGNRDOT> RDOT;
            STRING RDMP;
            STRING ICON;
            std::vector<REGNRDGS> RDGS;
            OptRecordField<REGNRDMD> RDMD;
            std::vector<REGNRDSD> RDSD;
            std::vector<REGNRDWT> RDWT;
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    RDAT.Debug("RDAT", debugLevel, indentation);
                    if(RDOT.size())
                        {
                        PrintIndent(indentation);
                        printf("RDOT:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < RDOT.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            RDOT[p].Debug(debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    RDMP.Debug("RDMP", debugLevel, indentation);
                    ICON.Debug("ICON", debugLevel, indentation);
                    if(RDGS.size())
                        {
                        PrintIndent(indentation);
                        printf("RDGS:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < RDGS.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            RDGS[p].Debug(debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    RDMD.Debug("RDMD", debugLevel, indentation);
                    if(RDSD.size())
                        {
                        PrintIndent(indentation);
                        printf("RDSD:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < RDSD.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            RDSD[p].Debug(debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    if(RDWT.size())
                        {
                        PrintIndent(indentation);
                        printf("RDWT:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < RDWT.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            RDWT[p].Debug(debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    indentation -= 2;
                    }
                }
            #endif
            enum RDATFlags
                {
                fIsOverride = 0x00000001
                };
            enum eRDATType
                {
                eObject  = 2,
                eWeather = 3,
                eMap     = 4,
                eUnkIcon = 5,
                eGrass   = 6,
                eSound   = 7
                };
            enum eRDMDType
                {
                eDefault,
                ePublic,
                eDungeon
                };
            bool IsOverride()
                {
                return (RDAT.value.flags & fIsOverride) != 0;
                }
            void IsOverride(bool value)
                {
                if(value)
                    RDAT.value.flags |= fIsOverride;
                else
                    RDAT.value.flags &= ~fIsOverride;
                }
            bool IsFlagMask(unsigned char Mask, bool Exact=false)
                {
                if(Exact)
                    return (RDAT.value.flags & Mask) == Mask;
                else
                    return (RDAT.value.flags & Mask) != 0;
                }
            void SetFlagMask(unsigned char Mask)
                {
                RDAT.value.flags = Mask;
                }
            bool IsObject()
                {
                return (RDAT.value.entryType == eObject);
                }
            void IsObject(bool value)
                {
                if(value)
                    RDAT.value.entryType = eObject;
                else if(IsObject())
                    RDAT.value.entryType = eWeather;
                }
            bool IsWeather()
                {
                return (RDAT.value.entryType == eWeather);
                }
            void IsWeather(bool value)
                {
                if(value)
                    RDAT.value.entryType = eWeather;
                else if(IsWeather())
                    RDAT.value.entryType = eObject;
                }
            bool IsMap()
                {
                return (RDAT.value.entryType == eMap);
                }
            void IsMap(bool value)
                {
                if(value)
                    RDAT.value.entryType = eMap;
                else if(IsMap())
                    RDAT.value.entryType = eObject;
                }
            bool IsIcon()
                {
                return (RDAT.value.entryType == eUnkIcon);
                }
            void IsIcon(bool value)
                {
                if(value)
                    RDAT.value.entryType = eUnkIcon;
                else if(IsIcon())
                    RDAT.value.entryType = eObject;
                }
            bool IsGrass()
                {
                return (RDAT.value.entryType == eGrass);
                }
            void IsGrass(bool value)
                {
                if(value)
                    RDAT.value.entryType = eGrass;
                else if(IsGrass())
                    RDAT.value.entryType = eObject;
                }
            bool IsSound()
                {
                return (RDAT.value.entryType == eSound);
                }
            void IsSound(bool value)
                {
                if(value)
                    RDAT.value.entryType = eSound;
                else if(IsSound())
                    RDAT.value.entryType = eObject;
                }
            bool IsType(unsigned int Type)
                {
                return (RDAT.value.entryType == Type);
                }
            void SetType(unsigned int Type)
                {
                RDAT.value.entryType = Type;
                }
            bool IsDefaultMusic()
                {
                return (RDMD->type == eDefault);
                }
            void IsDefaultMusic(bool value)
                {
                if(value)
                    RDMD->type = eDefault;
                else if(IsDefaultMusic())
                    RDMD->type = ePublic;
                }
            bool IsPublicMusic()
                {
                return (RDMD->type == ePublic);
                }
            void IsPublicMusic(bool value)
                {
                if(value)
                    RDMD->type = ePublic;
                else if(IsPublicMusic())
                    RDMD->type = eDefault;
                }
            bool IsDungeonMusic()
                {
                return (RDMD->type == eDungeon);
                }
            void IsDungeonMusic(bool value)
                {
                if(value)
                    RDMD->type = eDungeon;
                else if(IsDungeonMusic())
                    RDMD->type = eDefault;
                }
            bool IsMusicType(unsigned int Type)
                {
                return (RDMD->type == Type);
                }
            void SetMusicType(unsigned int Type)
                {
                RDMD->type = Type;
                }
            };
    public:

        enum REGNType {
            eREGNObjects=2,
            eREGNWeathers=3,
            eREGNMap=4,
            eREGNIcon=5,
            eREGNGrasses=6,
            eREGNSounds=7
            };
        STRING EDID;
        STRING ICON;
        ReqRecordField<GENCLR> RCLR;
        RecordField<GENFID> WNAM;
        std::vector<REGNArea *> Areas;
        std::vector<REGNEntry *> Entries;
        REGNRecord(bool newRecord=false):Record(newRecord) {}
        REGNRecord(const unsigned int &newFormID):Record(newFormID) {}
        REGNRecord(REGNRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            ICON = srcRecord->ICON;
            RCLR = srcRecord->RCLR;
            WNAM = srcRecord->WNAM;

            Areas.clear();
            Areas.resize(srcRecord->Areas.size());
            for(unsigned int x = 0; x < srcRecord->Areas.size(); x++)
                {
                Areas[x] = new REGNArea;
                Areas[x]->RPLI = srcRecord->Areas[x]->RPLI;
                Areas[x]->RPLD = srcRecord->Areas[x]->RPLD;
                }

            Entries.clear();
            Entries.resize(srcRecord->Entries.size());
            for(unsigned int x = 0; x < srcRecord->Entries.size(); x++)
                {
                Entries[x] = new REGNEntry;
                Entries[x]->RDAT = srcRecord->Entries[x]->RDAT;
                Entries[x]->RDOT = srcRecord->Entries[x]->RDOT;
                Entries[x]->RDMP = srcRecord->Entries[x]->RDMP;
                Entries[x]->ICON = srcRecord->Entries[x]->ICON;
                Entries[x]->RDGS = srcRecord->Entries[x]->RDGS;
                Entries[x]->RDMD = srcRecord->Entries[x]->RDMD;
                Entries[x]->RDSD = srcRecord->Entries[x]->RDSD;
                Entries[x]->RDWT = srcRecord->Entries[x]->RDWT;
                }
            return;
            }
        ~REGNRecord()
            {
            for(unsigned int x = 0; x < Areas.size(); x++)
                delete Areas[x];
            for(unsigned int x = 0; x < Entries.size(); x++)
                delete Entries[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            ICON.Unload();
            RCLR.Unload();
            WNAM.Unload();
            for(unsigned int x = 0; x < Areas.size(); x++)
                delete Areas[x];
            Areas.clear();
            for(unsigned int x = 0; x < Entries.size(); x++)
                delete Entries[x];
            Entries.clear();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            FormIDs.push_back(&WNAM.value.fid);
            for(unsigned int x = 0; x < Entries.size(); x++)
                {
                for(unsigned int y = 0; y < Entries[x]->RDOT.size(); y++)
                    FormIDs.push_back(&Entries[x]->RDOT[y].objectId);
                for(unsigned int y = 0; y < Entries[x]->RDGS.size(); y++)
                    FormIDs.push_back(&Entries[x]->RDGS[y].grass);
                for(unsigned int y = 0; y < Entries[x]->RDSD.size(); y++)
                    FormIDs.push_back(&Entries[x]->RDSD[y].sound);
                for(unsigned int y = 0; y < Entries[x]->RDWT.size(); y++)
                    FormIDs.push_back(&Entries[x]->RDWT[y].weather);
                }
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int CreateListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        int DeleteListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        int GetListX2FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListX2Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetListX2ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void GetListX2Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void * GetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned short FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eREGN;}
        char * GetStrType() {return "REGN";}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
    };
