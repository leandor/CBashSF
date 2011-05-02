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
#include "RACERecord.h"

namespace FNV
{
void RACERecord::RACEPart::Write(UINT32 index, FileWriter &writer)
    {
    writer.record_write_subrecord('XDNI', &index, 4);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    }

void RACERecord::RACEPart::WriteIconsFirst(UINT32 index, FileWriter &writer)
    {
    writer.record_write_subrecord('XDNI', &index, 4);
    WRITE(ICON);
    WRITE(MICO);
    MODL.Write(writer);
    }

bool RACERecord::RACEPart::operator ==(const RACEPart &other) const
    {
    return (MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO));
    }

bool RACERecord::RACEPart::operator !=(const RACEPart &other) const
    {
    return !(*this == other);
    }

RACERecord::RACERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

RACERecord::RACERecord(RACERecord *srcRecord):
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
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    ONAM = srcRecord->ONAM;
    YNAM = srcRecord->YNAM;
    VTCK = srcRecord->VTCK;
    DNAM = srcRecord->DNAM;
    CNAM = srcRecord->CNAM;
    PNAM = srcRecord->PNAM;
    UNAM = srcRecord->UNAM;
    ATTR = srcRecord->ATTR;

    MHMOD0 = srcRecord->MHMOD0;
    MHMOD1 = srcRecord->MHMOD1;
    MHMOD2 = srcRecord->MHMOD2;
    MHMOD3 = srcRecord->MHMOD3;
    MHMOD4 = srcRecord->MHMOD4;
    MHMOD5 = srcRecord->MHMOD5;
    MHMOD6 = srcRecord->MHMOD6;
    MHMOD7 = srcRecord->MHMOD7;

    FHMOD0 = srcRecord->FHMOD0;
    FHMOD1 = srcRecord->FHMOD1;
    FHMOD2 = srcRecord->FHMOD2;
    FHMOD3 = srcRecord->FHMOD3;
    FHMOD4 = srcRecord->FHMOD4;
    FHMOD5 = srcRecord->FHMOD5;
    FHMOD6 = srcRecord->FHMOD6;
    FHMOD7 = srcRecord->FHMOD7;

    MBMOD0 = srcRecord->MBMOD0;
    MBMOD1 = srcRecord->MBMOD1;
    MBMOD2 = srcRecord->MBMOD2;
    MBMOD3 = srcRecord->MBMOD3;

    FBMOD0 = srcRecord->FBMOD0;
    FBMOD1 = srcRecord->FBMOD1;
    FBMOD2 = srcRecord->FBMOD2;
    FBMOD3 = srcRecord->FBMOD3;

    HNAM = srcRecord->HNAM;
    ENAM = srcRecord->ENAM;

    MaleFGGS = srcRecord->MaleFGGS;
    MaleFGGA = srcRecord->MaleFGGA;
    MaleFGTS = srcRecord->MaleFGTS;
    MaleSNAM = srcRecord->MaleSNAM;

    FemaleFGGS = srcRecord->FemaleFGGS;
    FemaleFGGA = srcRecord->FemaleFGGA;
    FemaleFGTS = srcRecord->FemaleFGTS;
    FemaleSNAM = srcRecord->FemaleSNAM;
    return;
    }

RACERecord::~RACERecord()
    {
    //
    }

