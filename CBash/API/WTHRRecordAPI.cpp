# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
#include "..\Common.h"
#include "..\Records\WTHRRecord.h"

int WTHRRecord::CreateListElement(const unsigned int subField)
    {
    ReqRecordField<WTHRSNAM> *curSNAM = NULL;
    switch(subField)
        {
        case 204: //sounds
            curSNAM = new ReqRecordField<WTHRSNAM>;
            Sounds.push_back(curSNAM);
            return (int)Sounds.size() - 1;
        default:
            return -1;
        }
    }

int WTHRRecord::DeleteListElement(const unsigned int subField)
    {
    ReqRecordField<WTHRSNAM> *curSNAM = NULL;
    switch(subField)
        {
        case 204: //sounds
            curSNAM = Sounds.back();
            delete curSNAM;
            Sounds.pop_back();
            return (int)Sounds.size() - 1;
        default:
            return -1;
        }
    }

int WTHRRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //lowerLayer
            return STRING_FIELD;
        case 7: //upperLayer
            return STRING_FIELD;
        case 8: //modPath
            return STRING_FIELD;
        case 9: //modb
            return FLOAT_FIELD;
        case 10: //modt_p
            return BYTES_FIELD;
        case 11: //upperSky.rise.red
            return UBYTE_FIELD;
        case 12: //upperSky.rise.green
            return UBYTE_FIELD;
        case 13: //upperSky.rise.blue
            return UBYTE_FIELD;
        case 14: //upperSky.rise.unused1
            return BYTES_FIELD;
        case 15: //upperSky.day.red
            return UBYTE_FIELD;
        case 16: //upperSky.day.green
            return UBYTE_FIELD;
        case 17: //upperSky.day.blue
            return UBYTE_FIELD;
        case 18: //upperSky.day.unused1
            return BYTES_FIELD;
        case 19: //upperSky.set.red
            return UBYTE_FIELD;
        case 20: //upperSky.set.green
            return UBYTE_FIELD;
        case 21: //upperSky.set.blue
            return UBYTE_FIELD;
        case 22: //upperSky.set.unused1
            return BYTES_FIELD;
        case 23: //upperSky.night.red
            return UBYTE_FIELD;
        case 24: //upperSky.night.green
            return UBYTE_FIELD;
        case 25: //upperSky.night.blue
            return UBYTE_FIELD;
        case 26: //upperSky.night.unused1
            return BYTES_FIELD;
        case 27: //fog.rise.red
            return UBYTE_FIELD;
        case 28: //fog.rise.green
            return UBYTE_FIELD;
        case 29: //fog.rise.blue
            return UBYTE_FIELD;
        case 30: //fog.rise.unused1
            return BYTES_FIELD;
        case 31: //fog.day.red
            return UBYTE_FIELD;
        case 32: //fog.day.green
            return UBYTE_FIELD;
        case 33: //fog.day.blue
            return UBYTE_FIELD;
        case 34: //fog.day.unused1
            return BYTES_FIELD;
        case 35: //fog.set.red
            return UBYTE_FIELD;
        case 36: //fog.set.green
            return UBYTE_FIELD;
        case 37: //fog.set.blue
            return UBYTE_FIELD;
        case 38: //fog.set.unused1
            return BYTES_FIELD;
        case 39: //fog.night.red
            return UBYTE_FIELD;
        case 40: //fog.night.green
            return UBYTE_FIELD;
        case 41: //fog.night.blue
            return UBYTE_FIELD;
        case 42: //fog.night.unused1
            return BYTES_FIELD;
        case 43: //lowerClouds.rise.red
            return UBYTE_FIELD;
        case 44: //lowerClouds.rise.green
            return UBYTE_FIELD;
        case 45: //lowerClouds.rise.blue
            return UBYTE_FIELD;
        case 46: //lowerClouds.unused1
            return BYTES_FIELD;
        case 47: //lowerClouds.day.red
            return UBYTE_FIELD;
        case 48: //lowerClouds.day.green
            return UBYTE_FIELD;
        case 49: //lowerClouds.day.blue
            return UBYTE_FIELD;
        case 50: //lowerClouds.day.unused1
            return BYTES_FIELD;
        case 51: //lowerClouds.set.red
            return UBYTE_FIELD;
        case 52: //lowerClouds.set.green
            return UBYTE_FIELD;
        case 53: //lowerClouds.set.blue
            return UBYTE_FIELD;
        case 54: //lowerClouds.set.unused1
            return BYTES_FIELD;
        case 55: //lowerClouds.night.red
            return UBYTE_FIELD;
        case 56: //lowerClouds.night.green
            return UBYTE_FIELD;
        case 57: //lowerClouds.night.blue
            return UBYTE_FIELD;
        case 58: //lowerClouds.night.unused1
            return BYTES_FIELD;
        case 59: //ambient.rise.red
            return UBYTE_FIELD;
        case 60: //ambient.rise.green
            return UBYTE_FIELD;
        case 61: //ambient.rise.blue
            return UBYTE_FIELD;
        case 62: //ambient.unused1
            return BYTES_FIELD;
        case 63: //ambient.day.red
            return UBYTE_FIELD;
        case 64: //ambient.day.green
            return UBYTE_FIELD;
        case 65: //ambient.day.blue
            return UBYTE_FIELD;
        case 66: //ambient.day.unused1
            return BYTES_FIELD;
        case 67: //ambient.set.red
            return UBYTE_FIELD;
        case 68: //ambient.set.green
            return UBYTE_FIELD;
        case 69: //ambient.set.blue
            return UBYTE_FIELD;
        case 70: //ambient.set.unused1
            return BYTES_FIELD;
        case 71: //ambient.night.red
            return UBYTE_FIELD;
        case 72: //ambient.night.green
            return UBYTE_FIELD;
        case 73: //ambient.night.blue
            return UBYTE_FIELD;
        case 74: //ambient.night.unused1
            return BYTES_FIELD;
        case 75: //sunlight.rise.red
            return UBYTE_FIELD;
        case 76: //sunlight.rise.green
            return UBYTE_FIELD;
        case 77: //sunlight.rise.blue
            return UBYTE_FIELD;
        case 78: //sunlight.rise.unused1
            return BYTES_FIELD;
        case 79: //sunlight.day.red
            return UBYTE_FIELD;
        case 80: //sunlight.day.green
            return UBYTE_FIELD;
        case 81: //sunlight.day.blue
            return UBYTE_FIELD;
        case 82: //sunlight.day.unused1
            return BYTES_FIELD;
        case 83: //sunlight.set.red
            return UBYTE_FIELD;
        case 84: //sunlight.set.green
            return UBYTE_FIELD;
        case 85: //sunlight.set.blue
            return UBYTE_FIELD;
        case 86: //sunlight.set.unused1
            return BYTES_FIELD;
        case 87: //sunlight.night.red
            return UBYTE_FIELD;
        case 88: //sunlight.night.green
            return UBYTE_FIELD;
        case 89: //sunlight.night.blue
            return UBYTE_FIELD;
        case 90: //sunlight.night.unused1
            return BYTES_FIELD;
        case 91: //sun.rise.red
            return UBYTE_FIELD;
        case 92: //sun.rise.green
            return UBYTE_FIELD;
        case 93: //sun.rise.blue
            return UBYTE_FIELD;
        case 94: //sun.rise.unused1
            return BYTES_FIELD;
        case 95: //sun.day.red
            return UBYTE_FIELD;
        case 96: //sun.day.green
            return UBYTE_FIELD;
        case 97: //sun.day.blue
            return UBYTE_FIELD;
        case 98: //sun.day.unused1
            return BYTES_FIELD;
        case 99: //sun.set.red
            return UBYTE_FIELD;
        case 100: //sun.set.green
            return UBYTE_FIELD;
        case 101: //sun.set.blue
            return UBYTE_FIELD;
        case 102: //sun.set.unused1
            return BYTES_FIELD;
        case 103: //sun.night.red
            return UBYTE_FIELD;
        case 104: //sun.night.green
            return UBYTE_FIELD;
        case 105: //sun.night.blue
            return UBYTE_FIELD;
        case 106: //sun.night.unused1
            return BYTES_FIELD;
        case 107: //stars.rise.red
            return UBYTE_FIELD;
        case 108: //stars.rise.green
            return UBYTE_FIELD;
        case 109: //stars.rise.blue
            return UBYTE_FIELD;
        case 110: //stars.rise.unused1
            return BYTES_FIELD;
        case 111: //stars.day.red
            return UBYTE_FIELD;
        case 112: //stars.day.green
            return UBYTE_FIELD;
        case 113: //stars.day.blue
            return UBYTE_FIELD;
        case 114: //stars.day.unused1
            return BYTES_FIELD;
        case 115: //stars.set.red
            return UBYTE_FIELD;
        case 116: //stars.set.green
            return UBYTE_FIELD;
        case 117: //stars.set.blue
            return UBYTE_FIELD;
        case 118: //stars.set.unused1
            return BYTES_FIELD;
        case 119: //stars.night.red
            return UBYTE_FIELD;
        case 120: //stars.night.green
            return UBYTE_FIELD;
        case 121: //stars.night.blue
            return UBYTE_FIELD;
        case 122: //stars.night.unused1
            return BYTES_FIELD;
        case 123: //lowerSky.rise.red
            return UBYTE_FIELD;
        case 124: //lowerSky.rise.green
            return UBYTE_FIELD;
        case 125: //lowerSky.rise.blue
            return UBYTE_FIELD;
        case 126: //lowerSky.rise.unused1
            return BYTES_FIELD;
        case 127: //lowerSky.day.red
            return UBYTE_FIELD;
        case 128: //lowerSky.day.green
            return UBYTE_FIELD;
        case 129: //lowerSky.day.blue
            return UBYTE_FIELD;
        case 130: //lowerSky.day.unused1
            return BYTES_FIELD;
        case 131: //lowerSky.set.red
            return UBYTE_FIELD;
        case 132: //lowerSky.set.green
            return UBYTE_FIELD;
        case 133: //lowerSky.set.blue
            return UBYTE_FIELD;
        case 134: //lowerSky.set.unused1
            return BYTES_FIELD;
        case 135: //lowerSky.night.red
            return UBYTE_FIELD;
        case 136: //lowerSky.night.green
            return UBYTE_FIELD;
        case 137: //lowerSky.night.blue
            return UBYTE_FIELD;
        case 138: //lowerSky.night.unused1
            return BYTES_FIELD;
        case 139: //horizon.rise.red
            return UBYTE_FIELD;
        case 140: //horizon.rise.green
            return UBYTE_FIELD;
        case 141: //horizon.rise.blue
            return UBYTE_FIELD;
        case 142: //horizon.rise.unused1
            return BYTES_FIELD;
        case 143: //horizon.day.red
            return UBYTE_FIELD;
        case 144: //horizon.day.green
            return UBYTE_FIELD;
        case 145: //horizon.day.blue
            return UBYTE_FIELD;
        case 146: //horizon.day.unused1
            return BYTES_FIELD;
        case 147: //horizon.set.red
            return UBYTE_FIELD;
        case 148: //horizon.set.green
            return UBYTE_FIELD;
        case 149: //horizon.set.blue
            return UBYTE_FIELD;
        case 150: //horizon.set.unused1
            return BYTES_FIELD;
        case 151: //horizon.night.red
            return UBYTE_FIELD;
        case 152: //horizon.night.green
            return UBYTE_FIELD;
        case 153: //horizon.night.blue
            return UBYTE_FIELD;
        case 154: //horizon.night.unused1
            return BYTES_FIELD;
        case 155: //upperClouds.rise.red
            return UBYTE_FIELD;
        case 156: //upperClouds.rise.green
            return UBYTE_FIELD;
        case 157: //upperClouds.rise.blue
            return UBYTE_FIELD;
        case 158: //upperClouds.rise.unused1
            return BYTES_FIELD;
        case 159: //upperClouds.day.red
            return UBYTE_FIELD;
        case 160: //upperClouds.day.green
            return UBYTE_FIELD;
        case 161: //upperClouds.day.blue
            return UBYTE_FIELD;
        case 162: //upperClouds.day.unused1
            return BYTES_FIELD;
        case 163: //upperClouds.set.red
            return UBYTE_FIELD;
        case 164: //upperClouds.set.green
            return UBYTE_FIELD;
        case 165: //upperClouds.set.blue
            return UBYTE_FIELD;
        case 166: //upperClouds.set.unused1
            return BYTES_FIELD;
        case 167: //upperClouds.night.red
            return UBYTE_FIELD;
        case 168: //upperClouds.night.green
            return UBYTE_FIELD;
        case 169: //upperClouds.night.blue
            return UBYTE_FIELD;
        case 170: //upperClouds.night.unused1
            return BYTES_FIELD;

        case 171: //fogDayNear
            return FLOAT_FIELD;
        case 172: //fogDayFar
            return FLOAT_FIELD;
        case 173: //fogNightNear
            return FLOAT_FIELD;
        case 174: //fogNightFar
            return FLOAT_FIELD;

        case 175: //eyeAdaptSpeed
            return FLOAT_FIELD;
        case 176: //blurRadius
            return FLOAT_FIELD;
        case 177: //blurPasses
            return FLOAT_FIELD;
        case 178: //emissiveMult
            return FLOAT_FIELD;
        case 179: //targetLum
            return FLOAT_FIELD;
        case 180: //upperLumClamp
            return FLOAT_FIELD;
        case 181: //brightScale
            return FLOAT_FIELD;
        case 182: //brightClamp
            return FLOAT_FIELD;
        case 183: //lumRampNoTex
            return FLOAT_FIELD;
        case 184: //lumRampMin
            return FLOAT_FIELD;
        case 185: //lumRampMax
            return FLOAT_FIELD;
        case 186: //sunlightDimmer
            return FLOAT_FIELD;
        case 187: //grassDimmer
            return FLOAT_FIELD;
        case 188: //treeDimmer
            return FLOAT_FIELD;

        case 189: //windSpeed
            return UBYTE_FIELD;
        case 190: //lowerCloudSpeed
            return UBYTE_FIELD;
        case 191: //upperCloudSpeed
            return UBYTE_FIELD;
        case 192: //transDelta
            return UBYTE_FIELD;
        case 193: //sunGlare
            return UBYTE_FIELD;
        case 194: //sunDamage
            return UBYTE_FIELD;
        case 195: //rainFadeIn
            return UBYTE_FIELD;
        case 196: //rainFadeOut
            return UBYTE_FIELD;
        case 197: //boltFadeIn
            return UBYTE_FIELD;
        case 198: //boltFadeOut
            return UBYTE_FIELD;
        case 199: //boltFrequency
            return UBYTE_FIELD;
        case 200: //weatherType
            return UBYTE_FIELD;
        case 201: //boltRed
            return UBYTE_FIELD;
        case 202: //boltGreen
            return UBYTE_FIELD;
        case 203: //boltBlue
            return UBYTE_FIELD;

        case 204: //sounds
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * WTHRRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //lowerLayer
            return CNAM.value;
        case 7: //upperLayer
            return DNAM.value;
        case 8: //modPath
            return MODL.MODL.value;
        case 9: //modb
            return &MODL.MODB.value.MODB;
        case 11: //upperSky.rise.red
            return &NAM0.value.upperSky.rise.red;
        case 12: //upperSky.rise.green
            return &NAM0.value.upperSky.rise.green;
        case 13: //upperSky.rise.blue
            return &NAM0.value.upperSky.rise.blue;
        case 15: //upperSky.day.red
            return &NAM0.value.upperSky.day.red;
        case 16: //upperSky.day.green
            return &NAM0.value.upperSky.day.green;
        case 17: //upperSky.day.blue
            return &NAM0.value.upperSky.day.blue;
        case 19: //upperSky.set.red
            return &NAM0.value.upperSky.set.red;
        case 20: //upperSky.set.green
            return &NAM0.value.upperSky.set.green;
        case 21: //upperSky.set.blue
            return &NAM0.value.upperSky.set.blue;
        case 23: //upperSky.night.red
            return &NAM0.value.upperSky.night.red;
        case 24: //upperSky.night.green
            return &NAM0.value.upperSky.night.green;
        case 25: //upperSky.night.blue
            return &NAM0.value.upperSky.night.blue;
        case 27: //fog.rise.red
            return &NAM0.value.fog.rise.red;
        case 28: //fog.rise.green
            return &NAM0.value.fog.rise.green;
        case 29: //fog.rise.blue
            return &NAM0.value.fog.rise.blue;
        case 31: //fog.day.red
            return &NAM0.value.fog.day.red;
        case 32: //fog.day.green
            return &NAM0.value.fog.day.green;
        case 33: //fog.day.blue
            return &NAM0.value.fog.day.blue;
        case 35: //fog.set.red
            return &NAM0.value.fog.set.red;
        case 36: //fog.set.green
            return &NAM0.value.fog.set.green;
        case 37: //fog.set.blue
            return &NAM0.value.fog.set.blue;
        case 39: //fog.night.red
            return &NAM0.value.fog.night.red;
        case 40: //fog.night.green
            return &NAM0.value.fog.night.green;
        case 41: //fog.night.blue
            return &NAM0.value.fog.night.blue;
        case 43: //lowerClouds.rise.red
            return &NAM0.value.lowerClouds.rise.red;
        case 44: //lowerClouds.rise.green
            return &NAM0.value.lowerClouds.rise.green;
        case 45: //lowerClouds.rise.blue
            return &NAM0.value.lowerClouds.rise.blue;
        case 47: //lowerClouds.day.red
            return &NAM0.value.lowerClouds.day.red;
        case 48: //lowerClouds.day.green
            return &NAM0.value.lowerClouds.day.green;
        case 49: //lowerClouds.day.blue
            return &NAM0.value.lowerClouds.day.blue;
        case 51: //lowerClouds.set.red
            return &NAM0.value.lowerClouds.set.red;
        case 52: //lowerClouds.set.green
            return &NAM0.value.lowerClouds.set.green;
        case 53: //lowerClouds.set.blue
            return &NAM0.value.lowerClouds.set.blue;
        case 55: //lowerClouds.night.red
            return &NAM0.value.lowerClouds.night.red;
        case 56: //lowerClouds.night.green
            return &NAM0.value.lowerClouds.night.green;
        case 57: //lowerClouds.night.blue
            return &NAM0.value.lowerClouds.night.blue;
        case 59: //ambient.rise.red
            return &NAM0.value.ambient.rise.red;
        case 60: //ambient.rise.green
            return &NAM0.value.ambient.rise.green;
        case 61: //ambient.rise.blue
            return &NAM0.value.ambient.rise.blue;
        case 63: //ambient.day.red
            return &NAM0.value.ambient.day.red;
        case 64: //ambient.day.green
            return &NAM0.value.ambient.day.green;
        case 65: //ambient.day.blue
            return &NAM0.value.ambient.day.blue;
        case 67: //ambient.set.red
            return &NAM0.value.ambient.set.red;
        case 68: //ambient.set.green
            return &NAM0.value.ambient.set.green;
        case 69: //ambient.set.blue
            return &NAM0.value.ambient.set.blue;
        case 71: //ambient.night.red
            return &NAM0.value.ambient.night.red;
        case 72: //ambient.night.green
            return &NAM0.value.ambient.night.green;
        case 73: //ambient.night.blue
            return &NAM0.value.ambient.night.blue;
        case 75: //sunlight.rise.red
            return &NAM0.value.sunlight.rise.red;
        case 76: //sunlight.rise.green
            return &NAM0.value.sunlight.rise.green;
        case 77: //sunlight.rise.blue
            return &NAM0.value.sunlight.rise.blue;
        case 79: //sunlight.day.red
            return &NAM0.value.sunlight.day.red;
        case 80: //sunlight.day.green
            return &NAM0.value.sunlight.day.green;
        case 81: //sunlight.day.blue
            return &NAM0.value.sunlight.day.blue;
        case 83: //sunlight.set.red
            return &NAM0.value.sunlight.set.red;
        case 84: //sunlight.set.green
            return &NAM0.value.sunlight.set.green;
        case 85: //sunlight.set.blue
            return &NAM0.value.sunlight.set.blue;
        case 87: //sunlight.night.red
            return &NAM0.value.sunlight.night.red;
        case 88: //sunlight.night.green
            return &NAM0.value.sunlight.night.green;
        case 89: //sunlight.night.blue
            return &NAM0.value.sunlight.night.blue;
        case 91: //sun.rise.red
            return &NAM0.value.sun.rise.red;
        case 92: //sun.rise.green
            return &NAM0.value.sun.rise.green;
        case 93: //sun.rise.blue
            return &NAM0.value.sun.rise.blue;
        case 95: //sun.day.red
            return &NAM0.value.sun.day.red;
        case 96: //sun.day.green
            return &NAM0.value.sun.day.green;
        case 97: //sun.day.blue
            return &NAM0.value.sun.day.blue;
        case 99: //sun.set.red
            return &NAM0.value.sun.set.red;
        case 100: //sun.set.green
            return &NAM0.value.sun.set.green;
        case 101: //sun.set.blue
            return &NAM0.value.sun.set.blue;
        case 103: //sun.night.red
            return &NAM0.value.sun.night.red;
        case 104: //sun.night.green
            return &NAM0.value.sun.night.green;
        case 105: //sun.night.blue
            return &NAM0.value.sun.night.blue;
        case 107: //stars.rise.red
            return &NAM0.value.stars.rise.red;
        case 108: //stars.rise.green
            return &NAM0.value.stars.rise.green;
        case 109: //stars.rise.blue
            return &NAM0.value.stars.rise.blue;
        case 111: //stars.day.red
            return &NAM0.value.stars.day.red;
        case 112: //stars.day.green
            return &NAM0.value.stars.day.green;
        case 113: //stars.day.blue
            return &NAM0.value.stars.day.blue;
        case 115: //stars.set.red
            return &NAM0.value.stars.set.red;
        case 116: //stars.set.green
            return &NAM0.value.stars.set.green;
        case 117: //stars.set.blue
            return &NAM0.value.stars.set.blue;
        case 119: //stars.night.red
            return &NAM0.value.stars.night.red;
        case 120: //stars.night.green
            return &NAM0.value.stars.night.green;
        case 121: //stars.night.blue
            return &NAM0.value.stars.night.blue;
        case 123: //lowerSky.rise.red
            return &NAM0.value.lowerSky.rise.red;
        case 124: //lowerSky.rise.green
            return &NAM0.value.lowerSky.rise.green;
        case 125: //lowerSky.rise.blue
            return &NAM0.value.lowerSky.rise.blue;
        case 127: //lowerSky.day.red
            return &NAM0.value.lowerSky.day.red;
        case 128: //lowerSky.day.green
            return &NAM0.value.lowerSky.day.green;
        case 129: //lowerSky.day.blue
            return &NAM0.value.lowerSky.day.blue;
        case 131: //lowerSky.set.red
            return &NAM0.value.lowerSky.set.red;
        case 132: //lowerSky.set.green
            return &NAM0.value.lowerSky.set.green;
        case 133: //lowerSky.set.blue
            return &NAM0.value.lowerSky.set.blue;
        case 135: //lowerSky.night.red
            return &NAM0.value.lowerSky.night.red;
        case 136: //lowerSky.night.green
            return &NAM0.value.lowerSky.night.green;
        case 137: //lowerSky.night.blue
            return &NAM0.value.lowerSky.night.blue;
        case 139: //horizon.rise.red
            return &NAM0.value.horizon.rise.red;
        case 140: //horizon.rise.green
            return &NAM0.value.horizon.rise.green;
        case 141: //horizon.rise.blue
            return &NAM0.value.horizon.rise.blue;
        case 143: //horizon.day.red
            return &NAM0.value.horizon.day.red;
        case 144: //horizon.day.green
            return &NAM0.value.horizon.day.green;
        case 145: //horizon.day.blue
            return &NAM0.value.horizon.day.blue;
        case 147: //horizon.set.red
            return &NAM0.value.horizon.set.red;
        case 148: //horizon.set.green
            return &NAM0.value.horizon.set.green;
        case 149: //horizon.set.blue
            return &NAM0.value.horizon.set.blue;
        case 151: //horizon.night.red
            return &NAM0.value.horizon.night.red;
        case 152: //horizon.night.green
            return &NAM0.value.horizon.night.green;
        case 153: //horizon.night.blue
            return &NAM0.value.horizon.night.blue;
        case 155: //upperClouds.rise.red
            return &NAM0.value.upperClouds.rise.red;
        case 156: //upperClouds.rise.green
            return &NAM0.value.upperClouds.rise.green;
        case 157: //upperClouds.rise.blue
            return &NAM0.value.upperClouds.rise.blue;
        case 159: //upperClouds.day.red
            return &NAM0.value.upperClouds.day.red;
        case 160: //upperClouds.day.green
            return &NAM0.value.upperClouds.day.green;
        case 161: //upperClouds.day.blue
            return &NAM0.value.upperClouds.day.blue;
        case 163: //upperClouds.set.red
            return &NAM0.value.upperClouds.set.red;
        case 164: //upperClouds.set.green
            return &NAM0.value.upperClouds.set.green;
        case 165: //upperClouds.set.blue
            return &NAM0.value.upperClouds.set.blue;
        case 167: //upperClouds.night.red
            return &NAM0.value.upperClouds.night.red;
        case 168: //upperClouds.night.green
            return &NAM0.value.upperClouds.night.green;
        case 169: //upperClouds.night.blue
            return &NAM0.value.upperClouds.night.blue;

        case 171: //fogDayNear
            return &FNAM.value.fogDayNear;
        case 172: //fogDayFar
            return &FNAM.value.fogDayFar;
        case 173: //fogNightNear
            return &FNAM.value.fogNightNear;
        case 174: //fogNightFar
            return &FNAM.value.fogNightFar;

        case 175: //eyeAdaptSpeed
            return &HNAM.value.eyeAdaptSpeed;
        case 176: //blurRadius
            return &HNAM.value.blurRadius;
        case 177: //blurPasses
            return &HNAM.value.blurPasses;
        case 178: //emissiveMult
            return &HNAM.value.emissiveMult;
        case 179: //targetLum
            return &HNAM.value.targetLum;
        case 180: //upperLumClamp
            return &HNAM.value.upperLumClamp;
        case 181: //brightScale
            return &HNAM.value.brightScale;
        case 182: //brightClamp
            return &HNAM.value.brightClamp;
        case 183: //lumRampNoTex
            return &HNAM.value.lumRampNoTex;
        case 184: //lumRampMin
            return &HNAM.value.lumRampMin;
        case 185: //lumRampMax
            return &HNAM.value.lumRampMax;
        case 186: //sunlightDimmer
            return &HNAM.value.sunlightDimmer;
        case 187: //grassDimmer
            return &HNAM.value.grassDimmer;
        case 188: //treeDimmer
            return &HNAM.value.treeDimmer;

        case 189: //windSpeed
            return &DATA.value.windSpeed;
        case 190: //lowerCloudSpeed
            return &DATA.value.lowerCloudSpeed;
        case 191: //upperCloudSpeed
            return &DATA.value.upperCloudSpeed;
        case 192: //transDelta
            return &DATA.value.transDelta;
        case 193: //sunGlare
            return &DATA.value.sunGlare;
        case 194: //sunDamage
            return &DATA.value.sunDamage;
        case 195: //rainFadeIn
            return &DATA.value.rainFadeIn;
        case 196: //rainFadeOut
            return &DATA.value.rainFadeOut;
        case 197: //boltFadeIn
            return &DATA.value.boltFadeIn;
        case 198: //boltFadeOut
            return &DATA.value.boltFadeOut;
        case 199: //boltFrequency
            return &DATA.value.boltFrequency;
        case 200: //weatherType
            return &DATA.value.weatherType;
        case 201: //boltRed
            return &DATA.value.boltRed;
        case 202: //boltGreen
            return &DATA.value.boltGreen;
        case 203: //boltBlue
            return &DATA.value.boltBlue;
        default:
            return NULL;
        }
    }
