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
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class NAVIRecord : public FNVRecord //Navigation Mesh Info Map
    {
    private:
        //This subrecord uses a very non-standard format
        //The details of unknown2 seem to vary widely based on the contents of unknown1
        //Normally, it would be expected for unknown2 to be a separate chunk with varying sig's
        struct NAVINVMI
            {
            UINT8   unknown1[4];
            FORMID  mesh, location;
            SINT16  xGrid, yGrid;
            UINT8ARRAY unknown2;
            UINT32  unknown2Size;

            NAVINVMI();
            ~NAVINVMI();

            bool Read(unsigned char *&buffer, const UINT32 &subSize);
            void Write(FileWriter &writer);

            NAVINVMI& operator = (const NAVINVMI &rhs);
            bool operator ==(const NAVINVMI &other) const;
            bool operator !=(const NAVINVMI &other) const;
            };

        //This subrecord uses a very non-standard format
        //It combines a formid and several arrays of formids into a single chunk
        //Normally, it would be expected for the arrays to be in separate chunks
        struct NAVINVCI
            {
            FORMID  unknown1;
            std::vector<FORMID> unknown2;
            std::vector<FORMID> unknown3;
            std::vector<FORMID> doors;

            NAVINVCI();
            ~NAVINVCI();

            bool Read(unsigned char *&buffer, const UINT32 &subSize);
            void Write(FileWriter &writer);

            bool operator ==(const NAVINVCI &other) const;
            bool operator !=(const NAVINVCI &other) const;
            };

    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<UINT32> NVER; //Version
        UnorderedSparseArray<NAVINVMI *> NVMI; //Unknown
        UnorderedSparseArray<NAVINVCI *> NVCI; //Unknown

        NAVIRecord(unsigned char *_recData=NULL);
        NAVIRecord(NAVIRecord *srcRecord);
        ~NAVIRecord();

        bool   VisitFormIDs(FormIDOp &op);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const NAVIRecord &other) const;
        bool operator !=(const NAVIRecord &other) const;
        bool equals(Record *other);
    };
}