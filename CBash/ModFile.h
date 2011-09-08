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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#pragma once
// ModFile.h
#include "Common.h"
#include "GenericRecord.h"
#include "TES4Record.h" //Is shared across all mod types

class Collection;

class ModFile
    {
    public:
        boost::iostreams::mapped_file_source file_map;

        STRING FileName;
        STRING ModName;

        unsigned char *buffer_start, *buffer_position, *buffer_end;

        FormIDHandlerClass FormIDHandler;
        ModFlags Flags;
        time_t ModTime;
        UINT32 ModID;

        Collection *Parent;

        TES4Record TES4;

        ModFile(Collection *_Parent, STRING FileName, STRING ModName, const UINT32 _flags);
        virtual ~ModFile();

        bool operator <(ModFile &other);
        bool operator >(ModFile &other);

        time_t mtime();
        bool   exists();

        bool   Open();
        bool   Close();

        virtual SINT32   LoadTES4() abstract {};
        virtual SINT32   Load(RecordOp &read_parser, RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords) abstract {};
        virtual UINT32   GetNumRecords(const UINT32 &RecordType) abstract {};
        virtual Record * CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options) abstract {};
        virtual SINT32   DeleteRecord(Record *&curRecord, RecordOp &deindexer) abstract {};
        virtual SINT32   Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod, RecordOp &indexer) abstract {};

        virtual void     VisitAllRecords(RecordOp &op) abstract {};
        virtual void     VisitRecords(const UINT32 &RecordType, RecordOp &op) abstract {};
    };

class FormIDMasterUpdater : public FormIDOp
    {
    private:
        FormIDHandlerClass &FormIDHandler;
        const UINT8 &ExpandedIndex;
        const UINT8 &CollapsedIndex;
        const UINT8 (&ExpandTable)[256];
        const UINT8 (&CollapseTable)[256];

    public:
        FormIDMasterUpdater(FormIDHandlerClass &_FormIDHandler);
        FormIDMasterUpdater(ModFile *ModID);
        FormIDMasterUpdater(Record *RecordID);
        ~FormIDMasterUpdater();

        bool Accept(UINT32 &curFormID);
        bool AcceptMGEF(UINT32 &curMgefCode);
    };