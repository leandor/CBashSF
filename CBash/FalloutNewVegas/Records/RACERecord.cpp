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

    XNAM.resize(srcRecord->XNAM.size());
    for(UINT32 x = 0; x < srcRecord->XNAM.size(); x++)
        {
        XNAM[x] = new ReqSubRecord<FNVXNAM>;
        *XNAM[x] = *srcRecord->XNAM[x];
        }

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

    HNAM.resize(srcRecord->HNAM.size());
    for(UINT32 x = 0; x < srcRecord->HNAM.size(); x++)
        HNAM[x] = srcRecord->HNAM[x];

    ENAM.resize(srcRecord->ENAM.size());
    for(UINT32 x = 0; x < srcRecord->ENAM.size(); x++)
        ENAM[x] = srcRecord->ENAM[x];

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
    for(UINT32 x = 0; x < XNAM.size(); x++)
        delete XNAM[x];
    }

bool RACERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < XNAM.size(); x++)
        op.Accept(XNAM[x]->value.faction);
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

    for(UINT32 x = 0; x < HNAM.size(); x++)
        op.Accept(HNAM[x]);
    for(UINT32 x = 0; x < ENAM.size(); x++)
        op.Accept(ENAM[x]);

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

UINT32 RACERecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-20];

    UINT32 cSize = 0;
    UINT32 TotSize = 306; // All empty markers + records written even if empty
    //TotSize += 54; from markers
    //TotSize += 240; from indices
    //TotSize += 12; from enam and hnam that are always written
    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DESC.IsLoaded())
        {
        cSize = DESC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    for(UINT32 p = 0; p < XNAM.size(); p++)
        TotSize += XNAM[p]->GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(ONAM.IsLoaded())
        TotSize += ONAM.GetSize() + 6;

    if(YNAM.IsLoaded())
        TotSize += YNAM.GetSize() + 6;

    if(VTCK.IsLoaded())
        TotSize += VTCK.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;

    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;

    if(UNAM.IsLoaded())
        TotSize += UNAM.GetSize() + 6;

    if(ATTR.IsLoaded())
        {
        cSize = ATTR.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MHMOD0.MODL.IsLoaded())
        {
        if(MHMOD0.MODL->MODL.IsLoaded())
            {
            cSize = MHMOD0.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD0.MODL->MODB.IsLoaded())
            TotSize += MHMOD0.MODL->MODB.GetSize() + 6;
        if(MHMOD0.MODL->MODT.IsLoaded())
            {
            cSize = MHMOD0.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD0.MODL->Textures.IsLoaded())
            {
            cSize = MHMOD0.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD0.MODL->MODD.IsLoaded())
            TotSize += MHMOD0.MODL->MODD.GetSize() + 6;
        }
    if(MHMOD0.ICON.IsLoaded())
        {
        cSize = MHMOD0.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MHMOD0.MICO.IsLoaded())
        {
        cSize = MHMOD0.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MHMOD1.MODL.IsLoaded())
        {
        if(MHMOD1.MODL->MODL.IsLoaded())
            {
            cSize = MHMOD1.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD1.MODL->MODB.IsLoaded())
            TotSize += MHMOD1.MODL->MODB.GetSize() + 6;
        if(MHMOD1.MODL->MODT.IsLoaded())
            {
            cSize = MHMOD1.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD1.MODL->Textures.IsLoaded())
            {
            cSize = MHMOD1.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD1.MODL->MODD.IsLoaded())
            TotSize += MHMOD1.MODL->MODD.GetSize() + 6;
        }
    if(MHMOD1.ICON.IsLoaded())
        {
        cSize = MHMOD1.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MHMOD1.MICO.IsLoaded())
        {
        cSize = MHMOD1.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MHMOD2.MODL.IsLoaded())
        {
        if(MHMOD2.MODL->MODL.IsLoaded())
            {
            cSize = MHMOD2.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD2.MODL->MODB.IsLoaded())
            TotSize += MHMOD2.MODL->MODB.GetSize() + 6;
        if(MHMOD2.MODL->MODT.IsLoaded())
            {
            cSize = MHMOD2.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD2.MODL->Textures.IsLoaded())
            {
            cSize = MHMOD2.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD2.MODL->MODD.IsLoaded())
            TotSize += MHMOD2.MODL->MODD.GetSize() + 6;
        }
    if(MHMOD2.ICON.IsLoaded())
        {
        cSize = MHMOD2.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MHMOD2.MICO.IsLoaded())
        {
        cSize = MHMOD2.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MHMOD3.MODL.IsLoaded())
        {
        if(MHMOD3.MODL->MODL.IsLoaded())
            {
            cSize = MHMOD3.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD3.MODL->MODB.IsLoaded())
            TotSize += MHMOD3.MODL->MODB.GetSize() + 6;
        if(MHMOD3.MODL->MODT.IsLoaded())
            {
            cSize = MHMOD3.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD3.MODL->Textures.IsLoaded())
            {
            cSize = MHMOD3.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD3.MODL->MODD.IsLoaded())
            TotSize += MHMOD3.MODL->MODD.GetSize() + 6;
        }
    if(MHMOD3.ICON.IsLoaded())
        {
        cSize = MHMOD3.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MHMOD3.MICO.IsLoaded())
        {
        cSize = MHMOD3.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MHMOD4.MODL.IsLoaded())
        {
        if(MHMOD4.MODL->MODL.IsLoaded())
            {
            cSize = MHMOD4.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD4.MODL->MODB.IsLoaded())
            TotSize += MHMOD4.MODL->MODB.GetSize() + 6;
        if(MHMOD4.MODL->MODT.IsLoaded())
            {
            cSize = MHMOD4.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD4.MODL->Textures.IsLoaded())
            {
            cSize = MHMOD4.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD4.MODL->MODD.IsLoaded())
            TotSize += MHMOD4.MODL->MODD.GetSize() + 6;
        }
    if(MHMOD4.ICON.IsLoaded())
        {
        cSize = MHMOD4.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MHMOD4.MICO.IsLoaded())
        {
        cSize = MHMOD4.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MHMOD5.MODL.IsLoaded())
        {
        if(MHMOD5.MODL->MODL.IsLoaded())
            {
            cSize = MHMOD5.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD5.MODL->MODB.IsLoaded())
            TotSize += MHMOD5.MODL->MODB.GetSize() + 6;
        if(MHMOD5.MODL->MODT.IsLoaded())
            {
            cSize = MHMOD5.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD5.MODL->Textures.IsLoaded())
            {
            cSize = MHMOD5.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD5.MODL->MODD.IsLoaded())
            TotSize += MHMOD5.MODL->MODD.GetSize() + 6;
        }
    if(MHMOD5.ICON.IsLoaded())
        {
        cSize = MHMOD5.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MHMOD5.MICO.IsLoaded())
        {
        cSize = MHMOD5.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MHMOD6.MODL.IsLoaded())
        {
        if(MHMOD6.MODL->MODL.IsLoaded())
            {
            cSize = MHMOD6.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD6.MODL->MODB.IsLoaded())
            TotSize += MHMOD6.MODL->MODB.GetSize() + 6;
        if(MHMOD6.MODL->MODT.IsLoaded())
            {
            cSize = MHMOD6.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD6.MODL->Textures.IsLoaded())
            {
            cSize = MHMOD6.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD6.MODL->MODD.IsLoaded())
            TotSize += MHMOD6.MODL->MODD.GetSize() + 6;
        }
    if(MHMOD6.ICON.IsLoaded())
        {
        cSize = MHMOD6.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MHMOD6.MICO.IsLoaded())
        {
        cSize = MHMOD6.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MHMOD7.MODL.IsLoaded())
        {
        if(MHMOD7.MODL->MODL.IsLoaded())
            {
            cSize = MHMOD7.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD7.MODL->MODB.IsLoaded())
            TotSize += MHMOD7.MODL->MODB.GetSize() + 6;
        if(MHMOD7.MODL->MODT.IsLoaded())
            {
            cSize = MHMOD7.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD7.MODL->Textures.IsLoaded())
            {
            cSize = MHMOD7.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MHMOD7.MODL->MODD.IsLoaded())
            TotSize += MHMOD7.MODL->MODD.GetSize() + 6;
        }
    if(MHMOD7.ICON.IsLoaded())
        {
        cSize = MHMOD7.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MHMOD7.MICO.IsLoaded())
        {
        cSize = MHMOD7.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FHMOD0.MODL.IsLoaded())
        {
        if(FHMOD0.MODL->MODL.IsLoaded())
            {
            cSize = FHMOD0.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD0.MODL->MODB.IsLoaded())
            TotSize += FHMOD0.MODL->MODB.GetSize() + 6;
        if(FHMOD0.MODL->MODT.IsLoaded())
            {
            cSize = FHMOD0.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD0.MODL->Textures.IsLoaded())
            {
            cSize = FHMOD0.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD0.MODL->MODD.IsLoaded())
            TotSize += FHMOD0.MODL->MODD.GetSize() + 6;
        }
    if(FHMOD0.ICON.IsLoaded())
        {
        cSize = FHMOD0.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FHMOD0.MICO.IsLoaded())
        {
        cSize = FHMOD0.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FHMOD1.MODL.IsLoaded())
        {
        if(FHMOD1.MODL->MODL.IsLoaded())
            {
            cSize = FHMOD1.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD1.MODL->MODB.IsLoaded())
            TotSize += FHMOD1.MODL->MODB.GetSize() + 6;
        if(FHMOD1.MODL->MODT.IsLoaded())
            {
            cSize = FHMOD1.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD1.MODL->Textures.IsLoaded())
            {
            cSize = FHMOD1.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD1.MODL->MODD.IsLoaded())
            TotSize += FHMOD1.MODL->MODD.GetSize() + 6;
        }
    if(FHMOD1.ICON.IsLoaded())
        {
        cSize = FHMOD1.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FHMOD1.MICO.IsLoaded())
        {
        cSize = FHMOD1.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FHMOD2.MODL.IsLoaded())
        {
        if(FHMOD2.MODL->MODL.IsLoaded())
            {
            cSize = FHMOD2.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD2.MODL->MODB.IsLoaded())
            TotSize += FHMOD2.MODL->MODB.GetSize() + 6;
        if(FHMOD2.MODL->MODT.IsLoaded())
            {
            cSize = FHMOD2.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD2.MODL->Textures.IsLoaded())
            {
            cSize = FHMOD2.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD2.MODL->MODD.IsLoaded())
            TotSize += FHMOD2.MODL->MODD.GetSize() + 6;
        }
    if(FHMOD2.ICON.IsLoaded())
        {
        cSize = FHMOD2.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FHMOD2.MICO.IsLoaded())
        {
        cSize = FHMOD2.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FHMOD3.MODL.IsLoaded())
        {
        if(FHMOD3.MODL->MODL.IsLoaded())
            {
            cSize = FHMOD3.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD3.MODL->MODB.IsLoaded())
            TotSize += FHMOD3.MODL->MODB.GetSize() + 6;
        if(FHMOD3.MODL->MODT.IsLoaded())
            {
            cSize = FHMOD3.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD3.MODL->Textures.IsLoaded())
            {
            cSize = FHMOD3.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD3.MODL->MODD.IsLoaded())
            TotSize += FHMOD3.MODL->MODD.GetSize() + 6;
        }
    if(FHMOD3.ICON.IsLoaded())
        {
        cSize = FHMOD3.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FHMOD3.MICO.IsLoaded())
        {
        cSize = FHMOD3.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FHMOD4.MODL.IsLoaded())
        {
        if(FHMOD4.MODL->MODL.IsLoaded())
            {
            cSize = FHMOD4.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD4.MODL->MODB.IsLoaded())
            TotSize += FHMOD4.MODL->MODB.GetSize() + 6;
        if(FHMOD4.MODL->MODT.IsLoaded())
            {
            cSize = FHMOD4.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD4.MODL->Textures.IsLoaded())
            {
            cSize = FHMOD4.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD4.MODL->MODD.IsLoaded())
            TotSize += FHMOD4.MODL->MODD.GetSize() + 6;
        }
    if(FHMOD4.ICON.IsLoaded())
        {
        cSize = FHMOD4.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FHMOD4.MICO.IsLoaded())
        {
        cSize = FHMOD4.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FHMOD5.MODL.IsLoaded())
        {
        if(FHMOD5.MODL->MODL.IsLoaded())
            {
            cSize = FHMOD5.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD5.MODL->MODB.IsLoaded())
            TotSize += FHMOD5.MODL->MODB.GetSize() + 6;
        if(FHMOD5.MODL->MODT.IsLoaded())
            {
            cSize = FHMOD5.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD5.MODL->Textures.IsLoaded())
            {
            cSize = FHMOD5.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD5.MODL->MODD.IsLoaded())
            TotSize += FHMOD5.MODL->MODD.GetSize() + 6;
        }
    if(FHMOD5.ICON.IsLoaded())
        {
        cSize = FHMOD5.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FHMOD5.MICO.IsLoaded())
        {
        cSize = FHMOD5.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FHMOD6.MODL.IsLoaded())
        {
        if(FHMOD6.MODL->MODL.IsLoaded())
            {
            cSize = FHMOD6.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD6.MODL->MODB.IsLoaded())
            TotSize += FHMOD6.MODL->MODB.GetSize() + 6;
        if(FHMOD6.MODL->MODT.IsLoaded())
            {
            cSize = FHMOD6.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD6.MODL->Textures.IsLoaded())
            {
            cSize = FHMOD6.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD6.MODL->MODD.IsLoaded())
            TotSize += FHMOD6.MODL->MODD.GetSize() + 6;
        }
    if(FHMOD6.ICON.IsLoaded())
        {
        cSize = FHMOD6.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FHMOD6.MICO.IsLoaded())
        {
        cSize = FHMOD6.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FHMOD7.MODL.IsLoaded())
        {
        if(FHMOD7.MODL->MODL.IsLoaded())
            {
            cSize = FHMOD7.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD7.MODL->MODB.IsLoaded())
            TotSize += FHMOD7.MODL->MODB.GetSize() + 6;
        if(FHMOD7.MODL->MODT.IsLoaded())
            {
            cSize = FHMOD7.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD7.MODL->Textures.IsLoaded())
            {
            cSize = FHMOD7.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FHMOD7.MODL->MODD.IsLoaded())
            TotSize += FHMOD7.MODL->MODD.GetSize() + 6;
        }
    if(FHMOD7.ICON.IsLoaded())
        {
        cSize = FHMOD7.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FHMOD7.MICO.IsLoaded())
        {
        cSize = FHMOD7.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MBMOD0.MODL.IsLoaded())
        {
        if(MBMOD0.MODL->MODL.IsLoaded())
            {
            cSize = MBMOD0.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD0.MODL->MODB.IsLoaded())
            TotSize += MBMOD0.MODL->MODB.GetSize() + 6;
        if(MBMOD0.MODL->MODT.IsLoaded())
            {
            cSize = MBMOD0.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD0.MODL->Textures.IsLoaded())
            {
            cSize = MBMOD0.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD0.MODL->MODD.IsLoaded())
            TotSize += MBMOD0.MODL->MODD.GetSize() + 6;
        }
    if(MBMOD0.ICON.IsLoaded())
        {
        cSize = MBMOD0.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MBMOD0.MICO.IsLoaded())
        {
        cSize = MBMOD0.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MBMOD1.MODL.IsLoaded())
        {
        if(MBMOD1.MODL->MODL.IsLoaded())
            {
            cSize = MBMOD1.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD1.MODL->MODB.IsLoaded())
            TotSize += MBMOD1.MODL->MODB.GetSize() + 6;
        if(MBMOD1.MODL->MODT.IsLoaded())
            {
            cSize = MBMOD1.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD1.MODL->Textures.IsLoaded())
            {
            cSize = MBMOD1.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD1.MODL->MODD.IsLoaded())
            TotSize += MBMOD1.MODL->MODD.GetSize() + 6;
        }
    if(MBMOD1.ICON.IsLoaded())
        {
        cSize = MBMOD1.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MBMOD1.MICO.IsLoaded())
        {
        cSize = MBMOD1.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MBMOD2.MODL.IsLoaded())
        {
        if(MBMOD2.MODL->MODL.IsLoaded())
            {
            cSize = MBMOD2.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD2.MODL->MODB.IsLoaded())
            TotSize += MBMOD2.MODL->MODB.GetSize() + 6;
        if(MBMOD2.MODL->MODT.IsLoaded())
            {
            cSize = MBMOD2.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD2.MODL->Textures.IsLoaded())
            {
            cSize = MBMOD2.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD2.MODL->MODD.IsLoaded())
            TotSize += MBMOD2.MODL->MODD.GetSize() + 6;
        }
    if(MBMOD2.ICON.IsLoaded())
        {
        cSize = MBMOD2.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MBMOD2.MICO.IsLoaded())
        {
        cSize = MBMOD2.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MBMOD3.MODL.IsLoaded())
        {
        if(MBMOD3.MODL->MODL.IsLoaded())
            {
            cSize = MBMOD3.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD3.MODL->MODB.IsLoaded())
            TotSize += MBMOD3.MODL->MODB.GetSize() + 6;
        if(MBMOD3.MODL->MODT.IsLoaded())
            {
            cSize = MBMOD3.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD3.MODL->Textures.IsLoaded())
            {
            cSize = MBMOD3.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MBMOD3.MODL->MODD.IsLoaded())
            TotSize += MBMOD3.MODL->MODD.GetSize() + 6;
        }
    if(MBMOD3.ICON.IsLoaded())
        {
        cSize = MBMOD3.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MBMOD3.MICO.IsLoaded())
        {
        cSize = MBMOD3.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FBMOD0.MODL.IsLoaded())
        {
        if(FBMOD0.MODL->MODL.IsLoaded())
            {
            cSize = FBMOD0.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD0.MODL->MODB.IsLoaded())
            TotSize += FBMOD0.MODL->MODB.GetSize() + 6;
        if(FBMOD0.MODL->MODT.IsLoaded())
            {
            cSize = FBMOD0.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD0.MODL->Textures.IsLoaded())
            {
            cSize = FBMOD0.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD0.MODL->MODD.IsLoaded())
            TotSize += FBMOD0.MODL->MODD.GetSize() + 6;
        }
    if(FBMOD0.ICON.IsLoaded())
        {
        cSize = FBMOD0.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FBMOD0.MICO.IsLoaded())
        {
        cSize = FBMOD0.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FBMOD1.MODL.IsLoaded())
        {
        if(FBMOD1.MODL->MODL.IsLoaded())
            {
            cSize = FBMOD1.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD1.MODL->MODB.IsLoaded())
            TotSize += FBMOD1.MODL->MODB.GetSize() + 6;
        if(FBMOD1.MODL->MODT.IsLoaded())
            {
            cSize = FBMOD1.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD1.MODL->Textures.IsLoaded())
            {
            cSize = FBMOD1.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD1.MODL->MODD.IsLoaded())
            TotSize += FBMOD1.MODL->MODD.GetSize() + 6;
        }
    if(FBMOD1.ICON.IsLoaded())
        {
        cSize = FBMOD1.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FBMOD1.MICO.IsLoaded())
        {
        cSize = FBMOD1.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FBMOD2.MODL.IsLoaded())
        {
        if(FBMOD2.MODL->MODL.IsLoaded())
            {
            cSize = FBMOD2.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD2.MODL->MODB.IsLoaded())
            TotSize += FBMOD2.MODL->MODB.GetSize() + 6;
        if(FBMOD2.MODL->MODT.IsLoaded())
            {
            cSize = FBMOD2.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD2.MODL->Textures.IsLoaded())
            {
            cSize = FBMOD2.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD2.MODL->MODD.IsLoaded())
            TotSize += FBMOD2.MODL->MODD.GetSize() + 6;
        }
    if(FBMOD2.ICON.IsLoaded())
        {
        cSize = FBMOD2.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FBMOD2.MICO.IsLoaded())
        {
        cSize = FBMOD2.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FBMOD3.MODL.IsLoaded())
        {
        if(FBMOD3.MODL->MODL.IsLoaded())
            {
            cSize = FBMOD3.MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD3.MODL->MODB.IsLoaded())
            TotSize += FBMOD3.MODL->MODB.GetSize() + 6;
        if(FBMOD3.MODL->MODT.IsLoaded())
            {
            cSize = FBMOD3.MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD3.MODL->Textures.IsLoaded())
            {
            cSize = FBMOD3.MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FBMOD3.MODL->MODD.IsLoaded())
            TotSize += FBMOD3.MODL->MODD.GetSize() + 6;
        }
    if(FBMOD3.ICON.IsLoaded())
        {
        cSize = FBMOD3.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FBMOD3.MICO.IsLoaded())
        {
        cSize = FBMOD3.MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(HNAM.size())
        {
        cSize = (sizeof(UINT32) * (UINT32)HNAM.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize;
        }

    if(ENAM.size())
        {
        cSize = (sizeof(UINT32) * (UINT32)ENAM.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize;
        }

    if(MaleFGGS.IsLoaded())
        TotSize += MaleFGGS.GetSize() + 6;

    if(MaleFGGA.IsLoaded())
        TotSize += MaleFGGA.GetSize() + 6;

    if(MaleFGTS.IsLoaded())
        TotSize += MaleFGTS.GetSize() + 6;

    if(MaleSNAM.IsLoaded())
        TotSize += MaleSNAM.GetSize() + 6;

    if(FemaleFGGS.IsLoaded())
        TotSize += FemaleFGGS.GetSize() + 6;

    if(FemaleFGGA.IsLoaded())
        TotSize += FemaleFGGA.GetSize() + 6;

    if(FemaleFGTS.IsLoaded())
        TotSize += FemaleFGTS.GetSize() + 6;

    if(FemaleSNAM.IsLoaded())
        TotSize += FemaleSNAM.GetSize() + 6;

    return TotSize;
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
                XNAM.push_back(new ReqSubRecord<FNVXNAM>);
                XNAM.back()->Read(buffer, subSize, curPos);
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
                if(subSize % sizeof(FORMID) == 0)
                    {
                    if(subSize == 0)
                        break;
                    HNAM.resize(subSize / sizeof(FORMID));
                    _readBuffer(&HNAM[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized HNAM size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case 'MANE':
                if(subSize % sizeof(FORMID) == 0)
                    {
                    if(subSize == 0)
                        break;
                    ENAM.resize(subSize / sizeof(FORMID));
                    _readBuffer(&ENAM[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized ENAM size: %i\n", subSize);
                    curPos += subSize;
                    }
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

    for(UINT32 x = 0; x < XNAM.size(); x++)
        delete XNAM[x];
    XNAM.clear();

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

    HNAM.clear();
    ENAM.clear();

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

SINT32 RACERecord::WriteRecord(_FileHandler &SaveHandler)
    {
    UINT32 curINDX = 0;
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(DESC.IsLoaded())
        SaveHandler.writeSubRecord('CSED', DESC.value, DESC.GetSize());

    for(UINT32 p = 0; p < XNAM.size(); p++)
        SaveHandler.writeSubRecord('MANX', &XNAM[p]->value, XNAM[p]->GetSize());

    SaveHandler.writeSubRecord('ATAD', &DATA.value, DATA.GetSize());

    if(ONAM.IsLoaded())
        SaveHandler.writeSubRecord('MANO', &ONAM.value, ONAM.GetSize());

    if(YNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANY', &YNAM.value, YNAM.GetSize());

    SaveHandler.writeSubRecordHeader('2MAN', 0);

    if(VTCK.IsLoaded())
        SaveHandler.writeSubRecord('KCTV', &VTCK.value, VTCK.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', &DNAM.value, DNAM.GetSize());

    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANC', &CNAM.value, CNAM.GetSize());

    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANP', &PNAM.value, PNAM.GetSize());

    if(UNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANU', &UNAM.value, UNAM.GetSize());

    if(ATTR.IsLoaded())
        SaveHandler.writeSubRecord('RTTA', ATTR.value, ATTR.GetSize());

    SaveHandler.writeSubRecordHeader('0MAN', 0);
    SaveHandler.writeSubRecordHeader('MANM', 0);

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MHMOD0.MODL.IsLoaded())
        {
        if(MHMOD0.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MHMOD0.MODL->MODL.value, MHMOD0.MODL->MODL.GetSize());
        if(MHMOD0.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MHMOD0.MODL->MODB.value, MHMOD0.MODL->MODB.GetSize());
        if(MHMOD0.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MHMOD0.MODL->MODT.value, MHMOD0.MODL->MODT.GetSize());
        if(MHMOD0.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MHMOD0.MODL->Textures.GetSize());
            UINT32 cSize = MHMOD0.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MHMOD0.MODL->Textures.MODS.size(); ++p)
                {
                if(MHMOD0.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MHMOD0.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MHMOD0.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MHMOD0.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MHMOD0.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MHMOD0.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MHMOD0.MODL->MODD.value, MHMOD0.MODL->MODD.GetSize());
        }
    if(MHMOD0.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MHMOD0.ICON.value, MHMOD0.ICON.GetSize());
    if(MHMOD0.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MHMOD0.MICO.value, MHMOD0.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MHMOD1.MODL.IsLoaded())
        {
        if(MHMOD1.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MHMOD1.MODL->MODL.value, MHMOD1.MODL->MODL.GetSize());
        if(MHMOD1.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MHMOD1.MODL->MODB.value, MHMOD1.MODL->MODB.GetSize());
        if(MHMOD1.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MHMOD1.MODL->MODT.value, MHMOD1.MODL->MODT.GetSize());
        if(MHMOD1.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MHMOD1.MODL->Textures.GetSize());
            UINT32 cSize = MHMOD1.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MHMOD1.MODL->Textures.MODS.size(); ++p)
                {
                if(MHMOD1.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MHMOD1.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MHMOD1.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MHMOD1.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MHMOD1.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MHMOD1.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MHMOD1.MODL->MODD.value, MHMOD1.MODL->MODD.GetSize());
        }
    if(MHMOD1.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MHMOD1.ICON.value, MHMOD1.ICON.GetSize());
    if(MHMOD1.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MHMOD1.MICO.value, MHMOD1.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MHMOD2.MODL.IsLoaded())
        {
        if(MHMOD2.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MHMOD2.MODL->MODL.value, MHMOD2.MODL->MODL.GetSize());
        if(MHMOD2.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MHMOD2.MODL->MODB.value, MHMOD2.MODL->MODB.GetSize());
        if(MHMOD2.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MHMOD2.MODL->MODT.value, MHMOD2.MODL->MODT.GetSize());
        if(MHMOD2.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MHMOD2.MODL->Textures.GetSize());
            UINT32 cSize = MHMOD2.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MHMOD2.MODL->Textures.MODS.size(); ++p)
                {
                if(MHMOD2.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MHMOD2.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MHMOD2.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MHMOD2.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MHMOD2.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MHMOD2.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MHMOD2.MODL->MODD.value, MHMOD2.MODL->MODD.GetSize());
        }
    if(MHMOD2.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MHMOD2.ICON.value, MHMOD2.ICON.GetSize());
    if(MHMOD2.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MHMOD2.MICO.value, MHMOD2.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MHMOD3.MODL.IsLoaded())
        {
        if(MHMOD3.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MHMOD3.MODL->MODL.value, MHMOD3.MODL->MODL.GetSize());
        if(MHMOD3.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MHMOD3.MODL->MODB.value, MHMOD3.MODL->MODB.GetSize());
        if(MHMOD3.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MHMOD3.MODL->MODT.value, MHMOD3.MODL->MODT.GetSize());
        if(MHMOD3.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MHMOD3.MODL->Textures.GetSize());
            UINT32 cSize = MHMOD3.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MHMOD3.MODL->Textures.MODS.size(); ++p)
                {
                if(MHMOD3.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MHMOD3.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MHMOD3.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MHMOD3.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MHMOD3.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MHMOD3.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MHMOD3.MODL->MODD.value, MHMOD3.MODL->MODD.GetSize());
        }
    if(MHMOD3.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MHMOD3.ICON.value, MHMOD3.ICON.GetSize());
    if(MHMOD3.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MHMOD3.MICO.value, MHMOD3.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MHMOD4.MODL.IsLoaded())
        {
        if(MHMOD4.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MHMOD4.MODL->MODL.value, MHMOD4.MODL->MODL.GetSize());
        if(MHMOD4.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MHMOD4.MODL->MODB.value, MHMOD4.MODL->MODB.GetSize());
        if(MHMOD4.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MHMOD4.MODL->MODT.value, MHMOD4.MODL->MODT.GetSize());
        if(MHMOD4.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MHMOD4.MODL->Textures.GetSize());
            UINT32 cSize = MHMOD4.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MHMOD4.MODL->Textures.MODS.size(); ++p)
                {
                if(MHMOD4.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MHMOD4.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MHMOD4.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MHMOD4.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MHMOD4.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MHMOD4.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MHMOD4.MODL->MODD.value, MHMOD4.MODL->MODD.GetSize());
        }
    if(MHMOD4.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MHMOD4.ICON.value, MHMOD4.ICON.GetSize());
    if(MHMOD4.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MHMOD4.MICO.value, MHMOD4.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MHMOD5.MODL.IsLoaded())
        {
        if(MHMOD5.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MHMOD5.MODL->MODL.value, MHMOD5.MODL->MODL.GetSize());
        if(MHMOD5.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MHMOD5.MODL->MODB.value, MHMOD5.MODL->MODB.GetSize());
        if(MHMOD5.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MHMOD5.MODL->MODT.value, MHMOD5.MODL->MODT.GetSize());
        if(MHMOD5.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MHMOD5.MODL->Textures.GetSize());
            UINT32 cSize = MHMOD5.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MHMOD5.MODL->Textures.MODS.size(); ++p)
                {
                if(MHMOD5.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MHMOD5.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MHMOD5.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MHMOD5.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MHMOD5.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MHMOD5.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MHMOD5.MODL->MODD.value, MHMOD5.MODL->MODD.GetSize());
        }
    if(MHMOD5.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MHMOD5.ICON.value, MHMOD5.ICON.GetSize());
    if(MHMOD5.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MHMOD5.MICO.value, MHMOD5.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MHMOD6.MODL.IsLoaded())
        {
        if(MHMOD6.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MHMOD6.MODL->MODL.value, MHMOD6.MODL->MODL.GetSize());
        if(MHMOD6.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MHMOD6.MODL->MODB.value, MHMOD6.MODL->MODB.GetSize());
        if(MHMOD6.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MHMOD6.MODL->MODT.value, MHMOD6.MODL->MODT.GetSize());
        if(MHMOD6.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MHMOD6.MODL->Textures.GetSize());
            UINT32 cSize = MHMOD6.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MHMOD6.MODL->Textures.MODS.size(); ++p)
                {
                if(MHMOD6.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MHMOD6.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MHMOD6.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MHMOD6.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MHMOD6.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MHMOD6.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MHMOD6.MODL->MODD.value, MHMOD6.MODL->MODD.GetSize());
        }
    if(MHMOD6.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MHMOD6.ICON.value, MHMOD6.ICON.GetSize());
    if(MHMOD6.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MHMOD6.MICO.value, MHMOD6.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MHMOD7.MODL.IsLoaded())
        {
        if(MHMOD7.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MHMOD7.MODL->MODL.value, MHMOD7.MODL->MODL.GetSize());
        if(MHMOD7.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MHMOD7.MODL->MODB.value, MHMOD7.MODL->MODB.GetSize());
        if(MHMOD7.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MHMOD7.MODL->MODT.value, MHMOD7.MODL->MODT.GetSize());
        if(MHMOD7.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MHMOD7.MODL->Textures.GetSize());
            UINT32 cSize = MHMOD7.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MHMOD7.MODL->Textures.MODS.size(); ++p)
                {
                if(MHMOD7.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MHMOD7.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MHMOD7.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MHMOD7.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MHMOD7.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MHMOD7.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MHMOD7.MODL->MODD.value, MHMOD7.MODL->MODD.GetSize());
        }
    if(MHMOD7.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MHMOD7.ICON.value, MHMOD7.ICON.GetSize());
    if(MHMOD7.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MHMOD7.MICO.value, MHMOD7.MICO.GetSize());

    curINDX = 0;
    SaveHandler.writeSubRecordHeader('MANF', 0);

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FHMOD0.MODL.IsLoaded())
        {
        if(FHMOD0.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FHMOD0.MODL->MODL.value, FHMOD0.MODL->MODL.GetSize());
        if(FHMOD0.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FHMOD0.MODL->MODB.value, FHMOD0.MODL->MODB.GetSize());
        if(FHMOD0.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FHMOD0.MODL->MODT.value, FHMOD0.MODL->MODT.GetSize());
        if(FHMOD0.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FHMOD0.MODL->Textures.GetSize());
            UINT32 cSize = FHMOD0.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FHMOD0.MODL->Textures.MODS.size(); ++p)
                {
                if(FHMOD0.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FHMOD0.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FHMOD0.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FHMOD0.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FHMOD0.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FHMOD0.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FHMOD0.MODL->MODD.value, FHMOD0.MODL->MODD.GetSize());
        }
    if(FHMOD0.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FHMOD0.ICON.value, FHMOD0.ICON.GetSize());
    if(FHMOD0.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FHMOD0.MICO.value, FHMOD0.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FHMOD1.MODL.IsLoaded())
        {
        if(FHMOD1.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FHMOD1.MODL->MODL.value, FHMOD1.MODL->MODL.GetSize());
        if(FHMOD1.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FHMOD1.MODL->MODB.value, FHMOD1.MODL->MODB.GetSize());
        if(FHMOD1.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FHMOD1.MODL->MODT.value, FHMOD1.MODL->MODT.GetSize());
        if(FHMOD1.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FHMOD1.MODL->Textures.GetSize());
            UINT32 cSize = FHMOD1.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FHMOD1.MODL->Textures.MODS.size(); ++p)
                {
                if(FHMOD1.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FHMOD1.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FHMOD1.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FHMOD1.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FHMOD1.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FHMOD1.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FHMOD1.MODL->MODD.value, FHMOD1.MODL->MODD.GetSize());
        }
    if(FHMOD1.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FHMOD1.ICON.value, FHMOD1.ICON.GetSize());
    if(FHMOD1.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FHMOD1.MICO.value, FHMOD1.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FHMOD2.MODL.IsLoaded())
        {
        if(FHMOD2.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FHMOD2.MODL->MODL.value, FHMOD2.MODL->MODL.GetSize());
        if(FHMOD2.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FHMOD2.MODL->MODB.value, FHMOD2.MODL->MODB.GetSize());
        if(FHMOD2.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FHMOD2.MODL->MODT.value, FHMOD2.MODL->MODT.GetSize());
        if(FHMOD2.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FHMOD2.MODL->Textures.GetSize());
            UINT32 cSize = FHMOD2.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FHMOD2.MODL->Textures.MODS.size(); ++p)
                {
                if(FHMOD2.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FHMOD2.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FHMOD2.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FHMOD2.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FHMOD2.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FHMOD2.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FHMOD2.MODL->MODD.value, FHMOD2.MODL->MODD.GetSize());
        }
    if(FHMOD2.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FHMOD2.ICON.value, FHMOD2.ICON.GetSize());
    if(FHMOD2.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FHMOD2.MICO.value, FHMOD2.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FHMOD3.MODL.IsLoaded())
        {
        if(FHMOD3.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FHMOD3.MODL->MODL.value, FHMOD3.MODL->MODL.GetSize());
        if(FHMOD3.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FHMOD3.MODL->MODB.value, FHMOD3.MODL->MODB.GetSize());
        if(FHMOD3.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FHMOD3.MODL->MODT.value, FHMOD3.MODL->MODT.GetSize());
        if(FHMOD3.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FHMOD3.MODL->Textures.GetSize());
            UINT32 cSize = FHMOD3.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FHMOD3.MODL->Textures.MODS.size(); ++p)
                {
                if(FHMOD3.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FHMOD3.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FHMOD3.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FHMOD3.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FHMOD3.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FHMOD3.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FHMOD3.MODL->MODD.value, FHMOD3.MODL->MODD.GetSize());
        }
    if(FHMOD3.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FHMOD3.ICON.value, FHMOD3.ICON.GetSize());
    if(FHMOD3.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FHMOD3.MICO.value, FHMOD3.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FHMOD4.MODL.IsLoaded())
        {
        if(FHMOD4.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FHMOD4.MODL->MODL.value, FHMOD4.MODL->MODL.GetSize());
        if(FHMOD4.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FHMOD4.MODL->MODB.value, FHMOD4.MODL->MODB.GetSize());
        if(FHMOD4.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FHMOD4.MODL->MODT.value, FHMOD4.MODL->MODT.GetSize());
        if(FHMOD4.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FHMOD4.MODL->Textures.GetSize());
            UINT32 cSize = FHMOD4.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FHMOD4.MODL->Textures.MODS.size(); ++p)
                {
                if(FHMOD4.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FHMOD4.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FHMOD4.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FHMOD4.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FHMOD4.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FHMOD4.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FHMOD4.MODL->MODD.value, FHMOD4.MODL->MODD.GetSize());
        }
    if(FHMOD4.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FHMOD4.ICON.value, FHMOD4.ICON.GetSize());
    if(FHMOD4.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FHMOD4.MICO.value, FHMOD4.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FHMOD5.MODL.IsLoaded())
        {
        if(FHMOD5.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FHMOD5.MODL->MODL.value, FHMOD5.MODL->MODL.GetSize());
        if(FHMOD5.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FHMOD5.MODL->MODB.value, FHMOD5.MODL->MODB.GetSize());
        if(FHMOD5.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FHMOD5.MODL->MODT.value, FHMOD5.MODL->MODT.GetSize());
        if(FHMOD5.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FHMOD5.MODL->Textures.GetSize());
            UINT32 cSize = FHMOD5.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FHMOD5.MODL->Textures.MODS.size(); ++p)
                {
                if(FHMOD5.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FHMOD5.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FHMOD5.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FHMOD5.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FHMOD5.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FHMOD5.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FHMOD5.MODL->MODD.value, FHMOD5.MODL->MODD.GetSize());
        }
    if(FHMOD5.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FHMOD5.ICON.value, FHMOD5.ICON.GetSize());
    if(FHMOD5.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FHMOD5.MICO.value, FHMOD5.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FHMOD6.MODL.IsLoaded())
        {
        if(FHMOD6.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FHMOD6.MODL->MODL.value, FHMOD6.MODL->MODL.GetSize());
        if(FHMOD6.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FHMOD6.MODL->MODB.value, FHMOD6.MODL->MODB.GetSize());
        if(FHMOD6.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FHMOD6.MODL->MODT.value, FHMOD6.MODL->MODT.GetSize());
        if(FHMOD6.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FHMOD6.MODL->Textures.GetSize());
            UINT32 cSize = FHMOD6.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FHMOD6.MODL->Textures.MODS.size(); ++p)
                {
                if(FHMOD6.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FHMOD6.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FHMOD6.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FHMOD6.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FHMOD6.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FHMOD6.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FHMOD6.MODL->MODD.value, FHMOD6.MODL->MODD.GetSize());
        }
    if(FHMOD6.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FHMOD6.ICON.value, FHMOD6.ICON.GetSize());
    if(FHMOD6.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FHMOD6.MICO.value, FHMOD6.MICO.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FHMOD7.MODL.IsLoaded())
        {
        if(FHMOD7.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FHMOD7.MODL->MODL.value, FHMOD7.MODL->MODL.GetSize());
        if(FHMOD7.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FHMOD7.MODL->MODB.value, FHMOD7.MODL->MODB.GetSize());
        if(FHMOD7.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FHMOD7.MODL->MODT.value, FHMOD7.MODL->MODT.GetSize());
        if(FHMOD7.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FHMOD7.MODL->Textures.GetSize());
            UINT32 cSize = FHMOD7.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FHMOD7.MODL->Textures.MODS.size(); ++p)
                {
                if(FHMOD7.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FHMOD7.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FHMOD7.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FHMOD7.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FHMOD7.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FHMOD7.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FHMOD7.MODL->MODD.value, FHMOD7.MODL->MODD.GetSize());
        }
    if(FHMOD7.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FHMOD7.ICON.value, FHMOD7.ICON.GetSize());
    if(FHMOD7.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FHMOD7.MICO.value, FHMOD7.MICO.GetSize());

    curINDX = 0;
    SaveHandler.writeSubRecordHeader('1MAN', 0);
    SaveHandler.writeSubRecordHeader('MANM', 0);

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MBMOD0.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MBMOD0.ICON.value, MBMOD0.ICON.GetSize());
    if(MBMOD0.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MBMOD0.MICO.value, MBMOD0.MICO.GetSize());
    if(MBMOD0.MODL.IsLoaded())
        {
        if(MBMOD0.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MBMOD0.MODL->MODL.value, MBMOD0.MODL->MODL.GetSize());
        if(MBMOD0.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MBMOD0.MODL->MODB.value, MBMOD0.MODL->MODB.GetSize());
        if(MBMOD0.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MBMOD0.MODL->MODT.value, MBMOD0.MODL->MODT.GetSize());
        if(MBMOD0.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MBMOD0.MODL->Textures.GetSize());
            UINT32 cSize = MBMOD0.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MBMOD0.MODL->Textures.MODS.size(); ++p)
                {
                if(MBMOD0.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MBMOD0.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MBMOD0.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MBMOD0.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MBMOD0.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MBMOD0.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MBMOD0.MODL->MODD.value, MBMOD0.MODL->MODD.GetSize());
        }
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MBMOD1.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MBMOD1.ICON.value, MBMOD1.ICON.GetSize());
    if(MBMOD1.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MBMOD1.MICO.value, MBMOD1.MICO.GetSize());
    if(MBMOD1.MODL.IsLoaded())
        {
        if(MBMOD1.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MBMOD1.MODL->MODL.value, MBMOD1.MODL->MODL.GetSize());
        if(MBMOD1.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MBMOD1.MODL->MODB.value, MBMOD1.MODL->MODB.GetSize());
        if(MBMOD1.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MBMOD1.MODL->MODT.value, MBMOD1.MODL->MODT.GetSize());
        if(MBMOD1.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MBMOD1.MODL->Textures.GetSize());
            UINT32 cSize = MBMOD1.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MBMOD1.MODL->Textures.MODS.size(); ++p)
                {
                if(MBMOD1.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MBMOD1.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MBMOD1.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MBMOD1.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MBMOD1.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MBMOD1.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MBMOD1.MODL->MODD.value, MBMOD1.MODL->MODD.GetSize());
        }
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MBMOD2.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MBMOD2.ICON.value, MBMOD2.ICON.GetSize());
    if(MBMOD2.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MBMOD2.MICO.value, MBMOD2.MICO.GetSize());
    if(MBMOD2.MODL.IsLoaded())
        {
        if(MBMOD2.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MBMOD2.MODL->MODL.value, MBMOD2.MODL->MODL.GetSize());
        if(MBMOD2.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MBMOD2.MODL->MODB.value, MBMOD2.MODL->MODB.GetSize());
        if(MBMOD2.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MBMOD2.MODL->MODT.value, MBMOD2.MODL->MODT.GetSize());
        if(MBMOD2.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MBMOD2.MODL->Textures.GetSize());
            UINT32 cSize = MBMOD2.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MBMOD2.MODL->Textures.MODS.size(); ++p)
                {
                if(MBMOD2.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MBMOD2.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MBMOD2.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MBMOD2.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MBMOD2.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MBMOD2.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MBMOD2.MODL->MODD.value, MBMOD2.MODL->MODD.GetSize());
        }
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(MBMOD3.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', MBMOD3.ICON.value, MBMOD3.ICON.GetSize());
    if(MBMOD3.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MBMOD3.MICO.value, MBMOD3.MICO.GetSize());
    if(MBMOD3.MODL.IsLoaded())
        {
        if(MBMOD3.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MBMOD3.MODL->MODL.value, MBMOD3.MODL->MODL.GetSize());
        if(MBMOD3.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MBMOD3.MODL->MODB.value, MBMOD3.MODL->MODB.GetSize());
        if(MBMOD3.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MBMOD3.MODL->MODT.value, MBMOD3.MODL->MODT.GetSize());
        if(MBMOD3.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MBMOD3.MODL->Textures.GetSize());
            UINT32 cSize = MBMOD3.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MBMOD3.MODL->Textures.MODS.size(); ++p)
                {
                if(MBMOD3.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MBMOD3.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MBMOD3.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&MBMOD3.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MBMOD3.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MBMOD3.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MBMOD3.MODL->MODD.value, MBMOD3.MODL->MODD.GetSize());
        }

    curINDX = 0;
    SaveHandler.writeSubRecordHeader('MANF', 0);

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FBMOD0.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FBMOD0.ICON.value, FBMOD0.ICON.GetSize());
    if(FBMOD0.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FBMOD0.MICO.value, FBMOD0.MICO.GetSize());
    if(FBMOD0.MODL.IsLoaded())
        {
        if(FBMOD0.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FBMOD0.MODL->MODL.value, FBMOD0.MODL->MODL.GetSize());
        if(FBMOD0.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FBMOD0.MODL->MODB.value, FBMOD0.MODL->MODB.GetSize());
        if(FBMOD0.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FBMOD0.MODL->MODT.value, FBMOD0.MODL->MODT.GetSize());
        if(FBMOD0.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FBMOD0.MODL->Textures.GetSize());
            UINT32 cSize = FBMOD0.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FBMOD0.MODL->Textures.MODS.size(); ++p)
                {
                if(FBMOD0.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FBMOD0.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FBMOD0.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FBMOD0.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FBMOD0.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FBMOD0.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FBMOD0.MODL->MODD.value, FBMOD0.MODL->MODD.GetSize());
        }
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FBMOD1.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FBMOD1.ICON.value, FBMOD1.ICON.GetSize());
    if(FBMOD1.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FBMOD1.MICO.value, FBMOD1.MICO.GetSize());
    if(FBMOD1.MODL.IsLoaded())
        {
        if(FBMOD1.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FBMOD1.MODL->MODL.value, FBMOD1.MODL->MODL.GetSize());
        if(FBMOD1.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FBMOD1.MODL->MODB.value, FBMOD1.MODL->MODB.GetSize());
        if(FBMOD1.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FBMOD1.MODL->MODT.value, FBMOD1.MODL->MODT.GetSize());
        if(FBMOD1.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FBMOD1.MODL->Textures.GetSize());
            UINT32 cSize = FBMOD1.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FBMOD1.MODL->Textures.MODS.size(); ++p)
                {
                if(FBMOD1.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FBMOD1.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FBMOD1.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FBMOD1.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FBMOD1.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FBMOD1.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FBMOD1.MODL->MODD.value, FBMOD1.MODL->MODD.GetSize());
        }
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FBMOD2.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FBMOD2.ICON.value, FBMOD2.ICON.GetSize());
    if(FBMOD2.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FBMOD2.MICO.value, FBMOD2.MICO.GetSize());
    if(FBMOD2.MODL.IsLoaded())
        {
        if(FBMOD2.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FBMOD2.MODL->MODL.value, FBMOD2.MODL->MODL.GetSize());
        if(FBMOD2.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FBMOD2.MODL->MODB.value, FBMOD2.MODL->MODB.GetSize());
        if(FBMOD2.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FBMOD2.MODL->MODT.value, FBMOD2.MODL->MODT.GetSize());
        if(FBMOD2.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FBMOD2.MODL->Textures.GetSize());
            UINT32 cSize = FBMOD2.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FBMOD2.MODL->Textures.MODS.size(); ++p)
                {
                if(FBMOD2.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FBMOD2.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FBMOD2.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FBMOD2.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FBMOD2.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FBMOD2.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FBMOD2.MODL->MODD.value, FBMOD2.MODL->MODD.GetSize());
        }
    curINDX++;

    SaveHandler.writeSubRecord('XDNI', &curINDX, 4);
    if(FBMOD3.ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', FBMOD3.ICON.value, FBMOD3.ICON.GetSize());
    if(FBMOD3.MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', FBMOD3.MICO.value, FBMOD3.MICO.GetSize());
    if(FBMOD3.MODL.IsLoaded())
        {
        if(FBMOD3.MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', FBMOD3.MODL->MODL.value, FBMOD3.MODL->MODL.GetSize());
        if(FBMOD3.MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &FBMOD3.MODL->MODB.value, FBMOD3.MODL->MODB.GetSize());
        if(FBMOD3.MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', FBMOD3.MODL->MODT.value, FBMOD3.MODL->MODT.GetSize());
        if(FBMOD3.MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', FBMOD3.MODL->Textures.GetSize());
            UINT32 cSize = FBMOD3.MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < FBMOD3.MODL->Textures.MODS.size(); ++p)
                {
                if(FBMOD3.MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(FBMOD3.MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(FBMOD3.MODL->Textures.MODS[p]->name, cSize);
                    }
                SaveHandler.write(&FBMOD3.MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&FBMOD3.MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(FBMOD3.MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &FBMOD3.MODL->MODD.value, FBMOD3.MODL->MODD.GetSize());
        }

    if(HNAM.size())
        SaveHandler.writeSubRecord('MANH', &HNAM[0], (UINT32)HNAM.size() * sizeof(FORMID));
    else
        SaveHandler.writeSubRecordHeader('MANH', 0);

    if(ENAM.size())
        SaveHandler.writeSubRecord('MANE', &ENAM[0], (UINT32)ENAM.size() * sizeof(FORMID));
    else
        SaveHandler.writeSubRecordHeader('MANE', 0);

    SaveHandler.writeSubRecordHeader('MANM', 0);

    if(MaleFGGS.IsLoaded())
        SaveHandler.writeSubRecord('SGGF', MaleFGGS.value, MaleFGGS.GetSize());
    if(MaleFGGA.IsLoaded())
        SaveHandler.writeSubRecord('AGGF', MaleFGGA.value, MaleFGGA.GetSize());
    if(MaleFGTS.IsLoaded())
        SaveHandler.writeSubRecord('STGF', MaleFGTS.value, MaleFGTS.GetSize());
    if(MaleSNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', &MaleSNAM.value, MaleSNAM.GetSize());

    SaveHandler.writeSubRecordHeader('MANF', 0);

    if(FemaleFGGS.IsLoaded())
        SaveHandler.writeSubRecord('SGGF', FemaleFGGS.value, FemaleFGGS.GetSize());
    if(FemaleFGGA.IsLoaded())
        SaveHandler.writeSubRecord('AGGF', FemaleFGGA.value, FemaleFGGA.GetSize());
    if(FemaleFGTS.IsLoaded())
        SaveHandler.writeSubRecord('STGF', FemaleFGTS.value, FemaleFGTS.GetSize());
    if(FemaleSNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', &FemaleSNAM.value, FemaleSNAM.GetSize());

    return -1;
    }

bool RACERecord::operator ==(const RACERecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
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
        XNAM.size() == other.XNAM.size() &&
        HNAM.size() == other.HNAM.size() &&
        ENAM.size() == other.ENAM.size())
        {
        //Not sure if record order matters on relations, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < XNAM.size(); ++x)
            if(*XNAM[x] != *other.XNAM[x])
                return false;

        //Record order doesn't matter on hairs, so equality testing isn't easy
        //The proper solution would be to check each spell against every other spell to see if there's a one-to-one match
        //Perhaps using a disjoint set
        //Fix-up later
        for(UINT32 x = 0; x < HNAM.size(); ++x)
            if(HNAM[x] != other.HNAM[x])
                return false;

        //Record order doesn't matter on eyes, so equality testing isn't easy
        //The proper solution would be to check each spell against every other spell to see if there's a one-to-one match
        //Perhaps using a disjoint set
        //Fix-up later
        for(UINT32 x = 0; x < ENAM.size(); ++x)
            if(ENAM[x] != other.ENAM[x])
                return false;

        return true;
        }

    return false;
    }

bool RACERecord::operator !=(const RACERecord &other) const
    {
    return !(*this == other);
    }
}