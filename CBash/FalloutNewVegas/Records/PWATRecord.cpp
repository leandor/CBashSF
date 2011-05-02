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
    //if(DNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DNAM->value);

    return op.Stop();
    }

bool PWATRecord::IsReflects()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflects) != 0;
    }

void PWATRecord::IsReflects(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsReflects) : (Dummy->flags & ~fIsReflects);
    }

bool PWATRecord::IsReflectsActors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsActors) != 0;
    }

void PWATRecord::IsReflectsActors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsReflectsActors) : (Dummy->flags & ~fIsReflectsActors);
    }

bool PWATRecord::IsReflectsLand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsLand) != 0;
    }

void PWATRecord::IsReflectsLand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsReflectsLand) : (Dummy->flags & ~fIsReflectsLand);
    }

bool PWATRecord::IsReflectsLODLand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsLODLand) != 0;
    }

void PWATRecord::IsReflectsLODLand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsReflectsLODLand) : (Dummy->flags & ~fIsReflectsLODLand);
    }

bool PWATRecord::IsReflectsLODBuildings()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsLODBuildings) != 0;
    }

void PWATRecord::IsReflectsLODBuildings(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsReflectsLODBuildings) : (Dummy->flags & ~fIsReflectsLODBuildings);
    }

bool PWATRecord::IsReflectsTrees()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsTrees) != 0;
    }

void PWATRecord::IsReflectsTrees(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsReflectsTrees) : (Dummy->flags & ~fIsReflectsTrees);
    }

bool PWATRecord::IsReflectsSky()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsSky) != 0;
    }

void PWATRecord::IsReflectsSky(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsReflectsSky) : (Dummy->flags & ~fIsReflectsSky);
    }

bool PWATRecord::IsReflectsDynamicObjects()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsDynamicObjects) != 0;
    }

void PWATRecord::IsReflectsDynamicObjects(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsReflectsDynamicObjects) : (Dummy->flags & ~fIsReflectsDynamicObjects);
    }

bool PWATRecord::IsReflectsDeadBodies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsDeadBodies) != 0;
    }

void PWATRecord::IsReflectsDeadBodies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsReflectsDeadBodies) : (Dummy->flags & ~fIsReflectsDeadBodies);
    }

bool PWATRecord::IsRefracts()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefracts) != 0;
    }

void PWATRecord::IsRefracts(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRefracts) : (Dummy->flags & ~fIsRefracts);
    }

bool PWATRecord::IsRefractsActors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefractsActors) != 0;
    }

void PWATRecord::IsRefractsActors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRefractsActors) : (Dummy->flags & ~fIsRefractsActors);
    }

bool PWATRecord::IsRefractsDeadBodies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefractsDeadBodies) != 0;
    }

void PWATRecord::IsRefractsDeadBodies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRefractsDeadBodies) : (Dummy->flags & ~fIsRefractsDeadBodies);
    }

bool PWATRecord::IsRefractsDynamicObjects()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefractsDynamicObjects) != 0;
    }

void PWATRecord::IsRefractsDynamicObjects(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRefractsDynamicObjects) : (Dummy->flags & ~fIsRefractsDynamicObjects);
    }

bool PWATRecord::IsRefractsDeadBodies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefractsDeadBodies) != 0;
    }

void PWATRecord::IsRefractsDeadBodies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRefractsDeadBodies) : (Dummy->flags & ~fIsRefractsDeadBodies);
    }

bool PWATRecord::IsSilhouetteReflections()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSilhouetteReflections) != 0;
    }

void PWATRecord::IsSilhouetteReflections(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsSilhouetteReflections) : (Dummy->flags & ~fIsSilhouetteReflections);
    }

bool PWATRecord::IsDepth()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDepth) != 0;
    }

void PWATRecord::IsDepth(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDepth) : (Dummy->flags & ~fIsDepth);
    }

bool PWATRecord::IsObjectTextureCoordinates()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsObjectTextureCoordinates) != 0;
    }

void PWATRecord::IsObjectTextureCoordinates(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsObjectTextureCoordinates) : (Dummy->flags & ~fIsObjectTextureCoordinates);
    }

bool PWATRecord::IsNoUnderwaterFog()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoUnderwaterFog) != 0;
    }

void PWATRecord::IsNoUnderwaterFog(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoUnderwaterFog) : (Dummy->flags & ~fIsNoUnderwaterFog);
    }

bool PWATRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void PWATRecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
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

SINT32 PWATRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    WRITE(EDID);
    WRITE(OBND);

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());
        if(MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MODL->Textures.GetSize());
            UINT32 cSize = MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MODL->Textures.MODS.size(); ++p)
                {
                if(MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MODL->Textures.MODS[p]->name, cSize);
                    }

                SaveHandler.write(&MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MODL->MODD.value, MODL->MODD.GetSize());
        }

    WRITE(DNAM);

    return -1;
    }

bool PWATRecord::operator ==(const PWATRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            MODL == other.MODL &&
            DNAM == other.DNAM);
    }

bool PWATRecord::operator !=(const PWATRecord &other) const
    {
    return !(*this == other);
    }
}