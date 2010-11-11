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
#include "..\Common.h"
#include "..\BaseRecord.h"

class ACHRRecord : public Record
    {
    private:
        enum ACHRSubrecords {
            eEDID = 0x44494445,
            eNAME = 0x454D414E,
            eXPCI = 0x49435058,
            eXLOD = 0x444F4C58,
            eFULL = 0x4C4C5546,
            eXESP = 0x50534558,
            eXMRC = 0x43524D58,
            eXHRS = 0x53524858,
            eXRGD = 0x44475258,
            eXSCL = 0x4C435358,
            eDATA = 0x41544144
            };
    public:
        enum flagsFlags
            {
            fIsOppositeParent = 0x00000001
            };
        STRING EDID;
        ReqSubRecord<GENFID> NAME;
        OptSubRecord<GENXPCI> XPCI;
        OptSubRecord<GENXLOD> XLOD;
        OptSubRecord<GENXESP> XESP;
        OptSubRecord<GENFID> XMRC;
        SubRecord<GENFID> XHRS;
        RAWBYTES XRGD;
        OptSubRecord<GENXSCL> XSCL;
        ReqSubRecord<GENPOSDATA> DATA;
        ACHRRecord(bool newRecord=false):Record(newRecord) {IsPersistent(true);}
        ACHRRecord(const unsigned int &newFormID):Record(newFormID) {IsPersistent(true);}
        ACHRRecord(ACHRRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            NAME = srcRecord->NAME;
            if(srcRecord->XPCI.IsLoaded())
                {
                XPCI.Load();
                XPCI->XPCI = srcRecord->XPCI->XPCI;
                XPCI->FULL = srcRecord->XPCI->FULL;
                }
            XLOD = srcRecord->XLOD;
            XESP = srcRecord->XESP;
            XMRC = srcRecord->XMRC;
            XHRS = srcRecord->XHRS;
            XRGD = srcRecord->XRGD;
            XSCL = srcRecord->XSCL;
            DATA = srcRecord->DATA;
            return;
            }
        ~ACHRRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            NAME.Unload();
            XPCI.Unload();
            XLOD.Unload();
            XESP.Unload();
            XMRC.Unload();
            XHRS.Unload();
            XRGD.Unload();
            XSCL.Unload();
            DATA.Unload();
            }

        void VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return;
            op.Accept(NAME.value.fid);
            if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
                op.Accept(XPCI->XPCI->fid);
            if(XESP.IsLoaded())
                op.Accept(XESP->parent);
            if(XMRC.IsLoaded())
                op.Accept(XMRC->fid);
            op.Accept(XHRS.value.fid);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(const unsigned int Field, char *FieldValue);
        void SetOtherField(const unsigned int Field, unsigned int FieldValue);
        void SetField(const unsigned int Field, float FieldValue);
        void SetField(const unsigned int Field, unsigned char FieldValue);
        void SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eACHR;}
        char * GetStrType() {return "ACHR";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsOppositeParent()
            {
            if(!XESP.IsLoaded()) return false;
            return (XESP->flags & fIsOppositeParent) != 0;
            }
        void IsOppositeParent(bool value)
            {
            if(!XESP.IsLoaded()) return;
            if(value)
                XESP->flags |= fIsOppositeParent;
            else
                XESP->flags &= ~fIsOppositeParent;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(!XESP.IsLoaded()) return false;
            if(Exact)
                return (XESP->flags & Mask) == Mask;
            else
                return (XESP->flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            if(!XESP.IsLoaded()) return;
            XESP->flags = Mask;
            }
    };
