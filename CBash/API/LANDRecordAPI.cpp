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
#include "..\Common.h"
#include "..\Records\LANDRecord.h"

int LANDRecord::CreateListElement(const unsigned int subField)
    {
    switch(subField)
        {
        case 12: //baseTextures
            BTXT.push_back(new ReqSubRecord<LANDGENTXT>);
            return (int)BTXT.size() - 1;
        case 13: //alphaLayers
            Layers.push_back(new LANDLAYERS());
            return (int)Layers.size() - 1;
        case 14: //vertexTextures
            VTEX.push_back(0);
            return (int)VTEX.size() - 1;
        default:
            return -1;
        }
    }

int LANDRecord::DeleteListElement(const unsigned int subField)
    {
    switch(subField)
        {
        case 12: //baseTextures
            delete BTXT.back();
            BTXT.pop_back();
            return (int)BTXT.size() - 1;
        case 13: //alphaLayers
            delete Layers.back();
            Layers.pop_back();
            return (int)Layers.size() - 1;
        case 14: //vertexTextures
            VTEX.pop_back();
            return (int)VTEX.size() - 1;
        default:
            return -1;
        }
    }

int LANDRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //data
            return BYTES_FIELD;
        case 7: //normals
            return LIST_FIELD;
        case 8: //heightOffset
            return FLOAT_FIELD;
        case 9: //heights
            return LIST_FIELD;
        case 10: //unused1
            return BYTES_FIELD;
        case 11: //colors
            return LIST_FIELD;
        case 12: //baseTextures
            return LIST_FIELD;
        case 13: //alphaLayers
            return LIST_FIELD;
        case 14: //vertexTextures
            return LIST_FIELD;
        case 15: //Position
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LANDRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //heightOffset
            if(VHGT.IsLoaded())
                return &VHGT->offset;
            return NULL;
        default:
            return NULL;
        }
    }

int LANDRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 12: //baseTextures
            switch(listField)
                {
                case 1: //texture
                    return FID_FIELD;
                case 2: //quadrant
                    return BYTE_FIELD;
                case 3: //unused1
                    return BYTES_FIELD;
                case 4: //layer
                    return SHORT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //alphaLayers
            switch(listField)
                {
                case 1: //texture
                    return FID_FIELD;
                case 2: //quadrant
                    return BYTE_FIELD;
                case 3: //unused1
                    return BYTES_FIELD;
                case 4: //layer
                    return SHORT_FIELD;
                case 5: //opacities
                    return LIST_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //vertexTextures
            switch(listField)
                {
                case 1: //texture
                    return FID_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

int LANDRecord::GetListX2FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field)
    {
    switch(subField)
        {
        case 7: //normals
            switch(listX2Field)
                {
                case 1: //x
                    return UBYTE_FIELD;
                case 2: //y
                    return UBYTE_FIELD;
                case 3: //z
                    return UBYTE_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 9: //heights
            switch(listX2Field)
                {
                case 1: //height
                    return BYTE_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 11: //colors
            switch(listX2Field)
                {
                case 1: //red
                    return UBYTE_FIELD;
                case 2: //green
                    return UBYTE_FIELD;
                case 3: //blue
                    return UBYTE_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //alphaLayers
            switch(listField)
                {
                case 5: //opacities
                    switch(listX2Field)
                        {
                        case 1: //position
                            return USHORT_FIELD;
                        case 2: //unused1
                            return BYTES_FIELD;
                        case 3: //opacity
                            return FLOAT_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                default:
                    return UNKNOWN_FIELD;
                }
        case 15: //Position
            switch(listX2Field)
                {
                case 1: //height
                    return FLOAT_FIELD;
                case 2: //normalX
                    return UBYTE_FIELD;
                case 3: //normalY
                    return UBYTE_FIELD;
                case 4: //normalZ
                    return UBYTE_FIELD;
                case 5: //red
                    return UBYTE_FIELD;
                case 6: //green
                    return UBYTE_FIELD;
                case 7: //blue
                    return UBYTE_FIELD;
                case 8: //baseTexture
                    return FID_FIELD;
                case 9: //alphaLayer1Texture
                    return FID_FIELD;
                case 10: //alphaLayer1Opacity
                    return FLOAT_FIELD;
                case 11: //alphaLayer2Texture
                    return FID_FIELD;
                case 12: //alphaLayer2Opacity
                    return FLOAT_FIELD;
                case 13: //alphaLayer3Texture
                    return FID_FIELD;
                case 14: //alphaLayer3Opacity
                    return FLOAT_FIELD;
                case 15: //alphaLayer4Texture
                    return FID_FIELD;
                case 16: //alphaLayer4Opacity
                    return FLOAT_FIELD;
                case 17: //alphaLayer5Texture
                    return FID_FIELD;
                case 18: //alphaLayer5Opacity
                    return FLOAT_FIELD;
                case 19: //alphaLayer6Texture
                    return FID_FIELD;
                case 20: //alphaLayer6Opacity
                    return FLOAT_FIELD;
                case 21: //alphaLayer7Texture
                    return FID_FIELD;
                case 22: //alphaLayer7Opacity
                    return FLOAT_FIELD;
                case 23: //alphaLayer8Texture
                    return FID_FIELD;
                case 24: //alphaLayer8Opacity
                    return FLOAT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int LANDRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 12: //baseTextures
            return (unsigned int)BTXT.size();
        case 13: //alphaLayers
            return (unsigned int)Layers.size();
        case 14: //vertexTextures
            return (unsigned int)VTEX.size();
        default:
            return 0;
        }
    }
unsigned int LANDRecord::GetListX2Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 7: //normals
            if(listIndex > 32)
                return 0;
            return 33;
        case 9: //heights
            if(listIndex > 32)
                return 0;
            return 33;
        case 11: //colors
            if(listIndex > 32)
                return 0;
            return 33;
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return 0;
            switch(listField)
                {
                case 5: //opacities
                    return (unsigned int)Layers[listIndex]->VTXT.size();
                default:
                    return 0;
                }
        case 15: //Position
            if(listIndex > 32)
                return 0;
            return 33;
        default:
            return 0;
        }
    }

unsigned int LANDRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 12: //baseTextures
            switch(listField)
                {
                case 3: //unused1
                    return 1;
                default:
                    return 0;
                }
        case 13: //alphaLayers
            switch(listField)
                {
                case 3: //unused1
                    return 1;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned int LANDRecord::GetListX2ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    switch(subField)
        {
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return 0;
            switch(listField)
                {
                case 5: //opacities
                    if(listX2Index >= Layers[listIndex]->VTXT.size())
                        return 0;
                    switch(listX2Field)
                        {
                        case 2: //unused1
                            return 2;
                        default:
                            return 0;
                        }
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned int LANDRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //data
            return DATA.size;
        case 10: //unused1
            if(VHGT.IsLoaded())
                return 3;
            return 0;
        default:
            return 0;
        }
    }

void LANDRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 6: //data
            *FieldValues = DATA.value;
            return;
        case 10: //unused1
            if(VHGT.IsLoaded())
                *FieldValues = &VHGT->unused1[0];
            else
                *FieldValues = NULL;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void LANDRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 12: //baseTextures
            if(listIndex >= BTXT.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 3: //unused1
                    *FieldValues = &BTXT[listIndex]->value.unused1;
                    return;
                default:
                    *FieldValues = NULL;
                    return;
                }
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 3: //unused1
                    *FieldValues = &Layers[listIndex]->ATXT.value.unused1;
                    return;
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }

void LANDRecord::GetListX2Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues)
    {
    switch(subField)
        {
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 5: //opacities
                    if(listX2Index >= Layers[listIndex]->VTXT.size())
                        {
                        *FieldValues = NULL;
                        return;
                        }
                    switch(listX2Field)
                        {
                        case 2: //unused1
                            *FieldValues = &Layers[listIndex]->VTXT[listX2Index].unused1[0];
                            return;
                        default:
                            *FieldValues = NULL;
                            return;
                        }
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }


void * LANDRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 12: //baseTextures
            if(listIndex >= BTXT.size())
                return NULL;
            switch(listField)
                {
                case 1: //texture
                    return &BTXT[listIndex]->value.texture;
                case 2: //quadrant
                    return &BTXT[listIndex]->value.quadrant;
                case 4: //layer
                    return &BTXT[listIndex]->value.layer;
                default:
                    return NULL;
                }
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return NULL;
            switch(listField)
                {
                case 1: //texture
                    return &Layers[listIndex]->ATXT.value.texture;
                case 2: //quadrant
                    return &Layers[listIndex]->ATXT.value.quadrant;
                case 4: //layer
                    return &Layers[listIndex]->ATXT.value.layer;
                default:
                    return NULL;
                }
        case 14: //vertexTextures
            if(listIndex >= VTEX.size())
                return NULL;
            switch(listField)
                {
                case 1: //texture
                    return &VTEX[listField];
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void * LANDRecord::GetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    static float fRetValue = 0.0f;
    unsigned char curQuadrant;
    unsigned short curPosition;
    switch(subField)
        {
        case 7: //normals
            if(listIndex > 32)
                return NULL;
            if(listX2Index > 32)
                return NULL;
            switch(listX2Field)
                {
                case 1: //x
                    if(VNML.IsLoaded())
                        return &VNML->VNML[listIndex][listX2Index].x;
                    return NULL;
                case 2: //y
                    if(VNML.IsLoaded())
                        return &VNML->VNML[listIndex][listX2Index].y;
                    return NULL;
                case 3: //z
                    if(VNML.IsLoaded())
                        return &VNML->VNML[listIndex][listX2Index].z;
                    return NULL;
                default:
                    return NULL;
                }
        case 9: //heights
            if(listIndex > 32)
                return NULL;
            if(listX2Index > 32)
                return NULL;
            switch(listX2Field)
                {
                case 1: //height
                    if(VHGT.IsLoaded())
                        return &VHGT->VHGT[listIndex][listX2Index];
                    return NULL;
                default:
                    return NULL;
                }
        case 11: //colors
            if(listIndex > 32)
                return NULL;
            if(listX2Index > 32)
                return NULL;
            switch(listX2Field)
                {
                case 1: //red
                    if(VCLR.IsLoaded())
                        return &VCLR->VCLR[listIndex][listX2Index].red;
                    return NULL;
                case 2: //green
                    if(VCLR.IsLoaded())
                        return &VCLR->VCLR[listIndex][listX2Index].green;
                    return NULL;
                case 3: //blue
                    if(VCLR.IsLoaded())
                        return &VCLR->VCLR[listIndex][listX2Index].blue;
                    return NULL;
                default:
                    return NULL;
                }
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return NULL;
            switch(listField)
                {
                case 5: //opacities
                    if(listX2Index >= Layers[listIndex]->VTXT.size())
                        return NULL;
                    switch(listX2Field)
                        {
                        case 1: //position
                            return &Layers[listIndex]->VTXT[listX2Index].position;
                        case 3: //opacity
                            return &Layers[listIndex]->VTXT[listX2Index].opacity;
                        default:
                            return NULL;
                        }
                default:
                    return NULL;
                }
        case 15: //Position
            if(listIndex > 32)
                return NULL;
            if(listX2Index > 32)
                return NULL;
            switch(listX2Field)
                {
                case 1: //height
                    if(!VHGT.IsLoaded())
                        return NULL;
                    fRetValue = CalcHeight(listIndex, listX2Index);
                    return &fRetValue;
                case 2: //normalX
                    if(VNML.IsLoaded())
                        return &VNML->VNML[listIndex][listX2Index].x;
                    return NULL;
                case 3: //normalY
                    if(VNML.IsLoaded())
                        return &VNML->VNML[listIndex][listX2Index].y;
                    return NULL;
                case 4: //normalZ
                    if(VNML.IsLoaded())
                        return &VNML->VNML[listIndex][listX2Index].z;
                    return NULL;
                case 5: //red
                    if(VCLR.IsLoaded())
                        return &VCLR->VCLR[listIndex][listX2Index].red;
                    return NULL;
                case 6: //green
                    if(VCLR.IsLoaded())
                        return &VCLR->VCLR[listIndex][listX2Index].green;
                    return NULL;
                case 7: //blue
                    if(VCLR.IsLoaded())
                        return &VCLR->VCLR[listIndex][listX2Index].blue;
                    return NULL;
                case 8: //baseTexture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < BTXT.size(); ++x)
                        if(BTXT[x]->value.quadrant == curQuadrant)
                            return &BTXT[x]->value.texture;
                    return NULL;
                case 9: //alphaLayer1Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 0)
                            return &Layers[x]->ATXT.value.texture;
                    return NULL;
                case 10: //alphaLayer1Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 0)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    return &Layers[x]->VTXT[y].opacity;
                    return NULL;
                case 11: //alphaLayer2Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 1)
                            return &Layers[x]->ATXT.value.texture;
                    return NULL;
                case 12: //alphaLayer2Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 1)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    return &Layers[x]->VTXT[y].opacity;
                    return NULL;
                case 13: //alphaLayer3Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 2)
                            return &Layers[x]->ATXT.value.texture;
                    return NULL;
                case 14: //alphaLayer3Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 2)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    return &Layers[x]->VTXT[y].opacity;
                    return NULL;
                case 15: //alphaLayer4Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 3)
                            return &Layers[x]->ATXT.value.texture;
                    return NULL;
                case 16: //alphaLayer4Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 3)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    return &Layers[x]->VTXT[y].opacity;
                    return NULL;
                case 17: //alphaLayer5Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 4)
                            return &Layers[x]->ATXT.value.texture;
                    return NULL;
                case 18: //alphaLayer5Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 4)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    return &Layers[x]->VTXT[y].opacity;
                    return NULL;
                case 19: //alphaLayer6Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 5)
                            return &Layers[x]->ATXT.value.texture;
                    return NULL;
                case 20: //alphaLayer6Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 5)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    return &Layers[x]->VTXT[y].opacity;
                    return NULL;
                case 21: //alphaLayer7Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 6)
                            return &Layers[x]->ATXT.value.texture;
                    return NULL;
                case 22: //alphaLayer7Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 6)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    return &Layers[x]->VTXT[y].opacity;
                    return NULL;
                case 23: //alphaLayer8Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 7)
                            return &Layers[x]->ATXT.value.texture;
                    return NULL;
                case 24: //alphaLayer8Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 7)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    return &Layers[x]->VTXT[y].opacity;
                    return NULL;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }


void LANDRecord::SetField(const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //heightOffset
            VHGT.Load();
            VHGT->offset = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void LANDRecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 6: //data
            DATA.Copy(FieldValue, nSize);
            break;
        case 10: //unused1
            if(nSize != 3)
                return;
            VHGT.Load();
            VHGT->unused1[0] = FieldValue[0];
            VHGT->unused1[1] = FieldValue[1];
            VHGT->unused1[2] = FieldValue[2];
            break;
        default:
            return;
        }
    return;
    }

void LANDRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 12: //baseTextures
            if(listIndex >= BTXT.size())
                return;
            switch(listField)
                {
                case 1: //texture
                    BTXT[listIndex]->value.texture = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return;
            switch(listField)
                {
                case 1: //texture
                    Layers[listIndex]->ATXT.value.texture = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 14: //vertexTextures
            if(listIndex >= VTEX.size())
                return;
            switch(listField)
                {
                case 1: //texture
                    VTEX[listIndex] = FieldValue;
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


void LANDRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 12: //baseTextures
            if(listIndex >= BTXT.size())
                return;
            switch(listField)
                {
                case 2: //quadrant
                    BTXT[listIndex]->value.quadrant = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return;
            switch(listField)
                {
                case 2: //quadrant
                    Layers[listIndex]->ATXT.value.quadrant = FieldValue;
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

void LANDRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 12: //baseTextures
            if(listIndex >= BTXT.size())
                return;
            switch(listField)
                {
                case 3: //unused1
                    if(nSize != 1)
                        return;
                    BTXT[listIndex]->value.unused1 = FieldValue[0];
                    break;
                default:
                    return;
                }
            break;
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return;
            switch(listField)
                {
                case 3: //unused1
                    if(nSize != 1)
                        return;
                    Layers[listIndex]->ATXT.value.unused1 = FieldValue[0];
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

void LANDRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue)
    {
    switch(subField)
        {
        case 12: //baseTextures
            if(listIndex >= BTXT.size())
                return;
            switch(listField)
                {
                case 4: //layer
                    BTXT[listIndex]->value.layer = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return;
            switch(listField)
                {
                case 4: //layer
                    Layers[listIndex]->ATXT.value.layer = FieldValue;
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

void LANDRecord::SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 7: //normals
            if(listIndex > 32)
                return;
            if(listX2Index > 32)
                return;
            switch(listX2Field)
                {
                case 1: //x
                    VNML.Load();
                    VNML->VNML[listIndex][listX2Index].x = FieldValue;
                    break;
                case 2: //y
                    VNML.Load();
                    VNML->VNML[listIndex][listX2Index].y = FieldValue;
                    break;
                case 3: //z
                    VNML.Load();
                    VNML->VNML[listIndex][listX2Index].z = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 11: //colors
            if(listIndex > 32)
                return;
            if(listX2Index > 32)
                return;
            switch(listX2Field)
                {
                case 1: //red
                    VCLR.Load();
                    VCLR->VCLR[listIndex][listX2Index].red = FieldValue;
                    break;
                case 2: //green
                    VCLR.Load();
                    VCLR->VCLR[listIndex][listX2Index].green = FieldValue;
                    break;
                case 3: //blue
                    VCLR.Load();
                    VCLR->VCLR[listIndex][listX2Index].blue = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 15: //Position
            if(listIndex > 32)
                return;
            if(listX2Index > 32)
                return;
            switch(listX2Field)
                {
                case 2: //normalX
                    VNML.Load();
                    VNML->VNML[listIndex][listX2Index].x = FieldValue;
                    break;
                case 3: //normalY
                    VNML.Load();
                    VNML->VNML[listIndex][listX2Index].y = FieldValue;
                    break;
                case 4: //normalZ
                    VNML.Load();
                    VNML->VNML[listIndex][listX2Index].z = FieldValue;
                    break;
                case 5: //red
                    VCLR.Load();
                    VCLR->VCLR[listIndex][listX2Index].red = FieldValue;
                    break;
                case 6: //green
                    VCLR.Load();
                    VCLR->VCLR[listIndex][listX2Index].green = FieldValue;
                    break;
                case 7: //blue
                    VCLR.Load();
                    VCLR->VCLR[listIndex][listX2Index].blue = FieldValue;
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

void LANDRecord::SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char FieldValue)
    {
    switch(subField)
        {
        case 9: //heights
            if(listIndex > 32)
                return;
            if(listX2Index > 32)
                return;
            switch(listX2Field)
                {
                case 1: //height
                    VHGT.Load();
                    VHGT->VHGT[listIndex][listX2Index] = FieldValue;
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

void LANDRecord::SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned short FieldValue)
    {
    switch(subField)
        {
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return;
            switch(listField)
                {
                case 5: //opacities
                    if(listX2Index >= Layers[listIndex]->VTXT.size())
                        return;
                    switch(listX2Field)
                        {
                        case 1: //position
                            Layers[listIndex]->VTXT[listX2Index].position = FieldValue;
                            break;
                        default:
                            return;
                        }
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

void LANDRecord::SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return;
            switch(listField)
                {
                case 5: //opacities
                    if(listX2Index >= Layers[listIndex]->VTXT.size())
                        return;
                    switch(listX2Field)
                        {
                        case 2: //unused1
                            if(nSize != 2)
                                return;
                            Layers[listIndex]->VTXT[listX2Index].unused1[0] = FieldValue[0];
                            Layers[listIndex]->VTXT[listX2Index].unused1[1] = FieldValue[1];
                            break;
                        default:
                            return;
                        }
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

void LANDRecord::SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue)
    {
    signed char newOffset;
    unsigned char curQuadrant;
    unsigned short curPosition;
    LANDVTXT curVTXT;
    switch(subField)
        {
        case 13: //alphaLayers
            if(listIndex >= Layers.size())
                return;
            switch(listField)
                {
                case 5: //opacities
                    if(listX2Index >= Layers[listIndex]->VTXT.size())
                        return;
                    switch(listX2Field)
                        {
                        case 3: //opacity
                            Layers[listIndex]->VTXT[listX2Index].opacity = FieldValue;
                            break;
                        default:
                            return;
                        }
                    break;
                default:
                    return;
                }
            break;
        case 15: //Position
            if(listIndex > 32)
                return;
            if(listX2Index > 32)
                return;
            switch(listX2Field)
                {
                case 1: //height
                    //Changing height is tricky because the co-ords to the east and possibly north have to be updated as well
                    //These other co-ords may be in other cells.  Example: the corners of the cell must update four different VHGT records
                    //If any of the cells happen to be 0,0, then the baseHeight offset of that cell must be changed instead
                    //The borders of the cells must match the height of the surrounding cells or there will be visual tearing
                    VHGT.Load();
                    newOffset = (signed char)((FieldValue - CalcHeight(listIndex, listX2Index)) / 8.0f);

                    //Set the co-ords to the proper offset.  If the co-ords are 0,0, then change the baseHeight offset instead
                    if(listIndex == 0 && listX2Index == 0)
                        {
                        VHGT->VHGT[0][0] = 0;
                        VHGT->offset = FieldValue;
                        }
                    else
                        VHGT->VHGT[listIndex][listX2Index] += newOffset;

                    //Update the co-ords to the east
                    if(listX2Index == 32) //the co-ords to update are in the next cell to the east
                        {
                        if(listIndex == 0)
                            {
                            //At a corner, so update the three overlapped cells
                            if(EastLand != NULL)
                                {
                                EastLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - EastLand->VHGT->offset) / 8.0f);
                                EastLand->VHGT->VHGT[0][0] = 0;
                                EastLand->VHGT->offset = FieldValue;
                                EastLand->VHGT->VHGT[0][1] -= newOffset;
                                EastLand->VHGT->VHGT[1][0] -= newOffset;
                                }

                            if(EastLand != NULL && EastLand->SouthLand != NULL)
                                {
                                EastLand->SouthLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - EastLand->SouthLand->CalcHeight(32, 0)) / 8.0f);
                                EastLand->SouthLand->VHGT->VHGT[32][0] += newOffset;
                                EastLand->SouthLand->VHGT->VHGT[32][1] -= newOffset;
                                }
                            else if(SouthLand != NULL && SouthLand->EastLand != NULL)
                                {
                                SouthLand->EastLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - SouthLand->EastLand->CalcHeight(32, 0)) / 8.0f);
                                SouthLand->EastLand->VHGT->VHGT[32][0] += newOffset;
                                SouthLand->EastLand->VHGT->VHGT[32][1] -= newOffset;
                                }

                            if(SouthLand != NULL)
                                {
                                SouthLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - SouthLand->CalcHeight(32, 32)) / 8.0f);
                                SouthLand->VHGT->VHGT[32][32] += newOffset;
                                }
                            }
                        else if(listIndex == 32)
                            {
                            //At a corner, so update the three overlapped cells
                            if(EastLand != NULL)
                                {
                                EastLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - EastLand->CalcHeight(32, 0)) / 8.0f);
                                EastLand->VHGT->VHGT[32][0] += newOffset;
                                EastLand->VHGT->VHGT[32][1] -= newOffset;
                                }

                            //Two ways of getting to the same cell
                            if(EastLand != NULL && EastLand->NorthLand != NULL)
                                {
                                EastLand->NorthLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - EastLand->NorthLand->VHGT->offset) / 8.0f);
                                EastLand->NorthLand->VHGT->VHGT[0][0] = 0;
                                EastLand->NorthLand->VHGT->offset = FieldValue;
                                EastLand->NorthLand->VHGT->VHGT[0][1] -= newOffset;
                                EastLand->NorthLand->VHGT->VHGT[1][0] -= newOffset;
                                }
                            else if(NorthLand != NULL && NorthLand->EastLand != NULL)
                                {
                                NorthLand->EastLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - NorthLand->EastLand->VHGT->offset) / 8.0f);
                                NorthLand->EastLand->VHGT->VHGT[0][0] = 0;
                                NorthLand->EastLand->VHGT->offset = FieldValue;
                                NorthLand->EastLand->VHGT->VHGT[0][1] -= newOffset;
                                NorthLand->EastLand->VHGT->VHGT[1][0] -= newOffset;
                                }

                            if(NorthLand != NULL)
                                {
                                NorthLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - NorthLand->CalcHeight(0, 32)) / 8.0f);
                                NorthLand->VHGT->VHGT[0][32] += newOffset;
                                }
                            }
                        else
                            {
                            //In between the corners of the eastern edge, so update overlapped cell
                            if(EastLand != NULL)
                                {
                                newOffset = (signed char)((FieldValue - EastLand->CalcHeight(listIndex, 0)) / 8.0f);
                                EastLand->VHGT->VHGT[listIndex][0] += newOffset;

                                //Then, update the co-ords to the east and north.
                                EastLand->VHGT->VHGT[listIndex][1] -= newOffset;
                                EastLand->VHGT->VHGT[listIndex + 1][0] -= newOffset;
                                }
                            }
                        }
                    //Update the co-ords to the north, if needed
                    else if(listX2Index == 0) //first column is offset by the values to the south
                        {
                        if(listIndex == 0)
                            {
                            VHGT->VHGT[0][1] -= newOffset;
                            VHGT->VHGT[1][0] -= newOffset;

                            //At a corner, so update the three overlapped cells
                            if(SouthLand != NULL)
                                {
                                SouthLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - SouthLand->CalcHeight(32, 0)) / 8.0f);
                                SouthLand->VHGT->VHGT[32][0] += newOffset;
                                SouthLand->VHGT->VHGT[32][1] -= newOffset;
                                }

                            if(SouthLand != NULL && SouthLand->WestLand != NULL)
                                {
                                SouthLand->WestLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - SouthLand->WestLand->CalcHeight(32, 32)) / 8.0f);
                                SouthLand->WestLand->VHGT->VHGT[32][32] += newOffset;
                                }
                            else if(WestLand != NULL && WestLand->SouthLand != NULL)
                                {
                                WestLand->SouthLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - WestLand->SouthLand->CalcHeight(32, 32)) / 8.0f);
                                WestLand->SouthLand->VHGT->VHGT[32][32] += newOffset;
                                }

                            if(WestLand != NULL)
                                {
                                WestLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - WestLand->CalcHeight(0, 32)) / 8.0f);
                                WestLand->VHGT->VHGT[0][32] += newOffset;
                                }

                            if(EastLand != NULL)
                                {
                                EastLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - EastLand->VHGT->offset) / 8.0f);
                                EastLand->VHGT->VHGT[0][0] = 0;
                                EastLand->VHGT->offset = FieldValue;
                                EastLand->VHGT->VHGT[0][1] -= newOffset;
                                EastLand->VHGT->VHGT[1][0] -= newOffset;
                                }
                            }
                        else if(listIndex == 32)
                            {
                            VHGT->VHGT[32][1] -= newOffset;

                            //At a corner, so update the three overlapped cells
                            if(WestLand != NULL)
                                {
                                WestLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - WestLand->CalcHeight(32, 32)) / 8.0f);
                                WestLand->VHGT->VHGT[32][32] += newOffset;
                                }

                            if(NorthLand != NULL)
                                {
                                NorthLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - NorthLand->VHGT->offset) / 8.0f);
                                NorthLand->VHGT->VHGT[0][0] = 0;
                                NorthLand->VHGT->offset = FieldValue;
                                NorthLand->VHGT->VHGT[0][1] -= newOffset;
                                NorthLand->VHGT->VHGT[1][0] -= newOffset;
                                }

                            if(NorthLand != NULL && NorthLand->WestLand != NULL)
                                {
                                NorthLand->WestLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - NorthLand->WestLand->CalcHeight(0, 32)) / 8.0f);
                                NorthLand->WestLand->VHGT->VHGT[0][32] += newOffset;
                                }
                            else if(WestLand != NULL && WestLand->NorthLand != NULL)
                                {
                                WestLand->NorthLand->VHGT.Load();
                                newOffset = (signed char)((FieldValue - WestLand->NorthLand->CalcHeight(0, 32)) / 8.0f);
                                WestLand->NorthLand->VHGT->VHGT[0][32] += newOffset;
                                }
                            }
                        else
                            {
                            VHGT->VHGT[listIndex][1] -= newOffset;
                            VHGT->VHGT[listIndex + 1][0] -= newOffset;
                            //In between the corners of the western edge, so update overlapped cell
                            if(WestLand != NULL)
                                {
                                newOffset = (signed char)((FieldValue - WestLand->CalcHeight(listIndex, 32)) / 8.0f);
                                WestLand->VHGT->VHGT[listIndex][32] += newOffset;
                                }
                            }
                        }
                    //Update the co-ords to the south, if needed
                    else if(listIndex == 0)
                        {
                        VHGT->VHGT[0][listX2Index + 1] -= newOffset;
                        //In between the corners of the western edge, so update overlapped cell
                        if(SouthLand != NULL)
                            {
                            newOffset = (signed char)((FieldValue - SouthLand->CalcHeight(32, listX2Index)) / 8.0f);
                            SouthLand->VHGT->VHGT[32][listX2Index] += newOffset;
                            SouthLand->VHGT->VHGT[32][listX2Index + 1] -= newOffset;
                            }
                        }
                    //Update the co-ords to the north, if needed
                    else if(listIndex == 32)
                        {
                        VHGT->VHGT[0][listX2Index + 1] -= newOffset;
                        //In between the corners of the western edge, so update overlapped cell
                        if(NorthLand != NULL)
                            {
                            newOffset = (signed char)((FieldValue - NorthLand->CalcHeight(0, listX2Index)) / 8.0f);
                            NorthLand->VHGT->VHGT[0][listX2Index] += newOffset;
                            NorthLand->VHGT->VHGT[0][listX2Index + 1] -= newOffset;
                            }
                        }
                    else //the co-ords are contained within the cell
                        VHGT->VHGT[listIndex][listX2Index + 1] -= newOffset;
                    break;
                case 10: //alphaLayer1Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 0)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    {
                                    Layers[x]->VTXT[y].opacity = FieldValue;
                                    return;
                                    }
                    //No existing VTXT, so make one
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 0)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = FieldValue;
                            Layers[x]->VTXT.push_back(curVTXT);
                            return;
                            }
                    //No existing ATXT, so do nothing
                    break;
                case 12: //alphaLayer2Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 1)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    {
                                    Layers[x]->VTXT[y].opacity = FieldValue;
                                    return;
                                    }
                    //No existing VTXT, so make one
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 1)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = FieldValue;
                            Layers[x]->VTXT.push_back(curVTXT);
                            return;
                            }
                    //No existing ATXT, so do nothing
                    break;
                case 14: //alphaLayer3Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 2)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    {
                                    Layers[x]->VTXT[y].opacity = FieldValue;
                                    return;
                                    }
                    //No existing VTXT, so make one
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 2)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = FieldValue;
                            Layers[x]->VTXT.push_back(curVTXT);
                            return;
                            }
                    //No existing ATXT, so do nothing
                    break;
                case 16: //alphaLayer4Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 3)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    {
                                    Layers[x]->VTXT[y].opacity = FieldValue;
                                    return;
                                    }
                    //No existing VTXT, so make one
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 3)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = FieldValue;
                            Layers[x]->VTXT.push_back(curVTXT);
                            return;
                            }
                    //No existing ATXT, so do nothing
                    break;
                case 18: //alphaLayer5Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 4)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    {
                                    Layers[x]->VTXT[y].opacity = FieldValue;
                                    return;
                                    }
                    //No existing VTXT, so make one
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 4)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = FieldValue;
                            Layers[x]->VTXT.push_back(curVTXT);
                            return;
                            }
                    //No existing ATXT, so do nothing
                    break;
                case 20: //alphaLayer6Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 5)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    {
                                    Layers[x]->VTXT[y].opacity = FieldValue;
                                    return;
                                    }
                    //No existing VTXT, so make one
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 5)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = FieldValue;
                            Layers[x]->VTXT.push_back(curVTXT);
                            return;
                            }
                    //No existing ATXT, so do nothing
                    break;
                case 22: //alphaLayer7Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 6)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    {
                                    Layers[x]->VTXT[y].opacity = FieldValue;
                                    return;
                                    }
                    //No existing VTXT, so make one
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 6)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = FieldValue;
                            Layers[x]->VTXT.push_back(curVTXT);
                            return;
                            }
                    //No existing ATXT, so do nothing
                    break;
                case 24: //alphaLayer8Opacity
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    curPosition = CalcPosition(curQuadrant, listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 7)
                            for(unsigned int y = 0; y < Layers[x]->VTXT.size(); ++y)
                                if(Layers[x]->VTXT[y].position == curPosition)
                                    {
                                    Layers[x]->VTXT[y].opacity = FieldValue;
                                    return;
                                    }
                    //No existing VTXT, so make one
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 7)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = FieldValue;
                            Layers[x]->VTXT.push_back(curVTXT);
                            return;
                            }
                    //No existing ATXT, so do nothing
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

