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

class RACERecord : public Record
    {
    private:
        enum RACERecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,
            eDESC = 0x43534544,
            eSPLO = 0x4F4C5053,
            eXNAM = 0x4D414E58,
            eDATA = 0x41544144,
            eVNAM = 0x4D414E56,

            eDNAM = 0x4D414E44,
            eCNAM = 0x4D414E43,
            ePNAM = 0x4D414E50,
            eUNAM = 0x4D414E55,
            eATTR = 0x52545441,
            eNAM0 = 0x304D414E,

            eINDX = 0x58444E49,
            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,
            eICON = 0x4E4F4349,

            eNAM1 = 0x314D414E,
            eMNAM = 0x4D414E4D,

            eFNAM = 0x4D414E46,
            eHNAM = 0x4D414E48,
            eENAM = 0x4D414E45,

            eFGGS = 0x53474746,
            eFGGA = 0x41474746,
            eFGTS = 0x53544746,
            eSNAM = 0x4D414E53
            };

        struct RACESKILL
            {
            char value, boost;
            RACESKILL(bool newRecord=false):value(-1), boost(0) {}
            bool operator ==(const RACESKILL &other) const
                {
                return (value == other.value && 
                        boost == other.boost);
                }
            bool operator !=(const RACESKILL &other) const
                {
                return !(*this == other);
                }
            };

        struct RACEDATA
            {
            RACESKILL skills[7];
            unsigned char unused1[2];
            float maleHeight, femaleHeight, maleWeight, femaleWeight;
            unsigned int flags;
            RACEDATA(bool newRecord=false):maleHeight(1.0f), femaleHeight(1.0f), maleWeight(1.0f), femaleWeight(1.0f), flags(0)
                {
                memset(&unused1, 0x00, 2);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("skill1 = %i, boost1 = %i\n", skills[0].value, skills[0].boost);
                    PrintIndent(indentation);
                    printf("skill2 = %i, boost2 = %i\n", skills[1].value, skills[1].boost);
                    PrintIndent(indentation);
                    printf("skill3 = %i, boost3 = %i\n", skills[2].value, skills[2].boost);
                    PrintIndent(indentation);
                    printf("skill4 = %i, boost4 = %i\n", skills[3].value, skills[3].boost);
                    PrintIndent(indentation);
                    printf("skill5 = %i, boost5 = %i\n", skills[4].value, skills[4].boost);
                    PrintIndent(indentation);
                    printf("skill6 = %i, boost6 = %i\n", skills[5].value, skills[5].boost);
                    PrintIndent(indentation);
                    printf("skill7 = %i, boost7 = %i\n", skills[6].value, skills[6].boost);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1      = %02X%02X\n", unused1[0], unused1[1]);
                        }
                    PrintIndent(indentation);
                    printf("maleHeight   = %f\n", maleHeight);
                    PrintIndent(indentation);
                    printf("femaleHeight = %f\n", femaleHeight);
                    PrintIndent(indentation);
                    printf("maleWeight   = %f\n", maleWeight);
                    PrintIndent(indentation);
                    printf("femaleWeight = %f\n", femaleWeight);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags        = %u\n", flags);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const RACEDATA &other) const
                {
                return (skills[0] == other.skills[0] && 
                        skills[1] == other.skills[1] && 
                        skills[2] == other.skills[2] && 
                        skills[3] == other.skills[3] && 
                        skills[4] == other.skills[4] && 
                        skills[5] == other.skills[5] && 
                        skills[6] == other.skills[6] && 
                        AlmostEqual(maleHeight,other.maleHeight,2) && 
                        AlmostEqual(femaleHeight,other.femaleHeight,2) && 
                        AlmostEqual(maleWeight,other.maleWeight,2) && 
                        AlmostEqual(femaleWeight,other.femaleWeight,2) && 
                        flags == other.flags);
                }
            bool operator !=(const RACEDATA &other) const
                {
                return !(*this == other);
                }
            };

        struct RACEVNAM
            {
            unsigned int maleVoice, femaleVoice;
            RACEVNAM(bool newRecord=false):maleVoice(0), femaleVoice(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("maleVoice   = %s\n", PrintFormID(maleVoice));
                    PrintIndent(indentation);
                    printf("femaleVoice = %s\n", PrintFormID(femaleVoice));
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const RACEVNAM &other) const
                {
                return (maleVoice == other.maleVoice && 
                        femaleVoice == other.femaleVoice);
                }
            bool operator !=(const RACEVNAM &other) const
                {
                return !(*this == other);
                }
            };

        struct RACEDNAM
            {
            unsigned int defaultHairMale, defaultHairFemale;
            RACEDNAM(bool newRecord=false):defaultHairMale(0), defaultHairFemale(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("defaultHairMale   = %s\n", PrintFormID(defaultHairMale));
                    PrintIndent(indentation);
                    printf("defaultHairFemale = %s\n", PrintFormID(defaultHairFemale));
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const RACEDNAM &other) const
                {
                return (defaultHairMale == other.defaultHairMale && 
                        defaultHairFemale == other.defaultHairFemale);
                }
            bool operator !=(const RACEDNAM &other) const
                {
                return !(*this == other);
                }
            };

        struct RACECNAM
            {
            unsigned char defaultHairColor;
            RACECNAM(bool newRecord=false):defaultHairColor(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("defaultHairColor = %u\n", defaultHairColor);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const RACECNAM &other) const
                {
                return (defaultHairColor == other.defaultHairColor);
                }
            bool operator !=(const RACECNAM &other) const
                {
                return !(*this == other);
                }
            };

        struct RACEPNAM
            {
            float mainClamp;
            RACEPNAM(bool newRecord=false):mainClamp(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("mainClamp = %f\n", mainClamp);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const RACEPNAM &other) const
                {
                return (AlmostEqual(mainClamp,other.mainClamp,2));
                }
            bool operator !=(const RACEPNAM &other) const
                {
                return !(*this == other);
                }
            };

        struct RACEUNAM
            {
            float faceClamp;
            RACEUNAM(bool newRecord=false):faceClamp(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("faceClamp = %f\n", faceClamp);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const RACEUNAM &other) const
                {
                return (AlmostEqual(faceClamp,other.faceClamp,2));
                }
            bool operator !=(const RACEUNAM &other) const
                {
                return !(*this == other);
                }
            };

        struct RACEATTR
            {
            unsigned char maleStrength, maleIntelligence, maleWillpower,
                 maleAgility, maleSpeed, maleEndurance,
                 malePersonality, maleLuck;
            unsigned char femaleStrength, femaleIntelligence, femaleWillpower,
                 femaleAgility, femaleSpeed, femaleEndurance,
                 femalePersonality, femaleLuck;
            RACEATTR(bool newRecord=false):maleStrength(50), maleIntelligence(50),
                maleWillpower(50), maleAgility(50),
                maleSpeed(50), maleEndurance(50),
                malePersonality(50), maleLuck(50),
                femaleStrength(50), femaleIntelligence(50),
                femaleWillpower(50), femaleAgility(50),
                femaleSpeed(50), femaleEndurance(50),
                femalePersonality(50), femaleLuck(50) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("maleStrength     = %u\n", maleStrength);
                    PrintIndent(indentation);
                    printf("maleIntelligence = %u\n", maleIntelligence);
                    PrintIndent(indentation);
                    printf("maleWillpower    = %u\n", maleWillpower);
                    PrintIndent(indentation);
                    printf("maleAgility      = %u\n", maleAgility);
                    PrintIndent(indentation);
                    printf("maleSpeed        = %u\n", maleSpeed);
                    PrintIndent(indentation);
                    printf("maleEndurance    = %u\n", maleEndurance);
                    PrintIndent(indentation);
                    printf("malePersonality  = %u\n", malePersonality);
                    PrintIndent(indentation);
                    printf("maleLuck         = %u\n", maleLuck);
                    PrintIndent(indentation);
                    printf("femaleStrength     = %u\n", femaleStrength);
                    PrintIndent(indentation);
                    printf("femaleIntelligence = %u\n", femaleIntelligence);
                    PrintIndent(indentation);
                    printf("femaleWillpower    = %u\n", femaleWillpower);
                    PrintIndent(indentation);
                    printf("femaleAgility      = %u\n", femaleAgility);
                    PrintIndent(indentation);
                    printf("femaleSpeed        = %u\n", femaleSpeed);
                    PrintIndent(indentation);
                    printf("femaleEndurance    = %u\n", femaleEndurance);
                    PrintIndent(indentation);
                    printf("femalePersonality  = %u\n", femalePersonality);
                    PrintIndent(indentation);
                    printf("femaleLuck         = %u\n", femaleLuck);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const RACEATTR &other) const
                {
                return (maleStrength == other.maleStrength && 
                        maleIntelligence == other.maleIntelligence && 
                        maleWillpower == other.maleWillpower && 
                        maleAgility == other.maleAgility && 
                        maleSpeed == other.maleSpeed && 
                        maleEndurance == other.maleEndurance && 
                        malePersonality == other.malePersonality && 
                        maleLuck == other.maleLuck && 
                        femaleStrength == other.femaleStrength && 
                        femaleIntelligence == other.femaleIntelligence && 
                        femaleWillpower == other.femaleWillpower && 
                        femaleAgility == other.femaleAgility && 
                        femaleSpeed == other.femaleSpeed && 
                        femaleEndurance == other.femaleEndurance && 
                        femalePersonality == other.femalePersonality && 
                        femaleLuck == other.femaleLuck);
                }
            bool operator !=(const RACEATTR &other) const
                {
                return !(*this == other);
                }
            };

        struct RACEMODEL
            {
            ReqRecordField<MODELMODB> MODB;
            STRING MODL;
            RAWBYTES MODT;
            STRING ICON;
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
                    MODL.Debug("MODL", debugLevel, indentation);
                    MODB.Debug("MODB", debugLevel, indentation);
                    MODT.Debug("MODT", debugLevel, indentation);
                    ICON.Debug("ICON", debugLevel, indentation);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const RACEMODEL &other) const
                {
                return (MODB == other.MODB && 
                        MODL == other.MODL && 
                        MODT == other.MODT && 
                        ICON == other.ICON);
                }
            bool operator !=(const RACEMODEL &other) const
                {
                return !(*this == other);
                }
            };

        struct RACESNAM
            {
            unsigned char SNAM[2];
            RACESNAM()
                {
                memset(&SNAM, 0x00, 2);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("SNAM = %02X%02X\n", SNAM[0], SNAM[1]);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const RACESNAM &other) const
                {
                return (SNAM[0] == other.SNAM[0] && 
                        SNAM[1] == other.SNAM[1]);
                }
            bool operator !=(const RACESNAM &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum flagsFlags
            {
            fIsPlayable   = 0x00000001
            };
        STRING EDID;
        STRING FULL;
        STRING DESC;
        std::vector<unsigned int *> SPLO;
        std::vector<ReqRecordField<GENXNAM> *> XNAM;
        ReqRecordField<RACEDATA> DATA;
        RecordField<RACEVNAM> VNAM;
        RecordField<RACEDNAM> DNAM;
        ReqRecordField<RACECNAM> CNAM;
        RecordField<RACEPNAM> PNAM;
        RecordField<RACEUNAM> UNAM;
        ReqRecordField<RACEATTR> ATTR;
        OptRecordField<RACEMODEL> MOD0;
        OptRecordField<RACEMODEL> MOD1;
        OptRecordField<RACEMODEL> MOD2;
        OptRecordField<RACEMODEL> MOD3;
        OptRecordField<RACEMODEL> MOD4;
        OptRecordField<RACEMODEL> MOD5;
        OptRecordField<RACEMODEL> MOD6;
        OptRecordField<RACEMODEL> MOD7;
        OptRecordField<RACEMODEL> MOD8;

        OptRecordField<GENMODEL> MMODL;

        STRING MICON0;
        STRING MICON1;
        STRING MICON2;
        STRING MICON3;
        STRING MICON4;

        OptRecordField<GENMODEL> FMODL;

        STRING FICON0;
        STRING FICON1;
        STRING FICON2;
        STRING FICON3;
        STRING FICON4;

        std::vector<unsigned int> HNAM;
        std::vector<unsigned int> ENAM;
        RAWBYTES FGGS;
        RAWBYTES FGGA;
        RAWBYTES FGTS;
        ReqRecordField<RACESNAM> SNAM;

        RACERecord(bool newRecord=false):Record(newRecord) {}
        RACERecord(const unsigned int &newFormID):Record(newFormID) {}
        RACERecord(RACERecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            DESC = srcRecord->DESC;

            SPLO.clear();
            SPLO.resize(srcRecord->SPLO.size());
            for(unsigned int x = 0; x < srcRecord->SPLO.size(); x++)
                SPLO[x] = new unsigned int(*srcRecord->SPLO[x]);

            XNAM.clear();
            XNAM.resize(srcRecord->XNAM.size());
            for(unsigned int x = 0; x < srcRecord->XNAM.size(); x++)
                {
                XNAM[x] = new ReqRecordField<GENXNAM>;
                *XNAM[x] = *srcRecord->XNAM[x];
                }

            DATA = srcRecord->DATA;

            VNAM = srcRecord->VNAM;
            DNAM = srcRecord->DNAM;

            CNAM = srcRecord->CNAM;
            PNAM = srcRecord->PNAM;
            UNAM = srcRecord->UNAM;
            ATTR = srcRecord->ATTR;

            if(srcRecord->MOD0.IsLoaded())
                {
                MOD0.Load();
                MOD0->MODB = srcRecord->MOD0->MODB;
                MOD0->MODL = srcRecord->MOD0->MODL;
                MOD0->MODT = srcRecord->MOD0->MODT;
                MOD0->ICON = srcRecord->MOD0->ICON;
                }

            if(srcRecord->MOD1.IsLoaded())
                {
                MOD1.Load();
                MOD1->MODB = srcRecord->MOD1->MODB;
                MOD1->MODL = srcRecord->MOD1->MODL;
                MOD1->MODT = srcRecord->MOD1->MODT;
                MOD1->ICON = srcRecord->MOD1->ICON;
                }

            if(srcRecord->MOD2.IsLoaded())
                {
                MOD2.Load();
                MOD2->MODB = srcRecord->MOD2->MODB;
                MOD2->MODL = srcRecord->MOD2->MODL;
                MOD2->MODT = srcRecord->MOD2->MODT;
                MOD2->ICON = srcRecord->MOD2->ICON;
                }

            if(srcRecord->MOD3.IsLoaded())
                {
                MOD3.Load();
                MOD3->MODB = srcRecord->MOD3->MODB;
                MOD3->MODL = srcRecord->MOD3->MODL;
                MOD3->MODT = srcRecord->MOD3->MODT;
                MOD3->ICON = srcRecord->MOD3->ICON;
                }

            if(srcRecord->MOD4.IsLoaded())
                {
                MOD4.Load();
                MOD4->MODB = srcRecord->MOD4->MODB;
                MOD4->MODL = srcRecord->MOD4->MODL;
                MOD4->MODT = srcRecord->MOD4->MODT;
                MOD4->ICON = srcRecord->MOD4->ICON;
                }

            if(srcRecord->MOD5.IsLoaded())
                {
                MOD5.Load();
                MOD5->MODB = srcRecord->MOD5->MODB;
                MOD5->MODL = srcRecord->MOD5->MODL;
                MOD5->MODT = srcRecord->MOD5->MODT;
                MOD5->ICON = srcRecord->MOD5->ICON;
                }

            if(srcRecord->MOD6.IsLoaded())
                {
                MOD6.Load();
                MOD6->MODB = srcRecord->MOD6->MODB;
                MOD6->MODL = srcRecord->MOD6->MODL;
                MOD6->MODT = srcRecord->MOD6->MODT;
                MOD6->ICON = srcRecord->MOD6->ICON;
                }

            if(srcRecord->MOD7.IsLoaded())
                {
                MOD7.Load();
                MOD7->MODB = srcRecord->MOD7->MODB;
                MOD7->MODL = srcRecord->MOD7->MODL;
                MOD7->MODT = srcRecord->MOD7->MODT;
                MOD7->ICON = srcRecord->MOD7->ICON;
                }

            if(srcRecord->MOD8.IsLoaded())
                {
                MOD8.Load();
                MOD8->MODB = srcRecord->MOD8->MODB;
                MOD8->MODL = srcRecord->MOD8->MODL;
                MOD8->MODT = srcRecord->MOD8->MODT;
                MOD8->ICON = srcRecord->MOD8->ICON;
                }

            if(srcRecord->MMODL.IsLoaded())
                {
                MMODL.Load();
                MMODL->MODB = srcRecord->MMODL->MODB;
                MMODL->MODL = srcRecord->MMODL->MODL;
                MMODL->MODT = srcRecord->MMODL->MODT;
                }

            MICON0 = srcRecord->MICON0;
            MICON1 = srcRecord->MICON1;
            MICON2 = srcRecord->MICON2;
            MICON3 = srcRecord->MICON3;
            MICON4 = srcRecord->MICON4;

            if(srcRecord->FMODL.IsLoaded())
                {
                FMODL.Load();
                FMODL->MODB = srcRecord->FMODL->MODB;
                FMODL->MODL = srcRecord->FMODL->MODL;
                FMODL->MODT = srcRecord->FMODL->MODT;
                }

            FICON0 = srcRecord->FICON0;
            FICON1 = srcRecord->FICON1;
            FICON2 = srcRecord->FICON2;
            FICON3 = srcRecord->FICON3;
            FICON4 = srcRecord->FICON4;
            HNAM = srcRecord->HNAM;
            ENAM = srcRecord->ENAM;
            FGGS = srcRecord->FGGS;
            FGGA = srcRecord->FGGA;
            FGTS = srcRecord->FGTS;
            SNAM = srcRecord->SNAM;
            }
        ~RACERecord()
            {
            for(unsigned int x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            for(unsigned int x = 0; x < XNAM.size(); x++)
                delete XNAM[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            DESC.Unload();
            for(unsigned int x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            SPLO.clear();

            for(unsigned int x = 0; x < XNAM.size(); x++)
                delete XNAM[x];
            XNAM.clear();

            DATA.Unload();

            VNAM.Unload();
            DNAM.Unload();

            CNAM.Unload();
            PNAM.Unload();
            UNAM.Unload();
            ATTR.Unload();

            MOD0.Unload();
            MOD1.Unload();
            MOD2.Unload();
            MOD3.Unload();
            MOD4.Unload();
            MOD5.Unload();
            MOD6.Unload();
            MOD7.Unload();
            MOD8.Unload();

            MMODL.Unload();

            MICON0.Unload();
            MICON1.Unload();
            MICON2.Unload();
            MICON3.Unload();
            MICON4.Unload();

            FMODL.Unload();

            FICON0.Unload();
            FICON1.Unload();
            FICON2.Unload();
            FICON3.Unload();
            FICON4.Unload();
            HNAM.clear();
            ENAM.clear();
            FGGS.Unload();
            FGGA.Unload();
            FGTS.Unload();
            SNAM.Unload();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            for(unsigned int x = 0; x < SPLO.size(); x++)
                FormIDs.push_back(SPLO[x]);
            for(unsigned int x = 0; x < XNAM.size(); x++)
                FormIDs.push_back(&XNAM[x]->value.faction);
            FormIDs.push_back(&VNAM.value.femaleVoice);
            FormIDs.push_back(&VNAM.value.maleVoice);
            FormIDs.push_back(&DNAM.value.defaultHairFemale);
            FormIDs.push_back(&DNAM.value.defaultHairMale);
            for(unsigned int x = 0; x < HNAM.size(); x++)
                FormIDs.push_back(&HNAM[x]);
            for(unsigned int x = 0; x < ENAM.size(); x++)
                FormIDs.push_back(&ENAM[x]);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eRACE;}
        char * GetStrType() {return "RACE";}
        int WriteRecord(_FileHandler &SaveHandler);

        bool IsPlayable()
            {
            return (DATA.value.flags & fIsPlayable) != 0;
            }
        void IsPlayable(bool value)
            {
            if(value)
                DATA.value.flags |= fIsPlayable;
            else
                DATA.value.flags &= ~fIsPlayable;
            }
        bool IsFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned int Mask)
            {
            DATA.value.flags = Mask;
            }
    };
