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
#include "Common.h"
#include "TES4Record.h"
#include "zlib/zlib.h"

TES4Record::TES4HEDR::TES4HEDR(FLOAT32 _version, UINT32 _numRecords, UINT32 _nextObject):
    version(_version),
    numRecords(_numRecords),
    nextObject(_nextObject)
    {
    //
    }

TES4Record::TES4HEDR::~TES4HEDR()
    {
    //
    }

bool TES4Record::TES4HEDR::operator ==(const TES4HEDR &other) const
    {
    return (AlmostEqual(version,other.version,2) &&
            numRecords == other.numRecords &&
            nextObject == other.nextObject);
    }

bool TES4Record::TES4HEDR::operator !=(const TES4HEDR &other) const
    {
    return !(*this == other);
    }

TES4Record::TES4Record(unsigned char *_recData):
    Record(_recData),
    formVersion(0)
    {
    memset(&versionControl2[0], 0x00, 2);
    }

TES4Record::TES4Record(TES4Record *srcRecord):
    Record()
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

    //EDID = srcRecord->EDID;
    HEDR = srcRecord->HEDR;
    OFST = srcRecord->OFST;
    DELE = srcRecord->DELE;
    CNAM = srcRecord->CNAM;
    SNAM = srcRecord->SNAM;
    MAST = srcRecord->MAST;
    ONAM = srcRecord->ONAM;
    SCRN = srcRecord->SCRN;
    return;
    }

TES4Record::~TES4Record()
    {
    //
    }

bool TES4Record::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < ONAM.size(); x++)
        op.Accept(ONAM[x]);

    return op.Stop();
    }

bool TES4Record::IsESM()
    {
    if(!IsLoaded()) return false;
    return (flags & fIsESM) != 0;
    }

void TES4Record::IsESM(bool value)
    {
    if(!IsLoaded()) return;
    flags = value ? (flags | fIsESM) : (flags & ~fIsESM);
    }

UINT32 TES4Record::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-16];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    switch(whichGame)
        {
        case eIsOblivion:
            if(HEDR.IsLoaded())
                TotSize += HEDR.GetSize() + 6;

            if(OFST.IsLoaded())
                {
                cSize = OFST.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }

            if(DELE.IsLoaded())
                {
                cSize = DELE.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }

            if(CNAM.IsLoaded())
                {
                cSize = CNAM.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }

            if(SNAM.IsLoaded())
                {
                cSize = SNAM.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }

            for(UINT32 p = 0; p < MAST.size(); p++)
                {
                cSize = MAST[p].GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 20;//accounts for associated DATA element, subTypes and sizes
                }
            break;
        case eIsFallout3:
            return 0;

        case eIsFalloutNewVegas:
            if(HEDR.IsLoaded())
                TotSize += HEDR.GetSize() + 6;

            if(OFST.IsLoaded())
                {
                cSize = OFST.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }

            if(DELE.IsLoaded())
                {
                cSize = DELE.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }

            if(CNAM.IsLoaded())
                {
                cSize = CNAM.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }

            if(SNAM.IsLoaded())
                {
                cSize = SNAM.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }

            for(UINT32 p = 0; p < MAST.size(); p++)
                {
                cSize = MAST[p].GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 20;//accounts for associated DATA element, subTypes and sizes
                }

            if(ONAM.size())
                TotSize += ONAM.size() * sizeof(FORMID) + 6;

            if(SCRN.IsLoaded())
                {
                cSize = SCRN.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            break;
        }

    return TotSize;
    }

UINT32 TES4Record::GetType()
    {
    return '4SET';
    }

STRING TES4Record::GetStrType()
    {
    return "TES4";
    }

