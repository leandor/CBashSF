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
#include "GenericRecord.h"
#include "zlib/zlib.h"

FormIDOp::FormIDOp():
    count(0),
    stop(false)
    {
    //
    }

FormIDOp::~FormIDOp()
    {
    //
    }

UINT32 FormIDOp::GetCount()
    {
    return count;
    }

void FormIDOp::ResetCount()
    {
    count = 0;
    }

bool FormIDOp::Stop()
    {
    return stop;
    }

bool FormIDOp::GetResult()
    {
    return result;
    }

FormIDResolver::FormIDResolver(const UINT8 (&_ResolveTable)[256]):
    FormIDOp(),
    ResolveTable(_ResolveTable)
    {
    //
    }

FormIDResolver::~FormIDResolver()
    {
    //
    }

bool FormIDResolver::Accept(UINT32 &curFormID)
    {
    curFormID = (ResolveTable[curFormID >> 24] << 24 ) | (curFormID & 0x00FFFFFF);
    return stop;
    }

bool FormIDResolver::AcceptMGEF(UINT32 &curMgefCode)
    {
    curMgefCode = (ResolveTable[curMgefCode & 0x000000FF]) | (curMgefCode & 0xFFFFFF00);
    return stop;
    }

RecordOp::RecordOp():
    count(0),
    stop(false)
    {
    //
    }

RecordOp::~RecordOp()
    {
    //
    }

RecordReader::RecordReader(FormIDHandlerClass &_FormIDHandler):
    RecordOp(),
    expander(_FormIDHandler.ExpandTable)
    {
    //
    }

RecordReader::~RecordReader()
    {
    //
    }

bool RecordReader::Accept(Record **curRecord)
    {
    result = (*curRecord)->Read();
    if(result)
        {
        (*curRecord)->VisitFormIDs(expander);
        ++count;
        }
    return stop;
    }

UINT32 RecordOp::GetCount()
    {
    return count;
    }

void RecordOp::ResetCount()
    {
    count = 0;
    }

bool RecordOp::Stop()
    {
    return stop;
    }

bool RecordOp::GetResult()
    {
    return result;
    }

Record::Record(unsigned char *_recData):
    flags(0),
    formID(0),
    flagsUnk(0),
    recData(_recData)
    {
    //If a buffer is provided, the record isn't loaded
    // until the record is read
    //Otherwise, it's a new record and is considered loaded
    IsLoaded(_recData == NULL);
    }

Record::~Record()
    {
    //
    }

UINT32 Record::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    return UNKNOWN_FIELD;
    }

void * Record::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    return NULL;
    }

bool Record::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    return false;
    }

void Record::DeleteField(FIELD_IDENTIFIERS)
    {
    return;
    }

UINT32 Record::GetParentType()
    {
    return 0;
    }

bool Record::IsKeyedByEditorID()
    {
    return false;
    }

bool Record::HasSubRecords()
    {
    return false;
    }

bool Record::VisitSubRecords(const UINT32 &RecordType, RecordOp &op)
    {
    return false;
    }

bool Record::VisitFormIDs(FormIDOp &op)
    {
    return false;
    }

bool Record::Read()
    {
    if(IsLoaded() || IsChanged())
        return false;

    UINT32 recSize = GetSize();

    if (IsCompressed())
        {
        unsigned char localBuffer[BUFFERSIZE];
        unsigned char *buffer = NULL;
        UINT32 expandedRecSize = *(UINT32*)recData;
        if(expandedRecSize >= BUFFERSIZE)
            buffer = new unsigned char[expandedRecSize];
        else
            buffer = &localBuffer[0];
        uncompress(buffer, (uLongf*)&expandedRecSize, &recData[4], recSize - 4);
        ParseRecord(buffer, expandedRecSize);
        if(buffer != &localBuffer[0])
            delete [] buffer;
        }
    else
        ParseRecord(recData, recSize);

    IsLoaded(true);

    return true;
    }

UINT32 Record::Write(_FileHandler &SaveHandler, FormIDHandlerClass &FormIDHandler)
    {
    UINT32 recSize = 0;
    FormIDResolver expander(FormIDHandler.ExpandTable);
    if(!IsChanged())
        {
        if(FormIDHandler.MastersChanged())
            {
            //if masters have changed, all formIDs have to be updated...
            //so the record can't just be written as is.
            if(Read())
                VisitFormIDs(expander);
            }
        else
            {
            //if masters have not changed, the record can just be written from the read buffer
            recSize = GetSize();
            SaveHandler.write(recData - 20, recSize + 20);
            Unload();
            return recSize + 20;
            }
        }
    recSize = IsDeleted() ? 0 : GetSize(true);

    FormIDResolver collapser(FormIDHandler.CollapseTable);
    collapser.Accept(formID);
    VisitFormIDs(collapser);

    IsLoaded(false);
    UINT32 recType = GetType();
    SaveHandler.write(&recType, 4);
    SaveHandler.write(&recSize, 4);
    SaveHandler.write(&flags, 4);
    SaveHandler.write(&formID, 4);
    SaveHandler.write(&flagsUnk, 4);
    IsLoaded(true);

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
                printf("Not in cache, written improperly!\n  Size: %u\n", recSize);
                return recSize + 20;
                }
            SaveHandler.set_used((compSize + 4) - recSize);
            recSize = compSize + 4;
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
    return recSize + 20;
    }

bool Record::IsDeleted() const
    {
    return (flags & fIsDeleted) != 0;
    }

void Record::IsDeleted(bool value)
    {
    if(value)
        flags |= fIsDeleted;
    else
        flags &= ~fIsDeleted;
    }

bool Record::IsBorderRegion()
    {
    return (flags & fIsBorderRegion) != 0;
    }

