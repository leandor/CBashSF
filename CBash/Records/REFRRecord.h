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

class REFRRecord : public Record
    {
    private:
        enum REFRSubrecords {
            eEDID = 0x44494445,
            eNAME = 0x454D414E,
            eXTEL = 0x4C455458,
            eXLOC = 0x434F4C58,

            eXOWN = 0x4E574F58,
            eXRNK = 0x4B4E5258,
            eXGLB = 0x424C4758,

            eXESP = 0x50534558,
            eXTRG = 0x47525458,
            eXSED = 0x44455358,
            eXLOD = 0x444F4C58,

            eXCHG = 0x47484358,
            eXHLT = 0x544C4858,

            eXPCI = 0x49435058,
            eFULL = 0x4C4C5546,

            eXLCM = 0x4D434C58,
            eXRTM = 0x4D545258,
            eXACT = 0x54434158,
            eXCNT = 0x544E4358,
            eXMRK = 0x4B524D58,
            eFNAM = 0x4D414E46,
            eTNAM = 0x4D414E54,
            eONAM = 0x4D414E4F,
            eXSCL = 0x4C435358,
            eXSOL = 0x4C4F5358,
            eDATA = 0x41544144
            };

        struct REFRXTEL
            {
            unsigned int destinationFid;
            GENPOSDATA destination;
            REFRXTEL():destinationFid(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("destinationFid = %s\n", PrintFormID(destinationFid));
                    indentation -= 2;
                    destination.Debug(debugLevel, indentation);
                    }
                }
            #endif
            };

        struct REFRXLOC
            {
            unsigned char level, unused1[3];
            unsigned int key;
            unsigned char unused2[4], flags, unused3[3];
            REFRXLOC():level(0), key(0), flags(0)
                {
                memset(&unused1, 0x00, 3);
                memset(&unused2, 0x00, 4);
                memset(&unused3, 0x00, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("level  = %c\n", level);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1 = %c%c%c\n", unused1[0], unused1[1], unused1[2]);
                        }
                    PrintIndent(indentation);
                    printf("key    = %s\n", PrintFormID(key));
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused2 = %c%c%c%c\n", unused2[0], unused2[1], unused2[2], unused2[3]);
                        }
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags   = %u\n", flags);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused3 = %c%c%c\n", unused3[0], unused3[1], unused3[2]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct REFRXSED
            {
            union
                {
                unsigned int seed;
                unsigned char offset;
                };
            bool isOffset;
            REFRXSED():seed(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                indentation += 2;
                PrintIndent(indentation);
                if(isOffset)
                    if(debugLevel > 3)
                        printf("offset = %u\n", offset);
                    else
                        printf("offset\n");
                else
                    if(debugLevel > 3)
                        printf("seed = %u\n", seed);
                    else
                        printf("seed\n");
                indentation -= 2;
                }
            #endif
            };

        struct REFRXCHG
            {
            float charge;
            REFRXCHG():charge(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("charge = %f\n", charge);
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct REFRXHLT
            {
            int health;
            REFRXHLT():health(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("health = %i\n", health);
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct REFRXLCM
            {
            int levelMod;
            REFRXLCM():levelMod(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("levelMod = %i\n", levelMod);
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct REFRXCNT
            {
            int count;
            REFRXCNT():count(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("count = %i\n", count);
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct REFRTNAM
            {
            unsigned char markerType, unused1;
            REFRTNAM():markerType(0), unused1(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("markerType = %u\n", markerType);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1    = %c\n", unused1);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct REFRMAPMARKER
            {
            ReqRecordField<GENFLAG> FNAM;
            STRING FULL;
            ReqRecordField<REFRTNAM> TNAM;
            #ifdef _DEBUG
            void Debug(char *name, int debugLevel, size_t &indentation)
                {
                if(name != NULL)
                    {
                    PrintIndent(indentation);
                    printf("%s\n", name);
                    }
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    XMRK.Debug("XMRK", debugLevel, indentation);
                    FNAM.Debug("FNAM", debugLevel, indentation);
                    FULL.Debug("FULL", debugLevel, indentation);
                    TNAM.Debug("TNAM", debugLevel, indentation);
                    indentation -= 2;
                    }
                }
            #endif
            };

    public:
        enum flagsFlags
            {
            fIsOppositeParent = 0x00000001
            };
        enum fnamFlags
            {
            fVisible     = 0x00000001,
            fCanTravelTo = 0x00000002
            };
        enum xactFlags
            {
            fUseDefault    = 0x00000001,
            fActivate      = 0x00000002,
            fOpen          = 0x00000004,
            fOpenByDefault = 0x00000008
            };
        enum xlocFlags
            {
            fLeveledLock = 0x00000004
            };
        enum markerTypeTypes
            {
            eMarkerNone      = 0x00000000,
            eCamp            = 0x00000001,
            eCave            = 0x00000002,
            eCity            = 0x00000003,
            eElvenRuin       = 0x00000004,
            eFortRuin        = 0x00000005,
            eMine            = 0x00000006,
            eLandmark        = 0x00000007,
            eTavern          = 0x00000008,
            eSettlement      = 0x00000009,
            eDaedricShrine   = 0x0000000A,
            eOblivionGate    = 0x0000000B,
            eUnknownDoorIcon = 0x0000000C
            };
        enum eSoulType
            {
            eNone    = 0,
            ePetty   = 1,
            eLesser  = 2,
            eCommon  = 3,
            eGreater = 4,
            eGrand   = 5
            };

        STRING EDID;
        ReqRecordField<GENFID> NAME;
        OptRecordField<REFRXTEL> XTEL;
        OptRecordField<REFRXLOC> XLOC;
        OptRecordField<GENXOWN> Ownership;
        OptRecordField<GENXESP> XESP;
        OptRecordField<GENFID> XTRG;
        OptRecordField<REFRXSED> XSED;
        OptRecordField<GENXLOD> XLOD;
        OptRecordField<REFRXCHG> XCHG;
        OptRecordField<REFRXHLT> XHLT;
        OptRecordField<GENXPCI> XPCI;
        OptRecordField<REFRXLCM> XLCM;
        OptRecordField<GENFID> XRTM;
        OptRecordField<GENUFLAG> XACT;
        OptRecordField<REFRXCNT> XCNT;
        OptRecordField<REFRMAPMARKER> Marker;
        //bool ONAM; //Open by Default, empty marker, written whenever fOpenByDefault is true
        OptRecordField<GENXSCL> XSCL;
        OptRecordField<GENFLAG> XSOL;
        ReqRecordField<GENPOSDATA> DATA;

        REFRRecord(bool newRecord=false):Record(newRecord) {}
        REFRRecord(const unsigned int &newFormID):Record(newFormID) {}
        REFRRecord(REFRRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            NAME = srcRecord->NAME;
            XTEL = srcRecord->XTEL;
            XLOC = srcRecord->XLOC;
            if(srcRecord->Ownership.IsLoaded())
                {
                Ownership.Load();
                Ownership->XOWN = srcRecord->Ownership->XOWN;
                Ownership->XRNK = srcRecord->Ownership->XRNK;
                Ownership->XGLB = srcRecord->Ownership->XGLB;
                }
            XESP = srcRecord->XESP;
            XTRG = srcRecord->XTRG;
            XSED = srcRecord->XSED;
            XLOD = srcRecord->XLOD;
            XCHG = srcRecord->XCHG;
            XHLT = srcRecord->XHLT;
            if(srcRecord->XPCI.IsLoaded())
                {
                XPCI.Load();
                XPCI->XPCI = srcRecord->XPCI->XPCI;
                XPCI->FULL = srcRecord->XPCI->FULL;
                }
            XLCM = srcRecord->XLCM;
            XRTM = srcRecord->XRTM;
            XACT = srcRecord->XACT;
            XCNT = srcRecord->XCNT;
            if(srcRecord->Marker.IsLoaded())
                {
                Marker.Load();
                Marker->FNAM = srcRecord->Marker->FNAM;
                Marker->FULL = srcRecord->Marker->FULL;
                Marker->TNAM = srcRecord->Marker->TNAM;
                }
            if(srcRecord->IsOpenByDefault())//bool ONAM; //Open by Default, empty marker, written whenever fOpenByDefault is true
                IsOpenByDefault(true);
            XSCL = srcRecord->XSCL;
            XSOL = srcRecord->XSOL;
            DATA = srcRecord->DATA;
            return;
            }
        ~REFRRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            NAME.Unload();
            XTEL.Unload();
            XLOC.Unload();
            Ownership.Unload();
            XESP.Unload();
            XTRG.Unload();
            XSED.Unload();
            XLOD.Unload();
            XCHG.Unload();
            XHLT.Unload();
            XPCI.Unload();
            XLCM.Unload();
            XRTM.Unload();
            XACT.Unload();
            XCNT.Unload();
            Marker.Unload();
            XSCL.Unload();
            XSOL.Unload();
            DATA.Unload();
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            FormIDHandler.ExpandFormID(NAME.value.fid);
            if(XTEL.IsLoaded())
                FormIDHandler.ExpandFormID(XTEL->destinationFid);
            if(XLOC.IsLoaded())
                FormIDHandler.ExpandFormID(XLOC->key);
            if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
                FormIDHandler.ExpandFormID(Ownership->XOWN.value.fid);
            if(Ownership.IsLoaded() && Ownership->XGLB.IsLoaded())
                FormIDHandler.ExpandFormID(Ownership->XGLB->fid);
            if(XESP.IsLoaded())
                FormIDHandler.ExpandFormID(XESP->parent);
            if(XTRG.IsLoaded())
                FormIDHandler.ExpandFormID(XTRG->fid);
            if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
                FormIDHandler.ExpandFormID(XPCI->XPCI->fid);
            if(XRTM.IsLoaded())
                FormIDHandler.ExpandFormID(XRTM->fid);
            }
        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            FormIDHandler.CollapseFormID(NAME.value.fid);
            if(XTEL.IsLoaded())
                FormIDHandler.CollapseFormID(XTEL->destinationFid);
            if(XLOC.IsLoaded())
                FormIDHandler.CollapseFormID(XLOC->key);
            if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
                FormIDHandler.CollapseFormID(Ownership->XOWN.value.fid);
            if(Ownership.IsLoaded() && Ownership->XGLB.IsLoaded())
                FormIDHandler.CollapseFormID(Ownership->XGLB->fid);
            if(XESP.IsLoaded())
                FormIDHandler.CollapseFormID(XESP->parent);
            if(XTRG.IsLoaded())
                FormIDHandler.CollapseFormID(XTRG->fid);
            if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
                FormIDHandler.CollapseFormID(XPCI->XPCI->fid);
            if(XRTM.IsLoaded())
                FormIDHandler.CollapseFormID(XRTM->fid);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eREFR;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
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
        bool IsParentFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(!XESP.IsLoaded()) return false;
            if(Exact)
                return (XESP->flags & Mask) == Mask;
            else
                return (XESP->flags & Mask) != 0;
            }
        void SetParentFlagMask(unsigned char Mask)
            {
            if(!XESP.IsLoaded()) return;
            XESP->flags = Mask;
            }
        bool IsVisible()
            {
            if(!Marker.IsLoaded() && !Marker->FNAM.IsLoaded()) return false;
            return (Marker->FNAM.value.flags & fVisible) != 0;
            }
        void IsVisible(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->FNAM.IsLoaded()) return;
            if(value)
                Marker->FNAM.value.flags |= fVisible;
            else
                Marker->FNAM.value.flags &= ~fVisible;
            }
        bool IsCanTravelTo()
            {
            if(!Marker.IsLoaded() && !Marker->FNAM.IsLoaded()) return false;
            return (Marker->FNAM.value.flags & fCanTravelTo) != 0;
            }
        void IsCanTravelTo(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->FNAM.IsLoaded()) return;
            if(value)
                Marker->FNAM.value.flags |= fCanTravelTo;
            else
                Marker->FNAM.value.flags &= ~fCanTravelTo;
            }
        bool IsMapFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(!Marker.IsLoaded() && !Marker->FNAM.IsLoaded()) return false;
            if(Exact)
                return (Marker->FNAM.value.flags & Mask) == Mask;
            else
                return (Marker->FNAM.value.flags & Mask) != 0;
            }
        void SetMapFlagMask(unsigned char Mask)
            {
            if(!Marker.IsLoaded() && !Marker->FNAM.IsLoaded()) return;
            Marker->FNAM.value.flags = Mask;
            }
        bool IsUseDefault()
            {
            if(!XACT.IsLoaded()) return false;
            return (XACT->flags & fUseDefault) != 0;
            }
        void IsUseDefault(bool value)
            {
            if(!XACT.IsLoaded()) return;
            if(value)
                XACT->flags |= fUseDefault;
            else
                XACT->flags &= ~fUseDefault;
            }
        bool IsActivate()
            {
            if(!XACT.IsLoaded()) return false;
            return (XACT->flags & fActivate) != 0;
            }
        void IsActivate(bool value)
            {
            if(!XACT.IsLoaded()) return;
            if(value)
                XACT->flags |= fActivate;
            else
                XACT->flags &= ~fActivate;
            }
        bool IsOpen()
            {
            if(!XACT.IsLoaded()) return false;
            return (XACT->flags & fOpen) != 0;
            }
        void IsOpen(bool value)
            {
            if(!XACT.IsLoaded()) return;
            if(value)
                XACT->flags |= fOpen;
            else
                XACT->flags &= ~fOpen;
            }
        bool IsOpenByDefault()
            {
            if(!XACT.IsLoaded()) return false;
            return (XACT->flags & fOpenByDefault) != 0;
            }
        void IsOpenByDefault(bool value)
            {
            if(!XACT.IsLoaded()) return;
            if(value)
                XACT->flags |= fOpenByDefault;
            else
                XACT->flags &= ~fOpenByDefault;
            }
        bool IsActionFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(!XACT.IsLoaded()) return false;
            if(Exact)
                return (XACT->flags & Mask) == Mask;
            else
                return (XACT->flags & Mask) != 0;
            }
        void SetActionFlagMask(unsigned int Mask)
            {
            if(!XACT.IsLoaded()) return;
            XACT->flags = Mask;
            }
        bool IsLeveledLock()
            {
            if(!XLOC.IsLoaded()) return false;
            return (XLOC->flags & fLeveledLock) != 0;
            }
        void IsLeveledLock(bool value)
            {
            if(!XLOC.IsLoaded()) return;
            if(value)
                XLOC->flags |= fLeveledLock;
            else
                XLOC->flags &= ~fLeveledLock;
            }
        bool IsLockFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(!XLOC.IsLoaded()) return false;
            if(Exact)
                return (XLOC->flags & Mask) == Mask;
            else
                return (XLOC->flags & Mask) != 0;
            }
        void SetLockFlagMask(unsigned char Mask)
            {
            if(!XLOC.IsLoaded()) return;
            XLOC->flags = Mask;
            }
        bool IsNoMarker()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return true;
            return (Marker->TNAM.value.markerType == eMarkerNone);
            }
        void IsNoMarker(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eMarkerNone;
            else if(IsNoMarker())
                Marker->TNAM.value.markerType = eCamp;
            }
        bool IsCamp()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eCamp);
            }
        void IsCamp(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eCamp;
            else if(IsCamp())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsCave()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eCave);
            }
        void IsCave(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eCave;
            else if(IsCave())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsCity()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eCity);
            }
        void IsCity(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eCity;
            else if(IsCity())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsElvenRuin()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eElvenRuin);
            }
        void IsElvenRuin(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eElvenRuin;
            else if(IsElvenRuin())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsFortRuin()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eFortRuin);
            }
        void IsFortRuin(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eFortRuin;
            else if(IsFortRuin())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsMine()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eMine);
            }
        void IsMine(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eMine;
            else if(IsMine())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsLandmark()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eLandmark);
            }
        void IsLandmark(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eLandmark;
            else if(IsLandmark())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsTavern()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eTavern);
            }
        void IsTavern(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eTavern;
            else if(IsTavern())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsSettlement()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eSettlement);
            }
        void IsSettlement(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eSettlement;
            else if(IsSettlement())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsDaedricShrine()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eDaedricShrine);
            }
        void IsDaedricShrine(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eDaedricShrine;
            else if(IsDaedricShrine())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsOblivionGate()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eOblivionGate);
            }
        void IsOblivionGate(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eOblivionGate;
            else if(IsOblivionGate())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsUnknownDoorIcon()
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == eUnknownDoorIcon);
            }
        void IsUnknownDoorIcon(bool value)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            if(value)
                Marker->TNAM.value.markerType = eUnknownDoorIcon;
            else if(IsUnknownDoorIcon())
                Marker->TNAM.value.markerType = eMarkerNone;
            }
        bool IsMarker(unsigned char Type)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return false;
            return (Marker->TNAM.value.markerType == Type);
            }
        void SetMarker(unsigned char Type)
            {
            if(!Marker.IsLoaded() && !Marker->TNAM.IsLoaded()) return;
            Marker->TNAM.value.markerType = Type;
            }
        bool IsNoSoul()
            {
            if(!XSOL.IsLoaded()) return true;
            return (XSOL->flags == eNone);
            }
        void IsNoSoul(bool value)
            {
            if(!XSOL.IsLoaded()) return;
            if(value)
                XSOL->flags = eNone;
            else if(IsNoSoul())
                XSOL->flags = ePetty;
            }
        bool IsPettySoul()
            {
            if(!XSOL.IsLoaded()) return false;
            return (XSOL->flags == ePetty);
            }
        void IsPettySoul(bool value)
            {
            if(!XSOL.IsLoaded()) return;
            if(value)
                XSOL->flags = ePetty;
            else if(IsPettySoul())
                XSOL->flags = eNone;
            }
        bool IsLesserSoul()
            {
            if(!XSOL.IsLoaded()) return false;
            return (XSOL->flags == eLesser);
            }
        void IsLesserSoul(bool value)
            {
            if(!XSOL.IsLoaded()) return;
            if(value)
                XSOL->flags = eLesser;
            else if(IsLesserSoul())
                XSOL->flags = eNone;
            }
        bool IsCommonSoul()
            {
            if(!XSOL.IsLoaded()) return false;
            return (XSOL->flags == eCommon);
            }
        void IsCommonSoul(bool value)
            {
            if(!XSOL.IsLoaded()) return;
            if(value)
                XSOL->flags = eCommon;
            else if(IsCommonSoul())
                XSOL->flags = eNone;
            }
        bool IsGreaterSoul()
            {
            if(!XSOL.IsLoaded()) return false;
            return (XSOL->flags == eGreater);
            }
        void IsGreaterSoul(bool value)
            {
            if(!XSOL.IsLoaded()) return;
            if(value)
                XSOL->flags = eGreater;
            else if(IsGreaterSoul())
                XSOL->flags = eNone;
            }
        bool IsGrandSoul()
            {
            if(!XSOL.IsLoaded()) return false;
            return (XSOL->flags == eGrand);
            }
        void IsGrandSoul(bool value)
            {
            if(!XSOL.IsLoaded()) return;
            if(value)
                XSOL->flags = eGrand;
            else if(IsGrandSoul())
                XSOL->flags = eNone;
            }
        bool IsSoul(unsigned char Type)
            {
            if(!XSOL.IsLoaded()) return false;
            return (XSOL->flags == Type);
            }
        void SetSoul(unsigned char Type)
            {
            if(!XSOL.IsLoaded()) return;
            XSOL->flags = Type;
            }
    };
