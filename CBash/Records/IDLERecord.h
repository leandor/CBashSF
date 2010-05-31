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

class IDLERecord : public Record
    {
    private:
        enum IDLERecordFields {
            eEDID = 0x44494445,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eCTDA = 0x41445443,
            eCTDT = 0x54445443,

            eANAM = 0x4D414E41,
            eDATA = 0x41544144
            };
        struct IDLEANAM
            {
            unsigned char group;
            IDLEANAM():group(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    if(IDLEGroup_Name.find(group) != IDLEGroup_Name.end())
                        printf("group = %u, %s\n", group, IDLEGroup_Name.find(group)->second);
                    else
                        printf("group = %u, Unknown Group!!!\n", group);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct IDLEDATA
            {
            unsigned int parent, prevId;
            IDLEDATA():parent(0), prevId(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("parent = %s\n", PrintFormID(parent));
                    PrintIndent(indentation);
                    printf("prevId = %s\n", PrintFormID(prevId));
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        enum groupType
            {
            eLowerBody   = 0x00000000,
            eLeftArm     = 0x00000001,
            eLeftHand    = 0x00000002,
            eRightArm    = 0x00000003,
            eSpecialIdle = 0x00000004,
            eWholeBody   = 0x00000005,
            eUpperBody   = 0x00000006
            };
        enum groupFlag
            {
            fIsNotReturnFile = 0x00000080
            };
        STRING EDID;
        GENMODEL MODL;
        std::vector<ReqRecordField<GENCTDA> *> CTDA;
        ReqRecordField<IDLEANAM> ANAM;
        ReqRecordField<IDLEDATA> DATA;

        IDLERecord(bool newRecord=false):Record(newRecord) {}
        IDLERecord(const unsigned int &newFormID):Record(newFormID) {}
        IDLERecord(IDLERecord *srcRecord):Record(true)
            {
            std::pair<unsigned int, unsigned int> CTDAFunction;
            std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
            CTDA.clear();
            CTDA.resize(srcRecord->CTDA.size());
            for(unsigned int x = 0; x < srcRecord->CTDA.size(); x++)
                {
                CTDA[x] = new ReqRecordField<GENCTDA>;
                *CTDA[x] = *srcRecord->CTDA[x];
                }
            ANAM = srcRecord->ANAM;
            DATA = srcRecord->DATA;
            return;
            }
        ~IDLERecord()
            {
            for(unsigned int x = 0; x < CTDA.size(); x++)
                delete CTDA[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            MODL.MODB.Unload();
            MODL.MODL.Unload();
            MODL.MODT.Unload();
            for(unsigned int x = 0; x < CTDA.size(); x++)
                delete CTDA[x];
            CTDA.clear();
            ANAM.Unload();
            DATA.Unload();
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            std::pair<unsigned int, unsigned int> CTDAFunction;
            std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
            for(unsigned int x = 0; x < CTDA.size(); x++)
                {
                curCTDAFunction = Function_Arguments.find(CTDA[x]->value.ifunc);
                if(curCTDAFunction != Function_Arguments.end())
                    {
                    CTDAFunction = curCTDAFunction->second;
                    if(CTDAFunction.first == eFID)
                        FormIDHandler.ExpandFormID(CTDA[x]->value.param1);
                    if(CTDAFunction.second == eFID)
                        FormIDHandler.ExpandFormID(CTDA[x]->value.param2);
                    }
                }
            FormIDHandler.ExpandFormID(DATA.value.parent);
            FormIDHandler.ExpandFormID(DATA.value.prevId);
            }
        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            std::pair<unsigned int, unsigned int> CTDAFunction;
            std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
            for(unsigned int x = 0; x < CTDA.size(); x++)
                {
                curCTDAFunction = Function_Arguments.find(CTDA[x]->value.ifunc);
                if(curCTDAFunction != Function_Arguments.end())
                    {
                    CTDAFunction = curCTDAFunction->second;
                    if(CTDAFunction.first == eFID)
                        FormIDHandler.CollapseFormID(CTDA[x]->value.param1);
                    if(CTDAFunction.second == eFID)
                        FormIDHandler.CollapseFormID(CTDA[x]->value.param2);
                    }
                }
            FormIDHandler.CollapseFormID(DATA.value.parent);
            FormIDHandler.CollapseFormID(DATA.value.prevId);
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
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eIDLE;}
        char * GetStrType() {return "IDLE";}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
        bool IsLowerBody()
            {
            return ((ANAM.value.group & 0x0F) == eLowerBody);
            }
        void IsLowerBody(bool value)
            {
            if(value)
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLowerBody;
                }
            else if(IsLowerBody())
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLeftArm;
                }
            }
        bool IsLeftArm()
            {
            return ((ANAM.value.group & 0x0F) == eLeftArm);
            }
        void IsLeftArm(bool value)
            {
            if(value)
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLeftArm;
                }
            else if(IsLeftArm())
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLowerBody;
                }
            }
        bool IsLeftHand()
            {
            return ((ANAM.value.group & 0x0F) == eLeftHand);
            }
        void IsLeftHand(bool value)
            {
            if(value)
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLeftHand;
                }
            else if(IsLeftHand())
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLowerBody;
                }
            }
        bool IsRightArm()
            {
            return ((ANAM.value.group & 0x0F) == eRightArm);
            }
        void IsRightArm(bool value)
            {
            if(value)
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eRightArm;
                }
            else if(IsRightArm())
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLowerBody;
                }
            }
        bool IsSpecialIdle()
            {
            return ((ANAM.value.group & 0x0F) == eSpecialIdle);
            }
        void IsSpecialIdle(bool value)
            {
            if(value)
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eSpecialIdle;
                }
            else if(IsLeftArm())
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLowerBody;
                }
            }
        bool IsWholeBody()
            {
            return ((ANAM.value.group & 0x0F) == eWholeBody);
            }
        void IsWholeBody(bool value)
            {
            if(value)
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eWholeBody;
                }
            else if(IsWholeBody())
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLowerBody;
                }
            }
        bool IsUpperBody()
            {
            return ((ANAM.value.group & 0x0F) == eUpperBody);
            }
        void IsUpperBody(bool value)
            {
            if(value)
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eUpperBody;
                }
            else if(IsUpperBody())
                {
                ANAM.value.group &= 0xF0;
                ANAM.value.group |= eLowerBody;
                }
            }
        bool IsType(unsigned char Type)
            {
            return ((ANAM.value.group & 0x0F) == (Type & 0x0F));
            }
        void SetType(unsigned char Type)
            {
            Type &= 0x0F;
            ANAM.value.group &= 0xF0;
            ANAM.value.group |= Type;
            }
        bool IsNotReturnFile()
            {
            return (ANAM.value.group & fIsNotReturnFile) != 0;
            }
        void IsNotReturnFile(bool value)
            {
            if(value)
                ANAM.value.group |= fIsNotReturnFile;
            else
                ANAM.value.group &= ~fIsNotReturnFile;
            }
        bool IsReturnFile()
            {
            return !(IsNotReturnFile());
            }
        void IsReturnFile(bool value)
            {
            if(value)
                IsNotReturnFile(false);
            else
                IsNotReturnFile(true);
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return ((ANAM.value.group & 0xF0) & (Mask & 0xF0)) == Mask;
            else
                return ((ANAM.value.group & 0xF0) & (Mask & 0xF0)) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            Mask &= 0xF0;
            ANAM.value.group &= 0x0F;
            ANAM.value.group |= Mask;
            }
    };
