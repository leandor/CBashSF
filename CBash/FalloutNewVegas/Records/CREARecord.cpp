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
#include "CREARecord.h"

namespace FNV
{
CREARecord::CREARecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CREARecord::CREARecord(CREARecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    SPLO = srcRecord->SPLO;
    EITM = srcRecord->EITM;
    EAMT = srcRecord->EAMT;
    NIFZ = srcRecord->NIFZ;
    NIFT = srcRecord->NIFT;
    ACBS = srcRecord->ACBS;
    SNAM = srcRecord->SNAM;
    INAM = srcRecord->INAM;
    VTCK = srcRecord->VTCK;
    TPLT = srcRecord->TPLT;
    if(srcRecord->DEST.IsLoaded())
        {
        DEST.Load();
        DEST->DEST = srcRecord->DEST->DEST;
        DEST->DSTD = srcRecord->DEST->DSTD;
        DEST->DMDL = srcRecord->DEST->DMDL;
        DEST->DMDT = srcRecord->DEST->DMDT;
        DEST->DSTF = srcRecord->DEST->DSTF;
        }
    SCRI = srcRecord->SCRI;
    CNTO = srcRecord->CNTO;
    AIDT = srcRecord->AIDT;
    PKID = srcRecord->PKID;
    KFFZ = srcRecord->KFFZ;
    DATA = srcRecord->DATA;
    RNAM = srcRecord->RNAM;
    ZNAM = srcRecord->ZNAM;
    PNAM = srcRecord->PNAM;
    TNAM = srcRecord->TNAM;
    BNAM = srcRecord->BNAM;
    WNAM = srcRecord->WNAM;
    NAM4 = srcRecord->NAM4;
    NAM5 = srcRecord->NAM5;
    CSCR = srcRecord->CSCR;
    if(srcRecord->CSDT.IsLoaded())
        {
        CSDT.Load();
        CSDT->CSDT = srcRecord->CSDT->CSDT;
        CSDT->CSDI = srcRecord->CSDT->CSDI;
        CSDT->CSDC = srcRecord->CSDT->CSDC;
        }
    CNAM = srcRecord->CNAM;
    LNAM = srcRecord->LNAM;
    return;
    }

CREARecord::~CREARecord()
    {
    //
    }

bool CREARecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    if(SPLO.IsLoaded())
        op.Accept(SPLO->value);
    if(EITM.IsLoaded())
        op.Accept(EITM->value);
    //if(SNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(SNAM->value);
    if(INAM.IsLoaded())
        op.Accept(INAM->value);
    if(VTCK.IsLoaded())
        op.Accept(VTCK->value);
    if(TPLT.IsLoaded())
        op.Accept(TPLT->value);
    if(DEST.IsLoaded() && DEST->DSTD.IsLoaded())
        op.Accept(DEST->DSTD->value);
    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    //if(CNTO.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CNTO->value);
    if(PKID.IsLoaded())
        op.Accept(PKID->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);
    if(PNAM.IsLoaded())
        op.Accept(PNAM->value);
    if(CSCR.IsLoaded())
        op.Accept(CSCR->value);
    if(CSDT.IsLoaded() && CSDT->CSDI.IsLoaded())
        op.Accept(CSDT->CSDI->value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM->value);
    if(LNAM.IsLoaded())
        op.Accept(LNAM->value);

    return op.Stop();
    }

