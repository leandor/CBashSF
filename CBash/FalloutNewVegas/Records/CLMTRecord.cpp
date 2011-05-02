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
#include "CLMTRecord.h"

namespace FNV
{
CLMTRecord::CLMTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CLMTRecord::CLMTRecord(CLMTRecord *srcRecord):
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
    WLST = srcRecord->WLST;
    FNAM = srcRecord->FNAM;
    GNAM = srcRecord->GNAM;

    MODL = srcRecord->MODL;

    TNAM = srcRecord->TNAM;
    return;
    }

CLMTRecord::~CLMTRecord()
    {
    //
    }

bool CLMTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(WLST.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(WLST->value);
    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);

    return op.Stop();
    }

UINT32 CLMTRecord::GetType()
    {
    return 'TMLC';
    }

STRING CLMTRecord::GetStrType()
    {
    return "CLMT";
    }

SINT32 CLMTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'TSLW':
                WLST.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANG':
                GNAM.Read(buffer, subSize, curPos);
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
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CLMT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CLMTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    WLST.Unload();
    FNAM.Unload();
    GNAM.Unload();
    MODL.Unload();
    TNAM.Unload();
    return 1;
    }

SINT32 CLMTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(WLST);
    WRITE(FNAM);
    WRITE(GNAM);

    MODL.Write(writer);

    WRITE(TNAM);

    return -1;
    }

bool CLMTRecord::operator ==(const CLMTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            WLST == other.WLST &&
            FNAM.equalsi(other.FNAM) &&
            GNAM.equalsi(other.GNAM) &&
            MODL == other.MODL &&
            TNAM == other.TNAM);
    }

bool CLMTRecord::operator !=(const CLMTRecord &other) const
    {
    return !(*this == other);
    }
}