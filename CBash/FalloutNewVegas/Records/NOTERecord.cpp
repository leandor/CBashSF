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
#include "NOTERecord.h"

namespace FNV
{
NOTERecord::NOTERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

NOTERecord::NOTERecord(NOTERecord *srcRecord):
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
    FULL = srcRecord->FULL;

    MODL = srcRecord->MODL;

    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    YNAM = srcRecord->YNAM;
    ZNAM = srcRecord->ZNAM;
    DATA = srcRecord->DATA;
    ONAM = srcRecord->ONAM;
    XNAM = srcRecord->XNAM;
    TNAM = srcRecord->TNAM;
    SNAM = srcRecord->SNAM;
    return;
    }

NOTERecord::~NOTERecord()
    {
    //
    }

bool NOTERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(YNAM.IsLoaded())
        op.Accept(YNAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);
    if(ONAM.IsLoaded())
        op.Accept(ONAM->value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);

    return op.Stop();
    }

bool NOTERecord::IsSound()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSound=0);
    }

void NOTERecord::IsSound(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSound=0 : eDummyDefault;
    }

bool NOTERecord::IsText()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eText);
    }

void NOTERecord::IsText(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eText : eDummyDefault;
    }

bool NOTERecord::IsImage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eImage);
    }

void NOTERecord::IsImage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eImage : eDummyDefault;
    }

bool NOTERecord::IsVoice()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVoice);
    }

void NOTERecord::IsVoice(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eVoice : eDummyDefault;
    }

bool NOTERecord::IsType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void NOTERecord::SetType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 NOTERecord::GetType()
    {
    return 'ETON';
    }

STRING NOTERecord::GetStrType()
    {
    return "NOTE";
    }

SINT32 NOTERecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
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
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'MANY':
                YNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANO':
                ONAM.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  NOTE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 NOTERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    YNAM.Unload();
    ZNAM.Unload();
    DATA.Unload();
    ONAM.Unload();
    XNAM.Unload();
    TNAM.Unload();
    SNAM.Unload();
    return 1;
    }

SINT32 NOTERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);

    MODL.Write(writer);

    WRITE(ICON);
    WRITE(MICO);
    WRITE(YNAM);
    WRITE(ZNAM);
    WRITE(DATA);
    WRITE(ONAM);
    WRITE(XNAM);
    WRITE(TNAM);
    WRITE(SNAM);

    return -1;
    }

bool NOTERecord::operator ==(const NOTERecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            DATA == other.DATA &&
            ONAM == other.ONAM &&
            XNAM.equalsi(other.XNAM) &&
            TNAM.equalsi(other.TNAM) &&
            SNAM == other.SNAM);
    }

bool NOTERecord::operator !=(const NOTERecord &other) const
    {
    return !(*this == other);
    }
}