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
#include <vector>

class ALCHRecord : public Record
    {
    private:
        enum ALCHSubRecords {
            eEDID = 0x44494445,
            eOBME = 0x454D424F,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eICON = 0x4E4F4349,
            eSCRI = 0x49524353,
            eDATA = 0x41544144,
            eENIT = 0x54494E45,

            eEFME = 0x454D4645,
            eEFID = 0x44494645,
            eEFIT = 0x54494645,
            eSCIT = 0x54494353,
            eEFII = 0x49494645,
            eEFIX = 0x58494645,
            eEFXX = 0x58584645,

            eDATX = 0x58544144
            };
    public:
        enum flagsFlags
            {
            fIsNoAutoCalc = 0x00000001,
            fIsFood       = 0x00000002
            };
        StringRecord EDID;
        StringRecord FULL;
        OptSubRecord<GENMODEL> MODL;
        StringRecord ICON;
        OptSubRecord<GENFID> SCRI;
        ReqSubRecord<GENWEIGHT> DATA;
        ReqSubRecord<GENENIT> ENIT;
        std::vector<GENEffect *> Effects;
        OptSubRecord<OBMEMAGIC> OBME;

        ALCHRecord(bool newRecord=false):Record(newRecord) {}
        ALCHRecord(ALCHRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eALCH)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            if(srcRecord->MODL.IsLoaded())
                {
                MODL.Load();
                MODL->MODB = srcRecord->MODL->MODB;
                MODL->MODL = srcRecord->MODL->MODL;
                MODL->MODT = srcRecord->MODL->MODT;
                }
            ICON = srcRecord->ICON;
            SCRI = srcRecord->SCRI;
            DATA = srcRecord->DATA;
            ENIT = srcRecord->ENIT;
            Effects.clear();
            Effects.resize(srcRecord->Effects.size());
            for(unsigned long x = 0; x < srcRecord->Effects.size(); x++)
                {
                Effects[x] = new GENEffect;
                Effects[x]->EFID = srcRecord->Effects[x]->EFID;
                Effects[x]->EFIT = srcRecord->Effects[x]->EFIT;
                Effects[x]->SCIT = srcRecord->Effects[x]->SCIT;
                Effects[x]->FULL = srcRecord->Effects[x]->FULL;
                if(srcRecord->Effects[x]->OBME.IsLoaded())
                    {
                    Effects[x]->OBME.Load();
                    Effects[x]->OBME->EFME = srcRecord->Effects[x]->OBME->EFME;
                    Effects[x]->OBME->EFII = srcRecord->Effects[x]->OBME->EFII;
                    Effects[x]->OBME->EFIX = srcRecord->Effects[x]->OBME->EFIX;
                    }
                }
            if(srcRecord->OBME.IsLoaded())
                {
                OBME.Load();
                OBME->OBME = srcRecord->OBME->OBME;
                OBME->DATX = srcRecord->OBME->DATX;
                }
            return;
            }
        ~ALCHRecord()
            {
            for(unsigned long x = 0; x < Effects.size(); x++)
                delete Effects[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.Unload();
            ICON.Unload();
            SCRI.Unload();
            DATA.Unload();
            ENIT.Unload();

            for(unsigned long x = 0; x < Effects.size(); x++)
                delete Effects[x];
            Effects.clear();
            OBME.Unload();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            if(SCRI.IsLoaded())
                op.Accept(SCRI->fid);
            for(unsigned long x = 0; x < Effects.size(); x++)
                {
                if(Effects[x]->OBME.IsLoaded())
                    {
                    if(Effects[x]->EFID.value.name >= 0x80000000)
                        op.AcceptMGEF(Effects[x]->EFID.value.name);
                    if(Effects[x]->EFIT.value.name >= 0x80000000)
                        op.AcceptMGEF(Effects[x]->EFIT.value.name);
                    switch(Effects[x]->OBME->EFME.value.efitParamInfo)
                        {
                        case 1: //It's a regular formID, so nothing fancy.
                            op.Accept(Effects[x]->EFIT.value.actorValue);
                            break;
                        case 2: //It's a mgefCode, and not a formID at all.
                            //Conditional resolution of mgefCode's based on JRoush's OBME mod
                            //It's resolved just like a formID, except it uses the lower byte instead of the upper
                            if(Effects[x]->EFIT.value.actorValue >= 0x80000000)
                                op.AcceptMGEF(Effects[x]->EFIT.value.actorValue);
                            break;
                        case 3: //It's an actor value, and not a formID at all.
                            //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                            //It's resolved just like a formID
                            if(Effects[x]->EFIT.value.actorValue >= 0x800)
                                op.Accept(Effects[x]->EFIT.value.actorValue);
                            break;
                        default: //It's not a formID, mgefCode, or fancied up actor value
                            //so do nothing
                            break;
                        }
                    if(Effects[x]->SCIT.IsLoaded())
                        {
                        if(Effects[x]->SCIT->visual >= 0x80000000)
                            op.AcceptMGEF(Effects[x]->SCIT->visual);
                        switch(Effects[x]->OBME->EFME.value.efixParamInfo)
                            {
                            case 1: //It's a regular formID, so nothing fancy.
                                op.Accept(Effects[x]->SCIT->script);
                                break;
                            case 2: //It's a mgefCode, and not a formID at all.
                                //Conditional resolution of mgefCode's based on JRoush's OBME mod
                                //It's resolved just like a formID, except it uses the lower byte instead of the upper
                                if(Effects[x]->SCIT->script >= 0x80000000)
                                    op.AcceptMGEF(Effects[x]->SCIT->script);
                                break;
                            case 3: //It's an actor value, and not a formID at all.
                                //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                                //It's resolved just like a formID
                                if(Effects[x]->SCIT->script >= 0x800)
                                    op.Accept(Effects[x]->SCIT->script);
                                break;
                            default: //It's not a formID, mgefCode, or fancied up actor value
                                //so do nothing
                                break;
                            }
                        }
                    if(Effects[x]->OBME->EFIX.IsLoaded())
                        if(Effects[x]->OBME->EFIX->resistAV >= 0x800)
                            op.Accept(Effects[x]->OBME->EFIX->resistAV);
                    }
                else
                    {
                    if(Effects[x]->SCIT.IsLoaded())
                        op.Accept(Effects[x]->SCIT->script);
                    }
                }

            return op.Stop();
            }

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long CreateListElement(const unsigned long subField);
        signed long DeleteListElement(const unsigned long subField);
        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        unsigned long GetFieldArraySize(const unsigned long Field);
        void GetFieldArray(const unsigned long Field, void **FieldValues);
        signed long GetListFieldType(const unsigned long subField, const unsigned long listField);
        unsigned long GetListSize(const unsigned long Field);
        unsigned long GetListArraySize(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void GetListArray(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues);
        void * GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void SetField(const unsigned long Field, char *FieldValue);
        void SetField(const unsigned long Field, float FieldValue);
        void SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize);
        void SetOtherField(const unsigned long Field, unsigned long FieldValue);
        void SetField(const unsigned long Field, signed long FieldValue);
        void SetField(const unsigned long Field, unsigned char FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, float FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char *FieldValue, unsigned long nSize);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, char *FieldValue);

        signed long DeleteField(const unsigned long Field);
        signed long DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eALCH;}
        char *GetStrType() {return "ALCH";}
        signed long WriteRecord(_FileHandler &SaveHandler);
        bool IsNoAutoCalc()
            {
            return (ENIT.value.flags & fIsNoAutoCalc) != 0;
            }
        void IsNoAutoCalc(bool value)
            {
            if(value)
                ENIT.value.flags |= fIsNoAutoCalc;
            else
                ENIT.value.flags &= ~fIsNoAutoCalc;
            }
        bool IsFood()
            {
            return (ENIT.value.flags & fIsFood) != 0;
            }
        void IsFood(bool value)
            {
            if(value)
                ENIT.value.flags |= fIsFood;
            else
                ENIT.value.flags &= ~fIsFood;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (ENIT.value.flags & Mask) == Mask;
            else
                return (ENIT.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            ENIT.value.flags = Mask;
            }
    };
