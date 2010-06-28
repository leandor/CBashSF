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

class LANDRecord : public Record
    {
    private:
        enum LANDSubRecords {
            eDATA = 0x41544144,
            eVNML = 0x4C4D4E56,
            eVHGT = 0x54474856,
            eVCLR = 0x524C4356,
            eBTXT = 0x54585442,
            eATXT = 0x54585441,
            eVTXT = 0x54585456,
            eVTEX = 0x58455456
            };

        struct LANDNORMALS
            {
            unsigned char x;
            unsigned char y;
            unsigned char z;
            LANDNORMALS():x(0), y(0), z(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("x = %u\n", x);
                    PrintIndent(indentation);
                    printf("y = %u\n", y);
                    PrintIndent(indentation);
                    printf("z = %u\n", z);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const LANDNORMALS &other) const
                {
                return (x == other.x && 
                        y == other.y && 
                        z == other.z);
                }
            bool operator !=(const LANDNORMALS &other) const
                {
                return !(*this == other);
                }
            };

        struct LANDVNML
            {
            LANDNORMALS VNML[33][33];
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("Normals:\n");
                        for(unsigned int x = 0; x < 33; ++x)
                            {
                            indentation += 2;
                            PrintIndent(indentation);
                            printf("Row: %u\n", x);
                            for(unsigned int y = 0; y < 33; ++y)
                                {
                                indentation += 2;
                                PrintIndent(indentation);
                                printf("Column: %u\n", y);
                                VNML[x][y].Debug(debugLevel, indentation);
                                indentation -= 2;
                                }
                            indentation -= 2;
                            }
                        }
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const LANDVNML &other) const
                {
                for(unsigned int x = 0; x < 33; ++x)
                    for(unsigned int y = 0; y < 33; ++y)
                        if(VNML[x][y] != other.VNML[x][y])
                            return false;
                return true;
                }
            bool operator !=(const LANDVNML &other) const
                {
                return !(*this == other);
                }
            };

        struct LANDVHGT
            {
            float offset;
            signed char VHGT[33][33];
            unsigned char unused1[3];
            LANDVHGT():offset(0.0f)
                {
                memset(&VHGT[0][0], 0, 1089);
                memset(&unused1[0], 0, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("offset = %f\n", offset);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("Heights:\n");
                        for(unsigned int x = 0; x < 33; ++x)
                            {
                            indentation += 2;
                            PrintIndent(indentation);
                            printf("Row: %u\n", x);
                            indentation += 2;
                            for(unsigned int y = 0; y < 33; ++y)
                                {
                                PrintIndent(indentation);
                                printf("Column: %u, Height\n", y, VHGT[x][y]);
                                }
                            indentation -= 2;
                            indentation -= 2;
                            }
                        PrintIndent(indentation);
                        printf("unused1 = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const LANDVHGT &other) const
                {
                if(!AlmostEqual(offset,other.offset,2))
                    return false;
                for(unsigned int x = 0; x < 33; ++x)
                    for(unsigned int y = 0; y < 33; ++y)
                        if(VHGT[x][y] != other.VHGT[x][y])
                            return false;
                return true;
                }
            bool operator !=(const LANDVHGT &other) const
                {
                return !(*this == other);
                }
            };

        struct LANDCOLORS
            {
            unsigned char red;
            unsigned char green;
            unsigned char blue;
            LANDCOLORS():red(0), green(0), blue(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("red   = %u\n", red);
                    PrintIndent(indentation);
                    printf("green = %u\n", green);
                    PrintIndent(indentation);
                    printf("blue  = %u\n", blue);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const LANDCOLORS &other) const
                {
                return (red == other.red && 
                        green == other.green && 
                        blue == other.blue);
                }
            bool operator !=(const LANDCOLORS &other) const
                {
                return !(*this == other);
                }
            };

        struct LANDVCLR
            {
            LANDCOLORS VCLR[33][33];
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("Colors:\n");
                        for(unsigned int x = 0; x < 33; ++x)
                            {
                            indentation += 2;
                            PrintIndent(indentation);
                            printf("Row: %u\n", x);
                            for(unsigned int y = 0; y < 33; ++y)
                                {
                                indentation += 2;
                                PrintIndent(indentation);
                                printf("Column: %u\n", y);
                                VNML[x][y].Debug(debugLevel, indentation);
                                indentation -= 2;
                                }
                            indentation -= 2;
                            }
                        }
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const LANDVCLR &other) const
                {
                for(unsigned int x = 0; x < 33; ++x)
                    for(unsigned int y = 0; y < 33; ++y)
                        if(VCLR[x][y] != other.VCLR[x][y])
                            return false;
                return true;
                }
            bool operator !=(const LANDVCLR &other) const
                {
                return !(*this == other);
                }
            };

        struct LANDGENTXT
            {
            unsigned int texture;
            unsigned char quadrant;
            unsigned char unused1;
            short layer;
            LANDGENTXT():texture(0), quadrant(0), unused1(0), layer(-1) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("texture  = %08X\n", texture);
                    PrintIndent(indentation);
                    printf("quadrant = %u\n", quadrant);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1  = %02X\n", unused1);
                        }
                    PrintIndent(indentation);
                    printf("layer    = %i\n", layer);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const LANDGENTXT &other) const
                {
                return (texture == other.texture && 
                        quadrant == other.quadrant && 
                        layer == other.layer);
                }
            bool operator !=(const LANDGENTXT &other) const
                {
                return !(*this == other);
                }
            };

        struct LANDVTXT
            {
            unsigned short position;
            unsigned char unused1[2];
            float opacity;
            LANDVTXT():position(0), opacity(0.0f)
                {
                memset(&unused1[0], 0, 2);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("position = %u\n", position);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1  = %02X%02X\n", unused1[0], unused1[1]);
                        }
                    PrintIndent(indentation);
                    printf("opacity  = %f\n", opacity);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const LANDVTXT &other) const
                {
                return (position == other.position && 
                        AlmostEqual(opacity,other.opacity,2));
                }
            bool operator !=(const LANDVTXT &other) const
                {
                return !(*this == other);
                }
            };

        struct LANDLAYERS
            {
            ReqSubRecord<LANDGENTXT> ATXT;
            std::vector<LANDVTXT> VTXT;
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    ATXT.Debug("ATXT", debugLevel, indentation);
                    VTXT.Debug("VTXT", debugLevel, indentation);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const LANDLAYERS &other) const
                {
                return (ATXT == other.ATXT && 
                        VTXT == other.VTXT);
                }
            bool operator !=(const LANDLAYERS &other) const
                {
                return !(*this == other);
                }
            };
        //struct LANDPOINTS
        //    {
        //    float AlphaLayer[8];
        //    unsigned char height;
        //    unsigned char normalX;
        //    unsigned char normalY;
        //    unsigned char normalZ;
        //    unsigned char red;
        //    unsigned char green;
        //    unsigned char blue;
        //    LANDPOINTS():AlphaLayer(8, 0.0) {}
        //    };
        //struct LANDMERGED
        //    {//156B, 40*33*33 (1.319GB), 28B - 7B*33*33 (265MB)
        //    LANDPOINTS Points[33][33];
        //    //unsigned int bottomLeftAlphas[8];
        //    //unsigned int bottomRightAlphas[8];
        //    //unsigned int topLeftAlphas[8];
        //    //unsigned int topRightAlphas[8];
        //    unsigned int bottomLeftBaseTexture;
        //    unsigned int bottomRightBaseTexture;
        //    unsigned int topLeftBaseTexture;
        //    unsigned int topRightBaseTexture;
        //    float heightOffset;
        //    short bottomLeftBaseLayer;
        //    short bottomRightBaseLayer;
        //    short topLeftBaseLayer;
        //    short topRightBaseLayer;
        //    //LANDMERGED():Points(33, std::vector<LANDPOINTS>(33)), bottomLeftAlphas(8),  bottomRightAlphas(8),  topLeftAlphas(8),  topRightAlphas(8) {}
        //    };

    public:
        enum QuadrantEnum {
            eBottomLeft,
            eBottomRight,
            eTopLeft,
            eTopRight
            };
        RAWBYTES DATA;
        OptSubRecord<LANDVNML> VNML;
        OptSubRecord<LANDVHGT> VHGT;
        OptSubRecord<LANDVCLR> VCLR;
        std::vector<ReqSubRecord<LANDGENTXT> *> BTXT;
        std::vector<LANDLAYERS *> Layers;
        std::vector<unsigned int> VTEX;
        //LANDMERGED *Merged;

        LANDRecord *WestLand;
        LANDRecord *EastLand;
        LANDRecord *NorthLand;
        LANDRecord *SouthLand;
        LANDRecord(bool newRecord=false):Record(newRecord), WestLand(NULL), EastLand(NULL), NorthLand(NULL), SouthLand(NULL) {IsCompressed(true);}
        LANDRecord(const unsigned int &newFormID):Record(newFormID), WestLand(NULL), EastLand(NULL), NorthLand(NULL), SouthLand(NULL) {IsCompressed(true);}
        LANDRecord(LANDRecord *srcRecord):Record(true), WestLand(NULL), EastLand(NULL), NorthLand(NULL), SouthLand(NULL)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;

            DATA = srcRecord->DATA;
            VNML = srcRecord->VNML;
            VHGT = srcRecord->VHGT;
            VCLR = srcRecord->VCLR;
            BTXT.clear();
            BTXT.resize(srcRecord->BTXT.size());
            for(unsigned int x = 0; x < srcRecord->BTXT.size(); ++x)
                {
                BTXT[x] = new ReqSubRecord<LANDGENTXT>;
                *BTXT[x] = *srcRecord->BTXT[x];
                }
            Layers.clear();
            Layers.resize(srcRecord->Layers.size());
            for(unsigned int x = 0; x < srcRecord->Layers.size(); ++x)
                {
                Layers[x] = new LANDLAYERS;
                Layers[x]->ATXT = srcRecord->Layers[x]->ATXT;
                Layers[x]->VTXT = srcRecord->Layers[x]->VTXT;
                }
            VTEX = srcRecord->VTEX;
            return;
            }
        ~LANDRecord()
            {
            for(unsigned int x = 0; x < BTXT.size(); ++x)
                delete BTXT[x];
            for(unsigned int x = 0; x < Layers.size(); ++x)
                delete Layers[x];
            }
        void Unload()
            {
            IsLoaded(false);
            DATA.Unload();
            VNML.Unload();
            VHGT.Unload();
            VCLR.Unload();
            for(unsigned int x = 0; x < BTXT.size(); ++x)
                delete BTXT[x];
            BTXT.clear();

            for(unsigned int x = 0; x < Layers.size(); ++x)
                delete Layers[x];
            Layers.clear();

            VTEX.clear();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            for(unsigned int x = 0; x < BTXT.size(); ++x)
                if(BTXT[x] != NULL)
                    FormIDs.push_back(&BTXT[x]->value.texture);
            for(unsigned int x = 0; x < Layers.size(); ++x)
                FormIDs.push_back(&Layers[x]->ATXT.value.texture);
            for(unsigned int x = 0; x < VTEX.size(); x++)
                FormIDs.push_back(&VTEX[x]);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        int GetListX2FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListX2Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetListX2ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void GetListX2Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void * GetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned short FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue);

        unsigned char CalcQuadrant(const unsigned int &row, const unsigned int &column);
        unsigned int CalcPosition(const unsigned int &curQuadrant, const unsigned int &row, const unsigned int &column);
        float CalcHeight(const unsigned int &row, const unsigned int &column);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eLAND;}
        char * GetStrType() {return "LAND";}
        int WriteRecord(_FileHandler &SaveHandler);
    };