SINT32 TES4Record::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    #ifdef CBASH_USE_LOGGING
        CLOGGER;
        BOOST_LOG_FUNCTION();
        BOOST_LOG_SEV(lg, trace) << "Parsing";
    #endif
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    StringRecord curMAST;
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
            case 'RDEH':
                HEDR.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'TSAM':
                curMAST.Read(buffer, subSize, curPos);
                MAST.push_back(curMAST);
                curMAST.Unload();
                break;
            case 'ATAD':
                curPos += subSize;
                break;
            case 'TSFO':
                OFST.Read(buffer, subSize, curPos);
                break;
            case 'ELED':
                DELE.Read(buffer, subSize, curPos);
                break;
            case 'MANO':
                if(subSize % sizeof(FORMID) == 0)
                    {
                    if(subSize == 0)
                        break;
                    ONAM.resize(subSize / sizeof(FORMID));
                    _readBuffer(&ONAM[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized ONAM size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case 'NRCS':
                SCRN.Read(buffer, subSize, curPos);
                break;
            default:
                #ifdef CBASH_USE_LOGGING
                    BOOST_LOG_SEV(lg, critical) << "TES4: Unknown subType = " << ((char *)&subType)[0] << ((char *)&subType)[1] << ((char *)&subType)[2] << ((char *)&subType)[3];
                    BOOST_LOG_SEV(lg, critical) << "      Size = " << subSize;
                    BOOST_LOG_SEV(lg, critical) << "      CurPos = " << curPos - 6;
                #else
                    //printf("FileName = %s\n", FileName);
                    printf("  TES4: %08X - Unknown subType = %04x\n", formID, subType);
                    printf("  Size = %i\n", subSize);
                    printf("  CurPos = %04x\n\n", curPos - 6);
                #endif
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 TES4Record::Unload()
    {
    //TES4 should never be unloaded, so do nothing
    return 1;
    }

SINT32 TES4Record::WriteRecord(_FileHandler &SaveHandler)
    {
    UINT8 DATA[8] = {0};
    switch(whichGame)
        {
        case eIsOblivion:
            SaveHandler.writeSubRecord('RDEH', &HEDR.value, sizeof(TES4HEDR));
            if(OFST.IsLoaded())
                SaveHandler.writeSubRecord('TSFO', OFST.value, OFST.GetSize());
            if(DELE.IsLoaded())
                SaveHandler.writeSubRecord('ELED', DELE.value, DELE.GetSize());
            if(CNAM.IsLoaded())
                SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());
            if(SNAM.IsLoaded())
                SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());
            for(UINT32 p = 0; p < MAST.size(); p++)
                {
                SaveHandler.writeSubRecord('TSAM', MAST[p].value, MAST[p].GetSize());
                SaveHandler.writeSubRecord('ATAD', &DATA[0], sizeof(DATA));
                }
            break;
        case eIsFallout3:
            printf("TES4Record::WriteRecord: Error - Unable to write TES4 record. Fallout 3 support not yet implemented.\n");
            return -1;
        case eIsFalloutNewVegas:
            SaveHandler.writeSubRecord('RDEH', &HEDR.value, sizeof(TES4HEDR));
            if(OFST.IsLoaded())
                SaveHandler.writeSubRecord('TSFO', OFST.value, OFST.GetSize());
            if(DELE.IsLoaded())
                SaveHandler.writeSubRecord('ELED', DELE.value, DELE.GetSize());
            if(CNAM.IsLoaded())
                SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());
            if(SNAM.IsLoaded())
                SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());
            for(UINT32 p = 0; p < MAST.size(); p++)
                {
                SaveHandler.writeSubRecord('TSAM', MAST[p].value, MAST[p].GetSize());
                SaveHandler.writeSubRecord('ATAD', &DATA[0], sizeof(DATA));
                }
            if(ONAM.size())
                SaveHandler.writeSubRecord('MANO', &ONAM[0], (UINT32)ONAM.size() * sizeof(FORMID));
            if(SCRN.IsLoaded())
                SaveHandler.writeSubRecord('NRCS', SCRN.value, SCRN.GetSize());
            break;
        }

    return -1;
    }

