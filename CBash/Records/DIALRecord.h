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
#include "INFORecord.h"
#include <vector>

class DIALRecord : public Record
    {
    private:
        enum DIALSubRecords {
            eEDID = 0x44494445,
            eQSTI = 0x49545351,
            eQSTR = 0x52545351,
            eFULL = 0x4C4C5546,
            eDATA = 0x41544144
            };
    public:
        enum eDialogType
            {
            eTopic        = 0,
            eConversation = 1,
            eCombat       = 2,
            ePersuasion   = 3,
            eDetection    = 4,
            eService      = 5,
            eMisc         = 6
            };
        StringRecord EDID;
        std::vector<unsigned long *> QSTI;
        std::vector<unsigned long *> QSTR;
        StringRecord FULL;
        ReqSubRecord<GENFLAG> DATA;
        std::vector<INFORecord *> INFO;

        DIALRecord(bool newRecord=false):Record(newRecord) {}
        DIALRecord(DIALRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eDIAL)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            QSTI.clear();
            QSTI.resize(srcRecord->QSTI.size());
            for(unsigned long x = 0; x < srcRecord->QSTI.size(); x++)
                QSTI[x] = new unsigned long(*srcRecord->QSTI[x]);
            FULL = srcRecord->FULL;
            DATA = srcRecord->DATA;
            return;
            }
        ~DIALRecord()
            {
            for(unsigned long x = 0; x < QSTI.size(); x++)
                delete QSTI[x];
            for(unsigned long x = 0; x < QSTR.size(); x++)
                delete QSTR[x];
            for(unsigned long x = 0; x < INFO.size(); x++)
                delete INFO[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();

            for(unsigned long x = 0; x < QSTI.size(); x++)
                delete QSTI[x];
            QSTI.clear();

            for(unsigned long x = 0; x < QSTR.size(); x++)
                delete QSTR[x];
            QSTR.clear();

            FULL.Unload();
            DATA.Unload();
            }

        bool HasSubRecords() {return true;}

        bool VisitSubRecords(const unsigned long &RecordType, RecordOp &op)
            {
            bool stop;

            if(RecordType == NULL || RecordType == eINFO)
                for(unsigned long x = 0; x < INFO.size();)
                    {
                    stop = op.Accept((Record **)&INFO[x]);
                    if(INFO[x] == NULL)
                        INFO.erase(INFO.begin() + x);
                    else
                        ++x;
                    if(stop)
                        return stop;
                    }

            return op.Stop();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            for(unsigned long x = 0; x < QSTI.size(); x++)
                op.Accept(*QSTI[x]);
            for(unsigned long x = 0; x < QSTR.size(); x++)
                op.Accept(*QSTR[x]);

            return op.Stop();
            }

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        unsigned long GetFieldArraySize(const unsigned long Field);
        void GetFieldArray(const unsigned long Field, void **FieldValues);
        void SetField(const unsigned long Field, char *FieldValue);
        void SetField(const unsigned long Field, unsigned long FieldValue[], unsigned long nSize);
        void SetField(const unsigned long Field, unsigned char FieldValue);

        signed long DeleteField(const unsigned long Field);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eDIAL;}
        char *GetStrType() {return "DIAL";}
        signed long WriteRecord(_FileHandler &SaveHandler);

        bool IsTopic()
            {
            return (DATA.value.flags == eTopic);
            }
        void IsTopic(bool value)
            {
            if(value)
                DATA.value.flags = eTopic;
            else if(IsTopic())
                DATA.value.flags = eConversation;
            }
        bool IsConversation()
            {
            return (DATA.value.flags == eConversation);
            }
        void IsConversation(bool value)
            {
            if(value)
                DATA.value.flags = eConversation;
            else if(IsConversation())
                DATA.value.flags = eTopic;
            }
        bool IsCombat()
            {
            return (DATA.value.flags == eCombat);
            }
        void IsCombat(bool value)
            {
            if(value)
                DATA.value.flags = eCombat;
            else if(IsCombat())
                DATA.value.flags = eTopic;
            }
        bool IsPersuasion()
            {
            return (DATA.value.flags == ePersuasion);
            }
        void IsPersuasion(bool value)
            {
            if(value)
                DATA.value.flags = ePersuasion;
            else if(IsPersuasion())
                DATA.value.flags = eTopic;
            }
        bool IsDetection()
            {
            return (DATA.value.flags == eDetection);
            }
        void IsDetection(bool value)
            {
            if(value)
                DATA.value.flags = eDetection;
            else if(IsDetection())
                DATA.value.flags = eTopic;
            }
        bool IsService()
            {
            return (DATA.value.flags == eService);
            }
        void IsService(bool value)
            {
            if(value)
                DATA.value.flags = eService;
            else if(IsService())
                DATA.value.flags = eTopic;
            }
        bool IsMisc()
            {
            return (DATA.value.flags == eMisc);
            }
        void IsMisc(bool value)
            {
            if(value)
                DATA.value.flags = eMisc;
            else if(IsMisc())
                DATA.value.flags = eTopic;
            }
        bool IsType(unsigned char Type)
            {
            return (DATA.value.flags == Type);
            }
        void SetType(unsigned char Type)
            {
            DATA.value.flags = Type;
            }
    };
