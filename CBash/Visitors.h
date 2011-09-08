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
// Visitors.h
#include "GenericRecord.h"
#include "ModFile.h"

class FormIDMatchCounter : public FormIDOp
    {
    private:
        const UINT32 &FormIDToMatch;

    public:
        FormIDMatchCounter(const UINT32 &_FormIDToMatch);
        ~FormIDMatchCounter();

        bool Accept(UINT32 &curFormID);
        bool AcceptMGEF(UINT32 &curMgefCode);
    };

class RecordUnloader : public RecordOp
    {
    public:
        RecordUnloader();
        ~RecordUnloader();

        bool Accept(Record *&curRecord);
    };

class RecordIDRetriever : public RecordOp
    {
    private:
        RECORDIDARRAY RecordIDs;

    public:
        RecordIDRetriever(RECORDIDARRAY _RecordIDs);
        ~RecordIDRetriever();

        bool Accept(Record *&curRecord);
    };

class FormIDSwapper : public FormIDOp
    {
    private:
        const UINT32 &FormIDToMatch;
        const UINT32 &FormIDToSwap;
        FormIDMasterUpdater checker;

    public:
        FormIDSwapper(const UINT32 &_FormIDToMatch, const UINT32 &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler);
        ~FormIDSwapper();

        bool Accept(UINT32 &curFormID);
        bool AcceptMGEF(UINT32 &curMgefCode);
    };

class RecordIndexer : public RecordOp
    {
    private:
        EditorID_Map &EditorID_ModFile_Record;
        FormID_Map &FormID_ModFile_Record;
        ModFile *curModFile;

    public:
        RecordIndexer(ModFile *_curModFile, EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map);
        RecordIndexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map);
        ~RecordIndexer();

        bool Accept(Record *&curRecord);

        void SetModFile(ModFile *_curModFile);
    };