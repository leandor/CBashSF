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
// FNVFile.cpp
#include "../Common.h"
#include "../GenericRecord.h"
#include "FNVFile.h"

FNVFile::FNVFile(STRING FileName, STRING ModName, const UINT32 _flags):
    ModFile(FileName, ModName, _flags)
    {
    //
    }

FNVFile::~FNVFile()
    {
    //
    }

SINT32 FNVFile::LoadTES4()
    {
    if(TES4.IsLoaded() || !Open())
        {
        if(!TES4.IsLoaded() && !Open())
            printf("FNVFile::LoadTES4: Error - Unable to load the TES4 record for mod \"%s\". The mod is not open for reading.\n", ReadHandler.getModName());
        return 0;
        }
    #ifdef CBASH_USE_LOGGING
        CLOGGER;
        BOOST_LOG_FUNCTION();
        BOOST_LOG_SEV(lg, trace) << "LoadTES4: " << FileName;
    #endif

    ReadHandler.set_used(4);
    UINT32 recSize = 0;
    ReadHandler.read(&recSize, 4);
    ReadHandler.read(&TES4.flags, 4);
    ReadHandler.read(&TES4.formID, 4);
    ReadHandler.read(&TES4.flagsUnk, 4);
    ReadHandler.read(&TES4.formVersion, 2);
    ReadHandler.read(&TES4.versionControl2[0], 2);
    if(TES4.IsLoaded())
        printf("_fIsLoaded Flag used!!!!: %08X\n", TES4.flags);

    //Normally would read the record with the read method
    //However, that requires recData to be set on the record
    // and that can only be set by the constructor
    //TES4 is constructed when the modfile is created
    // so the info isn't available then.
    //Must make sure this mimics the read method as needed
    TES4.ParseRecord(ReadHandler.getBuffer(24), recSize);
    TES4.IsLoaded(true);
    TES4.IsChanged(true);
    ReadHandler.set_used(recSize);
    return 1;
    }

SINT32 FNVFile::Load(RecordOp &indexer, std::vector<FormIDResolver *> &Expanders)
    {
    enum IgTopRecords {
        eIgGMST = 'TSMG' | 0x00001000, //Record::fIsIgnored
        eIgTXST = 'TSXT' | 0x00001000 
        };
    if(Flags.IsIgnoreExisting || !ReadHandler.IsOpen() || Flags.LoadedGRUPs)
        {
        if(!Flags.IsIgnoreExisting)
            {
            if(!ReadHandler.IsOpen())
                printf("FNVFile::Load: Error - Unable to load mod \"%s\". The mod is not open.\n", ReadHandler.getModName());
            else
                printf("FNVFile::Load: Error - Unable to load mod \"%s\". The mod is already loaded.\n", ReadHandler.getModName());
            }
        return 0;
        }

    Flags.LoadedGRUPs = true;
    UINT32 GRUPSize;
    UINT32 GRUPLabel;
    boost::unordered_set<UINT32> UsedFormIDs;

    RecordReader fullReader(FormIDHandler, Expanders);
    RecordOp skipReader;

    FNVRecordProcessor processor_min(ReadHandler, FormIDHandler, skipReader, Flags, UsedFormIDs);
    FNVRecordProcessor processor_full(ReadHandler, FormIDHandler, fullReader, Flags, UsedFormIDs);

    FNVRecordProcessor &processor = Flags.IsFullLoad ? processor_full : processor_min;

    while(!ReadHandler.eof()){
        ReadHandler.set_used(4); //Skip "GRUP"
        ReadHandler.read(&GRUPSize, 4);
        ReadHandler.read(&GRUPLabel, 4);
        ReadHandler.set_used(4); //Skip type (tops will all == 0)
        //printf("%c%c%c%c\n", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);
        switch(GRUPLabel)
            {
            case eIgGMST:
            case 'TSMG':
                ReadHandler.read(&GMST.stamp, 4);
                ReadHandler.read(&GMST.unknown, 4);
                GMST.Skim(ReadHandler, GRUPSize, processor_full, indexer);
                break;
            //case eIgTXST: //Same as normal
            case 'TSXT':
                ReadHandler.read(&TXST.stamp, 4);
                ReadHandler.read(&TXST.unknown, 4);
                TXST.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            //ADD DEFINITIONS HERE

            default:
                if(GRUPLabel == 0 && GRUPSize == 0)
                    {
                    printf("FNVFile::Skim: Warning - Unknown record group (%c%c%c%c) encountered in mod \"%s\". Bad file structure, zeros found past end of groups.\n", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ReadHandler.getModName());
                    return 1;
                    }
                //else
                //    printf("FNVFile::Skim: Error - Unknown record group (%c%c%c%c) encountered in mod \"%s\". ", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ReadHandler.getModName());

                if(GRUPSize == 0)
                    {
                    printf("Unable to continue loading.\n");
                    return 1;
                    }
                else
                    {
                    //printf("Attempting to skip and continue loading.\n");
                    ReadHandler.set_used(GRUPSize - 16); //Skip type (tops will all == 0)
                    }
                break;
            }
        };
    return 1;
    }

UINT32 FNVFile::GetNumRecords(const UINT32 &RecordType)
    {
    switch(RecordType)
        {
        case 'TSMG':
            return (UINT32)GMST.Records.size();
        case 'TSXT':
            return (UINT32)TXST.Records.size();
        default:
            printf("FNVFile::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". Unrecognized record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ReadHandler.getModName());
            break;
        }
    return 0;
    }

