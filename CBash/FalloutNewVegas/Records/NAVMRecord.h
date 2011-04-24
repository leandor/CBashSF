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
class NAVMRecord : public Record //Navigation Mesh
    {
    private:
        struct NAVMDATA // Data
            {
            FORMID  cell;
            UINT32  numVertices, numTriangles, numConnections, numNVCA, numDoors;

            NAVMDATA();
            ~NAVMDATA();

            bool operator ==(const NAVMDATA &other) const;
            bool operator !=(const NAVMDATA &other) const;
            };

        struct NAVMVertex // Vertex
            {
            FLOAT32 x, y, z;

            NAVMVertex();
            ~NAVMVertex();

            bool operator ==(const NAVMVertex &other) const;
            bool operator !=(const NAVMVertex &other) const;
            };

        struct NAVMNVTR // Triangle
            {
            SINT16  vertex1, vertex2, vertex3;
            SINT16  edge1, edge2, edge3;
            UINT32  flags;

            enum flagsFlags
                {
                fIsTriangle0External = 0x00000001,
                fIsTriangle1External = 0x00000002,
                fIsTriangle2External = 0x00000004,
                fIsUnknown4 = 0x00000008,
                fIsUnknown5 = 0x00000010,
                fIsUnknown6 = 0x00000020,
                fIsUnknown7 = 0x00000040,
                fIsUnknown8 = 0x00000080,
                fIsUnknown9 = 0x00000100,
                fIsUnknown10 = 0x00000200,
                fIsUnknown11 = 0x00000400,
                fIsUnknown12 = 0x00000800,
                fIsUnknown13 = 0x00001000,
                fIsUnknown14 = 0x00002000,
                fIsUnknown15 = 0x00004000,
                fIsUnknown16 = 0x00008000,
                fIsUnknown17 = 0x00010000,
                fIsUnknown18 = 0x00020000,
                fIsUnknown19 = 0x00040000,
                fIsUnknown20 = 0x00080000,
                fIsUnknown21 = 0x00100000,
                fIsUnknown22 = 0x00200000,
                fIsUnknown23 = 0x00400000,
                fIsUnknown24 = 0x00800000,
                fIsUnknown25 = 0x01000000,
                fIsUnknown26 = 0x02000000,
                fIsUnknown27 = 0x04000000,
                fIsUnknown28 = 0x08000000,
                fIsUnknown29 = 0x10000000,
                fIsUnknown30 = 0x20000000,
                fIsUnknown31 = 0x40000000,
                fIsUnknown32 = 0x80000000
                };

            NAVMNVTR();
            ~NAVMNVTR();

            bool   IsTriangle0External();
            void   IsTriangle0External(bool value);
            bool   IsTriangle1External();
            void   IsTriangle1External(bool value);
            bool   IsTriangle2External();
            void   IsTriangle2External(bool value);
            bool   IsUnknown4();
            void   IsUnknown4(bool value);
            bool   IsUnknown5();
            void   IsUnknown5(bool value);
            bool   IsUnknown6();
            void   IsUnknown6(bool value);
            bool   IsUnknown7();
            void   IsUnknown7(bool value);
            bool   IsUnknown8();
            void   IsUnknown8(bool value);
            bool   IsUnknown9();
            void   IsUnknown9(bool value);
            bool   IsUnknown10();
            void   IsUnknown10(bool value);
            bool   IsUnknown11();
            void   IsUnknown11(bool value);
            bool   IsUnknown12();
            void   IsUnknown12(bool value);
            bool   IsUnknown13();
            void   IsUnknown13(bool value);
            bool   IsUnknown14();
            void   IsUnknown14(bool value);
            bool   IsUnknown15();
            void   IsUnknown15(bool value);
            bool   IsUnknown16();
            void   IsUnknown16(bool value);
            bool   IsUnknown17();
            void   IsUnknown17(bool value);
            bool   IsUnknown18();
            void   IsUnknown18(bool value);
            bool   IsUnknown19();
            void   IsUnknown19(bool value);
            bool   IsUnknown20();
            void   IsUnknown20(bool value);
            bool   IsUnknown21();
            void   IsUnknown21(bool value);
            bool   IsUnknown22();
            void   IsUnknown22(bool value);
            bool   IsUnknown23();
            void   IsUnknown23(bool value);
            bool   IsUnknown24();
            void   IsUnknown24(bool value);
            bool   IsUnknown25();
            void   IsUnknown25(bool value);
            bool   IsUnknown26();
            void   IsUnknown26(bool value);
            bool   IsUnknown27();
            void   IsUnknown27(bool value);
            bool   IsUnknown28();
            void   IsUnknown28(bool value);
            bool   IsUnknown29();
            void   IsUnknown29(bool value);
            bool   IsUnknown30();
            void   IsUnknown30(bool value);
            bool   IsUnknown31();
            void   IsUnknown31(bool value);
            bool   IsUnknown32();
            void   IsUnknown32(bool value);
            bool   IsFlagMask(UINT32 Mask, bool Exact=false);
            void   SetFlagMask(UINT32 Mask);

            bool operator ==(const NAVMNVTR &other) const;
            bool operator !=(const NAVMNVTR &other) const;
            };

        struct NAVMNVDP // Door
            {
            FORMID  door;
            UINT16  unknown1;
            UINT8   unused1[2];

            NAVMNVDP();
            ~NAVMNVDP();

            bool operator ==(const NAVMNVDP &other) const;
            bool operator !=(const NAVMNVDP &other) const;
            };

        struct NAVMNVEX // External Connection
            {
            UINT8   unknown1[4];
            FORMID  mesh; // Navigation Mesh
            UINT16  triangle;

            NAVMNVEX();
            ~NAVMNVEX();

            bool operator ==(const NAVMNVEX &other) const;
            bool operator !=(const NAVMNVEX &other) const;
            };
        
    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<UINT32> NVER; //Version
        OptSubRecord<NAVMDATA> DATA; //Data
        std::vector<NAVMVertex> NVVX; //Vertices
        std::vector<NAVMNVTR> NVTR; //Triangles
        RawRecord NVCA; //Unknown
        std::vector<NAVMNVDP> NVDP; //Doors
        RawRecord NVGD; //Unknown
        std::vector<NAVMNVEX> NVEX; //External Connections

        NAVMRecord(unsigned char *_recData=NULL);
        NAVMRecord(NAVMRecord *srcRecord);
        ~NAVMRecord();

        bool   VisitFormIDs(FormIDOp &op);

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

        bool operator ==(const NAVMRecord &other) const;
        bool operator !=(const NAVMRecord &other) const;
    };
}