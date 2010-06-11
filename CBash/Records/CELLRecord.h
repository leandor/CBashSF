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
#include "ACHRRecord.h"
#include "ACRERecord.h"
#include "REFRRecord.h"
#include "PGRDRecord.h"
#include "LANDRecord.h"
#include "..\SubGRUPRecord.h"
#include <vector>

class CELLRecord : public Record
    {
    private:
        enum CELLRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,
            eDATA = 0x41544144,
            eXCLL = 0x4C4C4358,
            eXCMT = 0x544D4358,

            eXOWN = 0x4E574F58,
            eXRNK = 0x4B4E5258,
            eXGLB = 0x424C4758,

            eXCCM = 0x4D434358,
            eXCLW = 0x574C4358,
            eXCLR = 0x524C4358,
            eXCLC = 0x434C4358,
            eXCWT = 0x54574358
            };
        struct CELLXCLL
            {
            GENCLR ambient;
            GENCLR directional;
            GENCLR fog;
            float fogNear, fogFar;
            int directionalXY, directionalZ;
            float directionalFade, fogClip;
            CELLXCLL():fogNear(0), fogFar(0), directionalXY(0), directionalZ(0), directionalFade(1.0f), fogClip(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    ambient.Debug(debugLevel, indentation);
                    directional.Debug(debugLevel, indentation);
                    fog.Debug(debugLevel, indentation);
                    PrintIndent(indentation);
                    printf("fogNear         = %f\n", fogNear);
                    PrintIndent(indentation);
                    printf("fogFar          = %f\n", fogFar);
                    PrintIndent(indentation);
                    printf("directionalXY   = %i\n", directionalXY);
                    PrintIndent(indentation);
                    printf("directionalZ    = %i\n", directionalZ);
                    PrintIndent(indentation);
                    printf("directionalFade = %f\n", directionalFade);
                    PrintIndent(indentation);
                    printf("fogClip         = %f\n", fogClip);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct CELLXCLW
            {
            float waterHeight;
            CELLXCLW():waterHeight(-2147483648.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("waterHeight = %f\n", waterHeight);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct CELLXCLC
            {
            int posX, posY;
            CELLXCLC():posX(0), posY(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("posX = %i\n", posX);
                    PrintIndent(indentation);
                    printf("posY = %i\n", posY);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        enum flagsFlags
            {
            fIsInterior         = 0x00000001,
            fHasWater           = 0x00000002,
            fInvertFastTravel   = 0x00000004,
            fForceHideLand      = 0x00000008,
            fPublicPlace        = 0x00000020,
            fHandChanged        = 0x00000040,
            fBehaveLikeExterior = 0x00000080
            };
        enum eXCMTType
            {
            eDefault,
            ePublic,
            eDungeon
            };
        STRING EDID;
        STRING FULL;
        ReqRecordField<GENFLAG> DATA;
        OptRecordField<CELLXCLL> XCLL;
        RecordField<GENFLAG> XCMT;
        OptRecordField<GENXOWN> Ownership;
        RecordField<GENFID> XCCM;
        RecordField<CELLXCLW> XCLW;
        std::vector<unsigned int> XCLR;
        RecordField<CELLXCLC> XCLC;
        RecordField<GENFID> XCWT;
        std::vector<ACHRRecord *> ACHR;
        std::vector<ACRERecord *> ACRE;
        std::vector<REFRRecord *> REFR;
        PGRDRecord *PGRD;
        LANDRecord *LAND;
        CELLRecord(bool newRecord=false):Record(newRecord), PGRD(NULL), LAND(NULL) {}
        CELLRecord(const unsigned int &newFormID):Record(newFormID), PGRD(NULL), LAND(NULL) {}
        CELLRecord(CELLRecord *srcRecord):Record(true), PGRD(NULL), LAND(NULL)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            DATA = srcRecord->DATA;
            XCLL = srcRecord->XCLL;
            XCMT = srcRecord->XCMT;
            if(srcRecord->Ownership.IsLoaded())
                {
                Ownership.Load();
                Ownership->XOWN = srcRecord->Ownership->XOWN;
                Ownership->XRNK = srcRecord->Ownership->XRNK;
                Ownership->XGLB = srcRecord->Ownership->XGLB;
                }
            XCCM = srcRecord->XCCM;
            XCLW = srcRecord->XCLW;
            XCLR = srcRecord->XCLR;
            XCLC = srcRecord->XCLC;
            XCWT = srcRecord->XCWT;
            return;
            }
        ~CELLRecord()
            {
            for(unsigned int x = 0; x < ACHR.size(); ++x)
                delete ACHR[x];
            for(unsigned int x = 0; x < ACRE.size(); ++x)
                delete ACRE[x];
            for(unsigned int x = 0; x < REFR.size(); ++x)
                delete REFR[x];
            delete PGRD;
            delete LAND;
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            DATA.Unload();
            XCLL.Unload();
            XCMT.Unload();
            Ownership.Unload();
            XCCM.Unload();
            XCLW.Unload();
            XCLR.clear();
            XCLC.Unload();
            XCWT.Unload();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            if(Ownership.IsLoaded())
                {
                if(Ownership->XOWN.IsLoaded())
                    FormIDs.push_back(&Ownership->XOWN.value.fid);
                if(Ownership->XGLB.IsLoaded())
                    FormIDs.push_back(&Ownership->XGLB->fid);
                }
            FormIDs.push_back(&XCCM.value.fid);
            for(unsigned int x = 0; x < XCLR.size(); x++)
                FormIDs.push_back(&XCLR[x]);
            FormIDs.push_back(&XCWT.value.fid);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eCELL;}
        char * GetStrType() {return "CELL";}
        int WriteRecord(_FileHandler &SaveHandler);

        bool IsInterior()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fIsInterior) != 0;
            }
        void IsInterior(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fIsInterior;
            else
                DATA.value.flags &= ~fIsInterior;
            }
        bool IsHasWater()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fHasWater) != 0;
            }
        void IsHasWater(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fHasWater;
            else
                DATA.value.flags &= ~fHasWater;
            }
        bool IsInvertFastTravel()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fInvertFastTravel) != 0;
            }
        void IsInvertFastTravel(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fInvertFastTravel;
            else
                DATA.value.flags &= ~fInvertFastTravel;
            }
        bool IsForceHideLand()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fForceHideLand) != 0;
            }
        void IsForceHideLand(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fForceHideLand;
            else
                DATA.value.flags &= ~fForceHideLand;
            }
        bool IsPublicPlace()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fPublicPlace) != 0;
            }
        void IsPublicPlace(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fPublicPlace;
            else
                DATA.value.flags &= ~fPublicPlace;
            }
        bool IsHandChanged()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fHandChanged) != 0;
            }
        void IsHandChanged(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fHandChanged;
            else
                DATA.value.flags &= ~fHandChanged;
            }
        bool IsBehaveLikeExterior()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fBehaveLikeExterior) != 0;
            }
        void IsBehaveLikeExterior(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fBehaveLikeExterior;
            else
                DATA.value.flags &= ~fBehaveLikeExterior;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(!DATA.IsLoaded()) return false;
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            if(!DATA.IsLoaded()) return;
            DATA.value.flags = Mask;
            }
        bool IsDefaultMusic()
            {
            if(!XCMT.IsLoaded()) return false;
            return (XCMT.value.flags == eDefault);
            }
        void IsDefaultMusic(bool value)
            {
            if(!XCMT.IsLoaded()) return;
            if(value)
                XCMT.value.flags = eDefault;
            else if(IsDefaultMusic())
                XCMT.value.flags = ePublic;
            }
        bool IsPublicMusic()
            {
            if(!XCMT.IsLoaded()) return false;
            return (XCMT.value.flags == ePublic);
            }
        void IsPublicMusic(bool value)
            {
            if(!XCMT.IsLoaded()) return;
            if(value)
                XCMT.value.flags = ePublic;
            else if(IsPublicMusic())
                XCMT.value.flags = eDefault;
            }
        bool IsDungeonMusic()
            {
            if(!XCMT.IsLoaded()) return false;
            return (XCMT.value.flags == eDungeon);
            }
        void IsDungeonMusic(bool value)
            {
            if(!XCMT.IsLoaded()) return;
            if(value)
                XCMT.value.flags = eDungeon;
            else if(IsDungeonMusic())
                XCMT.value.flags = eDefault;
            }
        bool IsMusicType(unsigned int Type)
            {
            if(!XCMT.IsLoaded()) return false;
            return (XCMT.value.flags == Type);
            }
        void SetMusicType(unsigned int Type)
            {
            if(!XCMT.IsLoaded()) return;
            XCMT.value.flags = Type;
            }
    };
