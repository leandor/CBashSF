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

RecordOp::RecordOp():
    count(0),
    stop(false),
    result(false)
    {
    //
    }

RecordOp::~RecordOp()
    {
    //
    }

bool RecordOp::Accept(Record *&curRecord)
    {
    return false;
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

RecordReader::RecordReader(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    expander(_FormIDHandler.ExpandTable, _FormIDHandler.FileStart, _FormIDHandler.FileEnd),
    Expanders(_Expanders)
    {
    //
    }

RecordReader::~RecordReader()
    {
    //
    }

bool RecordReader::Accept(Record *&curRecord)
    {
    result = curRecord->Read();
    if(result)
        {
        if(curRecord->IsValid(expander))
            curRecord->VisitFormIDs(expander);
        else
            {
            SINT32 index = -1;
            for(UINT32 x = 0; x < Expanders.size(); ++x)
                if(curRecord->IsValid(*Expanders[x]))
                    {
                    //if(index != -1)
                    //    printer("Multiple 'Correct' expanders found! Using last one found (likely incorrect unless lucky)\n");
                    index = x;
                    break;
                    }
            if(index == -1)
                {
                printer("Unable to find the correct expander!\n");
                curRecord->VisitFormIDs(expander);
                }
            else
                curRecord->VisitFormIDs(*Expanders[index]);
            }
        ++count;
        }
    return stop;
    }

RecordProcessor::RecordProcessor(FileReader &reader, FormIDHandlerClass &_FormIDHandler, RecordOp &parser, const ModFlags &_Flags, boost::unordered_set<UINT32> &_UsedFormIDs, std::vector<Record *> &DeletedRecords):
    reader(reader),
    FormIDHandler(_FormIDHandler),
    parser(parser),
    expander(_FormIDHandler.ExpandTable, _FormIDHandler.FileStart, _FormIDHandler.FileEnd),
    Flags(_Flags),
    UsedFormIDs(_UsedFormIDs),
    DeletedRecords(DeletedRecords),
    IsSkipNewRecords(_Flags.IsSkipNewRecords),
    IsTrackNewTypes(_Flags.IsTrackNewTypes),
    IsAddMasters(_Flags.IsAddMasters)
    {
    //
    }

RecordProcessor::~RecordProcessor()
    {
    //
    }

bool RecordProcessor::operator()(Record *&curRecord)
    {
    reader.read(&curRecord->flags, 4);
    reader.read(&curRecord->formID, 4);
    reader.read(&curRecord->flagsUnk, 4);
    expander.Accept(curRecord->formID);

    //Testing Messages
    //if(curRecord->IsLoaded())
    //    printer("_fIsLoaded Flag used!!!! %s - %08X\n", curRecord->GetStrType(), curRecord->formID);
    //if((curRecord->flags & 0x4000) != 0)
    //    printer("0x4000 used: %08X!!!!\n", curRecord->formID);

    curRecord->IsLoaded(false); //just incase the chosen flags were in use, clear them

    if(IsSkipNewRecords && FormIDHandler.IsNewRecord(curRecord->formID))
        {
        delete curRecord;
        return false;
        }

    //Make sure the formID is unique within the mod
    if(UsedFormIDs.insert(curRecord->formID).second == true)
        {
        parser.Accept(curRecord);
        if(curRecord->IsDeleted())
            DeletedRecords.push_back(curRecord);
        //Threads.schedule(boost::bind(&RecordReader::Accept, reader, (Record **)&curRecord));
        if(IsTrackNewTypes && !curRecord->IsKeyedByEditorID() && FormIDHandler.IsNewRecord(curRecord->formID))
            FormIDHandler.NewTypes.insert(curRecord->GetType());
        return true;
        }
    else
        {
        if(!IsAddMasters) //Can cause any new records to be given a duplicate ID
            printer("RecordProcessor: Warning - Information lost. Record skipped with duplicate formID: %08X\n", curRecord->formID);
        delete curRecord;
        return false;
        }
    return true;
    }

void RecordProcessor::IsEmpty(bool value)
    {
    FormIDHandler.IsEmpty = value;
    }

FNVRecordProcessor::FNVRecordProcessor(FileReader &reader, FormIDHandlerClass &_FormIDHandler, RecordOp &parser, const ModFlags &_Flags, boost::unordered_set<UINT32> &_UsedFormIDs, std::vector<Record *> &DeletedRecords):
    reader(reader),
    FormIDHandler(_FormIDHandler),
    parser(parser),
    expander(_FormIDHandler.ExpandTable, _FormIDHandler.FileStart, _FormIDHandler.FileEnd),
    Flags(_Flags),
    UsedFormIDs(_UsedFormIDs),
    DeletedRecords(DeletedRecords),
    IsSkipNewRecords(_Flags.IsSkipNewRecords),
    IsTrackNewTypes(_Flags.IsTrackNewTypes),
    IsAddMasters(_Flags.IsAddMasters)
    {
    //
    }

FNVRecordProcessor::~FNVRecordProcessor()
    {
    //
    }

bool FNVRecordProcessor::operator()(Record *&curRecord)
    {
    reader.read(&curRecord->flags, 4);
    reader.read(&curRecord->formID, 4);
    reader.read(&curRecord->flagsUnk, 4); //VersionControl1
    reader.read(&((FNVRecord *)curRecord)->formVersion, 2);
    reader.read(&((FNVRecord *)curRecord)->versionControl2[0], 2);
    expander.Accept(curRecord->formID);
    //printer("Read %08X\n", curRecord->formID);

    //Testing Messages
    if(curRecord->IsLoaded())
        printer("_fIsLoaded Flag used!!!! %s - %08X\n", curRecord->GetStrType(), curRecord->formID);
    //if((curRecord->flags & 0x4000) != 0)
    //    printer("0x4000 used: %08X!!!!\n", curRecord->formID);

    curRecord->IsLoaded(false); //just incase the chosen flags were in use, clear them

    if(IsSkipNewRecords && FormIDHandler.IsNewRecord(curRecord->formID))
        {
        delete curRecord;
        return false;
        }

    //Make sure the formID is unique within the mod
    if(UsedFormIDs.insert(curRecord->formID).second == true)
        {
        parser.Accept(curRecord);
        if(curRecord->IsDeleted())
            DeletedRecords.push_back(curRecord);
        //Threads.schedule(boost::bind(&RecordReader::Accept, reader, (Record **)&curRecord));
        if(IsTrackNewTypes && !curRecord->IsKeyedByEditorID() && FormIDHandler.IsNewRecord(curRecord->formID))
            FormIDHandler.NewTypes.insert(curRecord->GetType());
        return true;
        }
    else
        {
        if(!IsAddMasters) //Can cause any new records to be given a duplicate ID
            printer("FNVRecordProcessor: Warning - Information lost. Record skipped with duplicate formID: %08X\n", curRecord->formID);
        delete curRecord;
        return false;
        }
    return true;
    }

void FNVRecordProcessor::IsEmpty(bool value)
    {
    FormIDHandler.IsEmpty = value;
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

STRING Record::GetEditorIDKey()
    {
    return (STRING)GetField(4);
    }

bool Record::SetEditorIDKey(STRING EditorID)
    {
    SetField(4, 0, 0, 0, 0, 0, 0, (void *)EditorID, 0);
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
    UINT32 recSize = *(UINT32*)&recData[-16];

    //Check against the original record flags to see if it is compressed since the current flags may have changed
    if ((*(UINT32*)&recData[-12] & fIsCompressed) != 0)
        {
        unsigned char localBuffer[BUFFERSIZE];
        UINT32 expandedRecSize = *(UINT32*)recData;
        unsigned char *buffer = (expandedRecSize >= BUFFERSIZE) ? new unsigned char[expandedRecSize] : &localBuffer[0];
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

bool Record::IsValid(FormIDResolver &expander)
    {
    return (recData <= expander.FileEnd && recData >= expander.FileStart);
    }

UINT32 Record::Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders)
    {
    UINT32 recSize = 0;
    UINT32 recType = GetType();
    collapser.Accept(formID);
    UINT32 cleanFlags = 0;
    //IsLoaded is used by CBash internally and is not part of the file format but shares the flags field to save space.
    //So it has to be cleaned before being written.
    if(IsLoaded())
        {
        IsLoaded(false);
        cleanFlags = flags;
        IsLoaded(true);
        }
    else
        cleanFlags = flags;

    if(!IsChanged())
        {
        if(bMastersChanged || cleanFlags != *(UINT32*)&recData[-12])
            {
            //if masters have changed, all formIDs have to be updated...
            //or if the flags have changed internally (notably fIsDeleted or fIsCompressed, possibly others)
            if(Read())
                {
                //if(expander.IsValid(recData)) //optimization disabled for testing
                //    VisitFormIDs(expander);
                //printer("Looking for correct expander\n");
                SINT32 index = -1;
                for(UINT32 x = 0; x < Expanders.size(); ++x)
                    if(IsValid(*Expanders[x]))
                        {
                        //if(index != -1)
                        //    {
                        //    printer("Multiple 'Correct' expanders found (%08X)! Using last one found (likely incorrect unless lucky)\n", formID);
                        //    printer("  %i:   %08X, %08X, %08X\n", index, Expanders[index]->FileStart, recData, Expanders[index]->FileEnd);
                        //    printer("  %i:   %08X, %08X, %08X\n", x, Expanders[x]->FileStart, recData, Expanders[x]->FileEnd);
                        //    printer("Expanders:\n");
                        //    for(UINT32 z = 0; z < Expanders.size(); ++z)
                        //        printer("  %i of %i:   %08X, %08X\n", z, Expanders.size(), Expanders[z]->FileStart, Expanders[z]->FileEnd);
                        //    }
                        index = x;
                        break;
                        }
                if(index == -1)
                    {
                    printer("Unable to find the correct expander!\n");
                    VisitFormIDs(expander);
                    }
                else
                    VisitFormIDs(*Expanders[index]);
                }
            }
        else
            {
            //if masters have not changed, the record can just be written from the read buffer
            recSize = *(UINT32*)&recData[-16];

            writer.file_write(&recType, 4);
            writer.file_write(&recSize, 4);
            writer.file_write(&cleanFlags, 4);
            writer.file_write(&formID, 4);
            writer.file_write(&flagsUnk, 4);
            writer.file_write(recData, recSize);
            Unload();
            return recSize + 20;
            }
        }

    VisitFormIDs(collapser);

    if(!IsDeleted())
        {
        //IsCompressed(true); //Test code
        WriteRecord(writer);
        recSize = IsCompressed() ? writer.record_compress() : writer.record_size();
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&cleanFlags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        //if(IsCompressed())
        //    {
        //    printer("Compressed: %08X\n", formID);
        //    }
        writer.record_flush();
        }
    else
        {
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&cleanFlags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
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
    flags = value ? (flags | fIsDeleted) : (flags & ~fIsDeleted);
    }

bool Record::IsBorderRegion()
    {
    return (flags & fIsBorderRegion) != 0;
    }

void Record::IsBorderRegion(bool value)
    {
    flags = value ? (flags | fIsBorderRegion) : (flags & ~fIsBorderRegion);
    }

bool Record::IsTurnOffFire()
    {
    return (flags & fIsTurnOffFire) != 0;
    }

void Record::IsTurnOffFire(bool value)
    {
    flags = value ? (flags | fIsTurnOffFire) : (flags & ~fIsTurnOffFire);
    }

bool Record::IsCastsShadows()
    {
    return (flags & fIsCastsShadows) != 0;
    }

void Record::IsCastsShadows(bool value)
    {
    flags = value ? (flags | fIsCastsShadows) : (flags & ~fIsCastsShadows);
    }

bool Record::IsQuestOrPersistent()
    {
    return (flags & fIsQuestOrPersistent) != 0;
    }

void Record::IsQuestOrPersistent(bool value)
    {
    flags = value ? (flags | fIsQuestOrPersistent) : (flags & ~fIsQuestOrPersistent);
    }

bool Record::IsQuest()
    {
    return (flags & fIsQuestOrPersistent) != 0;
    }

void Record::IsQuest(bool value)
    {
    flags = value ? (flags | fIsQuestOrPersistent) : (flags & ~fIsQuestOrPersistent);
    }

bool Record::IsPersistent()
    {
    return (flags & fIsQuestOrPersistent) != 0;
    }

void Record::IsPersistent(bool value)
    {
    flags = value ? (flags | fIsQuestOrPersistent) : (flags & ~fIsQuestOrPersistent);
    }

bool Record::IsInitiallyDisabled()
    {
    return (flags & fIsInitiallyDisabled) != 0;
    }

void Record::IsInitiallyDisabled(bool value)
    {
    flags = value ? (flags | fIsInitiallyDisabled) : (flags & ~fIsInitiallyDisabled);
    }

bool Record::IsIgnored()
    {
    return (flags & fIsIgnored) != 0;
    }

void Record::IsIgnored(bool value)
    {
    flags = value ? (flags | fIsIgnored) : (flags & ~fIsIgnored);
    }

bool Record::IsVisibleWhenDistant()
    {
    return (flags & fIsVisibleWhenDistant) != 0;
    }

void Record::IsVisibleWhenDistant(bool value)
    {
    flags = value ? (flags | fIsVisibleWhenDistant) : (flags & ~fIsVisibleWhenDistant);
    }

bool Record::IsVWD()
    {
    return (flags & fIsVisibleWhenDistant) != 0;
    }

void Record::IsVWD(bool value)
    {
    flags = value ? (flags | fIsVisibleWhenDistant) : (flags & ~fIsVisibleWhenDistant);
    }

bool Record::IsTemporary()
    {
    return (flags & (fIsVisibleWhenDistant | fIsQuestOrPersistent)) != 0;
    }

void Record::IsTemporary(bool value)
    {
    flags = value ? (flags & ~(fIsVisibleWhenDistant | fIsQuestOrPersistent)) : (flags | fIsQuestOrPersistent);
    }

bool Record::IsDangerousOrOffLimits()
    {
    return (flags & fIsDangerousOrOffLimits) != 0;
    }

void Record::IsDangerousOrOffLimits(bool value)
    {
    flags = value ? (flags | fIsDangerousOrOffLimits) : (flags & ~fIsDangerousOrOffLimits);
    }

bool Record::IsDangerous()
    {
    return (flags & fIsDangerousOrOffLimits) != 0;
    }

void Record::IsDangerous(bool value)
    {
    flags = value ? (flags | fIsDangerousOrOffLimits) : (flags & ~fIsDangerousOrOffLimits);
    }

bool Record::IsOffLimits()
    {
    return (flags & fIsDangerousOrOffLimits) != 0;
    }

void Record::IsOffLimits(bool value)
    {
    flags = value ? (flags | fIsDangerousOrOffLimits) : (flags & ~fIsDangerousOrOffLimits);
    }

bool Record::IsCompressed()
    {
    return (flags & fIsCompressed) != 0;
    }

void Record::IsCompressed(bool value)
    {
    flags = value ? (flags | fIsCompressed) : (flags & ~fIsCompressed);
    }

bool Record::IsCantWait()
    {
    return (flags & fIsCantWait) != 0;
    }

void Record::IsCantWait(bool value)
    {
    flags = value ? (flags | fIsCantWait) : (flags & ~fIsCantWait);
    }

bool Record::IsHeaderFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? (flags & Mask) == Mask : (flags & Mask) != 0;
    }

void Record::SetHeaderFlagMask(UINT32 Mask)
    {
    bool loaded = IsLoaded();
    flags = Mask;
    IsLoaded(loaded);
    }

bool Record::IsHeaderUnknownFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? (flagsUnk & Mask) == Mask : (flagsUnk & Mask) != 0;
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
    flags = value ? (flags | _fIsLoaded) : (flags & ~_fIsLoaded);
    }

bool Record::IsChanged(bool value)
    {
    //IsChanged(false) currently doesn't do anything. For now, once changed, always changed.
    //However, IsChanged(false) is consistently used where appropriate.
    // So if this function is updated, it should just work.
    //  Ideally, it would set recData back to its original value
    //   but that would require either an extra variable (increasing space)
    //   or reparsing the modfile (increasing time)
    //  Neither tradeoff seems worth it at this point.
    if(value)
        recData = NULL;
    return recData == NULL;
    }

FNVRecord::FNVRecord(unsigned char *_recData):
    Record(_recData),
    formVersion(0)
    {
    memset(&versionControl2[0], 0x00, 2);
    }

FNVRecord::~FNVRecord()
    {
    //
    }

bool FNVRecord::Read()
    {
    if(IsLoaded() || IsChanged())
        return false;
    UINT32 recSize = *(UINT32*)&recData[-20];

    //Check against the original record flags to see if it is compressed since the current flags may have changed
    if ((*(UINT32*)&recData[-16] & fIsCompressed) != 0)
        {
        unsigned char localBuffer[BUFFERSIZE];
        UINT32 expandedRecSize = *(UINT32*)recData;
        unsigned char *buffer = (expandedRecSize >= BUFFERSIZE) ? new unsigned char[expandedRecSize] : &localBuffer[0];
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

UINT32 FNVRecord::Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders)
    {
    UINT32 recSize = 0;
    UINT32 recType = GetType();
    UINT32 cleanFlags = 0;
    //IsLoaded is used by CBash internally and is not part of the file format but shares the flags field to save space.
    //So it has to be cleaned before being written.
    if(IsLoaded())
        {
        IsLoaded(false);
        cleanFlags = flags;
        IsLoaded(true);
        }
    else
        cleanFlags = flags;

    collapser.Accept(formID);

    if(!IsChanged())
        {
        if(bMastersChanged || cleanFlags != *(UINT32*)&recData[-16])
            {
            //if masters have changed, all formIDs have to be updated...
            //or if the flags have changed internally (notably fIsDeleted or fIsCompressed, possibly others)
            //so the record can't just be written as is.
            if(Read())
                {
                //if(expander.IsValid(recData)) //optimization disabled for testing
                //    VisitFormIDs(expander);
                //printer("Looking for correct expander\n");
                SINT32 index = -1;
                for(UINT32 x = 0; x < Expanders.size(); ++x)
                    if(IsValid(*Expanders[x]))
                        {
                        //if(index != -1)
                        //    {
                        //    printer("Multiple 'Correct' expanders found (%08X)! Using last one found (likely incorrect unless lucky)\n", formID);
                        //    printer("  %i:   %08X, %08X, %08X\n", index, Expanders[index]->FileStart, recData, Expanders[index]->FileEnd);
                        //    printer("  %i:   %08X, %08X, %08X\n", x, Expanders[x]->FileStart, recData, Expanders[x]->FileEnd);
                        //    printer("Expanders:\n");
                        //    for(UINT32 z = 0; z < Expanders.size(); ++z)
                        //        printer("  %i of %i:   %08X, %08X\n", z, Expanders.size(), Expanders[z]->FileStart, Expanders[z]->FileEnd);
                        //    }
                        index = x;
                        break;
                        }
                if(index == -1)
                    {
                    printer("Unable to find the correct expander!\n");
                    VisitFormIDs(expander);
                    }
                else
                    VisitFormIDs(*Expanders[index]);
                }
            }
        else
            {
            //if masters have not changed, the record can just be written from the read buffer
            recSize = *(UINT32*)&recData[-20];

            writer.file_write(&recType, 4);
            writer.file_write(&recSize, 4);
            writer.file_write(&cleanFlags, 4);
            writer.file_write(&formID, 4);
            writer.file_write(&flagsUnk, 4);
            writer.file_write(&formVersion, 2);
            writer.file_write(&versionControl2[0], 2);
            writer.file_write(recData, recSize);
            Unload();
            return recSize + 24;
            }
        }

    VisitFormIDs(collapser);

    if(!IsDeleted())
        {
        //IsCompressed(true); //Test code
        WriteRecord(writer);
        recSize = IsCompressed() ? writer.record_compress() : writer.record_size();
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&cleanFlags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
        //if(IsCompressed())
        //    {
        //    printer("Compressed: %08X\n", formID);
        //    }
        writer.record_flush();
        }
    else
        {
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&cleanFlags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
        }

    expander.Accept(formID);
    if(IsChanged())
        VisitFormIDs(expander);
    else
        Unload();
    return recSize + 24;
    }