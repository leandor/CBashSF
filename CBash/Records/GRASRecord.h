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

class GRASRecord : public Record
    {
    private:
        enum GRASRecordFields {
            eEDID = 0x44494445,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eDATA = 0x41544144
            };
        struct GRASDATA
            {
            unsigned char density, minSlope, maxSlope, unused1;
            unsigned short waterDistance;
            unsigned char unused2[2];
            unsigned int waterOp;
            float posRange, heightRange, colorRange, wavePeriod;
            unsigned char flags, unused3[3];
            GRASDATA():density(0), minSlope(0), maxSlope(0), unused1(0xCD),
                waterDistance(0), waterOp(0), posRange(0.0f),
                heightRange(0.0f), colorRange(0.0f), wavePeriod(0.0f),
                flags(0)
                {
                memset(&unused2, 0xCD, 2);
                memset(&unused3, 0xCD, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("density       = %u\n", density);
                    PrintIndent(indentation);
                    printf("minSlope      = %u\n", minSlope);
                    PrintIndent(indentation);
                    printf("maxSlope      = %u\n", maxSlope);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1       = %02X\n", unused1);
                        }
                    PrintIndent(indentation);
                    printf("waterDistance = %u\n", waterDistance);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused2       = %02X%02X\n", unused2[0], unused2[1]);
                        }
                    PrintIndent(indentation);
                    printf("waterOp       = %u\n", waterOp);
                    PrintIndent(indentation);
                    printf("posRange      = %f\n", posRange);
                    PrintIndent(indentation);
                    printf("heightRange   = %f\n", heightRange);
                    PrintIndent(indentation);
                    printf("colorRange    = %f\n", colorRange);
                    PrintIndent(indentation);
                    printf("wavePeriod    = %f\n", wavePeriod);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags         = %u\n", flags);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused3       = %02X%02X%02X\n", unused3[0], unused3[1], unused3[2]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        enum flagsFlags
            {
            fIsVLighting = 0x00000001,
            fIsUScaling  = 0x00000002,
            fIsFitSlope  = 0x00000004
            };
        STRING EDID;
        GENMODEL MODL;
        ReqRecordField<GRASDATA> DATA;

        GRASRecord(bool newRecord=false):Record(newRecord) {}
        GRASRecord(const unsigned int &newFormID):Record(newFormID) {}
        GRASRecord(GRASRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
            DATA = srcRecord->DATA;
            return;
            }
        ~GRASRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            MODL.MODB.Unload();
            MODL.MODL.Unload();
            MODL.MODT.Unload();
            DATA.Unload();
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eGRAS;}
        char * GetStrType() {return "GRAS";}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
        bool IsVLighting()
            {
            return (DATA.value.flags & fIsVLighting) != 0;
            }
        void IsVLighting(bool value)
            {
            if(value)
                DATA.value.flags |= fIsVLighting;
            else
                DATA.value.flags &= ~fIsVLighting;
            }
        bool IsUScaling()
            {
            return (DATA.value.flags & fIsUScaling) != 0;
            }
        void IsUScaling(bool value)
            {
            if(value)
                DATA.value.flags |= fIsUScaling;
            else
                DATA.value.flags &= ~fIsUScaling;
            }
        bool IsFitSlope()
            {
            return (DATA.value.flags & fIsFitSlope) != 0;
            }
        void IsFitSlope(bool value)
            {
            if(value)
                DATA.value.flags |= fIsFitSlope;
            else
                DATA.value.flags &= ~fIsFitSlope;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            DATA.value.flags = Mask;
            }
    };
