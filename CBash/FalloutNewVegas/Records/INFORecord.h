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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class INFORecord : public FNVRecord //Dialog response
    {
    private:
        struct INFODATA
            {
            UINT8   dialType; //Type
            UINT8   nextSpeaker; //Next Speaker
            UINT16  flags;

            INFODATA();
            ~INFODATA();

            bool operator ==(const INFODATA &other) const;
            bool operator !=(const INFODATA &other) const;
            };

        struct INFOTRDT //Response Data
            {
            UINT32  emotionType; //Emotion Type
            SINT32  emotionValue; //Emotion Value
            UINT8   unused1[4], responseNum, unused2[3]; //Unused, Response Number, Unused
            FORMID  sound; //Sound
            UINT8   flags, unused3[3]; //Flags, Unused

            INFOTRDT();
            ~INFOTRDT();

            bool operator ==(const INFOTRDT &other) const;
            bool operator !=(const INFOTRDT &other) const;
            };

        struct INFOResponse
            {
            ReqSubRecord<INFOTRDT> TRDT; //Response Data
            StringRecord NAM1; //Response Text (REQ)
            StringRecord NAM2; //Script Notes (REQ)
            StringRecord NAM3; //Edits (REQ)
            OptSimpleSubRecord<FORMID> SNAM; //Speaker Animation
            OptSimpleSubRecord<FORMID> LNAM; //Listener Animation

            enum eEmotionType
                {
                eNeutral  = 0,
                eAnger    = 1,
                eDisgust  = 2,
                eFear     = 3,
                eSad      = 4,
                eHappy    = 5,
                eSurprise = 6,
                ePained   = 7
                };

            enum flagsFlags
                {
                fIsUseEmotionAnim = 0x01
                };

            bool   IsNeutral();
            void   IsNeutral(bool value);
            bool   IsAnger();
            void   IsAnger(bool value);
            bool   IsDisgust();
            void   IsDisgust(bool value);
            bool   IsFear();
            void   IsFear(bool value);
            bool   IsSad();
            void   IsSad(bool value);
            bool   IsHappy();
            void   IsHappy(bool value);
            bool   IsSurprise();
            void   IsSurprise(bool value);
            bool   IsPained();
            void   IsPained(bool value);
            bool   IsType(UINT32 Type);
            void   SetType(UINT32 Type);

            bool   IsUseEmotionAnim();
            void   IsUseEmotionAnim(bool value);
            bool   IsFlagMask(UINT8 Mask, bool Exact=false);
            void   SetFlagMask(UINT8 Mask);

            void Write(FileWriter &writer);

            bool operator ==(const INFOResponse &other) const;
            bool operator !=(const INFOResponse &other) const;
            };

        enum eDialogType
            {
            eTopic        = 0,
            eConversation = 1,
            eCombat       = 2,
            ePersuasion   = 3,
            eDetection    = 4,
            eService      = 5,
            eMisc         = 6,
            eRadio        = 7
            };

        enum eSpeakerType
            {
            eTarget = 0,
            eSelf   = 1,
            eEither = 2
            };

        enum flagsFlags
            {
            fIsGoodbye         = 0x0001,
            fIsRandom          = 0x0002,
            fIsSayOnce         = 0x0004,
            fIsRunImmediately  = 0x0008,
            fIsInfoRefusal     = 0x0010,
            fIsRandomEnd       = 0x0020,
            fIsRunForRumors    = 0x0040,
            fIsSpeechChallenge = 0x0080,
            fIsSayOnceADay     = 0x0100,
            fIsAlwaysDarken    = 0x0200
            };

        enum eChallengeLevelType
            {
            eNone = 0,
            eVeryEasy,
            eEasy,
            eAverage,
            eHard,
            eVeryHard
            };

        enum schrFlags
            {
            fIsEnabled = 0x0001
            };

        enum scriptTypeTypes
            {
            eObject = 0x0000,
            eQuest  = 0x0001,
            eEffect = 0x0100
            };

    public:
        ReqSubRecord<INFODATA> DATA; //INFO Data
        ReqSimpleSubRecord<FORMID> QSTI; //Quest
        OptSimpleSubRecord<FORMID> TPIC; //Topic
        OptSimpleSubRecord<FORMID> PNAM; //Previous INFO
        UnorderedSparseArray<FORMID> NAME; //Topics
        UnorderedSparseArray<INFOResponse *> Responses; //Responses
        OrderedSparseArray<FNVCTDA *> CTDA; //Conditions

        UnorderedSparseArray<FORMID> TCLT; //Choices
        UnorderedSparseArray<FORMID> TCLF; //Link From
        UnorderedSparseArray<FORMID> TCFU; //Unknown
        ReqSubRecord<FNVSCHR> BeginSCHR; //Basic Script Data
        RawRecord BeginSCDA; //Unknown (Script Header?)
        NonNullStringRecord BeginSCTX; //Script Source
        OrderedSparseArray<GENVARS *, sortVARS> BeginVARS; //Local Variables
        OrderedSparseArray<GENSCR_ *> BeginSCR_; //References
        //NEXT empty marker (REQ)
        ReqSubRecord<FNVSCHR> EndSCHR; //Basic Script Data
        RawRecord EndSCDA; //Unknown (Script Header?)
        NonNullStringRecord EndSCTX; //Script Source
        OrderedSparseArray<GENVARS *, sortVARS> EndVARS; //Local Variables
        OrderedSparseArray<GENSCR_ *> EndSCR_; //References

        OptSimpleSubRecord<FORMID> SNDD; //Unused
        StringRecord RNAM; //Prompt
        OptSimpleSubRecord<FORMID> ANAM; //Speaker
        OptSimpleSubRecord<FORMID> KNAM; //ActorValue/Perk
        OptSimpleSubRecord<UINT32> DNAM; //Speech Challenge

        Record *Parent;

        INFORecord(unsigned char *_recData=NULL);
        INFORecord(INFORecord *srcRecord);
        ~INFORecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsGoodbye();
        void   IsGoodbye(bool value);
        bool   IsRandom();
        void   IsRandom(bool value);
        bool   IsSayOnce();
        void   IsSayOnce(bool value);
        bool   IsRunImmediately();
        void   IsRunImmediately(bool value);
        bool   IsInfoRefusal();
        void   IsInfoRefusal(bool value);
        bool   IsRandomEnd();
        void   IsRandomEnd(bool value);
        bool   IsRunForRumors();
        void   IsRunForRumors(bool value);
        bool   IsSpeechChallenge();
        void   IsSpeechChallenge(bool value);
        bool   IsSayOnceADay();
        void   IsSayOnceADay(bool value);
        bool   IsAlwaysDarken();
        void   IsAlwaysDarken(bool value);
        bool   IsFlagMask(UINT16 Mask, bool Exact=false);
        void   SetFlagMask(UINT16 Mask);

        bool   IsBeginScriptEnabled();
        void   IsBeginScriptEnabled(bool value);
        bool   IsBeginScriptFlagMask(UINT16 Mask, bool Exact=false);
        void   SetBeginScriptFlagMask(UINT16 Mask);

        bool   IsEndScriptEnabled();
        void   IsEndScriptEnabled(bool value);
        bool   IsEndScriptFlagMask(UINT16 Mask, bool Exact=false);
        void   SetEndScriptFlagMask(UINT16 Mask);

        bool   IsTopic();
        void   IsTopic(bool value);
        bool   IsConversation();
        void   IsConversation(bool value);
        bool   IsCombat();
        void   IsCombat(bool value);
        bool   IsPersuasion();
        void   IsPersuasion(bool value);
        bool   IsDetection();
        void   IsDetection(bool value);
        bool   IsService();
        void   IsService(bool value);
        bool   IsMisc();
        void   IsMisc(bool value);
        bool   IsRadio();
        void   IsRadio(bool value);
        bool   IsDialogType(UINT8 Type);
        void   SetDialogType(UINT8 Type);

        bool   IsTarget();
        void   IsTarget(bool value);
        bool   IsSelf();
        void   IsSelf(bool value);
        bool   IsEither();
        void   IsEither(bool value);
        bool   IsSpeakerType(UINT8 Type);
        void   SetSpeakerType(UINT8 Type);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsVeryEasy();
        void   IsVeryEasy(bool value);
        bool   IsEasy();
        void   IsEasy(bool value);
        bool   IsAverage();
        void   IsAverage(bool value);
        bool   IsHard();
        void   IsHard(bool value);
        bool   IsVeryHard();
        void   IsVeryHard(bool value);
        bool   IsDifficultyType(UINT8 Type);
        void   SetDifficultyType(UINT8 Type);

        bool   IsBeginObject();
        void   IsBeginObject(bool value);
        bool   IsBeginQuest();
        void   IsBeginQuest(bool value);
        bool   IsBeginEffect();
        void   IsBeginEffect(bool value);
        bool   IsBeginType(UINT16 Type);
        void   SetBeginType(UINT16 Type);

        bool   IsEndObject();
        void   IsEndObject(bool value);
        bool   IsEndQuest();
        void   IsEndQuest(bool value);
        bool   IsEndEffect();
        void   IsEndEffect(bool value);
        bool   IsEndType(UINT16 Type);
        void   SetEndType(UINT16 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const INFORecord &other) const;
        bool operator !=(const INFORecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}