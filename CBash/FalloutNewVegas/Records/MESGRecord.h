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
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class MESGRecord : public FNVRecord //Message
    {
    private:
        struct MESGButton
            {
            StringRecord ITXT; //Text
            std::vector<ReqSubRecord<FNVCTDA> *> CTDA; //Conditions

            bool operator ==(const MESGButton &other) const;
            bool operator !=(const MESGButton &other) const;
            };

        enum flagsFlags
            {
            fIsMessageBox  = 0x00000001,
            fIsAutoDisplay = 0x00000002
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord DESC; //Description
        StringRecord FULL; //Name
        OptSimpleSubRecord<FORMID> INAM; //Icon
        //OptSubRecord<GENNAM> NAM0; //Unused (Empty)
        //OptSubRecord<GENNAM1> NAM1; //Unused (Empty)
        //OptSubRecord<GENNAM2> NAM2; //Unused (Empty)
        //OptSubRecord<GENNAM3> NAM3; //Unused (Empty)
        //OptSubRecord<GENNAM4> NAM4; //Unused (Empty)
        //OptSubRecord<GENNAM5> NAM5; //Unused (Empty)
        //OptSubRecord<GENNAM6> NAM6; //Unused (Empty)
        //OptSubRecord<GENNAM7> NAM7; //Unused (Empty)
        //OptSubRecord<GENNAM8> NAM8; //Unused (Empty)
        //OptSubRecord<GENNAM> NAM9; //Unused (Empty)
        OptSimpleSubRecord<UINT32> DNAM; //Flags
        OptSimpleSubRecord<UINT32> TNAM; //Display Time
        std::vector<MESGButton *> Buttons; //Menu Buttons

        MESGRecord(unsigned char *_recData=NULL);
        MESGRecord(MESGRecord *srcRecord);
        ~MESGRecord();

        bool   VisitFormIDs(FormIDOp &op);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        //UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const MESGRecord &other) const;
        bool operator !=(const MESGRecord &other) const;
    };
}