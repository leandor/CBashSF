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
#include "PWATRecord.h"

namespace FNV
{
PWATRecord::PWATDNAM::PWATDNAM():
    flags(0),
    water(0)
    {
    //
    }

PWATRecord::PWATDNAM::~PWATDNAM()
    {
    //
    }

bool PWATRecord::PWATDNAM::operator ==(const PWATDNAM &other) const
    {
    return (flags == other.flags &&
            water == other.water);
    }

bool PWATRecord::PWATDNAM::operator !=(const PWATDNAM &other) const
    {
    return !(*this == other);
    }

PWATRecord::PWATRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

PWATRecord::PWATRecord(PWATRecord *srcRecord):
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
    OBND = srcRecord->OBND;
    MODL = srcRecord->MODL;
    DNAM = srcRecord->DNAM;
    return;
    }

PWATRecord::~PWATRecord()
    {
    //
    }

bool PWATRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    op.Accept(DNAM.value.water);

    return op.Stop();
    }

bool PWATRecord::IsReflects()
    {
    return (DNAM.value.flags & fIsReflects) != 0;
    }

void PWATRecord::IsReflects(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsReflects) : (DNAM.value.flags & ~fIsReflects);
    }

bool PWATRecord::IsReflectsActors()
    {
    return (DNAM.value.flags & fIsReflectsActors) != 0;
    }

void PWATRecord::IsReflectsActors(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsReflectsActors) : (DNAM.value.flags & ~fIsReflectsActors);
    }

bool PWATRecord::IsReflectsLand()
    {
    return (DNAM.value.flags & fIsReflectsLand) != 0;
    }

void PWATRecord::IsReflectsLand(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsReflectsLand) : (DNAM.value.flags & ~fIsReflectsLand);
    }

bool PWATRecord::IsReflectsLODLand()
    {
    return (DNAM.value.flags & fIsReflectsLODLand) != 0;
    }

void PWATRecord::IsReflectsLODLand(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsReflectsLODLand) : (DNAM.value.flags & ~fIsReflectsLODLand);
    }

bool PWATRecord::IsReflectsLODBuildings()
    {
    return (DNAM.value.flags & fIsReflectsLODBuildings) != 0;
    }

void PWATRecord::IsReflectsLODBuildings(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsReflectsLODBuildings) : (DNAM.value.flags & ~fIsReflectsLODBuildings);
    }

bool PWATRecord::IsReflectsTrees()
    {
    return (DNAM.value.flags & fIsReflectsTrees) != 0;
    }

void PWATRecord::IsReflectsTrees(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsReflectsTrees) : (DNAM.value.flags & ~fIsReflectsTrees);
    }

bool PWATRecord::IsReflectsSky()
    {
    return (DNAM.value.flags & fIsReflectsSky) != 0;
    }

void PWATRecord::IsReflectsSky(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsReflectsSky) : (DNAM.value.flags & ~fIsReflectsSky);
    }

bool PWATRecord::IsReflectsDynamicObjects()
    {
    return (DNAM.value.flags & fIsReflectsDynamicObjects) != 0;
    }

void PWATRecord::IsReflectsDynamicObjects(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsReflectsDynamicObjects) : (DNAM.value.flags & ~fIsReflectsDynamicObjects);
    }

bool PWATRecord::IsReflectsDeadBodies()
    {
    return (DNAM.value.flags & fIsReflectsDeadBodies) != 0;
    }

void PWATRecord::IsReflectsDeadBodies(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsReflectsDeadBodies) : (DNAM.value.flags & ~fIsReflectsDeadBodies);
    }

bool PWATRecord::IsRefracts()
    {
    return (DNAM.value.flags & fIsRefracts) != 0;
    }

void PWATRecord::IsRefracts(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsRefracts) : (DNAM.value.flags & ~fIsRefracts);
    }

bool PWATRecord::IsRefractsActors()
    {
    return (DNAM.value.flags & fIsRefractsActors) != 0;
    }

void PWATRecord::IsRefractsActors(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsRefractsActors) : (DNAM.value.flags & ~fIsRefractsActors);
    }

bool PWATRecord::IsRefractsLand()
    {
    return (DNAM.value.flags & fIsRefractsLand) != 0;
    }

void PWATRecord::IsRefractsLand(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsRefractsLand) : (DNAM.value.flags & ~fIsRefractsLand);
    }

bool PWATRecord::IsRefractsDynamicObjects()
    {
    return (DNAM.value.flags & fIsRefractsDynamicObjects) != 0;
    }

void PWATRecord::IsRefractsDynamicObjects(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsRefractsDynamicObjects) : (DNAM.value.flags & ~fIsRefractsDynamicObjects);
    }

bool PWATRecord::IsRefractsDeadBodies()
    {
    return (DNAM.value.flags & fIsRefractsDeadBodies) != 0;
    }

void PWATRecord::IsRefractsDeadBodies(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsRefractsDeadBodies) : (DNAM.value.flags & ~fIsRefractsDeadBodies);
    }

bool PWATRecord::IsSilhouetteReflections()
    {
    return (DNAM.value.flags & fIsSilhouetteReflections) != 0;
    }

void PWATRecord::IsSilhouetteReflections(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsSilhouetteReflections) : (DNAM.value.flags & ~fIsSilhouetteReflections);
    }

bool PWATRecord::IsDepth()
    {
    return (DNAM.value.flags & fIsDepth) != 0;
    }

void PWATRecord::IsDepth(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsDepth) : (DNAM.value.flags & ~fIsDepth);
    }

bool PWATRecord::IsObjectTextureCoordinates()
    {
    return (DNAM.value.flags & fIsObjectTextureCoordinates) != 0;
    }

void PWATRecord::IsObjectTextureCoordinates(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsObjectTextureCoordinates) : (DNAM.value.flags & ~fIsObjectTextureCoordinates);
    }

bool PWATRecord::IsNoUnderwaterFog()
    {
    return (DNAM.value.flags & fIsNoUnderwaterFog) != 0;
    }

void PWATRecord::IsNoUnderwaterFog(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsNoUnderwaterFog) : (DNAM.value.flags & ~fIsNoUnderwaterFog);
    }

bool PWATRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((DNAM.value.flags & Mask) == Mask) : ((DNAM.value.flags & Mask) != 0);
    }

void PWATRecord::SetFlagMask(UINT32 Mask)
    {
    DNAM.value.flags = Mask;
    }

UINT32 PWATRecord::GetType()
    {
    return 'TAWP';
    }

STRING PWATRecord::GetStrType()
    {
    return "PWAT";
    }

SINT32 PWATRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'DNBO':
                OBND.Read(buffer, subSize, curPos);
                break;
            case 'LDOM':
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case 'BDOM':
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case 'TDOM':
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case 'SDOM':
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case 'DDOM':
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  PWAT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 PWATRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    DNAM.Unload();
    return 1;
    }

SINT32 PWATRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    WRITE(DNAM);
    return -1;
    }

bool PWATRecord::operator ==(const PWATRecord &other) const
    {
    return (OBND == other.OBND &&
            DNAM == other.DNAM &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL);
    }

bool PWATRecord::operator !=(const PWATRecord &other) const
    {
    return !(*this == other);
    }
}