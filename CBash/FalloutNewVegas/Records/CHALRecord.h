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
class CHALRecord : public Record //Challenge
    {
    private:
        struct CHALDATA // Data
            {
            UINT32  challengeType, threshold, flags, interval; // Type, Threshold, Flags, Interval
            UINT8   var1[2], var2[2], var3[4]; //(depends on type)

            CHALDATA();
            ~CHALDATA();

            bool operator ==(const CHALDATA &other) const;
            bool operator !=(const CHALDATA &other) const;
            };

        enum challengeTypeTypes
            {
            eKillFromList = 0,
            eKillFormID,
            eKillInCategory,
            eHitEnemy,
            eDiscoverMapMarker,
            eUseItem,
            eGetItem,
            eUseSkill,
            eDoDamage,
            eUseItemFromList,
            eGetItemFromList,
            eMiscStat
            };

        enum challengeFlags
            {
            fIsStartDisabled    = 0x00000001,
            fIsRecurring        = 0x00000002,
            fIsShowZeroProgress = 0x00000004
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<FORMID> SCRI; //Script
        StringRecord DESC; //Description
        OptSubRecord<CHALDATA> DATA; //Data
        OptSimpleSubRecord<FORMID> SNAM; //(depends on type)
        OptSimpleSubRecord<FORMID> XNAM; //(depends on type)

        CHALRecord(unsigned char *_recData=NULL);
        CHALRecord(CHALRecord *srcRecord);
        ~CHALRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsStartDisabled();
        void   IsStartDisabled(bool value);
        bool   IsRecurring();
        void   IsRecurring(bool value);
        bool   IsShowZeroProgress();
        void   IsShowZeroProgress(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsKillFromList();
        void   IsKillFromList(bool value);
        bool   IsKillFormID();
        void   IsKillFormID(bool value);
        bool   IsKillInCategory();
        void   IsKillInCategory(bool value);
        bool   IsHitEnemy();
        void   IsHitEnemy(bool value);
        bool   IsDiscoverMapMarker();
        void   IsDiscoverMapMarker(bool value);
        bool   IsUseItem();
        void   IsUseItem(bool value);
        bool   IsGetItem();
        void   IsGetItem(bool value);
        bool   IsUseSkill();
        void   IsUseSkill(bool value);
        bool   IsDoDamage();
        void   IsDoDamage(bool value);
        bool   IsUseItemFromList();
        void   IsUseItemFromList(bool value);
        bool   IsGetItemFromList();
        void   IsGetItemFromList(bool value);
        bool   IsMiscStat();
        void   IsMiscStat(bool value);
        bool   IsType(UINT8 Type, bool Exact=false);
        void   SetType(UINT8 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(_FileHandler &SaveHandler);

        bool operator ==(const CHALRecord &other) const;
        bool operator !=(const CHALRecord &other) const;
    };
}