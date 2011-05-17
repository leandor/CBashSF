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
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class DIALRecord : public FNVRecord //Dialog Topic
    {
    private:
        struct DIALUNK
            {
            ReqSimpleSubRecord<FORMID> INFC; //Unknown
            OptSimpleSubRecord<SINT32> INFX; //Unknown (index? increases by one for each INFC)

            void Write(FileWriter &writer);

            bool operator ==(const DIALUNK &other) const;
            bool operator !=(const DIALUNK &other) const;
            };

        struct DIALQSTI
            {
            ReqSimpleSubRecord<FORMID> QSTI; //Quest
            UnorderedSparseArray<DIALUNK *> Unknown; //Unknown

            void Write(FileWriter &writer);

            bool operator ==(const DIALQSTI &other) const;
            bool operator !=(const DIALQSTI &other) const;
            };

        struct DIALQSTR
            {
            ReqSimpleSubRecord<FORMID> QSTR; //Quest
            UnorderedSparseArray<DIALUNK *> Unknown; //Unknown

            void Write(FileWriter &writer);

            bool operator ==(const DIALQSTR &other) const;
            bool operator !=(const DIALQSTR &other) const;
            };

        struct DIALDATA
            {
            UINT8   dialType; //Type
            UINT8   flags; //Flags

            DIALDATA();
            ~DIALDATA();

            bool operator ==(const DIALDATA &other) const;
            bool operator !=(const DIALDATA &other) const;
            };

        enum eDialogType
            {
            eTopic        = 0,
            eConversation = 1,
            eCombat       = 2,
            ePersuasion   = 3,
            eDetection    = 4,
            eService      = 5,
            eMisc         = 6,
            eRadio        = 7
            };

        enum flagsFlags
            {
            fIsRumors   = 0x01,
            fIsTopLevel = 0x02
            };
    public:
        StringRecord EDID; //Editor ID
        UnorderedSparseArray<DIALQSTI *> QSTI; //Added Quests
        UnorderedSparseArray<DIALQSTR *> QSTR; //Removed Quests
        StringRecord FULL; //Name
        OptSimpleFloatSubRecord<flt_0> PNAM; //Priority
        StringRecord TDUM; //Unknown
        ReqSubRecord<DIALDATA> DATA; //Dialog Data
        std::vector<Record *> INFO;

        DIALRecord(unsigned char *_recData=NULL);
        DIALRecord(DIALRecord *srcRecord);
        ~DIALRecord();

        bool   HasSubRecords();
        bool   VisitSubRecords(const UINT32 &RecordType, RecordOp &op);
        bool   VisitFormIDs(FormIDOp &op);

        bool   IsTopic();
        void   IsTopic(bool value);
        bool   IsConversation();
        void   IsConversation(bool value);
        bool   IsCombat();
        void   IsCombat(bool value);
        bool   IsPersuasion();
        void   IsPersuasion(bool value);
        bool   IsDetection();
        void   IsDetection(bool value);
        bool   IsService();
        void   IsService(bool value);
        bool   IsMisc();
        void   IsMisc(bool value);
        bool   IsRadio();
        void   IsRadio(bool value);
        bool   IsType(UINT8 Type);
        void   SetType(UINT8 Type);

        bool   IsRumors();
        void   IsRumors(bool value);
        bool   IsTopLevel();
        void   IsTopLevel(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);


        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const DIALRecord &other) const;
        bool operator !=(const DIALRecord &other) const;
    };
}