Record * FNVFile::CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options)
    {
    if(Flags.IsNoLoad)
        {
        printf("FNVFile::CreateRecord: Error - Unable to create any records in mod \"%s\". The mod is flagged not to be loaded.\n", ReadHandler.getModName());
        return NULL;
        }

    Record *newRecord = NULL;

    switch(RecordType)
        {
        case 'TSMG':
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printf("FNVFile::CreateRecord: Error - Unable to create GMST record in mod \"%s\". No valid editorID is available.\n", ReadHandler.getModName());
                return NULL;
                }

            GMST.Records.push_back(new FNV::GMSTRecord((FNV::GMSTRecord *)SourceRecord));
            newRecord = GMST.Records.back();

            if(RecordEditorID != NULL)
                {
                ((FNV::GMSTRecord *)newRecord)->EDID.Copy(RecordEditorID);
                ((FNV::GMSTRecord *)newRecord)->DATA.format = ((FNV::GMSTRecord *)newRecord)->EDID.value[0];
                }
            break;
        case 'TSXT':
            TXST.Records.push_back(new FNV::TXSTRecord((FNV::TXSTRecord *)SourceRecord));
            newRecord = TXST.Records.back();
            break;
        //case 'BOLG':
        //    GLOB.Records.push_back(new GLOBRecord((GLOBRecord *)SourceRecord));
        //    newRecord = GLOB.Records.back();
        //    break;

        default:
            printf("FNVFile::CreateRecord: Error - Unable to create (%c%c%c%c) record in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ReadHandler.getModName());
            break;
        }
    return newRecord;
    }

SINT32 FNVFile::CleanMasters(std::vector<FormIDResolver *> &Expanders)
    {
    if(Flags.IsNoLoad)
        {
        printf("FNVFile::CleanMasters: Error - Unable to clean masters in mod \"%s\". The mod is flagged not to be loaded.\n", ReadHandler.getModName());
        return -1;
        }

    UINT32 cleaned = 0;
    //FormIDHandlerClass TempHandler(FileName, TES4.MAST, TES4.HEDR.value.nextObject);
    //TempHandler.SetLoadOrder(FormIDHandler.LoadOrder255);
    //TempHandler.CreateFormIDLookup(FormIDHandler.ExpandedIndex);
    std::vector<UINT32> ToRemove;
    ToRemove.reserve(TES4.MAST.size());
    Record * topRecord = &TES4;

    for(UINT32 p = 0; p < (UINT8)TES4.MAST.size();++p)
        {
        RecordMasterChecker checker(FormIDHandler, Expanders, p);

        //printf("Checking: %s\n", TES4.MAST[p].value);
        if(checker.Accept(topRecord)) continue;
        if(GMST.VisitRecords(NULL, checker, false)) continue;
        if(TXST.VisitRecords(NULL, checker, false)) continue;

        //printf("ToRemove: %s\n", TES4.MAST[p].value);
        ToRemove.push_back(p);
        ++cleaned;
        }
    if(cleaned)
        {
        for(SINT32 p = (SINT32)ToRemove.size() - 1; p >= 0; --p)
            TES4.MAST.erase(TES4.MAST.begin() + ToRemove[p]);
        FormIDHandler.UpdateFormIDLookup();
        }
    return cleaned;
    }

SINT32 FNVFile::Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod)
    {
    if(!Flags.IsSaveable)
        {
        printf("FNVFile::Save: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", ReadHandler.getModName());
        return -1;
        }

    _FileHandler SaveHandler(SaveName, BUFFERSIZE);
    if(SaveHandler.open_ReadWrite() == -1)
        throw std::exception("Unable to open temporary file for writing\n");

    UINT32 formCount = 0;
    FormIDResolver expander(FormIDHandler.ExpandTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    FormIDResolver collapser(FormIDHandler.CollapseTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    //RecordReader reader(FormIDHandler);
    const bool bMastersChanged = FormIDHandler.MastersChanged();

    TES4.Write(SaveHandler, bMastersChanged, expander, collapser, Expanders);

    //ADD DEFINITIONS HERE
    formCount += GMST.WriteGRUP('TSMG', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TXST.WriteGRUP('TSXT', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    SaveHandler.writeAt(34, &formCount, 4);
    SaveHandler.close();
    if(CloseMod)
        Close();
    return 0;
    }

void FNVFile::VisitAllRecords(RecordOp &op)
    {
    if(Flags.IsNoLoad)
        {
        printf("FNVFile::VisitAllRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ReadHandler.getModName());
        return;
        }

    //This visits every record and subrecord
    Record * topRecord = &TES4;
    op.Accept(topRecord);
    GMST.VisitRecords(NULL, op, true);
    TXST.VisitRecords(NULL, op, true);

    return;
    }

void FNVFile::VisitRecords(const UINT32 &TopRecordType, const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
    {
    if(Flags.IsNoLoad)
        {
        printf("FNVFile::VisitRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ReadHandler.getModName());
        return;
        }

    //This visits only the top records specified.
    Record * topRecord = &TES4;
    switch(TopRecordType)
        {
        case '4SET':
            op.Accept(topRecord);
            break;
        case 'TSMG':
            GMST.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'TSXT':
            TXST.VisitRecords(RecordType, op, DeepVisit);
            break;

        default:
            printf("Error visiting records: %i\n", RecordType);
            break;
        }
    return;
    }