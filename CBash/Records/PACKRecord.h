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

class PACKRecord : public Record
    {
    private:
        enum PACKRecordFields {
            eEDID = 0x44494445,
            ePKDT = 0x54444B50,
            ePLDT = 0x54444C50,
            ePSDT = 0x54445350,
            ePTDT = 0x54445450,
            eCTDA = 0x41445443,
            eCTDT = 0x54445443
            };
        struct PACKPKDT
            {
            unsigned int flags;
            unsigned char aiType, unused1[3];
            PACKPKDT():flags(0), aiType(0)
                {
                memset(&unused1, 0x00, 3);
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
                        printf("flags    = %u\n", flags);
                        }
                    PrintIndent(indentation);
                    if(PACKAIType_Name.find(aiType) != PACKAIType_Name.end())
                        printf("aiType   = %u, %s\n", aiType, PACKAIType_Name.find(aiType)->second);
                    else
                        printf("aiType   = %u, Unknown aiType!!!\n", aiType);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1  = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct PACKPLDT
            {
            int locType;
            unsigned int locId;
            int locRadius;
            PACKPLDT():locType(0), locId(0), locRadius(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    if(PACKLocType_Name.find(locType) != PACKLocType_Name.end())
                        printf("locType    = %u, %s\n", locType, PACKLocType_Name.find(locType)->second);
                    else
                        printf("locType    = %u, Unknown locType!!!\n", locType);
                    PrintIndent(indentation);
                    if(locType != 5)
                        printf("locId      = %s\n", PrintFormID(locId));
                    else
                        printf("locId      = %u\n", locId);
                    PrintIndent(indentation);
                    printf("locRadius  = %i\n", locRadius);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct PACKPSDT
            {
            char month, day;
            unsigned char date;
            char time;
            int duration;
            PACKPSDT():month(0), day(0), date(0), time(0), duration(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("month     = %i\n", month);
                    PrintIndent(indentation);
                    printf("day       = %i\n", day);
                    PrintIndent(indentation);
                    printf("date      = %u\n", date);
                    PrintIndent(indentation);
                    printf("time      = %i\n", time);
                    PrintIndent(indentation);
                    printf("duration  = %i\n", duration);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct PACKPTDT
            {
            int targetType;
            unsigned int targetId;
            int targetCount;
            PACKPTDT():targetType(0), targetId(0), targetCount(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    if(PACKTargetType_Name.find(targetType) != PACKTargetType_Name.end())
                        printf("targetType  = %u, %s\n", targetType, PACKTargetType_Name.find(targetType)->second);
                    else
                        printf("targetType  = %u, Unknown targetType!!!\n", targetType);
                    PrintIndent(indentation);
                    if(targetType != 2)
                        printf("targetId    = %s\n", PrintFormID(targetId));
                    else
                        printf("targetId    = %u\n", targetId);
                    PrintIndent(indentation);
                    printf("targetCount = %i\n", targetCount);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        enum flagsFlags
            {
            fIsOffersServices    = 0x00000001,
            fIsMustReachLocation = 0x00000002,
            fIsMustComplete      = 0x00000004,
            fIsLockAtStart       = 0x00000008,
            fIsLockAtEnd         = 0x00000010,
            fIsLockAtLocation    = 0x00000020,
            fIsUnlockAtStart     = 0x00000040,
            fIsUnlockAtEnd       = 0x00000080,
            fIsUnlockAtLocation  = 0x00000100,
            fIsContinueIfPcNear  = 0x00000200,
            fIsOncePerDay        = 0x00000400,
            fIsSkipFallout       = 0x00001000,
            fIsAlwaysRun         = 0x00002000,
            fIsAlwaysSneak       = 0x00020000,
            fIsAllowSwimming     = 0x00040000,
            fIsAllowFalls        = 0x00080000,
            fIsUnequipArmor      = 0x00100000,
            fIsUnequipWeapons    = 0x00200000,
            fIsDefensiveCombat   = 0x00400000,
            fIsUseHorse          = 0x00800000,
            fIsNoIdleAnims       = 0x01000000
            };
        enum aiTypeType
            {
            eAIFind          = 0,
            eAIFollow        = 1,
            eAIEscort        = 2,
            eAIEat           = 3,
            eAISleep         = 4,
            eAIWander        = 5,
            eAITravel        = 6,
            eAIAccompany     = 7,
            eAIUseItemAt     = 8,
            eAIAmbush        = 9,
            eAIFleeNotCombat = 10,
            eAICastMagic     = 11
            };
        enum locTypeType
            {
            eLocNearReference       = 0,
            eLocInCell              = 1,
            eLocNearCurrentLocation = 2,
            eLocNearEditorLocation  = 3,
            eLocObjectID            = 4,
            eLocObjectType          = 5
            };
        enum targetTypeType
            {
            eTargetReference   = 0,
            eTargetObjectID    = 1,
            eTargetObjectType  = 2
            };
        STRING EDID;
        ReqRecordField<PACKPKDT> PKDT;
        OptRecordField<PACKPLDT> PLDT;
        ReqRecordField<PACKPSDT> PSDT;
        OptRecordField<PACKPTDT> PTDT;
        std::vector<ReqRecordField<GENCTDA> *> CTDA;

        PACKRecord(bool newRecord=false):Record(newRecord) {}
        PACKRecord(const unsigned int &newFormID):Record(newFormID) {}
        PACKRecord(PACKRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            PKDT = srcRecord->PKDT;
            PLDT = srcRecord->PLDT;
            PSDT = srcRecord->PSDT;
            PTDT = srcRecord->PTDT;
            CTDA.clear();
            CTDA.resize(srcRecord->CTDA.size());
            for(unsigned int x = 0; x < srcRecord->CTDA.size(); x++)
                {
                CTDA[x] = new ReqRecordField<GENCTDA>;
                *CTDA[x] = *srcRecord->CTDA[x];
                }
            return;
            }
        ~PACKRecord()
            {
            for(unsigned int x = 0; x < CTDA.size(); x++)
                delete CTDA[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            PKDT.Unload();
            PLDT.Unload();
            PSDT.Unload();
            PTDT.Unload();

            for(unsigned int x = 0; x < CTDA.size(); x++)
                delete CTDA[x];
            CTDA.clear();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            std::pair<unsigned int, unsigned int> CTDAFunction;
            std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
            if(PLDT.IsLoaded() && PLDT->locType != 5)
                FormIDs.push_back(&PLDT->locId);
            if(PTDT.IsLoaded() && PTDT->targetType != 2)
                FormIDs.push_back(&PTDT->targetId);
            for(unsigned int x = 0; x < CTDA.size(); x++)
                {
                curCTDAFunction = Function_Arguments.find(CTDA[x]->value.ifunc);
                if(curCTDAFunction != Function_Arguments.end())
                    {
                    CTDAFunction = curCTDAFunction->second;
                    if(CTDAFunction.first == eFID)
                        FormIDs.push_back(&CTDA[x]->value.param1);
                    if(CTDAFunction.second == eFID)
                        FormIDs.push_back(&CTDA[x]->value.param2);
                    }
                }
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return ePACK;}
        char * GetStrType() {return "PACK";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsAIFind()
            {
            return (PKDT.value.aiType == eAIFind);
            }
        void IsAIFind(bool value)
            {
            if(value)
                PKDT.value.aiType = eAIFind;
            else if(IsAIFind())
                PKDT.value.aiType = eAIFollow;
            }
        bool IsAIFollow()
            {
            return (PKDT.value.aiType == eAIFollow);
            }
        void IsAIFollow(bool value)
            {
            if(value)
                PKDT.value.aiType = eAIFollow;
            else if(IsAIFollow())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAIEscort()
            {
            return (PKDT.value.aiType == eAIEscort);
            }
        void IsAIEscort(bool value)
            {
            if(value)
                PKDT.value.aiType = eAIEscort;
            else if(IsAIEscort())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAIEat()
            {
            return (PKDT.value.aiType == eAIEat);
            }
        void IsAIEat(bool value)
            {
            if(value)
                PKDT.value.aiType = eAIEat;
            else if(IsAIEat())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAISleep()
            {
            return (PKDT.value.aiType == eAISleep);
            }
        void IsAISleep(bool value)
            {
            if(value)
                PKDT.value.aiType = eAISleep;
            else if(IsAISleep())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAIWander()
            {
            return (PKDT.value.aiType == eAIWander);
            }
        void IsAIWander(bool value)
            {
            if(value)
                PKDT.value.aiType = eAIWander;
            else if(IsAIWander())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAITravel()
            {
            return (PKDT.value.aiType == eAITravel);
            }
        void IsAITravel(bool value)
            {
            if(value)
                PKDT.value.aiType = eAITravel;
            else if(IsAIFollow())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAIAccompany()
            {
            return (PKDT.value.aiType == eAIAccompany);
            }
        void IsAIAccompany(bool value)
            {
            if(value)
                PKDT.value.aiType = eAIAccompany;
            else if(IsAIAccompany())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAIUseItemAt()
            {
            return (PKDT.value.aiType == eAIUseItemAt);
            }
        void IsAIUseItemAt(bool value)
            {
            if(value)
                PKDT.value.aiType = eAIUseItemAt;
            else if(IsAIUseItemAt())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAIAmbush()
            {
            return (PKDT.value.aiType == eAIAmbush);
            }
        void IsAIAmbush(bool value)
            {
            if(value)
                PKDT.value.aiType = eAIAmbush;
            else if(IsAIAmbush())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAIFleeNotCombat()
            {
            return (PKDT.value.aiType == eAIFleeNotCombat);
            }
        void IsAIFleeNotCombat(bool value)
            {
            if(value)
                PKDT.value.aiType = eAIFleeNotCombat;
            else if(IsAIFleeNotCombat())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAICastMagic()
            {
            return (PKDT.value.aiType == eAICastMagic);
            }
        void IsAICastMagic(bool value)
            {
            if(value)
                PKDT.value.aiType = eAICastMagic;
            else if(IsAICastMagic())
                PKDT.value.aiType = eAIFind;
            }
        bool IsAIType(unsigned char Type)
            {
            return (PKDT.value.aiType == Type);
            }
        void SetAIType(unsigned char Type)
            {
            PKDT.value.aiType = Type;
            }
        bool IsOffersServices()
            {
            return (PKDT.value.flags & fIsOffersServices) != 0;
            }
        void IsOffersServices(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsOffersServices;
            else
                PKDT.value.flags &= ~fIsOffersServices;
            }
        bool IsMustReachLocation()
            {
            return (PKDT.value.flags & fIsMustReachLocation) != 0;
            }
        void IsMustReachLocation(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsMustReachLocation;
            else
                PKDT.value.flags &= ~fIsMustReachLocation;
            }
        bool IsMustComplete()
            {
            return (PKDT.value.flags & fIsMustComplete) != 0;
            }
        void IsMustComplete(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsMustComplete;
            else
                PKDT.value.flags &= ~fIsMustComplete;
            }
        bool IsLockAtStart()
            {
            return (PKDT.value.flags & fIsLockAtStart) != 0;
            }
        void IsLockAtStart(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsLockAtStart;
            else
                PKDT.value.flags &= ~fIsLockAtStart;
            }
        bool IsLockAtEnd()
            {
            return (PKDT.value.flags & fIsLockAtEnd) != 0;
            }
        void IsLockAtEnd(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsLockAtEnd;
            else
                PKDT.value.flags &= ~fIsLockAtEnd;
            }
        bool IsLockAtLocation()
            {
            return (PKDT.value.flags & fIsLockAtLocation) != 0;
            }
        void IsLockAtLocation(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsLockAtLocation;
            else
                PKDT.value.flags &= ~fIsLockAtLocation;
            }
        bool IsUnlockAtStart()
            {
            return (PKDT.value.flags & fIsUnlockAtStart) != 0;
            }
        void IsUnlockAtStart(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsUnlockAtStart;
            else
                PKDT.value.flags &= ~fIsUnlockAtStart;
            }
        bool IsUnlockAtEnd()
            {
            return (PKDT.value.flags & fIsUnlockAtEnd) != 0;
            }
        void IsUnlockAtEnd(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsUnlockAtEnd;
            else
                PKDT.value.flags &= ~fIsUnlockAtEnd;
            }
        bool IsUnlockAtLocation()
            {
            return (PKDT.value.flags & fIsUnlockAtLocation) != 0;
            }
        void IsUnlockAtLocation(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsUnlockAtLocation;
            else
                PKDT.value.flags &= ~fIsUnlockAtLocation;
            }
        bool IsContinueIfPcNear()
            {
            return (PKDT.value.flags & fIsContinueIfPcNear) != 0;
            }
        void IsContinueIfPcNear(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsContinueIfPcNear;
            else
                PKDT.value.flags &= ~fIsContinueIfPcNear;
            }
        bool IsOncePerDay()
            {
            return (PKDT.value.flags & fIsOncePerDay) != 0;
            }
        void IsOncePerDay(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsOncePerDay;
            else
                PKDT.value.flags &= ~fIsOncePerDay;
            }
        bool IsSkipFallout()
            {
            return (PKDT.value.flags & fIsSkipFallout) != 0;
            }
        void IsSkipFallout(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsSkipFallout;
            else
                PKDT.value.flags &= ~fIsSkipFallout;
            }
        bool IsAlwaysRun()
            {
            return (PKDT.value.flags & fIsAlwaysRun) != 0;
            }
        void IsAlwaysRun(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsAlwaysRun;
            else
                PKDT.value.flags &= ~fIsAlwaysRun;
            }
        bool IsAlwaysSneak()
            {
            return (PKDT.value.flags & fIsAlwaysSneak) != 0;
            }
        void IsAlwaysSneak(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsAlwaysSneak;
            else
                PKDT.value.flags &= ~fIsAlwaysSneak;
            }
        bool IsAllowSwimming()
            {
            return (PKDT.value.flags & fIsAllowSwimming) != 0;
            }
        void IsAllowSwimming(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsAllowSwimming;
            else
                PKDT.value.flags &= ~fIsAllowSwimming;
            }
        bool IsAllowFalls()
            {
            return (PKDT.value.flags & fIsAllowFalls) != 0;
            }
        void IsAllowFalls(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsAllowFalls;
            else
                PKDT.value.flags &= ~fIsAllowFalls;
            }
        bool IsUnequipArmor()
            {
            return (PKDT.value.flags & fIsUnequipArmor) != 0;
            }
        void IsUnequipArmor(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsUnequipArmor;
            else
                PKDT.value.flags &= ~fIsUnequipArmor;
            }
        bool IsUnequipWeapons()
            {
            return (PKDT.value.flags & fIsUnequipWeapons) != 0;
            }
        void IsUnequipWeapons(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsUnequipWeapons;
            else
                PKDT.value.flags &= ~fIsUnequipWeapons;
            }
        bool IsDefensiveCombat()
            {
            return (PKDT.value.flags & fIsDefensiveCombat) != 0;
            }
        void IsDefensiveCombat(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsDefensiveCombat;
            else
                PKDT.value.flags &= ~fIsDefensiveCombat;
            }
        bool IsUseHorse()
            {
            return (PKDT.value.flags & fIsUseHorse) != 0;
            }
        void IsUseHorse(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsUseHorse;
            else
                PKDT.value.flags &= ~fIsUseHorse;
            }
        bool IsNoIdleAnims()
            {
            return (PKDT.value.flags & fIsNoIdleAnims) != 0;
            }
        void IsNoIdleAnims(bool value)
            {
            if(value)
                PKDT.value.flags |= fIsNoIdleAnims;
            else
                PKDT.value.flags &= ~fIsNoIdleAnims;
            }

        bool IsFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(Exact)
                return (PKDT.value.flags & Mask) == Mask;
            else
                return (PKDT.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned int Mask)
            {
            PKDT.value.flags = Mask;
            }
        bool IsLocNearReference()
            {
            if(!PLDT.IsLoaded()) return false;
            return (PLDT->locType == eLocNearReference);
            }
        void IsLocNearReference(bool value)
            {
            if(!PLDT.IsLoaded()) return;
            if(value)
                PLDT->locType = eLocNearReference;
            else if(IsLocNearReference())
                PLDT->locType = eLocInCell;
            }
        bool IsLocInCell()
            {
            if(!PLDT.IsLoaded()) return false;
            return (PLDT->locType == eLocInCell);
            }
        void IsLocInCell(bool value)
            {
            if(!PLDT.IsLoaded()) return;
            if(value)
                PLDT->locType = eLocInCell;
            else if(IsLocInCell())
                PLDT->locType = eLocNearReference;
            }
        bool IsLocNearCurrentLoc()
            {
            if(!PLDT.IsLoaded()) return false;
            return (PLDT->locType == eLocNearCurrentLocation);
            }
        void IsLocNearCurrentLoc(bool value)
            {
            if(!PLDT.IsLoaded()) return;
            if(value)
                PLDT->locType = eLocNearCurrentLocation;
            else if(IsLocNearCurrentLoc())
                PLDT->locType = eLocNearReference;
            }
        bool IsLocNearEditorLoc()
            {
            if(!PLDT.IsLoaded()) return false;
            return (PLDT->locType == eLocNearEditorLocation);
            }
        void IsLocNearEditorLoc(bool value)
            {
            if(!PLDT.IsLoaded()) return;
            if(value)
                PLDT->locType = eLocNearEditorLocation;
            else if(IsLocNearEditorLoc())
                PLDT->locType = eLocNearReference;
            }
        bool IsLocObjectID()
            {
            if(!PLDT.IsLoaded()) return false;
            return (PLDT->locType == eLocObjectID);
            }
        void IsLocObjectID(bool value)
            {
            if(!PLDT.IsLoaded()) return;
            if(value)
                PLDT->locType = eLocObjectID;
            else if(IsLocObjectID())
                PLDT->locType = eLocNearReference;
            }
        bool IsLocObjectType()
            {
            if(!PLDT.IsLoaded()) return false;
            return (PLDT->locType == eLocObjectType);
            }
        void IsLocObjectType(bool value)
            {
            if(!PLDT.IsLoaded()) return;
            if(value)
                PLDT->locType = eLocObjectType;
            else if(IsLocObjectType())
                PLDT->locType = eLocNearReference;
            }
        bool IsLocType(int Type)
            {
            if(!PLDT.IsLoaded()) return false;
            return (PLDT->locType == Type);
            }
        void SetLocType(int Type)
            {
            if(!PLDT.IsLoaded()) return;
            PLDT->locType = Type;
            }
        bool IsTargetReference()
            {
            if(!PTDT.IsLoaded()) return false;
            return (PTDT->targetType == eTargetReference);
            }
        void IsTargetReference(bool value)
            {
            if(!PTDT.IsLoaded()) return;
            if(value)
                PTDT->targetType = eTargetReference;
            else if(IsTargetReference())
                PTDT->targetType = eTargetObjectID;
            }
        bool IsTargetObjectID()
            {
            if(!PTDT.IsLoaded()) return false;
            return (PTDT->targetType == eTargetObjectID);
            }
        void IsTargetObjectID(bool value)
            {
            if(!PTDT.IsLoaded()) return;
            if(value)
                PTDT->targetType = eTargetObjectID;
            else if(IsTargetObjectID())
                PTDT->targetType = eTargetReference;
            }
        bool IsTargetObjectType()
            {
            if(!PTDT.IsLoaded()) return false;
            return (PTDT->targetType == eTargetObjectType);
            }
        void IsTargetObjectType(bool value)
            {
            if(!PTDT.IsLoaded()) return;
            if(value)
                PTDT->targetType = eTargetObjectType;
            else if(IsTargetObjectType())
                PTDT->targetType = eTargetReference;
            }
        bool IsTargetType(int Type)
            {
            if(!PTDT.IsLoaded()) return false;
            return (PTDT->targetType == Type);
            }
        void SetTargetType(int Type)
            {
            if(!PTDT.IsLoaded()) return;
            PTDT->targetType = Type;
            }
    };
