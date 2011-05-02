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
#include "..\..\Common.h"
#include "CLASRecord.h"

namespace FNV
{
CLASRecord::CLASDATA::CLASDATA():
    flags(0),
    services(0),
    trainSkill(0),
    trainLevel(0)
    {
    tagSkills[0] = 0;
    tagSkills[1] = 0;
    tagSkills[2] = 0;
    tagSkills[3] = 0;
    memset(&unused1, 0x00, 2);
    }

CLASRecord::CLASDATA::~CLASDATA()
    {
    //
    }

bool CLASRecord::CLASDATA::operator ==(const CLASDATA &other) const
    {
    return (tagSkills[0] == other.tagSkills[0] &&
            tagSkills[1] == other.tagSkills[1] &&
            tagSkills[2] == other.tagSkills[2] &&
            tagSkills[3] == other.tagSkills[3] &&
            flags == other.flags &&
            services == other.services &&
            trainSkill == other.trainSkill &&
            trainLevel == other.trainLevel);
    }

bool CLASRecord::CLASDATA::operator !=(const CLASDATA &other) const
    {
    return !(*this == other);
    }

CLASRecord::CLASATTR::CLASATTR():
    strength(0),
    perception(0),
    endurance(0),
    charisma(0),
    intelligence(0),
    agility(0),
    luck(0)
    {
    //
    }

CLASRecord::CLASATTR::~CLASATTR()
    {
    //
    }

bool CLASRecord::CLASATTR::operator ==(const CLASATTR &other) const
    {
    return (strength == other.strength &&
            perception == other.perception &&
            endurance == other.endurance &&
            charisma == other.charisma &&
            intelligence == other.intelligence &&
            agility == other.agility &&
            luck == other.luck);
    }

bool CLASRecord::CLASATTR::operator !=(const CLASATTR &other) const
    {
    return !(*this == other);
    }

CLASRecord::CLASRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CLASRecord::CLASRecord(CLASRecord *srcRecord):
    FNVRecord()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    DESC = srcRecord->DESC;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    DATA = srcRecord->DATA;
    ATTR = srcRecord->ATTR;
    return;
    }

CLASRecord::~CLASRecord()
    {
    //
    }

bool CLASRecord::IsPlayable()
    {
    return (DATA.value.flags & fIsPlayable) != 0;
    }

void CLASRecord::IsPlayable(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsPlayable) : (DATA.value.flags & ~fIsPlayable);
    }

bool CLASRecord::IsGuard()
    {
    return (DATA.value.flags & fIsGuard) != 0;
    }

void CLASRecord::IsGuard(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsGuard) : (DATA.value.flags & ~fIsGuard);
    }

bool CLASRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void CLASRecord::SetFlagMask(UINT32 Mask)
    {
    DATA.value.flags = Mask;
    }

bool CLASRecord::IsServicesWeapons()
    {
    return (DATA.value.services & fIsServicesWeapons) != 0;
    }

void CLASRecord::IsServicesWeapons(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesWeapons) : (DATA.value.services & ~fIsServicesWeapons);
    }

bool CLASRecord::IsServicesArmor()
    {
    return (DATA.value.services & fIsServicesArmor) != 0;
    }

void CLASRecord::IsServicesArmor(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesArmor) : (DATA.value.services & ~fIsServicesArmor);
    }

bool CLASRecord::IsServicesClothing()
    {
    return (DATA.value.services & fIsServicesClothing) != 0;
    }

void CLASRecord::IsServicesClothing(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesClothing) : (DATA.value.services & ~fIsServicesClothing);
    }

bool CLASRecord::IsServicesBooks()
    {
    return (DATA.value.services & fIsServicesBooks) != 0;
    }

void CLASRecord::IsServicesBooks(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesBooks) : (DATA.value.services & ~fIsServicesBooks);
    }

bool CLASRecord::IsServicesFood()
    {
    return (DATA.value.services & fIsServicesFood) != 0;
    }

void CLASRecord::IsServicesFood(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesFood) : (DATA.value.services & ~fIsServicesFood);
    }

bool CLASRecord::IsServicesChems()
    {
    return (DATA.value.services & fIsServicesChems) != 0;
    }

void CLASRecord::IsServicesChems(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesChems) : (DATA.value.services & ~fIsServicesChems);
    }

bool CLASRecord::IsServicesStimpacks()
    {
    return (DATA.value.services & fIsServicesStimpacks) != 0;
    }

void CLASRecord::IsServicesStimpacks(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesStimpacks) : (DATA.value.services & ~fIsServicesStimpacks);
    }

bool CLASRecord::IsServicesLights()
    {
    return (DATA.value.services & fIsServicesLights) != 0;
    }

void CLASRecord::IsServicesLights(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesLights) : (DATA.value.services & ~fIsServicesLights);
    }

bool CLASRecord::IsServicesMiscItems()
    {
    return (DATA.value.services & fIsServicesMiscItems) != 0;
    }

void CLASRecord::IsServicesMiscItems(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesMiscItems) : (DATA.value.services & ~fIsServicesMiscItems);
    }

bool CLASRecord::IsServicesPotions()
    {
    return (DATA.value.services & fIsServicesPotions) != 0;
    }

void CLASRecord::IsServicesPotions(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesPotions) : (DATA.value.services & ~fIsServicesPotions);
    }

bool CLASRecord::IsServicesTraining()
    {
    return (DATA.value.services & fIsServicesTraining) != 0;
    }

void CLASRecord::IsServicesTraining(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesTraining) : (DATA.value.services & ~fIsServicesTraining);
    }

bool CLASRecord::IsServicesRecharge()
    {
    return (DATA.value.services & fIsServicesRecharge) != 0;
    }

void CLASRecord::IsServicesRecharge(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesRecharge) : (DATA.value.services & ~fIsServicesRecharge);
    }

bool CLASRecord::IsServicesRepair()
    {
    return (DATA.value.services & fIsServicesRepair) != 0;
    }

void CLASRecord::IsServicesRepair(bool value)
    {
    DATA.value.services = value ? (DATA.value.services | fIsServicesRepair) : (DATA.value.services & ~fIsServicesRepair);
    }

bool CLASRecord::IsServicesFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.services & Mask) == Mask) : ((DATA.value.services & Mask) != 0);
    }

void CLASRecord::SetServicesFlagMask(UINT32 Mask)
    {
    DATA.value.services = Mask;
    }

UINT32 CLASRecord::GetType()
    {
    return 'SALC';
    }

STRING CLASRecord::GetStrType()
    {
    return "CLAS";
    }

SINT32 CLASRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case 'XXXX':
                curPos += 2;
                _readBuffer(&subSize, buffer, 4, curPos);
                _readBuffer(&subType, buffer, 4, curPos);
                curPos += 2;
                break;
            default:
                subSize = 0;
                _readBuffer(&subSize, buffer, 2, curPos);
                break;
            }
        switch(subType)
            {
            case 'DIDE':
                EDID.Read(buffer, subSize, curPos);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'CSED':
                DESC.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'RTTA':
                ATTR.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CLAS: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CLASRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    ICON.Unload();
    MICO.Unload();
    DATA.Unload();
    ATTR.Unload();
    return 1;
    }

SINT32 CLASRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITEREQ(DESC);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(DATA);
    WRITE(ATTR);
    return -1;
    }

bool CLASRecord::operator ==(const CLASRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            DATA == other.DATA &&
            ATTR == other.ATTR);
    }

bool CLASRecord::operator !=(const CLASRecord &other) const
    {
    return !(*this == other);
    }
}