void LANDRecord::SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue)
    {
    unsigned char curQuadrant;
    ReqSubRecord<LANDGENTXT> *curTexture;
    LANDLAYERS *curLayer;
    switch(subField)
        {
        case 15: //Position
            if(listIndex > 32)
                return;
            if(listX2Index > 32)
                return;
            switch(listX2Field)
                {
                case 8: //baseTexture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < BTXT.size(); ++x)
                        if(BTXT[x]->value.quadrant == curQuadrant)
                            {
                            BTXT[x]->value.texture = FieldValue;
                            return;
                            }
                    //No existing BTXT, so make one if able
                    if(BTXT.size() > 3)
                        return;
                    curTexture = new ReqSubRecord<LANDGENTXT>;
                    curTexture->value.layer = -1;
                    curTexture->value.quadrant = curQuadrant;
                    curTexture->value.texture = FieldValue;
                    BTXT.push_back(curTexture);
                    break;
                case 9: //alphaLayer1Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 0)
                            {
                            Layers[x]->ATXT.value.texture = FieldValue;
                            return;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 0;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = FieldValue;
                    Layers.push_back(curLayer);
                    break;
                case 11: //alphaLayer2Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 1)
                            {
                            Layers[x]->ATXT.value.texture = FieldValue;
                            return;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 1;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = FieldValue;
                    Layers.push_back(curLayer);
                    break;
                case 13: //alphaLayer3Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 2)
                            {
                            Layers[x]->ATXT.value.texture = FieldValue;
                            return;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 2;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = FieldValue;
                    Layers.push_back(curLayer);
                    break;
                case 15: //alphaLayer4Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 3)
                            {
                            Layers[x]->ATXT.value.texture = FieldValue;
                            return;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 3;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = FieldValue;
                    Layers.push_back(curLayer);
                    break;
                case 17: //alphaLayer5Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 4)
                            {
                            Layers[x]->ATXT.value.texture = FieldValue;
                            return;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 4;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = FieldValue;
                    Layers.push_back(curLayer);
                    break;
                case 19: //alphaLayer6Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 5)
                            {
                            Layers[x]->ATXT.value.texture = FieldValue;
                            return;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 5;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = FieldValue;
                    Layers.push_back(curLayer);
                    break;
                case 21: //alphaLayer7Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 6)
                            {
                            Layers[x]->ATXT.value.texture = FieldValue;
                            return;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 6;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = FieldValue;
                    Layers.push_back(curLayer);
                    break;
                case 23: //alphaLayer8Texture
                    curQuadrant = CalcQuadrant(listIndex, listX2Index);
                    for(unsigned int x = 0; x < Layers.size(); ++x)
                        if(Layers[x]->ATXT.value.quadrant == curQuadrant && Layers[x]->ATXT.value.layer == 7)
                            {
                            Layers[x]->ATXT.value.texture = FieldValue;
                            return;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 7;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = FieldValue;
                    Layers.push_back(curLayer);
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




