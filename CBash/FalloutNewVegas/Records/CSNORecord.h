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
class CSNORecord : public Record //Casino
    {
    private:
        struct CSNODATA
            {
            FLOAT32 shufflePercent; // Decks % Before Shuffle
            FLOAT32 bjPayoutRatio; // BlackJack Payout Ratio
            UINT32  symbol1Stop, symbol2Stop,
                    symbol3Stop, symbol4Stop,
                    symbol5Stop, symbol6Stop,
                    symbolWStop; // Slot Reel Stops
            UINT32  numDecks; // Number of Decks
            UINT32  maxWinnings; // Max Winnings
            FORMID  currency; // Currency
            FORMID  winningsQuest; // Casino Winnings Quest
            UINT32  flags;

            CSNODATA();
            ~CSNODATA();

            bool operator ==(const CSNODATA &other) const;
            bool operator !=(const CSNODATA &other) const;
            };

        enum csnoFlags
            {
            fIsDealerStayOnSoft17 = 0x00000001
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSubRecord<CSNODATA> DATA; //Data
        StringRecord MODL1; //$1 Chip Model
        StringRecord MODL5; //$5 Chip Model
        StringRecord MODL10; //$10 Chip Model
        StringRecord MODL25; //$25 Chip Model
        StringRecord MODL100; //$100 Chip Model
        StringRecord MODL500; //$500 Chip Model
        StringRecord MODLRoulette; //Roulette Chip
        StringRecord MODL; //Slot Machine Model
        StringRecord MOD2; //Slot Machine Model (again?)
        StringRecord MOD3; //BlackJack Table Model
        StringRecord MOD4; //Roulette Table Model
        StringRecord ICON1; //Symbol 1 Slot Reel Texture
        StringRecord ICON2; //Symbol 2 Slot Reel Texture
        StringRecord ICON3; //Symbol 3 Slot Reel Texture
        StringRecord ICON4; //Symbol 4 Slot Reel Texture
        StringRecord ICON5; //Symbol 5 Slot Reel Texture
        StringRecord ICON6; //Symbol 6 Slot Reel Texture
        StringRecord ICONW; //Symbol W Slot Reel Texture
        StringRecord ICO21; //BlackJack Deck 1
        StringRecord ICO22; //BlackJack Deck 2
        StringRecord ICO23; //BlackJack Deck 3
        StringRecord ICO24; //BlackJack Deck 4

        CSNORecord(unsigned char *_recData=NULL);
        CSNORecord(CSNORecord *srcRecord);
        ~CSNORecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsDealerStayOnSoft17();
        void   IsDealerStayOnSoft17(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(_FileHandler &SaveHandler);

        bool operator ==(const CSNORecord &other) const;
        bool operator !=(const CSNORecord &other) const;
    };
}