void Record::IsBorderRegion(bool value)
    {
    if(value)
        flags |= fIsBorderRegion;
    else
        flags &= ~fIsBorderRegion;
    }

bool Record::IsTurnOffFire()
    {
    return (flags & fTurnOffFire) != 0;
    }

void Record::IsTurnOffFire(bool value)
    {
    if(value)
        flags |= fTurnOffFire;
    else
        flags &= ~fTurnOffFire;
    }

bool Record::IsCastsShadows()
    {
    return (flags & fCastsShadows) != 0;
    }

void Record::IsCastsShadows(bool value)
    {
    if(value)
        flags |= fCastsShadows;
    else
        flags &= ~fCastsShadows;
    }

bool Record::IsQuestOrPersistent()
    {
    return (flags & fIsQuestOrPersistent) != 0;
    }

void Record::IsQuestOrPersistent(bool value)
    {
    if(value)
        flags |= fIsQuestOrPersistent;
    else
        flags &= ~fIsQuestOrPersistent;
    }

bool Record::IsQuest()
    {
    return (flags & fIsQuestOrPersistent) != 0;
    }

void Record::IsQuest(bool value)
    {
    if(value)
        flags |= fIsQuestOrPersistent;
    else
        flags &= ~fIsQuestOrPersistent;
    }

bool Record::IsPersistent()
    {
    return (flags & fIsQuestOrPersistent) != 0;
    }

void Record::IsPersistent(bool value)
    {
    if(value)
        flags |= fIsQuestOrPersistent;
    else
        flags &= ~fIsQuestOrPersistent;
    }

bool Record::IsInitiallyDisabled()
    {
    return (flags & fIsInitiallyDisabled) != 0;
    }

void Record::IsInitiallyDisabled(bool value)
    {
    if(value)
        flags |= fIsInitiallyDisabled;
    else
        flags &= ~fIsInitiallyDisabled;
    }

bool Record::IsIgnored()
    {
    return (flags & fIsIgnored) != 0;
    }

void Record::IsIgnored(bool value)
    {
    if(value)
        flags |= fIsIgnored;
    else
        flags &= ~fIsIgnored;
    }

bool Record::IsVisibleWhenDistant()
    {
    return (flags & fIsVisibleWhenDistant) != 0;
    }

void Record::IsVisibleWhenDistant(bool value)
    {
    if(value)
        flags |= fIsVisibleWhenDistant;
    else
        flags &= ~fIsVisibleWhenDistant;
    }

bool Record::IsVWD()
    {
    return (flags & fIsVisibleWhenDistant) != 0;
    }

void Record::IsVWD(bool value)
    {
    if(value)
        flags |= fIsVisibleWhenDistant;
    else
        flags &= ~fIsVisibleWhenDistant;
    }

bool Record::IsTemporary()
    {
    return (flags & (fIsVisibleWhenDistant | fIsQuestOrPersistent)) != 0;
    }

void Record::IsTemporary(bool value)
    {
    if(value)
        {
        flags &= ~fIsVisibleWhenDistant;
        flags &= ~fIsQuestOrPersistent;
        }
    else
        flags |= fIsQuestOrPersistent;
    }

bool Record::IsDangerousOrOffLimits()
    {
    return (flags & fIsDangerousOrOffLimits) != 0;
    }

void Record::IsDangerousOrOffLimits(bool value)
    {
    if(value)
        flags |= fIsDangerousOrOffLimits;
    else
        flags &= ~fIsDangerousOrOffLimits;
    }

bool Record::IsDangerous()
    {
    return (flags & fIsDangerousOrOffLimits) != 0;
    }

void Record::IsDangerous(bool value)
    {
    if(value)
        flags |= fIsDangerousOrOffLimits;
    else
        flags &= ~fIsDangerousOrOffLimits;
    }

bool Record::IsOffLimits()
    {
    return (flags & fIsDangerousOrOffLimits) != 0;
    }

void Record::IsOffLimits(bool value)
    {
    if(value)
        flags |= fIsDangerousOrOffLimits;
    else
        flags &= ~fIsDangerousOrOffLimits;
    }

bool Record::IsCompressed()
    {
    return (flags & fIsCompressed) != 0;
    }

void Record::IsCompressed(bool value)
    {
    if(value)
        flags |= fIsCompressed;
    else
        flags &= ~fIsCompressed;
    }

bool Record::IsCantWait()
    {
    return (flags & fCantWait) != 0;
    }

void Record::IsCantWait(bool value)
    {
    if(value)
        flags |= fCantWait;
    else
        flags &= ~fCantWait;
    }

bool Record::IsHeaderFlagMask(UINT32 Mask, bool Exact)
    {
    if(Exact)
        return (flags & Mask) == Mask;
    else
        return (flags & Mask) != 0;
    }

void Record::SetHeaderFlagMask(UINT32 Mask)
    {
    bool loaded = IsLoaded();
    flags = Mask;
    IsLoaded(loaded);
    }

bool Record::IsHeaderUnknownFlagMask(UINT32 Mask, bool Exact)
    {
    if(Exact)
        return (flagsUnk & Mask) == Mask;
    else
        return (flagsUnk & Mask) != 0;
    }

void Record::SetHeaderUnknownFlagMask(UINT32 Mask)
    {
    bool loaded = IsLoaded();
    flagsUnk = Mask;
    IsLoaded(loaded);
    }

bool Record::IsLoaded()
    {
    return (flags & _fIsLoaded) != 0;
    }

void Record::IsLoaded(bool value)
    {
    if(value)
        flags |= _fIsLoaded;
    else
        flags &= ~_fIsLoaded;
    }

bool Record::IsChanged(bool value)
    {
    if(value)
        recData = NULL;
    return recData == NULL;
    }