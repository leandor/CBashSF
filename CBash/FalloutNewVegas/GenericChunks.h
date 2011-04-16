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
// BaseRecord.h
#include "../Common.h"

struct GENOBND
    {
    SINT16   x;
    SINT16   y;
    SINT16   z;

    GENOBND();
    ~GENOBND();

    bool operator ==(const GENOBND &other) const;
    bool operator !=(const GENOBND &other) const;
    };

struct GENU16FLAG
    {
    UINT16  flags;

    GENU16FLAG();
    ~GENU16FLAG();

    bool operator ==(const GENU16FLAG &other) const;
    bool operator !=(const GENU16FLAG &other) const;
    };

struct GENDODT
    {
    FLOAT32 minWidth, maxWidth, minHeight, maxHeight, depth, shininess;
    FLOAT32 scale;
    UINT8   passes;
    UINT8   flags;
    UINT8   unused1[2];
    UINT8   red, green, blue, unused2;

    enum DODTFlags
        {
        fIsParallax      = 0x00000001,
        fIsAlphaBlending = 0x00000002,
        fIsAlphaTesting  = 0x00000004
        };

    GENDODT();
    ~GENDODT();

    bool operator ==(const GENDODT &other) const;
    bool operator !=(const GENDODT &other) const;

    bool IsParallax();
    void IsParallax(bool value);
    bool IsAlphaBlending();
    void IsAlphaBlending(bool value);
    bool IsAlphaTesting();
    void IsAlphaTesting(bool value);
    bool IsFlagMask(UINT8 Mask, bool Exact=false);
    void SetFlagMask(UINT8 Mask);
    };
    
    
    
    