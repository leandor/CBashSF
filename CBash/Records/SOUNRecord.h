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

class SOUNRecord : public Record
    {
    private:
        enum SOUNRecordFields {
            eEDID = 0x44494445,
            eFNAM = 0x4D414E46,
            eSNDD = 0x44444E53,
            eSNDX = 0x58444E53
            };

        struct SOUNSNDX
            {
            unsigned char minDistance, maxDistance;
            char freqAdjustment;
            unsigned char unused1;
            unsigned short flags;
            unsigned char unused2[2];
            short staticAtten;
            unsigned char stopTime,startTime;
            SOUNSNDX():minDistance(0), maxDistance(0), freqAdjustment(0),
                unused1(0), flags(0), staticAtten(0),
                stopTime(0), startTime(0)
                {
                memset(&unused2, 0x00, 2);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("minDistance    = %u\n", minDistance * 5);
                    PrintIndent(indentation);
                    printf("maxDistance    = %u\n", maxDistance * 100);
                    PrintIndent(indentation);
                    printf("freqAdjustment = %i\n", freqAdjustment);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1        = %02X\n", unused1);
                        }
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags          = %u\n", flags);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused2        = %02X%02X\n", unused2[0], unused2[1]);
                        }
                    PrintIndent(indentation);
                    printf("staticAtten    = %i\n", staticAtten);
                    PrintIndent(indentation);
                    printf("stopTime       = %u\n", stopTime);
                    PrintIndent(indentation);
                    printf("startTime      = %u\n", startTime);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const SOUNSNDX &other) const
                {
                return (minDistance == other.minDistance && 
                        maxDistance == other.maxDistance && 
                        freqAdjustment == other.freqAdjustment && 
                        flags == other.flags && 
                        staticAtten == other.staticAtten && 
                        stopTime == other.stopTime && 
                        startTime == other.startTime);
                }
            bool operator !=(const SOUNSNDX &other) const
                {
                return !(*this == other);
                }
            };

    public:
        enum flagsFlags
            {
            fIsRandomFrequencyShift = 0x00000001,
            fIsPlayAtRandom         = 0x00000002,
            fIsEnvironmentIgnored   = 0x00000004,
            fIsRandomLocation       = 0x00000008,
            fIsLoop                 = 0x00000010,
            fIsMenuSound            = 0x00000020,
            fIs2D                   = 0x00000040,
            fIs360LFE               = 0x00000080
            };
        STRING EDID;
        STRING FNAM;
        ReqRecordField<SOUNSNDX> SNDX;
        SOUNRecord(bool newRecord=false):Record(newRecord) {}
        SOUNRecord(const unsigned int &newFormID):Record(newFormID) {}
        SOUNRecord(SOUNRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FNAM = srcRecord->FNAM;
            SNDX = srcRecord->SNDX;
            return;
            }
        ~SOUNRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FNAM.Unload();
            SNDX.Unload();
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
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, short FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eSOUN;}
        char * GetStrType() {return "SOUN";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsRandomFrequencyShift()
            {
            return (SNDX.value.flags & fIsRandomFrequencyShift) != 0;
            }
        void IsRandomFrequencyShift(bool value)
            {
            if(value)
                SNDX.value.flags |= fIsRandomFrequencyShift;
            else
                SNDX.value.flags &= ~fIsRandomFrequencyShift;
            }
        bool IsPlayAtRandom()
            {
            return (SNDX.value.flags & fIsPlayAtRandom) != 0;
            }
        void IsPlayAtRandom(bool value)
            {
            if(value)
                SNDX.value.flags |= fIsPlayAtRandom;
            else
                SNDX.value.flags &= ~fIsPlayAtRandom;
            }
        bool IsEnvironmentIgnored()
            {
            return (SNDX.value.flags & fIsEnvironmentIgnored) != 0;
            }
        void IsEnvironmentIgnored(bool value)
            {
            if(value)
                SNDX.value.flags |= fIsEnvironmentIgnored;
            else
                SNDX.value.flags &= ~fIsEnvironmentIgnored;
            }
        bool IsRandomLocation()
            {
            return (SNDX.value.flags & fIsRandomLocation) != 0;
            }
        void IsRandomLocation(bool value)
            {
            if(value)
                SNDX.value.flags |= fIsRandomLocation;
            else
                SNDX.value.flags &= ~fIsRandomLocation;
            }
        bool IsLoop()
            {
            return (SNDX.value.flags & fIsLoop) != 0;
            }
        void IsLoop(bool value)
            {
            if(value)
                SNDX.value.flags |= fIsLoop;
            else
                SNDX.value.flags &= ~fIsLoop;
            }
        bool IsMenuSound()
            {
            return (SNDX.value.flags & fIsMenuSound) != 0;
            }
        void IsMenuSound(bool value)
            {
            if(value)
                SNDX.value.flags |= fIsMenuSound;
            else
                SNDX.value.flags &= ~fIsMenuSound;
            }
        bool Is2D()
            {
            return (SNDX.value.flags & fIs2D) != 0;
            }
        void Is2D(bool value)
            {
            if(value)
                SNDX.value.flags |= fIs2D;
            else
                SNDX.value.flags &= ~fIs2D;
            }
        bool Is360LFE()
            {
            return (SNDX.value.flags & fIs360LFE) != 0;
            }
        void Is360LFE(bool value)
            {
            if(value)
                SNDX.value.flags |= fIs360LFE;
            else
                SNDX.value.flags &= ~fIs360LFE;
            }
        bool IsFlagMask(unsigned short Mask, bool Exact=false)
            {
            if(Exact)
                return (SNDX.value.flags & Mask) == Mask;
            else
                return (SNDX.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned short Mask)
            {
            SNDX.value.flags = Mask;
            }
    };
