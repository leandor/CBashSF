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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class CLASRecord : public FNVRecord //Class
    {
    private:
        struct CLASDATA
            {
            SINT32  tagSkills[4];
            UINT32  flags, services;
            SINT8   trainSkill;
            UINT8   trainLevel;
            SINT8   unused1[2];

            CLASDATA();
            ~CLASDATA();

            bool operator ==(const CLASDATA &other) const;
            bool operator !=(const CLASDATA &other) const;
            };

        struct CLASATTR
            {
            UINT8   strength, perception, endurance,
                    charisma, intelligence, agility, luck;

            CLASATTR();
            ~CLASATTR();

            bool operator ==(const CLASATTR &other) const;
            bool operator !=(const CLASATTR &other) const;
            };

        enum flagsFlags
            {
            fIsPlayable = 0x00000001,
            fIsGuard    = 0x00000002
            };

        enum servicesFlags
            {
            fIsServicesWeapons   = 0x00000001,
            fIsServicesArmor     = 0x00000002,
            fIsServicesClothing  = 0x00000004,
            fIsServicesBooks     = 0x00000008,
            fIsServicesFood      = 0x00000010,
            fIsServicesChems     = 0x00000020,
            fIsServicesStimpacks = 0x00000040,
            fIsServicesLights    = 0x00000080, // ?
            fIsServicesMiscItems = 0x00000400,
            fIsServicesPotions   = 0x00002000, // ?
            fIsServicesTraining  = 0x00004000,
            fIsServicesRecharge  = 0x00010000,
            fIsServicesRepair    = 0x00020000
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord DESC; //Description
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        ReqSubRecord<CLASDATA> DATA; //Data
        ReqSubRecord<CLASATTR> ATTR; //Attributes

        CLASRecord(unsigned char *_recData=NULL);
        CLASRecord(CLASRecord *srcRecord);
        ~CLASRecord();

        bool   IsPlayable();
        void   IsPlayable(bool value);
        bool   IsGuard();
        void   IsGuard(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsServicesWeapons();
        void   IsServicesWeapons(bool value);
        bool   IsServicesArmor();
        void   IsServicesArmor(bool value);
        bool   IsServicesClothing();
        void   IsServicesClothing(bool value);
        bool   IsServicesBooks();
        void   IsServicesBooks(bool value);
        bool   IsServicesFood();
        void   IsServicesFood(bool value);
        bool   IsServicesChems();
        void   IsServicesChems(bool value);
        bool   IsServicesStimpacks();
        void   IsServicesStimpacks(bool value);
        bool   IsServicesLights();
        void   IsServicesLights(bool value);
        bool   IsServicesMiscItems();
        void   IsServicesMiscItems(bool value);
        bool   IsServicesPotions();
        void   IsServicesPotions(bool value);
        bool   IsServicesTraining();
        void   IsServicesTraining(bool value);
        bool   IsServicesRecharge();
        void   IsServicesRecharge(bool value);
        bool   IsServicesRepair();
        void   IsServicesRepair(bool value);
        bool   IsServicesFlagMask(UINT32 Mask, bool Exact=false);
        void   SetServicesFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CLASRecord &other) const;
        bool operator !=(const CLASRecord &other) const;
        bool equals(Record *other);
    };
}