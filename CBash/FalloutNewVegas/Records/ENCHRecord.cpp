/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "..\..\Common.h"
#include "ENCHRecord.h"

namespace FNV
{

ENCHRecord::ENCHENIT::ENCHENIT():
    itemType(0),
    chargeAmount(0),
    enchantCost(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

ENCHRecord::ENCHENIT::~ENCHENIT()
    {
    //
    }

bool ENCHRecord::ENCHENIT::operator ==(const ENCHENIT &other) const
    {
    return (itemType == other.itemType &&
            //chargeAmount == other.chargeAmount && //unused in FNV
            //enchantCost == other.enchantCost && //unused in FNV
            flags == other.flags);
    }

bool ENCHRecord::ENCHENIT::operator !=(const ENCHENIT &other) const
    {
    return !(*this == other);
    }

ENCHRecord::ENCHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ENCHRecord::ENCHRecord(ENCHRecord *srcRecord):
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    ENIT = srcRecord->ENIT;
    Effects = srcRecord->Effects;
    return;
    }

ENCHRecord::~ENCHRecord()
    {
    //
    }

bool ENCHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < Effects.value.size(); x++)
        Effects.value[x]->VisitFormIDs(op);

    return op.Stop();
    }

bool ENCHRecord::IsNoAutoCalc()
    {
    return (ENIT.value.flags & fIsNoAutoCalc) != 0;
    }

void ENCHRecord::IsNoAutoCalc(bool value)
    {
    ENIT.value.flags = value ? (ENIT.value.flags | fIsNoAutoCalc) : (ENIT.value.flags & ~fIsNoAutoCalc);
    }

bool ENCHRecord::IsHideEffect()
    {
    return (ENIT.value.flags & fIsHideEffect) != 0;
    }

void ENCHRecord::IsHideEffect(bool value)
    {
    ENIT.value.flags = value ? (ENIT.value.flags | fIsHideEffect) : (ENIT.value.flags & ~fIsHideEffect);
    }

bool ENCHRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((ENIT.value.flags & Mask) == Mask) : ((ENIT.value.flags & Mask) != 0);
    }

void ENCHRecord::SetFlagMask(UINT8 Mask)
    {
    ENIT.value.flags = Mask;
    }

bool ENCHRecord::IsWeapon()
    {
    return (ENIT.value.itemType == eWeapon);
    }

void ENCHRecord::IsWeapon(bool value)
    {
    ENIT.value.itemType = value ? eWeapon : eApparel;
    }

bool ENCHRecord::IsApparel()
    {
    return (ENIT.value.itemType == eApparel);
    }

void ENCHRecord::IsApparel(bool value)
    {
    ENIT.value.itemType = value ? eApparel : eWeapon;
    }

bool ENCHRecord::IsType(UINT32 Type)
    {
    return (ENIT.value.itemType == Type);
    }

void ENCHRecord::SetType(UINT32 Type)
    {
    ENIT.value.itemType = Type;
    }

UINT32 ENCHRecord::GetType()
    {
    return REV32(ENCH);
    }

STRING ENCHRecord::GetStrType()
    {
    return "ENCH";
    }

SINT32 ENCHRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ENIT):
                ENIT.Read(buffer, subSize);
                break;
            case REV32(EFID):
                Effects.value.push_back(new FNVEffect);
                Effects.value.back()->EFID.Read(buffer, subSize);
                break;
            case REV32(EFIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new FNVEffect);
                Effects.value.back()->EFIT.Read(buffer, subSize);
                break;
            case REV32(CTDA):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new FNVEffect);
                Effects.value.back()->CTDA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ENCH: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 ENCHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    ENIT.Unload();
    Effects.Unload();
    return 1;
    }

SINT32 ENCHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(ENIT);
    Effects.Write(writer);
    return -1;
    }

bool ENCHRecord::operator ==(const ENCHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ENIT == other.ENIT &&
            Effects == other.Effects);
    }

bool ENCHRecord::operator !=(const ENCHRecord &other) const
    {
    return !(*this == other);
    }

bool ENCHRecord::equals(Record *other)
    {
    return *this == *(ENCHRecord *)other;
    }
}