UINT32 CREARecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-16];

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

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

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

    if(SPLO.IsLoaded())
        TotSize += SPLO.GetSize() + 6;

    if(EITM.IsLoaded())
        TotSize += EITM.GetSize() + 6;

    if(EAMT.IsLoaded())
        TotSize += EAMT.GetSize() + 6;

    if(NIFZ.IsLoaded())
        TotSize += NIFZ.GetSize() + 6;

    if(NIFT.IsLoaded())
        {
        cSize = NIFT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(ACBS.IsLoaded())
        TotSize += ACBS.GetSize() + 6;

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    if(INAM.IsLoaded())
        TotSize += INAM.GetSize() + 6;

    if(VTCK.IsLoaded())
        TotSize += VTCK.GetSize() + 6;

    if(TPLT.IsLoaded())
        TotSize += TPLT.GetSize() + 6;

    if(DEST.IsLoaded())
        {
        if(DEST->DEST.IsLoaded())
            TotSize += DEST->DEST.GetSize() + 6;
        if(DEST->DSTD.IsLoaded())
            TotSize += DEST->DSTD.GetSize() + 6;
        if(DEST->DMDL.IsLoaded())
            {
            cSize = DEST->DMDL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(DEST->DMDT.IsLoaded())
            {
            cSize = DEST->DMDT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(DEST->DSTF.IsLoaded())
            TotSize += DEST->DSTF.GetSize() + 6;
        }

    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;

    if(CNTO.IsLoaded())
        TotSize += CNTO.GetSize() + 6;

    if(AIDT.IsLoaded())
        TotSize += AIDT.GetSize() + 6;

    if(PKID.IsLoaded())
        TotSize += PKID.GetSize() + 6;

    if(KFFZ.IsLoaded())
        TotSize += KFFZ.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(RNAM.IsLoaded())
        TotSize += RNAM.GetSize() + 6;

    if(ZNAM.IsLoaded())
        TotSize += ZNAM.GetSize() + 6;

    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;

    if(TNAM.IsLoaded())
        TotSize += TNAM.GetSize() + 6;

    if(BNAM.IsLoaded())
        TotSize += BNAM.GetSize() + 6;

    if(WNAM.IsLoaded())
        TotSize += WNAM.GetSize() + 6;

    if(NAM4.IsLoaded())
        TotSize += NAM4.GetSize() + 6;

    if(NAM5.IsLoaded())
        TotSize += NAM5.GetSize() + 6;

    if(CSCR.IsLoaded())
        TotSize += CSCR.GetSize() + 6;

    if(CSDT.IsLoaded())
        {
        if(CSDT->CSDT.IsLoaded())
            TotSize += CSDT->CSDT.GetSize() + 6;
        if(CSDT->CSDI.IsLoaded())
            TotSize += CSDT->CSDI.GetSize() + 6;
        if(CSDT->CSDC.IsLoaded())
            TotSize += CSDT->CSDC.GetSize() + 6;
        }

    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;

    if(LNAM.IsLoaded())
        TotSize += LNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 CREARecord::GetType()
    {
    return 'AERC';
    }

STRING CREARecord::GetStrType()
    {
    return "CREA";
    }

SINT32 CREARecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
                MODL->MODS.Read(buffer, subSize, curPos);
                break;
            case 'DDOM':
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case 'OLPS':
                SPLO.Read(buffer, subSize, curPos);
                break;
            case 'MTIE':
                EITM.Read(buffer, subSize, curPos);
                break;
            case 'TMAE':
                EAMT.Read(buffer, subSize, curPos);
                break;
            case 'ZFIN':
                NIFZ.Read(buffer, subSize, curPos);
                break;
            case 'TFIN':
                NIFT.Read(buffer, subSize, curPos);
                break;
            case 'SBCA':
                ACBS.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            case 'KCTV':
                VTCK.Read(buffer, subSize, curPos);
                break;
            case 'TLPT':
                TPLT.Read(buffer, subSize, curPos);
                break;
            case 'TSED':
                DEST.Load();
                DEST->DEST.Read(buffer, subSize, curPos);
                break;
            case 'DTSD':
                DEST.Load();
                DEST->DSTD.Read(buffer, subSize, curPos);
                break;
            case 'LDMD':
                DEST.Load();
                DEST->DMDL.Read(buffer, subSize, curPos);
                break;
            case 'TDMD':
                DEST.Load();
                DEST->DMDT.Read(buffer, subSize, curPos);
                break;
            case 'FTSD':
                //DEST.Load();
                //DEST->DSTF.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'OTNC':
                CNTO.Read(buffer, subSize, curPos);
                break;
            case 'TDIA':
                AIDT.Read(buffer, subSize, curPos);
                break;
            case 'DIKP':
                PKID.Read(buffer, subSize, curPos);
                break;
            case 'ZFFK':
                KFFZ.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANB':
                BNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANW':
                WNAM.Read(buffer, subSize, curPos);
                break;
            case '4MAN':
                NAM4.Read(buffer, subSize, curPos);
                break;
            case '5MAN':
                NAM5.Read(buffer, subSize, curPos);
                break;
            case 'RCSC':
                CSCR.Read(buffer, subSize, curPos);
                break;
            case 'TDSC':
                CSDT.Load();
                CSDT->CSDT.Read(buffer, subSize, curPos);
                break;
            case 'IDSC':
                CSDT.Load();
                CSDT->CSDI.Read(buffer, subSize, curPos);
                break;
            case 'CDSC':
                CSDT.Load();
                CSDT->CSDC.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANL':
                LNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CREA: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CREARecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SPLO.Unload();
    EITM.Unload();
    EAMT.Unload();
    NIFZ.Unload();
    NIFT.Unload();
    ACBS.Unload();
    SNAM.Unload();
    INAM.Unload();
    VTCK.Unload();
    TPLT.Unload();
    DEST.Unload();
    SCRI.Unload();
    CNTO.Unload();
    AIDT.Unload();
    PKID.Unload();
    KFFZ.Unload();
    DATA.Unload();
    RNAM.Unload();
    ZNAM.Unload();
    PNAM.Unload();
    TNAM.Unload();
    BNAM.Unload();
    WNAM.Unload();
    NAM4.Unload();
    NAM5.Unload();
    CSCR.Unload();
    CSDT.Unload();
    CNAM.Unload();
    LNAM.Unload();
    return 1;
    }

SINT32 CREARecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

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

    if(SPLO.IsLoaded())
        SaveHandler.writeSubRecord('OLPS', SPLO.value, SPLO.GetSize());

    if(EITM.IsLoaded())
        SaveHandler.writeSubRecord('MTIE', EITM.value, EITM.GetSize());

    if(EAMT.IsLoaded())
        SaveHandler.writeSubRecord('TMAE', EAMT.value, EAMT.GetSize());

    if(NIFZ.IsLoaded())
        SaveHandler.writeSubRecord('ZFIN', NIFZ.value, NIFZ.GetSize());

    if(NIFT.IsLoaded())
        SaveHandler.writeSubRecord('TFIN', NIFT.value, NIFT.GetSize());

    if(ACBS.IsLoaded())
        SaveHandler.writeSubRecord('SBCA', ACBS.value, ACBS.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(INAM.IsLoaded())
        SaveHandler.writeSubRecord('MANI', INAM.value, INAM.GetSize());

    if(VTCK.IsLoaded())
        SaveHandler.writeSubRecord('KCTV', VTCK.value, VTCK.GetSize());

    if(TPLT.IsLoaded())
        SaveHandler.writeSubRecord('TLPT', TPLT.value, TPLT.GetSize());

    if(DEST.IsLoaded())
        {
        if(DEST->DEST.IsLoaded())
            SaveHandler.writeSubRecord('TSED', DEST->DEST.value, DEST->DEST.GetSize());

        if(DEST->DSTD.IsLoaded())
            SaveHandler.writeSubRecord('DTSD', DEST->DSTD.value, DEST->DSTD.GetSize());

        if(DEST->DMDL.IsLoaded())
            SaveHandler.writeSubRecord('LDMD', DEST->DMDL.value, DEST->DMDL.GetSize());

        if(DEST->DMDT.IsLoaded())
            SaveHandler.writeSubRecord('TDMD', DEST->DMDT.value, DEST->DMDT.GetSize());

        //if(DEST->DSTF.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('FTSD', DEST->DSTF.value, DEST->DSTF.GetSize());

        }

    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord('IRCS', SCRI.value, SCRI.GetSize());

    if(CNTO.IsLoaded())
        SaveHandler.writeSubRecord('OTNC', CNTO.value, CNTO.GetSize());

    if(AIDT.IsLoaded())
        SaveHandler.writeSubRecord('TDIA', AIDT.value, AIDT.GetSize());

    if(PKID.IsLoaded())
        SaveHandler.writeSubRecord('DIKP', PKID.value, PKID.GetSize());

    if(KFFZ.IsLoaded())
        SaveHandler.writeSubRecord('ZFFK', KFFZ.value, KFFZ.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANR', RNAM.value, RNAM.GetSize());

    if(ZNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANZ', ZNAM.value, ZNAM.GetSize());

    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANP', PNAM.value, PNAM.GetSize());

    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANT', TNAM.value, TNAM.GetSize());

    if(BNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANB', BNAM.value, BNAM.GetSize());

    if(WNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANW', WNAM.value, WNAM.GetSize());

    if(NAM4.IsLoaded())
        SaveHandler.writeSubRecord('4MAN', NAM4.value, NAM4.GetSize());

    if(NAM5.IsLoaded())
        SaveHandler.writeSubRecord('5MAN', NAM5.value, NAM5.GetSize());

    if(CSCR.IsLoaded())
        SaveHandler.writeSubRecord('RCSC', CSCR.value, CSCR.GetSize());

    if(CSDT.IsLoaded())
        {
        if(CSDT->CSDT.IsLoaded())
            SaveHandler.writeSubRecord('TDSC', CSDT->CSDT.value, CSDT->CSDT.GetSize());

        if(CSDT->CSDI.IsLoaded())
            SaveHandler.writeSubRecord('IDSC', CSDT->CSDI.value, CSDT->CSDI.GetSize());

        if(CSDT->CSDC.IsLoaded())
            SaveHandler.writeSubRecord('CDSC', CSDT->CSDC.value, CSDT->CSDC.GetSize());

        }

    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());

    if(LNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANL', LNAM.value, LNAM.GetSize());

    return -1;
    }

bool CREARecord::operator ==(const CREARecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            SPLO == other.SPLO &&
            EITM == other.EITM &&
            EAMT == other.EAMT &&
            NIFZ == other.NIFZ &&
            NIFT == other.NIFT &&
            ACBS == other.ACBS &&
            SNAM == other.SNAM &&
            INAM == other.INAM &&
            VTCK == other.VTCK &&
            TPLT == other.TPLT &&
            DEST == other.DEST &&
            SCRI == other.SCRI &&
            CNTO == other.CNTO &&
            AIDT == other.AIDT &&
            PKID == other.PKID &&
            KFFZ == other.KFFZ &&
            DATA == other.DATA &&
            RNAM == other.RNAM &&
            ZNAM == other.ZNAM &&
            PNAM == other.PNAM &&
            TNAM == other.TNAM &&
            BNAM == other.BNAM &&
            WNAM == other.WNAM &&
            NAM4 == other.NAM4 &&
            NAM5 == other.NAM5 &&
            CSCR == other.CSCR &&
            CSDT == other.CSDT &&
            CNAM == other.CNAM &&
            LNAM == other.LNAM);
    }

bool CREARecord::operator !=(const CREARecord &other) const
    {
    return !(*this == other);
    }
}