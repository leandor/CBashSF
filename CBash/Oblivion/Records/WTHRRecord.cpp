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
#include "..\..\Common.h"
#include "WTHRRecord.h"

namespace Ob
{
bool WTHRRecord::WTHRColors::operator ==(const WTHRColors &other) const
    {
    return (rise == other.rise &&
            day == other.day &&
            set == other.set &&
            night == other.night);
    }

bool WTHRRecord::WTHRColors::operator !=(const WTHRColors &other) const
    {
    return !(*this == other);
    }

bool WTHRRecord::WTHRNAM0::operator ==(const WTHRNAM0 &other) const
    {
    return (upperSky == other.upperSky &&
            fog == other.fog &&
            lowerClouds == other.lowerClouds &&
            ambient == other.ambient &&
            sunlight == other.sunlight &&
            sun == other.sun &&
            stars == other.stars &&
            lowerSky == other.lowerSky &&
            horizon == other.horizon &&
            upperClouds == other.upperClouds);
    }

bool WTHRRecord::WTHRNAM0::operator !=(const WTHRNAM0 &other) const
    {
    return !(*this == other);
    }

WTHRRecord::WTHRFNAM::WTHRFNAM():
    fogDayNear(0.0f),
    fogDayFar(0.0f),
    fogNightNear(0.0f),
    fogNightFar(0.0f)
    {
    //
    }

WTHRRecord::WTHRFNAM::~WTHRFNAM()
    {
    //
    }

bool WTHRRecord::WTHRFNAM::operator ==(const WTHRFNAM &other) const
    {
    return (AlmostEqual(fogDayNear,other.fogDayNear,2) &&
            AlmostEqual(fogDayFar,other.fogDayFar,2) &&
            AlmostEqual(fogNightNear,other.fogNightNear,2) &&
            AlmostEqual(fogNightFar,other.fogNightFar,2));
    }

bool WTHRRecord::WTHRFNAM::operator !=(const WTHRFNAM &other) const
    {
    return !(*this == other);
    }

WTHRRecord::WTHRHNAM::WTHRHNAM():
    eyeAdaptSpeed(0.0f),
    blurRadius(0.0f),
    blurPasses(0.0f),
    emissiveMult(0.0f),
    targetLum(0.0f),
    upperLumClamp(0.0f),
    brightScale(0.0f),
    brightClamp(0.0f),
    lumRampNoTex(0.0f),
    lumRampMin(0.0f),
    lumRampMax(0.0f),
    sunlightDimmer(0.0f),
    grassDimmer(0.0f),
    treeDimmer(0.0f)
    {
    //
    }

WTHRRecord::WTHRHNAM::~WTHRHNAM()
    {
    //
    }

bool WTHRRecord::WTHRHNAM::operator ==(const WTHRHNAM &other) const
    {
    return (AlmostEqual(eyeAdaptSpeed,other.eyeAdaptSpeed,2) &&
            AlmostEqual(blurRadius,other.blurRadius,2) &&
            AlmostEqual(blurPasses,other.blurPasses,2) &&
            AlmostEqual(emissiveMult,other.emissiveMult,2) &&
            AlmostEqual(targetLum,other.targetLum,2) &&
            AlmostEqual(upperLumClamp,other.upperLumClamp,2) &&
            AlmostEqual(brightScale,other.brightScale,2) &&
            AlmostEqual(brightClamp,other.brightClamp,2) &&
            AlmostEqual(lumRampNoTex,other.lumRampNoTex,2) &&
            AlmostEqual(lumRampMin,other.lumRampMin,2) &&
            AlmostEqual(lumRampMax,other.lumRampMax,2) &&
            AlmostEqual(sunlightDimmer,other.sunlightDimmer,2) &&
            AlmostEqual(grassDimmer,other.grassDimmer,2) &&
            AlmostEqual(treeDimmer,other.treeDimmer,2));
    }

bool WTHRRecord::WTHRHNAM::operator !=(const WTHRHNAM &other) const
    {
    return !(*this == other);
    }

WTHRRecord::WTHRDATA::WTHRDATA():
    windSpeed(0),
    lowerCloudSpeed(0),
    upperCloudSpeed(0),
    transDelta(0),
    sunGlare(0),
    sunDamage(0),
    rainFadeIn(0),
    rainFadeOut(0),
    boltFadeIn(0),
    boltFadeOut(0),
    boltFrequency(0),
    weatherType(0),
    boltRed(0),
    boltGreen(0),
    boltBlue(0)
    {
    //
    }

WTHRRecord::WTHRDATA::~WTHRDATA()
    {
    //
    }

bool WTHRRecord::WTHRDATA::operator ==(const WTHRDATA &other) const
    {
    return (windSpeed == other.windSpeed &&
            lowerCloudSpeed == other.lowerCloudSpeed &&
            upperCloudSpeed == other.upperCloudSpeed &&
            transDelta == other.transDelta &&
            sunGlare == other.sunGlare &&
            sunDamage == other.sunDamage &&
            rainFadeIn == other.rainFadeIn &&
            rainFadeOut == other.rainFadeOut &&
            boltFadeIn == other.boltFadeIn &&
            boltFadeOut == other.boltFadeOut &&
            boltFrequency == other.boltFrequency &&
            weatherType == other.weatherType &&
            boltRed == other.boltRed &&
            boltGreen == other.boltGreen &&
            boltBlue == other.boltBlue);
    }

bool WTHRRecord::WTHRDATA::operator !=(const WTHRDATA &other) const
    {
    return !(*this == other);
    }

WTHRRecord::WTHRSNAM::WTHRSNAM():
    sound(0),
    type(0)
    {
    //
    }

WTHRRecord::WTHRSNAM::~WTHRSNAM()
    {
    //
    }

bool WTHRRecord::WTHRSNAM::IsDefault()
    {
    return (type == eDefault);
    }

void WTHRRecord::WTHRSNAM::IsDefault(bool value)
    {
    if(value)
        type = eDefault;
    else if(IsDefault())
        type = ePrecip;
    }

bool WTHRRecord::WTHRSNAM::IsPrecip()
    {
    return (type == ePrecip);
    }

void WTHRRecord::WTHRSNAM::IsPrecip(bool value)
    {
    if(value)
        type = ePrecip;
    else if(IsPrecip())
        type = eDefault;
    }

bool WTHRRecord::WTHRSNAM::IsPrecipitation()
    {
    return (type == ePrecip);
    }

void WTHRRecord::WTHRSNAM::IsPrecipitation(bool value)
    {
    if(value)
        type = ePrecip;
    else if(IsPrecipitation())
        type = eDefault;
    }

bool WTHRRecord::WTHRSNAM::IsWind()
    {
    return (type == eWind);
    }

void WTHRRecord::WTHRSNAM::IsWind(bool value)
    {
    if(value)
        type = eWind;
    else if(IsWind())
        type = eDefault;
    }

bool WTHRRecord::WTHRSNAM::IsThunder()
    {
    return (type == eThunder);
    }

void WTHRRecord::WTHRSNAM::IsThunder(bool value)
    {
    if(value)
        type = eThunder;
    else if(IsThunder())
        type = eDefault;
    }

bool WTHRRecord::WTHRSNAM::IsType(UINT32 Type)
    {
    return (type == Type);
    }

void WTHRRecord::WTHRSNAM::SetType(UINT32 Type)
    {
    type = Type;
    }

bool WTHRRecord::WTHRSNAM::operator ==(const WTHRSNAM &other) const
    {
    return (sound == other.sound &&
            type == other.type);
    }
bool WTHRRecord::WTHRSNAM::operator !=(const WTHRSNAM &other) const
    {
    return !(*this == other);
    }

WTHRRecord::WTHRRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

WTHRRecord::WTHRRecord(WTHRRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    CNAM = srcRecord->CNAM;
    DNAM = srcRecord->DNAM;
    MODL = srcRecord->MODL;
    NAM0 = srcRecord->NAM0;
    FNAM = srcRecord->FNAM;
    HNAM = srcRecord->HNAM;
    DATA = srcRecord->DATA;
    Sounds = srcRecord->Sounds;
    }

WTHRRecord::~WTHRRecord()
    {
    //
    }

bool WTHRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < Sounds.value.size(); ListIndex++)
        op.Accept(Sounds.value[ListIndex]->sound);

    return op.Stop();
    }

