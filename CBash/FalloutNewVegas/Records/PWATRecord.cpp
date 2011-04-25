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
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
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

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
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
    if(value)
        Dummy->flags |= fIsReflects;
    else
        Dummy->flags &= ~fIsReflects;
    }

bool PWATRecord::IsReflectsActors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsActors) != 0;
    }

void PWATRecord::IsReflectsActors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsReflectsActors;
    else
        Dummy->flags &= ~fIsReflectsActors;
    }

bool PWATRecord::IsReflectsLand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsLand) != 0;
    }

void PWATRecord::IsReflectsLand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsReflectsLand;
    else
        Dummy->flags &= ~fIsReflectsLand;
    }

bool PWATRecord::IsReflectsLODLand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsLODLand) != 0;
    }

void PWATRecord::IsReflectsLODLand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsReflectsLODLand;
    else
        Dummy->flags &= ~fIsReflectsLODLand;
    }

bool PWATRecord::IsReflectsLODBuildings()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsLODBuildings) != 0;
    }

void PWATRecord::IsReflectsLODBuildings(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsReflectsLODBuildings;
    else
        Dummy->flags &= ~fIsReflectsLODBuildings;
    }

bool PWATRecord::IsReflectsTrees()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsTrees) != 0;
    }

void PWATRecord::IsReflectsTrees(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsReflectsTrees;
    else
        Dummy->flags &= ~fIsReflectsTrees;
    }

bool PWATRecord::IsReflectsSky()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsSky) != 0;
    }

void PWATRecord::IsReflectsSky(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsReflectsSky;
    else
        Dummy->flags &= ~fIsReflectsSky;
    }

bool PWATRecord::IsReflectsDynamicObjects()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsDynamicObjects) != 0;
    }

void PWATRecord::IsReflectsDynamicObjects(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsReflectsDynamicObjects;
    else
        Dummy->flags &= ~fIsReflectsDynamicObjects;
    }

bool PWATRecord::IsReflectsDeadBodies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsReflectsDeadBodies) != 0;
    }

void PWATRecord::IsReflectsDeadBodies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsReflectsDeadBodies;
    else
        Dummy->flags &= ~fIsReflectsDeadBodies;
    }

bool PWATRecord::IsRefracts()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefracts) != 0;
    }

void PWATRecord::IsRefracts(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRefracts;
    else
        Dummy->flags &= ~fIsRefracts;
    }

bool PWATRecord::IsRefractsActors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefractsActors) != 0;
    }

void PWATRecord::IsRefractsActors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRefractsActors;
    else
        Dummy->flags &= ~fIsRefractsActors;
    }

bool PWATRecord::IsRefractsDeadBodies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefractsDeadBodies) != 0;
    }

void PWATRecord::IsRefractsDeadBodies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRefractsDeadBodies;
    else
        Dummy->flags &= ~fIsRefractsDeadBodies;
    }

bool PWATRecord::IsRefractsDynamicObjects()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefractsDynamicObjects) != 0;
    }

void PWATRecord::IsRefractsDynamicObjects(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRefractsDynamicObjects;
    else
        Dummy->flags &= ~fIsRefractsDynamicObjects;
    }

bool PWATRecord::IsRefractsDeadBodies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRefractsDeadBodies) != 0;
    }

void PWATRecord::IsRefractsDeadBodies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRefractsDeadBodies;
    else
        Dummy->flags &= ~fIsRefractsDeadBodies;
    }

bool PWATRecord::IsSilhouetteReflections()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSilhouetteReflections) != 0;
    }

void PWATRecord::IsSilhouetteReflections(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsSilhouetteReflections;
    else
        Dummy->flags &= ~fIsSilhouetteReflections;
    }

bool PWATRecord::IsDepth()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDepth) != 0;
    }

void PWATRecord::IsDepth(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDepth;
    else
        Dummy->flags &= ~fIsDepth;
    }

bool PWATRecord::IsObjectTextureCoordinates()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsObjectTextureCoordinates) != 0;
    }

void PWATRecord::IsObjectTextureCoordinates(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsObjectTextureCoordinates;
    else
        Dummy->flags &= ~fIsObjectTextureCoordinates;
    }

bool PWATRecord::IsNoUnderwaterFog()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoUnderwaterFog) != 0;
    }

void PWATRecord::IsNoUnderwaterFog(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoUnderwaterFog;
    else
        Dummy->flags &= ~fIsNoUnderwaterFog;
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

UINT32 PWATRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-20];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(OBND.IsLoaded())
        TotSize += OBND.GetSize() + 6;

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            {
            cSize = MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODB.IsLoaded())
            {
            cSize = MODL->MODB.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODT.IsLoaded())
            {
            cSize = MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODS.IsLoaded())
            TotSize += MODL->MODS.GetSize() + 6;
        if(MODL->MODD.IsLoaded())
            TotSize += MODL->MODD.GetSize() + 6;
        }

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    return TotSize;
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
                MODL->MODS.Read(buffer, subSize, curPos);
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
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());

        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', MODL->MODB.value, MODL->MODB.GetSize());

        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());

        if(MODL->MODS.IsLoaded())
            SaveHandler.writeSubRecord('SDOM', MODL->MODS.value, MODL->MODS.GetSize());

        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', MODL->MODD.value, MODL->MODD.GetSize());

        }

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

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