bool RACERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < XNAM.value.size(); x++)
        op.Accept(XNAM.value[x]->faction);
    if(ONAM.IsLoaded())
        op.Accept(ONAM.value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if(VTCK.IsLoaded())
        {
        op.Accept(VTCK.value.maleVoice);
        op.Accept(VTCK.value.femaleVoice);
        }
    if(DNAM.IsLoaded())
        {
        op.Accept(DNAM.value.defaultHairMale);
        op.Accept(DNAM.value.defaultHairFemale);
        }

    if(MHMOD0.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MHMOD0.MODL->Textures.MODS.size(); p++)
            op.Accept(MHMOD0.MODL->Textures.MODS[p]->texture);
        }

    if(MHMOD1.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MHMOD1.MODL->Textures.MODS.size(); p++)
            op.Accept(MHMOD1.MODL->Textures.MODS[p]->texture);
        }

    if(MHMOD2.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MHMOD2.MODL->Textures.MODS.size(); p++)
            op.Accept(MHMOD2.MODL->Textures.MODS[p]->texture);
        }

    if(MHMOD3.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MHMOD3.MODL->Textures.MODS.size(); p++)
            op.Accept(MHMOD3.MODL->Textures.MODS[p]->texture);
        }

    if(MHMOD4.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MHMOD4.MODL->Textures.MODS.size(); p++)
            op.Accept(MHMOD4.MODL->Textures.MODS[p]->texture);
        }

    if(MHMOD5.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MHMOD5.MODL->Textures.MODS.size(); p++)
            op.Accept(MHMOD5.MODL->Textures.MODS[p]->texture);
        }

    if(MHMOD6.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MHMOD6.MODL->Textures.MODS.size(); p++)
            op.Accept(MHMOD6.MODL->Textures.MODS[p]->texture);
        }

    if(MHMOD7.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MHMOD7.MODL->Textures.MODS.size(); p++)
            op.Accept(MHMOD7.MODL->Textures.MODS[p]->texture);
        }

    if(FHMOD0.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FHMOD0.MODL->Textures.MODS.size(); p++)
            op.Accept(FHMOD0.MODL->Textures.MODS[p]->texture);
        }

    if(FHMOD1.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FHMOD1.MODL->Textures.MODS.size(); p++)
            op.Accept(FHMOD1.MODL->Textures.MODS[p]->texture);
        }

    if(FHMOD2.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FHMOD2.MODL->Textures.MODS.size(); p++)
            op.Accept(FHMOD2.MODL->Textures.MODS[p]->texture);
        }

    if(FHMOD3.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FHMOD3.MODL->Textures.MODS.size(); p++)
            op.Accept(FHMOD3.MODL->Textures.MODS[p]->texture);
        }

    if(FHMOD4.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FHMOD4.MODL->Textures.MODS.size(); p++)
            op.Accept(FHMOD4.MODL->Textures.MODS[p]->texture);
        }

    if(FHMOD5.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FHMOD5.MODL->Textures.MODS.size(); p++)
            op.Accept(FHMOD5.MODL->Textures.MODS[p]->texture);
        }

    if(FHMOD6.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FHMOD6.MODL->Textures.MODS.size(); p++)
            op.Accept(FHMOD6.MODL->Textures.MODS[p]->texture);
        }

    if(FHMOD7.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FHMOD7.MODL->Textures.MODS.size(); p++)
            op.Accept(FHMOD7.MODL->Textures.MODS[p]->texture);
        }

    if(MBMOD0.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MBMOD0.MODL->Textures.MODS.size(); p++)
            op.Accept(MBMOD0.MODL->Textures.MODS[p]->texture);
        }

    if(MBMOD1.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MBMOD1.MODL->Textures.MODS.size(); p++)
            op.Accept(MBMOD1.MODL->Textures.MODS[p]->texture);
        }

    if(MBMOD2.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MBMOD2.MODL->Textures.MODS.size(); p++)
            op.Accept(MBMOD2.MODL->Textures.MODS[p]->texture);
        }

    if(MBMOD3.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < MBMOD3.MODL->Textures.MODS.size(); p++)
            op.Accept(MBMOD3.MODL->Textures.MODS[p]->texture);
        }

    if(FBMOD0.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FBMOD0.MODL->Textures.MODS.size(); p++)
            op.Accept(FBMOD0.MODL->Textures.MODS[p]->texture);
        }

    if(FBMOD1.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FBMOD1.MODL->Textures.MODS.size(); p++)
            op.Accept(FBMOD1.MODL->Textures.MODS[p]->texture);
        }

    if(FBMOD2.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FBMOD2.MODL->Textures.MODS.size(); p++)
            op.Accept(FBMOD2.MODL->Textures.MODS[p]->texture);
        }

    if(FBMOD3.MODL.IsLoaded())
        {
        for(UINT32 p = 0; p < FBMOD3.MODL->Textures.MODS.size(); p++)
            op.Accept(FBMOD3.MODL->Textures.MODS[p]->texture);
        }

    for(UINT32 x = 0; x < HNAM.value.size(); x++)
        op.Accept(HNAM.value[x]);
    for(UINT32 x = 0; x < ENAM.value.size(); x++)
        op.Accept(ENAM.value[x]);

    return op.Stop();
    }

bool RACERecord::IsPlayable()
    {
    return (DATA.value.flags & fIsPlayable) != 0;
    }

void RACERecord::IsPlayable(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsPlayable) : (DATA.value.flags & ~fIsPlayable);
    }

bool RACERecord::IsChild()
    {
    return (DATA.value.flags & fIsChild) != 0;
    }

void RACERecord::IsChild(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsChild) : (DATA.value.flags & ~fIsChild);
    }

bool RACERecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void RACERecord::SetFlagMask(UINT32 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 RACERecord::GetType()
    {
    return 'ECAR';
    }

STRING RACERecord::GetStrType()
    {
    return "RACE";
    }

SINT32 RACERecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    enum namFlags
        {
        fIsMale   = 0x00000001,
        fIsFemale = 0x00000002,
        fIsHead   = 0x00000004,
        fIsBody   = 0x00000008
        };

    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    UINT32 curNAM = 0;
    SINT32 curINDX = -1;
    FORMID curFormID = 0;
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
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANO':
                ONAM.Read(buffer, subSize, curPos);
                break;
            case 'MANY':
                YNAM.Read(buffer, subSize, curPos);
                break;
            case '2MAN': //Unknown empty marker
                break;
            case 'KCTV':
                VTCK.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANU':
                UNAM.Read(buffer, subSize, curPos);
                break;
            case 'RTTA':
                ATTR.Read(buffer, subSize, curPos);
                break;
            case '0MAN':
                curNAM = (curNAM & ~fIsBody) | fIsHead;
                curINDX = -1;
                break;
            case 'MANM':
                curNAM = (curNAM & ~fIsFemale) | fIsMale;
                break;
            case 'XDNI':
                _readBuffer(&curINDX, buffer, subSize, curPos);
                break;
            case 'LDOM':
                switch(curINDX) //Part ID
                    {
                    case 0:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD0.MODL.Load();
                                MHMOD0.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD0.MODL.Load();
                                FHMOD0.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD0.MODL.Load();
                                MBMOD0.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD0.MODL.Load();
                                FBMOD0.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODL\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 1:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD1.MODL.Load();
                                MHMOD1.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD1.MODL.Load();
                                FHMOD1.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD1.MODL.Load();
                                MBMOD1.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD1.MODL.Load();
                                FBMOD1.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODL\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD2.MODL.Load();
                                MHMOD2.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD2.MODL.Load();
                                FHMOD2.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD2.MODL.Load();
                                MBMOD2.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD2.MODL.Load();
                                FBMOD2.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODL\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 3:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD3.MODL.Load();
                                MHMOD3.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD3.MODL.Load();
                                FHMOD3.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD3.MODL.Load();
                                MBMOD3.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD3.MODL.Load();
                                FBMOD3.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODL\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 4:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD4.MODL.Load();
                                MHMOD4.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD4.MODL.Load();
                                FHMOD4.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODL\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 5:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD5.MODL.Load();
                                MHMOD5.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD5.MODL.Load();
                                FHMOD5.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODL\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 6:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD6.MODL.Load();
                                MHMOD6.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD6.MODL.Load();
                                FHMOD6.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODL\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 7:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD7.MODL.Load();
                                MHMOD7.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD7.MODL.Load();
                                FHMOD7.MODL->MODL.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODL\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected MODL\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'BDOM':
                switch(curINDX) //Part ID
                    {
                    case 0:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD0.MODL.Load();
                                MHMOD0.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD0.MODL.Load();
                                FHMOD0.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD0.MODL.Load();
                                MBMOD0.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD0.MODL.Load();
                                FBMOD0.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODB\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 1:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD1.MODL.Load();
                                MHMOD1.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD1.MODL.Load();
                                FHMOD1.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD1.MODL.Load();
                                MBMOD1.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD1.MODL.Load();
                                FBMOD1.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODB\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD2.MODL.Load();
                                MHMOD2.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD2.MODL.Load();
                                FHMOD2.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD2.MODL.Load();
                                MBMOD2.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD2.MODL.Load();
                                FBMOD2.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODB\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 3:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD3.MODL.Load();
                                MHMOD3.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD3.MODL.Load();
                                FHMOD3.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD3.MODL.Load();
                                MBMOD3.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD3.MODL.Load();
                                FBMOD3.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODB\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 4:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD4.MODL.Load();
                                MHMOD4.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD4.MODL.Load();
                                FHMOD4.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODB\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 5:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD5.MODL.Load();
                                MHMOD5.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD5.MODL.Load();
                                FHMOD5.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODB\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 6:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD6.MODL.Load();
                                MHMOD6.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD6.MODL.Load();
                                FHMOD6.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODB\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 7:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD7.MODL.Load();
                                MHMOD7.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD7.MODL.Load();
                                FHMOD7.MODL->MODB.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODB\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected MODB\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'TDOM':
                switch(curINDX) //Part ID
                    {
                    case 0:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD0.MODL.Load();
                                MHMOD0.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD0.MODL.Load();
                                FHMOD0.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD0.MODL.Load();
                                MBMOD0.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD0.MODL.Load();
                                FBMOD0.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODT\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 1:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD1.MODL.Load();
                                MHMOD1.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD1.MODL.Load();
                                FHMOD1.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD1.MODL.Load();
                                MBMOD1.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD1.MODL.Load();
                                FBMOD1.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODT\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD2.MODL.Load();
                                MHMOD2.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD2.MODL.Load();
                                FHMOD2.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD2.MODL.Load();
                                MBMOD2.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD2.MODL.Load();
                                FBMOD2.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODT\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 3:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD3.MODL.Load();
                                MHMOD3.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD3.MODL.Load();
                                FHMOD3.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD3.MODL.Load();
                                MBMOD3.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD3.MODL.Load();
                                FBMOD3.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODT\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 4:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD4.MODL.Load();
                                MHMOD4.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD4.MODL.Load();
                                FHMOD4.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODT\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 5:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD5.MODL.Load();
                                MHMOD5.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD5.MODL.Load();
                                FHMOD5.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODT\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 6:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD6.MODL.Load();
                                MHMOD6.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD6.MODL.Load();
                                FHMOD6.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODT\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 7:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD7.MODL.Load();
                                MHMOD7.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD7.MODL.Load();
                                FHMOD7.MODL->MODT.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODT\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected MODT\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'SDOM':
                switch(curINDX) //Part ID
                    {
                    case 0:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD0.MODL.Load();
                                MHMOD0.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD0.MODL.Load();
                                FHMOD0.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD0.MODL.Load();
                                MBMOD0.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD0.MODL.Load();
                                FBMOD0.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected Textures\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 1:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD1.MODL.Load();
                                MHMOD1.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD1.MODL.Load();
                                FHMOD1.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD1.MODL.Load();
                                MBMOD1.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD1.MODL.Load();
                                FBMOD1.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected Textures\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD2.MODL.Load();
                                MHMOD2.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD2.MODL.Load();
                                FHMOD2.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD2.MODL.Load();
                                MBMOD2.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD2.MODL.Load();
                                FBMOD2.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected Textures\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 3:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD3.MODL.Load();
                                MHMOD3.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD3.MODL.Load();
                                FHMOD3.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD3.MODL.Load();
                                MBMOD3.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD3.MODL.Load();
                                FBMOD3.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected Textures\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 4:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD4.MODL.Load();
                                MHMOD4.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD4.MODL.Load();
                                FHMOD4.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected Textures\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 5:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD5.MODL.Load();
                                MHMOD5.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD5.MODL.Load();
                                FHMOD5.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected Textures\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 6:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD6.MODL.Load();
                                MHMOD6.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD6.MODL.Load();
                                FHMOD6.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected Textures\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 7:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD7.MODL.Load();
                                MHMOD7.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD7.MODL.Load();
                                FHMOD7.MODL->Textures.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected Textures\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected Textures\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'DDOM':
                switch(curINDX) //Part ID
                    {
                    case 0:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD0.MODL.Load();
                                MHMOD0.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD0.MODL.Load();
                                FHMOD0.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD0.MODL.Load();
                                MBMOD0.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD0.MODL.Load();
                                FBMOD0.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODD\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 1:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD1.MODL.Load();
                                MHMOD1.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD1.MODL.Load();
                                FHMOD1.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD1.MODL.Load();
                                MBMOD1.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD1.MODL.Load();
                                FBMOD1.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODD\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD2.MODL.Load();
                                MHMOD2.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD2.MODL.Load();
                                FHMOD2.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD2.MODL.Load();
                                MBMOD2.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD2.MODL.Load();
                                FBMOD2.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODD\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 3:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD3.MODL.Load();
                                MHMOD3.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD3.MODL.Load();
                                FHMOD3.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD3.MODL.Load();
                                MBMOD3.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD3.MODL.Load();
                                FBMOD3.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODD\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 4:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD4.MODL.Load();
                                MHMOD4.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD4.MODL.Load();
                                FHMOD4.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODD\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 5:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD5.MODL.Load();
                                MHMOD5.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD5.MODL.Load();
                                FHMOD5.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODD\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 6:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD6.MODL.Load();
                                MHMOD6.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD6.MODL.Load();
                                FHMOD6.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODD\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 7:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD7.MODL.Load();
                                MHMOD7.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD7.MODL.Load();
                                FHMOD7.MODL->MODD.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MODD\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected MODD\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'NOCI':
                switch(curINDX) //Part ID
                    {
                    case 0:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD0.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD0.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD0.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD0.ICON.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 1:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD1.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD1.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD1.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD1.ICON.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD2.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD2.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD2.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD2.ICON.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 3:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD3.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD3.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD3.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD3.ICON.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 4:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD4.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD4.ICON.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 5:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD5.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD5.ICON.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 6:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD6.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD6.ICON.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 7:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD7.ICON.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD7.ICON.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected ICON\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'OCIM':
                switch(curINDX) //Part ID
                    {
                    case 0:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD0.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD0.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD0.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD0.MICO.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MICO\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 1:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD1.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD1.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD1.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD1.MICO.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MICO\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD2.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD2.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD2.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD2.MICO.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MICO\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 3:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD3.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD3.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsMale | fIsBody:
                                MBMOD3.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsBody:
                                FBMOD3.MICO.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MICO\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 4:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD4.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD4.MICO.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MICO\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 5:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD5.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD5.MICO.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MICO\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 6:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD6.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD6.MICO.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MICO\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 7:
                        switch(curNAM)
                            {
                            case fIsMale | fIsHead:
                                MHMOD7.MICO.Read(buffer, subSize, curPos);
                                break;
                            case fIsFemale | fIsHead:
                                FHMOD7.MICO.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected MICO\n", formID);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected MICO\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'MANF':
                curNAM = (curNAM & ~fIsMale) | fIsFemale;
                break;
            case '1MAN':
                curNAM = (curNAM & ~fIsHead) | fIsBody;
                curINDX = -1;
                break;
            case 'MANH':
                HNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANE':
                ENAM.Read(buffer, subSize, curPos);
                break;
            case 'SGGF':
                curNAM &= ~(fIsBody |fIsHead);
                switch(curNAM)
                    {
                    case fIsMale: //Male
                        MaleFGGS.Read(buffer, subSize, curPos);
                        break;
                    case fIsFemale: //Female
                        FemaleFGGS.Read(buffer, subSize, curPos);
                        break;
                    default:
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected FGGS\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'AGGF':
                curNAM &= ~(fIsBody |fIsHead);
                switch(curNAM)
                    {
                    case fIsMale: //Male
                        MaleFGGA.Read(buffer, subSize, curPos);
                        break;
                    case fIsFemale: //Female
                        FemaleFGGA.Read(buffer, subSize, curPos);
                        break;
                    default:
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected FGGA\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'STGF':
                curNAM &= ~(fIsBody |fIsHead);
                switch(curNAM)
                    {
                    case fIsMale: //Male
                        MaleFGTS.Read(buffer, subSize, curPos);
                        break;
                    case fIsFemale: //Female
                        FemaleFGTS.Read(buffer, subSize, curPos);
                        break;
                    default:
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected FGTS\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case 'MANS':
                curNAM &= ~(fIsBody |fIsHead);
                switch(curNAM)
                    {
                    case fIsMale: //Male
                        MaleSNAM.Read(buffer, subSize, curPos);
                        break;
                    case fIsFemale: //Female
                        FemaleSNAM.Read(buffer, subSize, curPos);
                        break;
                    default:
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected SNAM\n", formID);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  RACE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 RACERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    XNAM.Unload();
    DATA.Unload();
    ONAM.Unload();
    YNAM.Unload();
    VTCK.Unload();
    DNAM.Unload();
    CNAM.Unload();
    PNAM.Unload();
    UNAM.Unload();
    ATTR.Unload();

    MHMOD0.MODL.Unload();
    MHMOD0.ICON.Unload();
    MHMOD0.MICO.Unload();
    MHMOD1.MODL.Unload();
    MHMOD1.ICON.Unload();
    MHMOD1.MICO.Unload();
    MHMOD2.MODL.Unload();
    MHMOD2.ICON.Unload();
    MHMOD2.MICO.Unload();
    MHMOD3.MODL.Unload();
    MHMOD3.ICON.Unload();
    MHMOD3.MICO.Unload();
    MHMOD4.MODL.Unload();
    MHMOD4.ICON.Unload();
    MHMOD4.MICO.Unload();
    MHMOD5.MODL.Unload();
    MHMOD5.ICON.Unload();
    MHMOD5.MICO.Unload();
    MHMOD6.MODL.Unload();
    MHMOD6.ICON.Unload();
    MHMOD6.MICO.Unload();
    MHMOD7.MODL.Unload();
    MHMOD7.ICON.Unload();
    MHMOD7.MICO.Unload();

    FHMOD0.MODL.Unload();
    FHMOD0.ICON.Unload();
    FHMOD0.MICO.Unload();
    FHMOD1.MODL.Unload();
    FHMOD1.ICON.Unload();
    FHMOD1.MICO.Unload();
    FHMOD2.MODL.Unload();
    FHMOD2.ICON.Unload();
    FHMOD2.MICO.Unload();
    FHMOD3.MODL.Unload();
    FHMOD3.ICON.Unload();
    FHMOD3.MICO.Unload();
    FHMOD4.MODL.Unload();
    FHMOD4.ICON.Unload();
    FHMOD4.MICO.Unload();
    FHMOD5.MODL.Unload();
    FHMOD5.ICON.Unload();
    FHMOD5.MICO.Unload();
    FHMOD6.MODL.Unload();
    FHMOD6.ICON.Unload();
    FHMOD6.MICO.Unload();
    FHMOD7.MODL.Unload();
    FHMOD7.ICON.Unload();
    FHMOD7.MICO.Unload();

    MBMOD0.MODL.Unload();
    MBMOD0.ICON.Unload();
    MBMOD0.MICO.Unload();
    MBMOD1.MODL.Unload();
    MBMOD1.ICON.Unload();
    MBMOD1.MICO.Unload();
    MBMOD2.MODL.Unload();
    MBMOD2.ICON.Unload();
    MBMOD2.MICO.Unload();
    MBMOD3.MODL.Unload();
    MBMOD3.ICON.Unload();
    MBMOD3.MICO.Unload();

    FBMOD0.MODL.Unload();
    FBMOD0.ICON.Unload();
    FBMOD0.MICO.Unload();
    FBMOD1.MODL.Unload();
    FBMOD1.ICON.Unload();
    FBMOD1.MICO.Unload();
    FBMOD2.MODL.Unload();
    FBMOD2.ICON.Unload();
    FBMOD2.MICO.Unload();
    FBMOD3.MODL.Unload();
    FBMOD3.ICON.Unload();
    FBMOD3.MICO.Unload();

    HNAM.Unload();
    ENAM.Unload();

    MaleFGGS.Unload();
    MaleFGGA.Unload();
    MaleFGTS.Unload();
    MaleSNAM.Unload();

    FemaleFGGS.Unload();
    FemaleFGGA.Unload();
    FemaleFGTS.Unload();
    FemaleSNAM.Unload();
    return 1;
    }

SINT32 RACERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DESC);
    WRITE(XNAM);
    WRITE(DATA);
    WRITE(ONAM);
    WRITE(YNAM);

    writer.record_write_subheader('2MAN', 0);
    WRITE(VTCK);
    WRITE(DNAM);
    WRITE(CNAM);
    WRITE(PNAM);
    WRITE(UNAM);
    WRITE(ATTR);

    writer.record_write_subheader('0MAN', 0);
    writer.record_write_subheader('MANM', 0);
    UINT32 curINDX = 0;
    MHMOD0.Write(curINDX++, writer);
    MHMOD1.Write(curINDX++, writer);
    MHMOD2.Write(curINDX++, writer);
    MHMOD3.Write(curINDX++, writer);
    MHMOD4.Write(curINDX++, writer);
    MHMOD5.Write(curINDX++, writer);
    MHMOD6.Write(curINDX++, writer);
    MHMOD7.Write(curINDX, writer);

    writer.record_write_subheader('MANF', 0);
    curINDX = 0;
    FHMOD0.Write(curINDX++, writer);
    FHMOD1.Write(curINDX++, writer);
    FHMOD2.Write(curINDX++, writer);
    FHMOD3.Write(curINDX++, writer);
    FHMOD4.Write(curINDX++, writer);
    FHMOD5.Write(curINDX++, writer);
    FHMOD6.Write(curINDX++, writer);
    FHMOD7.Write(curINDX, writer);

    writer.record_write_subheader('1MAN', 0);
    writer.record_write_subheader('MANM', 0);
    curINDX = 0;
    MBMOD0.WriteIconsFirst(curINDX++, writer);
    MBMOD1.WriteIconsFirst(curINDX++, writer);
    MBMOD2.WriteIconsFirst(curINDX++, writer);
    MBMOD3.WriteIconsFirst(curINDX, writer);

    writer.record_write_subheader('MANF', 0);
    curINDX = 0;
    FBMOD0.WriteIconsFirst(curINDX++, writer);
    FBMOD1.WriteIconsFirst(curINDX++, writer);
    FBMOD2.WriteIconsFirst(curINDX++, writer);
    FBMOD3.WriteIconsFirst(curINDX, writer);

    if(HNAM.value.size())
        WRITE(HNAM);
    else
        writer.record_write_subheader('MANH', 0);

    if(ENAM.value.size())
        WRITE(ENAM);
    else
        writer.record_write_subheader('MANE', 0);

    writer.record_write_subheader('MANM', 0);
    WRITEALT(MaleFGGS,FGGS);
    WRITEALT(MaleFGGA,FGGA);
    WRITEALT(MaleFGTS,FGTS);
    WRITEALT(MaleSNAM,SNAM);

    writer.record_write_subheader('MANF', 0);
    WRITEALT(FemaleFGGS,FGGS);
    WRITEALT(FemaleFGGA,FGGA);
    WRITEALT(FemaleFGTS,FGTS);
    WRITEALT(FemaleSNAM,SNAM);
    return -1;
    }

bool RACERecord::operator ==(const RACERecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
        FULL.equals(other.FULL) &&
        DESC.equals(other.DESC) &&
        DATA == other.DATA &&
        VTCK == other.VTCK &&
        DNAM == other.DNAM &&
        CNAM == other.CNAM &&
        ONAM == other.ONAM &&
        YNAM == other.YNAM &&
        PNAM == other.PNAM &&
        UNAM == other.UNAM &&
        ATTR == other.ATTR &&
        MHMOD0 == other.MHMOD0 &&
        MHMOD1 == other.MHMOD1 &&
        MHMOD2 == other.MHMOD2 &&
        MHMOD3 == other.MHMOD3 &&
        MHMOD4 == other.MHMOD4 &&
        MHMOD5 == other.MHMOD5 &&
        MHMOD6 == other.MHMOD6 &&
        MHMOD7 == other.MHMOD7 &&
        FHMOD0 == other.FHMOD0 &&
        FHMOD1 == other.FHMOD1 &&
        FHMOD2 == other.FHMOD2 &&
        FHMOD3 == other.FHMOD3 &&
        FHMOD4 == other.FHMOD4 &&
        FHMOD5 == other.FHMOD5 &&
        FHMOD6 == other.FHMOD6 &&
        FHMOD7 == other.FHMOD7 &&
        MBMOD0 == other.MBMOD0 &&
        MBMOD1 == other.MBMOD1 &&
        MBMOD2 == other.MBMOD2 &&
        MBMOD3 == other.MBMOD3 &&
        FBMOD0 == other.FBMOD0 &&
        FBMOD1 == other.FBMOD1 &&
        FBMOD2 == other.FBMOD2 &&
        FBMOD3 == other.FBMOD3 &&
        MaleFGGS == other.MaleFGGS &&
        MaleFGGA == other.MaleFGGA &&
        MaleFGTS == other.MaleFGTS &&
        MaleSNAM == other.MaleSNAM &&
        FemaleFGGS == other.FemaleFGGS &&
        FemaleFGGA == other.FemaleFGGA &&
        FemaleFGTS == other.FemaleFGTS &&
        FemaleSNAM == other.FemaleSNAM &&
        XNAM == other.XNAM &&
        HNAM == other.HNAM &&
        ENAM == other.ENAM);
    }

bool RACERecord::operator !=(const RACERecord &other) const
    {
    return !(*this == other);
    }
}