bool WTHRRecord::IsPleasant()
    {
    return (DATA.value.weatherType & ePleasant) != 0;
    }

void WTHRRecord::IsPleasant(bool value)
    {
    if(value)
        {
        DATA.value.weatherType |= ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsPleasant())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsCloudy()
    {
    return (DATA.value.weatherType & eCloudy) != 0;
    }

void WTHRRecord::IsCloudy(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType |= eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsCloudy())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsRainy()
    {
    return (DATA.value.weatherType & eRainy) != 0;
    }

void WTHRRecord::IsRainy(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType |= eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsRainy())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsSnow()
    {
    return (DATA.value.weatherType & eSnow) != 0;
    }

void WTHRRecord::IsSnow(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType |= eSnow;
        }
    else if(IsSnow())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsNone()
    {
    return IsPleasant() == false && IsCloudy() == false && IsRainy() == false && IsSnow() == false;
    }

void WTHRRecord::IsNone(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsNone())
        {
        DATA.value.weatherType |= ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsUnk1()
    {
    return (DATA.value.weatherType & fUnk1) != 0;
    }

void WTHRRecord::IsUnk1(bool value)
    {
    DATA.value.weatherType = value ? (DATA.value.weatherType | fUnk1) : (DATA.value.weatherType & ~fUnk1);
    }

bool WTHRRecord::IsUnk2()
    {
    return (DATA.value.weatherType & fUnk2) != 0;
    }

void WTHRRecord::IsUnk2(bool value)
    {
    DATA.value.weatherType = value ? (DATA.value.weatherType | fUnk2) : (DATA.value.weatherType & ~fUnk2);
    }

bool WTHRRecord::IsType(UINT8 Type)
    {
    return (DATA.value.weatherType == Type);
    }

void WTHRRecord::SetType(UINT8 Type)
    {
    DATA.value.weatherType = Type;
    }

bool WTHRRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.weatherType & Mask) == Mask) : ((DATA.value.weatherType & Mask) != 0);
    }

void WTHRRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.weatherType = Mask;
    }

UINT32 WTHRRecord::GetType()
    {
    return REV32(WTHR);
    }

STRING WTHRRecord::GetStrType()
    {
    return "WTHR";
    }

SINT32 WTHRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM0):
                NAM0.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                Sounds.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  WTHR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 WTHRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    CNAM.Unload();
    DNAM.Unload();
    MODL.Unload();
    NAM0.Unload();
    FNAM.Unload();
    HNAM.Unload();
    DATA.Unload();
    Sounds.Unload();
    return 1;
    }

SINT32 WTHRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(CNAM);
    WRITE(DNAM);
    MODL.Write(writer);
    WRITE(NAM0);
    WRITE(FNAM);
    WRITE(HNAM);
    WRITE(DATA);
    WRITEAS(Sounds,SNAM);
    return -1;
    }

bool WTHRRecord::operator ==(const WTHRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            CNAM.equalsi(other.CNAM) &&
            DNAM.equalsi(other.DNAM) &&
            MODL == other.MODL &&
            NAM0 == other.NAM0 &&
            FNAM == other.FNAM &&
            HNAM == other.HNAM &&
            DATA == other.DATA &&
            Sounds == other.Sounds);
    }

bool WTHRRecord::operator !=(const WTHRRecord &other) const
    {
    return !(*this == other);
    }

bool WTHRRecord::equals(Record *other)
    {
    return *this == *(WTHRRecord *)other;
    }
}