UINT32 TES4Record::Write(_FileHandler &SaveHandler, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders)
    {
    UINT32 recSize = 0;
    UINT32 recType = GetType();
    collapser.Accept(formID);

    if(!IsChanged())
        {
        if(bMastersChanged)
            {
            //if masters have changed, all formIDs have to be updated...
            //so the record can't just be written as is.
            if(Read())
                {
                SINT32 index = -1;
                for(UINT32 x = 0; x < Expanders.size(); ++x)
                    if(IsValid(*Expanders[x]))
                        {
                        index = x;
                        break;
                        }
                if(index == -1)
                    {
                    printf("Unable to find the correct expander!\n");
                    VisitFormIDs(expander);
                    }
                else
                    VisitFormIDs(*Expanders[index]);
                }
            }
        else
            {
            //if masters have not changed, the record can just be written from the read buffer
            recSize = GetSize();

            IsLoaded(false);
            SaveHandler.write(&recType, 4);
            SaveHandler.write(&recSize, 4);
            SaveHandler.write(&flags, 4);
            SaveHandler.write(&formID, 4);
            SaveHandler.write(&flagsUnk, 4);
            if(whichGame == eIsFalloutNewVegas)
                {
                SaveHandler.write(&formVersion, 2);
                SaveHandler.write(&versionControl2[0], 2);
                }
            IsLoaded(true);
            SaveHandler.write(recData, recSize);
            Unload();
            if(whichGame == eIsFalloutNewVegas)
                return recSize + 24;
            else
                return recSize + 20;
            }
        }
    recSize = IsDeleted() ? 0 : GetSize(true);

    IsLoaded(false);
    SaveHandler.write(&recType, 4);
    SaveHandler.write(&recSize, 4);
    SaveHandler.write(&flags, 4);
    SaveHandler.write(&formID, 4);
    SaveHandler.write(&flagsUnk, 4);
    if(whichGame == eIsFalloutNewVegas)
        {
        SaveHandler.write(&formVersion, 2);
        SaveHandler.write(&versionControl2[0], 2);
        }
    IsLoaded(true);

    VisitFormIDs(collapser);

    if(!IsDeleted())
        {
        //IsCompressed(true); //Test code
        if(IsCompressed())
            {
            //printf("Compressed: %08X\n", formID);
            UINT32 recStart = SaveHandler.tell();
            UINT32 compSize = compressBound(recSize);
            unsigned char *compBuffer = new unsigned char[compSize + 4];
            SaveHandler.reserveBuffer(compSize + 4);
            WriteRecord(SaveHandler);
            memcpy(compBuffer, &recSize, 4);
            if(SaveHandler.IsCached(recStart) && ((SaveHandler.UnusedCache() + recSize) >= compSize))
                compress2(compBuffer + 4, &compSize, SaveHandler.getBuffer(recStart), recSize, 6);
            else
                {
                SaveHandler.flush();
                printf("TES4Record::WriteRecord: Error - Compressed record (%08X) written incorrectly. Requested data not in cache, size: %u\n", formID, recSize);
                if(whichGame == eIsFalloutNewVegas)
                    return recSize + 24;
                else
                    return recSize + 20;
                }
            SaveHandler.set_used((compSize + 4) - recSize);
            recSize = compSize + 4;
            if(whichGame == eIsFalloutNewVegas)
                SaveHandler.writeAt(recStart - 20, &recSize, 4);
            else
                SaveHandler.writeAt(recStart - 16, &recSize, 4);

            SaveHandler.writeAt(recStart, compBuffer, recSize);
            delete []compBuffer;
            }
        else
            WriteRecord(SaveHandler);
        }
    expander.Accept(formID);
    if(IsChanged())
        VisitFormIDs(expander);
    else
        Unload();
    if(whichGame == eIsFalloutNewVegas)
        return recSize + 24;
    else
        return recSize + 20;
    }

bool TES4Record::operator ==(const TES4Record &other) const
    {
    if(OFST == other.OFST &&
        DELE == other.DELE &&
        CNAM.equals(other.CNAM) &&
        SNAM.equals(other.SNAM) &&
        formVersion == other.formVersion &&
        versionControl2[0] == other.versionControl2[0] &&
        versionControl2[1] == other.versionControl2[1] &&
        SCRN == other.SCRN &&
        MAST.size() == other.MAST.size() &&
        ONAM.size() == other.ONAM.size())
        {
        //Record order kinda sorta but doesn't really matter on masters, so equality testing is easy
        //The order determines the mod index of all formIDs in the mod file
        //If both records have the same masters in the same orders, the formIDs will have the same master indexing
        //If both records have the same masters in different orders, the formIDs will have different indexing but be logically equivalent
        //The ordering has no effect on load order in game or in the editor
        for(UINT32 x = 0; x < MAST.size(); ++x)
            if(!(MAST[x].equalsi(other.MAST[x])))
                return false;
        //Record order probably doesn't matter on overrides, so equality testing isn't easy
        //The proper solution would be to make a set of each vector and compare that instead
        //Fix-up later
        for(UINT32 x = 0; x < ONAM.size(); ++x)
            if(ONAM[x] != other.ONAM[x])
                return false;
        return true;
        }

    return false;
    }

bool TES4Record::operator !=(const TES4Record &other) const
    {
    return !(*this == other);
    }