unsigned int WTHRRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 10: //modt_p
            return MODL.MODT.size;
        case 14: //upperSky.rise.unused1
            return 1;
        case 18: //upperSky.day.unused1
            return 1;
        case 22: //upperSky.set.unused1
            return 1;
        case 26: //upperSky.night.unused1
            return 1;
        case 30: //fog.rise.unused1
            return 1;
        case 34: //fog.day.unused1
            return 1;
        case 38: //fog.set.unused1
            return 1;
        case 42: //fog.night.unused1
            return 1;
        case 46: //lowerClouds.rise.unused1
            return 1;
        case 50: //lowerClouds.day.unused1
            return 1;
        case 54: //lowerClouds.set.unused1
            return 1;
        case 58: //lowerClouds.night.unused1
            return 1;
        case 62: //ambient.rise.unused1
            return 1;
        case 66: //ambient.day.unused1
            return 1;
        case 70: //ambient.set.unused1
            return 1;
        case 74: //ambient.night.unused1
            return 1;
        case 78: //sunlight.rise.unused1
            return 1;
        case 82: //sunlight.day.unused1
            return 1;
        case 86: //sunlight.set.unused1
            return 1;
        case 90: //sunlight.night.unused1
            return 1;
        case 94: //sun.rise.unused1
            return 1;
        case 98: //sun.day.unused1
            return 1;
        case 102: //sun.set.unused1
            return 1;
        case 106: //sun.night.unused1
            return 1;
        case 110: //stars.rise.unused1
            return 1;
        case 114: //stars.day.unused1
            return 1;
        case 118: //stars.set.unused1
            return 1;
        case 122: //stars.night.unused1
            return 1;
        case 126: //lowerSky.rise.unused1
            return 1;
        case 130: //lowerSky.day.unused1
            return 1;
        case 134: //lowerSky.set.unused1
            return 1;
        case 138: //lowerSky.night.unused1
            return 1;
        case 142: //horizon.rise.unused1
            return 1;
        case 146: //horizon.day.unused1
            return 1;
        case 150: //horizon.set.unused1
            return 1;
        case 154: //horizon.night.unused1
            return 1;
        case 158: //upperClouds.rise.unused1
            return 1;
        case 162: //upperClouds.day.unused1
            return 1;
        case 166: //upperClouds.set.unused1
            return 1;
        case 170: //upperClouds.night.unused1
            return 1;
        default:
            return 0;
        }
    }

void WTHRRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 10: //modt_p
            *FieldValues = MODL.MODT.value;
            return;
        case 14: //upperSky.rise.unused1
            *FieldValues = &NAM0.value.upperSky.rise.unused1;
            return;
        case 18: //upperSky.day.unused1
            *FieldValues = &NAM0.value.upperSky.day.unused1;
            return;
        case 22: //upperSky.set.unused1
            *FieldValues = &NAM0.value.upperSky.set.unused1;
            return;
        case 26: //upperSky.night.unused1
            *FieldValues = &NAM0.value.upperSky.night.unused1;
            return;
        case 30: //fog.rise.unused1
            *FieldValues = &NAM0.value.fog.rise.unused1;
            return;
        case 34: //fog.day.unused1
            *FieldValues = &NAM0.value.fog.day.unused1;
            return;
        case 38: //fog.set.unused1
            *FieldValues = &NAM0.value.fog.set.unused1;
            return;
        case 42: //fog.night.unused1
            *FieldValues = &NAM0.value.fog.night.unused1;
            return;
        case 46: //lowerClouds.rise.unused1
            *FieldValues = &NAM0.value.lowerClouds.rise.unused1;
            return;
        case 50: //lowerClouds.day.unused1
            *FieldValues = &NAM0.value.lowerClouds.day.unused1;
            return;
        case 54: //lowerClouds.set.unused1
            *FieldValues = &NAM0.value.lowerClouds.set.unused1;
            return;
        case 58: //lowerClouds.night.unused1
            *FieldValues = &NAM0.value.lowerClouds.night.unused1;
            return;
        case 62: //ambient.rise.unused1
            *FieldValues = &NAM0.value.ambient.rise.unused1;
            return;
        case 66: //ambient.day.unused1
            *FieldValues = &NAM0.value.ambient.day.unused1;
            return;
        case 70: //ambient.set.unused1
            *FieldValues = &NAM0.value.ambient.set.unused1;
            return;
        case 74: //ambient.night.unused1
            *FieldValues = &NAM0.value.ambient.night.unused1;
            return;
        case 78: //sunlight.rise.unused1
            *FieldValues = &NAM0.value.sunlight.rise.unused1;
            return;
        case 82: //sunlight.day.unused1
            *FieldValues = &NAM0.value.sunlight.day.unused1;
            return;
        case 86: //sunlight.set.unused1
            *FieldValues = &NAM0.value.sunlight.set.unused1;
            return;
        case 90: //sunlight.night.unused1
            *FieldValues = &NAM0.value.sunlight.night.unused1;
            return;
        case 94: //sun.rise.unused1
            *FieldValues = &NAM0.value.sun.rise.unused1;
            return;
        case 98: //sun.day.unused1
            *FieldValues = &NAM0.value.sun.day.unused1;
            return;
        case 102: //sun.set.unused1
            *FieldValues = &NAM0.value.sun.set.unused1;
            return;
        case 106: //sun.night.unused1
            *FieldValues = &NAM0.value.sun.night.unused1;
            return;
        case 110: //stars.rise.unused1
            *FieldValues = &NAM0.value.stars.rise.unused1;
            return;
        case 114: //stars.day.unused1
            *FieldValues = &NAM0.value.stars.day.unused1;
            return;
        case 118: //stars.set.unused1
            *FieldValues = &NAM0.value.stars.set.unused1;
            return;
        case 122: //stars.night.unused1
            *FieldValues = &NAM0.value.stars.night.unused1;
            return;
        case 126: //lowerSky.rise.unused1
            *FieldValues = &NAM0.value.lowerSky.rise.unused1;
            return;
        case 130: //lowerSky.day.unused1
            *FieldValues = &NAM0.value.lowerSky.day.unused1;
            return;
        case 134: //lowerSky.set.unused1
            *FieldValues = &NAM0.value.lowerSky.set.unused1;
            return;
        case 138: //lowerSky.night.unused1
            *FieldValues = &NAM0.value.lowerSky.night.unused1;
            return;
        case 142: //horizon.rise.unused1
            *FieldValues = &NAM0.value.horizon.rise.unused1;
            return;
        case 146: //horizon.day.unused1
            *FieldValues = &NAM0.value.horizon.day.unused1;
            return;
        case 150: //horizon.set.unused1
            *FieldValues = &NAM0.value.horizon.set.unused1;
            return;
        case 154: //horizon.night.unused1
            *FieldValues = &NAM0.value.horizon.night.unused1;
            return;
        case 158: //upperClouds.rise.unused1
            *FieldValues = &NAM0.value.upperClouds.rise.unused1;
            return;
        case 162: //upperClouds.day.unused1
            *FieldValues = &NAM0.value.upperClouds.day.unused1;
            return;
        case 166: //upperClouds.set.unused1
            *FieldValues = &NAM0.value.upperClouds.set.unused1;
            return;
        case 170: //upperClouds.night.unused1
            *FieldValues = &NAM0.value.upperClouds.night.unused1;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

int WTHRRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 204: //sounds
            switch(listField)
                {
                case 1: //sound
                    return FID_FIELD;
                case 2: //type
                    return UINT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }
unsigned int WTHRRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 204: //sounds
            return (unsigned int)Sounds.size();
        default:
            return 0;
        }
    }

void * WTHRRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 204: //sounds
            if(listIndex >= Sounds.size())
                return NULL;
            switch(listField)
                {
                case 1: //sound
                    return &Sounds[listIndex]->value.sound;
                case 2: //type
                    return &Sounds[listIndex]->value.type;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void WTHRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //lowerLayer
            CNAM.Copy(FieldValue);
            break;
        case 7: //upperLayer
            DNAM.Copy(FieldValue);
            break;
        case 8: //modPath
            MODL.MODL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void WTHRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 9: //modb
            MODL.MODB.value.MODB = FieldValue;
            MODL.MODB.isLoaded = true;
            break;
        case 171: //fogDayNear
            FNAM.value.fogDayNear = FieldValue;
            break;
        case 172: //fogDayFar
            FNAM.value.fogDayFar = FieldValue;
            break;
        case 173: //fogNightNear
            FNAM.value.fogNightNear = FieldValue;
            break;
        case 174: //fogNightFar
            FNAM.value.fogNightFar = FieldValue;
            break;

        case 175: //eyeAdaptSpeed
            HNAM.value.eyeAdaptSpeed = FieldValue;
            break;
        case 176: //blurRadius
            HNAM.value.blurRadius = FieldValue;
            break;
        case 177: //blurPasses
            HNAM.value.blurPasses = FieldValue;
            break;
        case 178: //emissiveMult
            HNAM.value.emissiveMult = FieldValue;
            break;
        case 179: //targetLum
            HNAM.value.targetLum = FieldValue;
            break;
        case 180: //upperLumClamp
            HNAM.value.upperLumClamp = FieldValue;
            break;
        case 181: //brightScale
            HNAM.value.brightScale = FieldValue;
            break;
        case 182: //brightClamp
            HNAM.value.brightClamp = FieldValue;
            break;
        case 183: //lumRampNoTex
            HNAM.value.lumRampNoTex = FieldValue;
            break;
        case 184: //lumRampMin
            HNAM.value.lumRampMin = FieldValue;
            break;
        case 185: //lumRampMax
            HNAM.value.lumRampMax = FieldValue;
            break;
        case 186: //sunlightDimmer
            HNAM.value.sunlightDimmer = FieldValue;
            break;
        case 187: //grassDimmer
            HNAM.value.grassDimmer = FieldValue;
            break;
        case 188: //treeDimmer
            HNAM.value.treeDimmer = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WTHRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 10: //modt_p
            MODL.MODT.Copy(FieldValue, nSize);
            break;
        case 14: //upperSky.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.upperSky.rise.unused1 = FieldValue[0];
            break;
        case 18: //upperSky.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.upperSky.day.unused1 = FieldValue[0];
            break;
        case 22: //upperSky.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.upperSky.set.unused1 = FieldValue[0];
            break;
        case 26: //upperSky.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.upperSky.night.unused1 = FieldValue[0];
            break;
        case 30: //fog.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.fog.rise.unused1 = FieldValue[0];
            break;
        case 34: //fog.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.fog.day.unused1 = FieldValue[0];
            break;
        case 38: //fog.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.fog.set.unused1 = FieldValue[0];
            break;
        case 42: //fog.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.fog.night.unused1 = FieldValue[0];
            break;
        case 46: //lowerClouds.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.lowerClouds.rise.unused1 = FieldValue[0];
            break;
        case 50: //lowerClouds.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.lowerClouds.day.unused1 = FieldValue[0];
            break;
        case 54: //lowerClouds.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.lowerClouds.set.unused1 = FieldValue[0];
            break;
        case 58: //lowerClouds.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.lowerClouds.night.unused1 = FieldValue[0];
            break;
        case 62: //ambient.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.ambient.rise.unused1 = FieldValue[0];
            break;
        case 66: //ambient.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.ambient.day.unused1 = FieldValue[0];
            break;
        case 70: //ambient.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.ambient.set.unused1 = FieldValue[0];
            break;
        case 74: //ambient.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.ambient.night.unused1 = FieldValue[0];
            break;
        case 78: //sunlight.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.sunlight.rise.unused1 = FieldValue[0];
            break;
        case 82: //sunlight.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.sunlight.day.unused1 = FieldValue[0];
            break;
        case 86: //sunlight.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.sunlight.set.unused1 = FieldValue[0];
            break;
        case 90: //sunlight.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.sunlight.night.unused1 = FieldValue[0];
            break;
        case 94: //sun.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.sun.rise.unused1 = FieldValue[0];
            break;
        case 98: //sun.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.sun.day.unused1 = FieldValue[0];
            break;
        case 102: //sun.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.sun.set.unused1 = FieldValue[0];
            break;
        case 106: //sun.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.sun.night.unused1 = FieldValue[0];
            break;
        case 110: //stars.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.stars.rise.unused1 = FieldValue[0];
            break;
        case 114: //stars.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.stars.day.unused1 = FieldValue[0];
            break;
        case 118: //stars.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.stars.set.unused1 = FieldValue[0];
            break;
        case 122: //stars.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.stars.night.unused1 = FieldValue[0];
            break;
        case 126: //lowerSky.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.lowerSky.rise.unused1 = FieldValue[0];
            break;
        case 130: //lowerSky.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.lowerSky.day.unused1 = FieldValue[0];
            break;
        case 134: //lowerSky.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.lowerSky.set.unused1 = FieldValue[0];
            break;
        case 138: //lowerSky.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.lowerSky.night.unused1 = FieldValue[0];
            break;
        case 142: //horizon.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.horizon.rise.unused1 = FieldValue[0];
            break;
        case 146: //horizon.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.horizon.day.unused1 = FieldValue[0];
            break;
        case 150: //horizon.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.horizon.set.unused1 = FieldValue[0];
            break;
        case 154: //horizon.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.horizon.night.unused1 = FieldValue[0];
            break;
        case 158: //upperClouds.rise.unused1
            if(nSize != 1)
                return;
            NAM0.value.upperClouds.rise.unused1 = FieldValue[0];
            break;
        case 162: //upperClouds.day.unused1
            if(nSize != 1)
                return;
            NAM0.value.upperClouds.day.unused1 = FieldValue[0];
            break;
        case 166: //upperClouds.set.unused1
            if(nSize != 1)
                return;
            NAM0.value.upperClouds.set.unused1 = FieldValue[0];
            break;
        case 170: //upperClouds.night.unused1
            if(nSize != 1)
                return;
            NAM0.value.upperClouds.night.unused1 = FieldValue[0];
            break;
        default:
            return;
        }
    return;
    }

void WTHRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 11: //upperSky.rise.red
            NAM0.value.upperSky.rise.red = FieldValue;
            break;
        case 12: //upperSky.rise.green
            NAM0.value.upperSky.rise.green = FieldValue;
            break;
        case 13: //upperSky.rise.blue
            NAM0.value.upperSky.rise.blue = FieldValue;
            break;
        case 15: //upperSky.day.red
            NAM0.value.upperSky.day.red = FieldValue;
            break;
        case 16: //upperSky.day.green
            NAM0.value.upperSky.day.green = FieldValue;
            break;
        case 17: //upperSky.day.blue
            NAM0.value.upperSky.day.blue = FieldValue;
            break;
        case 19: //upperSky.set.red
            NAM0.value.upperSky.set.red = FieldValue;
            break;
        case 20: //upperSky.set.green
            NAM0.value.upperSky.set.green = FieldValue;
            break;
        case 21: //upperSky.set.blue
            NAM0.value.upperSky.set.blue = FieldValue;
            break;
        case 23: //upperSky.night.red
            NAM0.value.upperSky.night.red = FieldValue;
            break;
        case 24: //upperSky.night.green
            NAM0.value.upperSky.night.green = FieldValue;
            break;
        case 25: //upperSky.night.blue
            NAM0.value.upperSky.night.blue = FieldValue;
            break;
        case 27: //fog.rise.red
            NAM0.value.fog.rise.red = FieldValue;
            break;
        case 28: //fog.rise.green
            NAM0.value.fog.rise.green = FieldValue;
            break;
        case 29: //fog.rise.blue
            NAM0.value.fog.rise.blue = FieldValue;
            break;
        case 31: //fog.day.red
            NAM0.value.fog.day.red = FieldValue;
            break;
        case 32: //fog.day.green
            NAM0.value.fog.day.green = FieldValue;
            break;
        case 33: //fog.day.blue
            NAM0.value.fog.day.blue = FieldValue;
            break;
        case 35: //fog.set.red
            NAM0.value.fog.set.red = FieldValue;
            break;
        case 36: //fog.set.green
            NAM0.value.fog.set.green = FieldValue;
            break;
        case 37: //fog.set.blue
            NAM0.value.fog.set.blue = FieldValue;
            break;
        case 39: //fog.night.red
            NAM0.value.fog.night.red = FieldValue;
            break;
        case 40: //fog.night.green
            NAM0.value.fog.night.green = FieldValue;
            break;
        case 41: //fog.night.blue
            NAM0.value.fog.night.blue = FieldValue;
            break;
        case 43: //lowerClouds.rise.red
            NAM0.value.lowerClouds.rise.red = FieldValue;
            break;
        case 44: //lowerClouds.rise.green
            NAM0.value.lowerClouds.rise.green = FieldValue;
            break;
        case 45: //lowerClouds.rise.blue
            NAM0.value.lowerClouds.rise.blue = FieldValue;
            break;
        case 47: //lowerClouds.day.red
            NAM0.value.lowerClouds.day.red = FieldValue;
            break;
        case 48: //lowerClouds.day.green
            NAM0.value.lowerClouds.day.green = FieldValue;
            break;
        case 49: //lowerClouds.day.blue
            NAM0.value.lowerClouds.day.blue = FieldValue;
            break;
        case 51: //lowerClouds.set.red
            NAM0.value.lowerClouds.set.red = FieldValue;
            break;
        case 52: //lowerClouds.set.green
            NAM0.value.lowerClouds.set.green = FieldValue;
            break;
        case 53: //lowerClouds.set.blue
            NAM0.value.lowerClouds.set.blue = FieldValue;
            break;
        case 55: //lowerClouds.night.red
            NAM0.value.lowerClouds.night.red = FieldValue;
            break;
        case 56: //lowerClouds.night.green
            NAM0.value.lowerClouds.night.green = FieldValue;
            break;
        case 57: //lowerClouds.night.blue
            NAM0.value.lowerClouds.night.blue = FieldValue;
            break;
        case 59: //ambient.rise.red
            NAM0.value.ambient.rise.red = FieldValue;
            break;
        case 60: //ambient.rise.green
            NAM0.value.ambient.rise.green = FieldValue;
            break;
        case 61: //ambient.rise.blue
            NAM0.value.ambient.rise.blue = FieldValue;
            break;
        case 63: //ambient.day.red
            NAM0.value.ambient.day.red = FieldValue;
            break;
        case 64: //ambient.day.green
            NAM0.value.ambient.day.green = FieldValue;
            break;
        case 65: //ambient.day.blue
            NAM0.value.ambient.day.blue = FieldValue;
            break;
        case 67: //ambient.set.red
            NAM0.value.ambient.set.red = FieldValue;
            break;
        case 68: //ambient.set.green
            NAM0.value.ambient.set.green = FieldValue;
            break;
        case 69: //ambient.set.blue
            NAM0.value.ambient.set.blue = FieldValue;
            break;
        case 71: //ambient.night.red
            NAM0.value.ambient.night.red = FieldValue;
            break;
        case 72: //ambient.night.green
            NAM0.value.ambient.night.green = FieldValue;
            break;
        case 73: //ambient.night.blue
            NAM0.value.ambient.night.blue = FieldValue;
            break;
        case 75: //sunlight.rise.red
            NAM0.value.sunlight.rise.red = FieldValue;
            break;
        case 76: //sunlight.rise.green
            NAM0.value.sunlight.rise.green = FieldValue;
            break;
        case 77: //sunlight.rise.blue
            NAM0.value.sunlight.rise.blue = FieldValue;
            break;
        case 79: //sunlight.day.red
            NAM0.value.sunlight.day.red = FieldValue;
            break;
        case 80: //sunlight.day.green
            NAM0.value.sunlight.day.green = FieldValue;
            break;
        case 81: //sunlight.day.blue
            NAM0.value.sunlight.day.blue = FieldValue;
            break;
        case 83: //sunlight.set.red
            NAM0.value.sunlight.set.red = FieldValue;
            break;
        case 84: //sunlight.set.green
            NAM0.value.sunlight.set.green = FieldValue;
            break;
        case 85: //sunlight.set.blue
            NAM0.value.sunlight.set.blue = FieldValue;
            break;
        case 87: //sunlight.night.red
            NAM0.value.sunlight.night.red = FieldValue;
            break;
        case 88: //sunlight.night.green
            NAM0.value.sunlight.night.green = FieldValue;
            break;
        case 89: //sunlight.night.blue
            NAM0.value.sunlight.night.blue = FieldValue;
            break;
        case 91: //sun.rise.red
            NAM0.value.sun.rise.red = FieldValue;
            break;
        case 92: //sun.rise.green
            NAM0.value.sun.rise.green = FieldValue;
            break;
        case 93: //sun.rise.blue
            NAM0.value.sun.rise.blue = FieldValue;
            break;
        case 95: //sun.day.red
            NAM0.value.sun.day.red = FieldValue;
            break;
        case 96: //sun.day.green
            NAM0.value.sun.day.green = FieldValue;
            break;
        case 97: //sun.day.blue
            NAM0.value.sun.day.blue = FieldValue;
            break;
        case 99: //sun.set.red
            NAM0.value.sun.set.red = FieldValue;
            break;
        case 100: //sun.set.green
            NAM0.value.sun.set.green = FieldValue;
            break;
        case 101: //sun.set.blue
            NAM0.value.sun.set.blue = FieldValue;
            break;
        case 103: //sun.night.red
            NAM0.value.sun.night.red = FieldValue;
            break;
        case 104: //sun.night.green
            NAM0.value.sun.night.green = FieldValue;
            break;
        case 105: //sun.night.blue
            NAM0.value.sun.night.blue = FieldValue;
            break;
        case 107: //stars.rise.red
            NAM0.value.stars.rise.red = FieldValue;
            break;
        case 108: //stars.rise.green
            NAM0.value.stars.rise.green = FieldValue;
            break;
        case 109: //stars.rise.blue
            NAM0.value.stars.rise.blue = FieldValue;
            break;
        case 111: //stars.day.red
            NAM0.value.stars.day.red = FieldValue;
            break;
        case 112: //stars.day.green
            NAM0.value.stars.day.green = FieldValue;
            break;
        case 113: //stars.day.blue
            NAM0.value.stars.day.blue = FieldValue;
            break;
        case 115: //stars.set.red
            NAM0.value.stars.set.red = FieldValue;
            break;
        case 116: //stars.set.green
            NAM0.value.stars.set.green = FieldValue;
            break;
        case 117: //stars.set.blue
            NAM0.value.stars.set.blue = FieldValue;
            break;
        case 119: //stars.night.red
            NAM0.value.stars.night.red = FieldValue;
            break;
        case 120: //stars.night.green
            NAM0.value.stars.night.green = FieldValue;
            break;
        case 121: //stars.night.blue
            NAM0.value.stars.night.blue = FieldValue;
            break;
        case 123: //lowerSky.rise.red
            NAM0.value.lowerSky.rise.red = FieldValue;
            break;
        case 124: //lowerSky.rise.green
            NAM0.value.lowerSky.rise.green = FieldValue;
            break;
        case 125: //lowerSky.rise.blue
            NAM0.value.lowerSky.rise.blue = FieldValue;
            break;
        case 127: //lowerSky.day.red
            NAM0.value.lowerSky.day.red = FieldValue;
            break;
        case 128: //lowerSky.day.green
            NAM0.value.lowerSky.day.green = FieldValue;
            break;
        case 129: //lowerSky.day.blue
            NAM0.value.lowerSky.day.blue = FieldValue;
            break;
        case 131: //lowerSky.set.red
            NAM0.value.lowerSky.set.red = FieldValue;
            break;
        case 132: //lowerSky.set.green
            NAM0.value.lowerSky.set.green = FieldValue;
            break;
        case 133: //lowerSky.set.blue
            NAM0.value.lowerSky.set.blue = FieldValue;
            break;
        case 135: //lowerSky.night.red
            NAM0.value.lowerSky.night.red = FieldValue;
            break;
        case 136: //lowerSky.night.green
            NAM0.value.lowerSky.night.green = FieldValue;
            break;
        case 137: //lowerSky.night.blue
            NAM0.value.lowerSky.night.blue = FieldValue;
            break;
        case 139: //horizon.rise.red
            NAM0.value.horizon.rise.red = FieldValue;
            break;
        case 140: //horizon.rise.green
            NAM0.value.horizon.rise.green = FieldValue;
            break;
        case 141: //horizon.rise.blue
            NAM0.value.horizon.rise.blue = FieldValue;
            break;
        case 143: //horizon.day.red
            NAM0.value.horizon.day.red = FieldValue;
            break;
        case 144: //horizon.day.green
            NAM0.value.horizon.day.green = FieldValue;
            break;
        case 145: //horizon.day.blue
            NAM0.value.horizon.day.blue = FieldValue;
            break;
        case 147: //horizon.set.red
            NAM0.value.horizon.set.red = FieldValue;
            break;
        case 148: //horizon.set.green
            NAM0.value.horizon.set.green = FieldValue;
            break;
        case 149: //horizon.set.blue
            NAM0.value.horizon.set.blue = FieldValue;
            break;
        case 151: //horizon.night.red
            NAM0.value.horizon.night.red = FieldValue;
            break;
        case 152: //horizon.night.green
            NAM0.value.horizon.night.green = FieldValue;
            break;
        case 153: //horizon.night.blue
            NAM0.value.horizon.night.blue = FieldValue;
            break;
        case 155: //upperClouds.rise.red
            NAM0.value.upperClouds.rise.red = FieldValue;
            break;
        case 156: //upperClouds.rise.green
            NAM0.value.upperClouds.rise.green = FieldValue;
            break;
        case 157: //upperClouds.rise.blue
            NAM0.value.upperClouds.rise.blue = FieldValue;
            break;
        case 159: //upperClouds.day.red
            NAM0.value.upperClouds.day.red = FieldValue;
            break;
        case 160: //upperClouds.day.green
            NAM0.value.upperClouds.day.green = FieldValue;
            break;
        case 161: //upperClouds.day.blue
            NAM0.value.upperClouds.day.blue = FieldValue;
            break;
        case 163: //upperClouds.set.red
            NAM0.value.upperClouds.set.red = FieldValue;
            break;
        case 164: //upperClouds.set.green
            NAM0.value.upperClouds.set.green = FieldValue;
            break;
        case 165: //upperClouds.set.blue
            NAM0.value.upperClouds.set.blue = FieldValue;
            break;
        case 167: //upperClouds.night.red
            NAM0.value.upperClouds.night.red = FieldValue;
            break;
        case 168: //upperClouds.night.green
            NAM0.value.upperClouds.night.green = FieldValue;
            break;
        case 169: //upperClouds.night.blue
            NAM0.value.upperClouds.night.blue = FieldValue;
            break;
        case 189: //windSpeed
            DATA.value.windSpeed = FieldValue;
            break;
        case 190: //lowerCloudSpeed
            DATA.value.lowerCloudSpeed = FieldValue;
            break;
        case 191: //upperCloudSpeed
            DATA.value.upperCloudSpeed = FieldValue;
            break;
        case 192: //transDelta
            DATA.value.transDelta = FieldValue;
            break;
        case 193: //sunGlare
            DATA.value.sunGlare = FieldValue;
            break;
        case 194: //sunDamage
            DATA.value.sunDamage = FieldValue;
            break;
        case 195: //rainFadeIn
            DATA.value.rainFadeIn = FieldValue;
            break;
        case 196: //rainFadeOut
            DATA.value.rainFadeOut = FieldValue;
            break;
        case 197: //boltFadeIn
            DATA.value.boltFadeIn = FieldValue;
            break;
        case 198: //boltFadeOut
            DATA.value.boltFadeOut = FieldValue;
            break;
        case 199: //boltFrequency
            DATA.value.boltFrequency = FieldValue;
            break;
        case 200: //weatherType
            DATA.value.weatherType = FieldValue;
            break;
        case 201: //boltRed
            DATA.value.boltRed = FieldValue;
            break;
        case 202: //boltGreen
            DATA.value.boltGreen = FieldValue;
            break;
        case 203: //boltBlue
            DATA.value.boltBlue = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WTHRRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 204: //sounds
            if(listIndex >= Sounds.size())
                return;
            switch(listField)
                {
                case 1: //sound
                    Sounds[listIndex]->value.sound = FieldValue;
                    FormIDHandler.AddMaster(Sounds[listIndex]->value.sound);
                    break;
                case 2: //type
                    Sounds[listIndex]->value.type = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }
