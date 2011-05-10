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
#include "BPTDRecord.h"

namespace FNV
{
bool BPTDRecord::BPTDPart::IsSeverable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSeverable) != 0;
    }

void BPTDRecord::BPTDPart::IsSeverable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsSeverable) : (Dummy->flags & ~fIsSeverable);
    }

bool BPTDRecord::BPTDPart::IsIKData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIKData) != 0;
    }

void BPTDRecord::BPTDPart::IsIKData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIKData) : (Dummy->flags & ~fIsIKData);
    }

bool BPTDRecord::BPTDPart::IsIKDataBipedData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIKDataBipedData) != 0;
    }

void BPTDRecord::BPTDPart::IsIKDataBipedData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIKDataBipedData) : (Dummy->flags & ~fIsIKDataBipedData);
    }

bool BPTDRecord::BPTDPart::IsExplodable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsExplodable) != 0;
    }

void BPTDRecord::BPTDPart::IsExplodable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsExplodable) : (Dummy->flags & ~fIsExplodable);
    }

bool BPTDRecord::BPTDPart::IsIKDataIsHead()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIKDataIsHead) != 0;
    }

void BPTDRecord::BPTDPart::IsIKDataIsHead(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIKDataIsHead) : (Dummy->flags & ~fIsIKDataIsHead);
    }

bool BPTDRecord::BPTDPart::IsIKDataHeadTracking()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIKDataHeadTracking) != 0;
    }

void BPTDRecord::BPTDPart::IsIKDataHeadTracking(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIKDataHeadTracking) : (Dummy->flags & ~fIsIKDataHeadTracking);
    }

bool BPTDRecord::BPTDPart::IsAbsoluteHitChance()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAbsoluteHitChance) != 0;
    }

void BPTDRecord::BPTDPart::IsAbsoluteHitChance(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAbsoluteHitChance) : (Dummy->flags & ~fIsAbsoluteHitChance);
    }

bool BPTDRecord::BPTDPart::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void BPTDRecord::BPTDPart::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool BPTDRecord::BPTDPart::IsTorso()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTorso);
    }

void BPTDRecord::BPTDPart::IsTorso(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTorso : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsHead1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHead1);
    }

void BPTDRecord::BPTDPart::IsHead1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHead1 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsHead2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHead2);
    }

void BPTDRecord::BPTDPart::IsHead2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHead2 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsLeftArm1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLeftArm1);
    }

void BPTDRecord::BPTDPart::IsLeftArm1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLeftArm1 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsLeftArm2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLeftArm2);
    }

void BPTDRecord::BPTDPart::IsLeftArm2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLeftArm2 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsRightArm1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRightArm1);
    }

void BPTDRecord::BPTDPart::IsRightArm1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRightArm1 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsRightArm2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRightArm2);
    }

void BPTDRecord::BPTDPart::IsRightArm2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRightArm2 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsLeftLeg1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLeftLeg1);
    }

void BPTDRecord::BPTDPart::IsLeftLeg1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLeftLeg1 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsLeftLeg2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLeftLeg2);
    }

void BPTDRecord::BPTDPart::IsLeftLeg2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLeftLeg2 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsLeftLeg3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLeftLeg3);
    }

void BPTDRecord::BPTDPart::IsLeftLeg3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLeftLeg3 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsRightLeg1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRightLeg1);
    }

void BPTDRecord::BPTDPart::IsRightLeg1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRightLeg1 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsRightLeg2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRightLeg2);
    }

void BPTDRecord::BPTDPart::IsRightLeg2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRightLeg2 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsRightLeg3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRightLeg3);
    }

void BPTDRecord::BPTDPart::IsRightLeg3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRightLeg3 : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsBrain()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBrain);
    }

void BPTDRecord::BPTDPart::IsBrain(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBrain : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWeapon);
    }

void BPTDRecord::BPTDPart::IsWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWeapon : eDummyDefault;
    }

bool BPTDRecord::BPTDPart::IsType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void BPTDRecord::BPTDPart::SetType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

BPTDRecord::BPTDRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

BPTDRecord::BPTDRecord(BPTDRecord *srcRecord):
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

    MODL = srcRecord->MODL;

    BPTN = srcRecord->BPTN;
    BPNN = srcRecord->BPNN;
    BPNT = srcRecord->BPNT;
    BPNI = srcRecord->BPNI;
    BPND = srcRecord->BPND;
    NAM1 = srcRecord->NAM1;
    NAM4 = srcRecord->NAM4;
    NAM5 = srcRecord->NAM5;
    RAGA = srcRecord->RAGA;
    return;
    }

BPTDRecord::~BPTDRecord()
    {
    //
    }

bool BPTDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    //if(BPND.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(BPND->value);
    if(RAGA.IsLoaded())
        op.Accept(RAGA->value);

    return op.Stop();
    }

UINT32 BPTDRecord::GetType()
    {
    return REV32(BPTD);
    }

STRING BPTDRecord::GetStrType()
    {
    return "BPTD";
    }

SINT32 BPTDRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case REV32(XXXX):
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
            case REV32(EDID):
                EDID.Read(buffer, subSize, curPos);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case REV32(BPTN):
                BPTN.Read(buffer, subSize, curPos);
                break;
            case REV32(BPNN):
                BPNN.Read(buffer, subSize, curPos);
                break;
            case REV32(BPNT):
                BPNT.Read(buffer, subSize, curPos);
                break;
            case REV32(BPNI):
                BPNI.Read(buffer, subSize, curPos);
                break;
            case REV32(BPND):
                BPND.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM4):
                NAM4.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM5):
                NAM5.Read(buffer, subSize, curPos);
                break;
            case REV32(RAGA):
                RAGA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  BPTD: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 BPTDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    BPTN.Unload();
    BPNN.Unload();
    BPNT.Unload();
    BPNI.Unload();
    BPND.Unload();
    NAM1.Unload();
    NAM4.Unload();
    NAM5.Unload();
    RAGA.Unload();
    return 1;
    }

SINT32 BPTDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);

    MODL.Write(writer);

    WRITE(BPTN);
    WRITE(BPNN);
    WRITE(BPNT);
    WRITE(BPNI);
    WRITE(BPND);
    WRITE(NAM1);
    WRITE(NAM4);
    WRITE(NAM5);
    WRITE(RAGA);

    return -1;
    }

bool BPTDRecord::operator ==(const BPTDRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            BPTN.equalsi(other.BPTN) &&
            BPNN.equalsi(other.BPNN) &&
            BPNT.equalsi(other.BPNT) &&
            BPNI.equalsi(other.BPNI) &&
            BPND == other.BPND &&
            NAM1.equalsi(other.NAM1) &&
            NAM4.equalsi(other.NAM4) &&
            NAM5 == other.NAM5 &&
            RAGA == other.RAGA);
    }

bool BPTDRecord::operator !=(const BPTDRecord &other) const
    {
    return !(*this == other);
    }
}