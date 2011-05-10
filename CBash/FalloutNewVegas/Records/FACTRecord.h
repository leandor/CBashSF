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
struct sortRNAM;

class FACTRecord : public FNVRecord //Faction
    {
    private:
        struct FACTDATA // older format is a single UINT8 flag. It updates itself without any special action
            {
            UINT16  flags;
            UINT8   unused1[2];

            FACTDATA();
            ~FACTDATA();

            bool operator ==(const FACTDATA &other) const;
            bool operator !=(const FACTDATA &other) const;
            };

        struct FACTRNAM // Rank
            {
            ReqSimpleSubRecord<SINT32> RNAM; //Rank#
            StringRecord MNAM, FNAM, INAM; // Male, Female, Insignia (Unused)

            void Write(FileWriter &writer);

            bool operator ==(const FACTRNAM &other) const;
            bool operator !=(const FACTRNAM &other) const;
            };

        enum flagsFlags
            {
            fIsHiddenFromPC  = 0x0001,
            fIsEvil          = 0x0002,
            fIsSpecialCombat = 0x0004,
            fIsTrackCrime    = 0x0100,
            fIsAllowSell     = 0x0200
            };

        friend sortRNAM;

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OrderedSparseArray<FNVXNAM *> XNAM; //Relations, not sure if record order matters
        ReqSubRecord<FACTDATA> DATA; //Data
        SemiOptSimpleFloatSubRecord<flt_1> CNAM; //Unused
        OrderedSparseArray<FACTRNAM *, sortRNAM> RNAM; // Ranks
        OptSimpleSubRecord<FORMID> WMI1; //Reputation

        FACTRecord(unsigned char *_recData=NULL);
        FACTRecord(FACTRecord *srcRecord);
        ~FACTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsHiddenFromPC();
        void   IsHiddenFromPC(bool value);
        bool   IsEvil();
        void   IsEvil(bool value);
        bool   IsSpecialCombat();
        void   IsSpecialCombat(bool value);
        bool   IsTrackCrime();
        void   IsTrackCrime(bool value);
        bool   IsAllowSell();
        void   IsAllowSell(bool value);
        bool   IsFlagMask(UINT16 Mask, bool Exact=false);
        void   SetFlagMask(UINT16 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const FACTRecord &other) const;
        bool operator !=(const FACTRecord &other) const;
    };

struct sortRNAM
    {
    bool operator()(const FACTRecord::FACTRNAM *lhs, const FACTRecord::FACTRNAM *rhs) const;
    };
}