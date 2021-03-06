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
#include "APPARecord.h"

namespace Ob
{
APPARecord::APPADATA::APPADATA():
    apparatus(0),
    value(25),
    weight(1.0f),
    quality(10.0f)
    {
    //
    }

APPARecord::APPADATA::~APPADATA()
    {
    //
    }

bool APPARecord::APPADATA::operator ==(const APPADATA &other) const
    {
    return (apparatus == other.apparatus &&
            value == other.value &&
            AlmostEqual(weight,other.weight,2) &&
            AlmostEqual(quality,other.quality,2));
    }

bool APPARecord::APPADATA::operator !=(const APPADATA &other) const
    {
    return !(*this == other);
    }

APPARecord::APPARecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

APPARecord::APPARecord(APPARecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    SCRI = srcRecord->SCRI;
    DATA = srcRecord->DATA;
    return;
    }

APPARecord::~APPARecord()
    {
    //
    }

bool APPARecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);

    return op.Stop();
    }

bool APPARecord::IsMortarPestle()
    {
    return (DATA.value.apparatus == eMortarPestle);
    }

void APPARecord::IsMortarPestle(bool value)
    {
    DATA.value.apparatus = value ? eMortarPestle : eAlembic;
    }

bool APPARecord::IsAlembic()
    {
    return (DATA.value.apparatus == eAlembic);
    }

void APPARecord::IsAlembic(bool value)
    {
    DATA.value.apparatus = value ? eAlembic : eMortarPestle;
    }

bool APPARecord::IsCalcinator()
    {
    return (DATA.value.apparatus == eCalcinator);
    }

void APPARecord::IsCalcinator(bool value)
    {
    DATA.value.apparatus = value ? eCalcinator : eMortarPestle;
    }

bool APPARecord::IsRetort()
    {
    return (DATA.value.apparatus == eRetort);
    }

void APPARecord::IsRetort(bool value)
    {
    DATA.value.apparatus = value ? eRetort : eMortarPestle;
    }

bool APPARecord::IsType(UINT8 Type)
    {
    return (DATA.value.apparatus == Type);
    }

void APPARecord::SetType(UINT8 Type)
    {
    DATA.value.apparatus = Type;
    }

UINT32 APPARecord::GetType()
    {
    return REV32(APPA);
    }

STRING APPARecord::GetStrType()
    {
    return "APPA";
    }

SINT32 APPARecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  APPA: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 APPARecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    SCRI.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 APPARecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(SCRI);
    WRITE(DATA);
    return -1;
    }

bool APPARecord::operator ==(const APPARecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            SCRI == other.SCRI &&
            DATA == other.DATA);
    }

bool APPARecord::operator !=(const APPARecord &other) const
    {
    return !(*this == other);
    }

bool APPARecord::equals(Record *other)
    {
    return *this == *(APPARecord *)other;
    }
}