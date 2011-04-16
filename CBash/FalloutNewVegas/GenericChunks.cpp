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

#include "../Common.h"
#include "GenericChunks.h"

GENOBND::GENOBND():
    x(0),
    y(0),
    z(0)
    {
    //
    }

GENOBND::~GENOBND()
    {
    //
    }

bool GENOBND::operator ==(const GENOBND &other) const
    {
    return (x == other.x &&
            y == other.y &&
            z == other.z);
    }

bool GENOBND::operator !=(const GENOBND &other) const
    {
    return !(*this == other);
    }

GENU16FLAG::GENU16FLAG():
    flags(0)
    {
    //
    }

GENU16FLAG::~GENU16FLAG()
    {
    //
    }

bool GENU16FLAG::operator ==(const GENU16FLAG &other) const
    {
    return flags == other.flags;
    }

bool GENU16FLAG::operator !=(const GENU16FLAG &other) const
    {
    return !(*this == other);
    }

GENDODT::GENDODT():
    minWidth(0.0f),
    maxWidth(0.0f),
    minHeight(0.0f),
    maxHeight(0.0f),
    depth(0.0f),
    shininess(0.0f),
    scale(0.0f),
    passes(0),
    flags(0),
    red(0),
    green(0),
    blue(0),
    unused2(0x00)
    {
    memset(&unused1[0], 0x00, 2);
    }

GENDODT::~GENDODT()
    {
    //
    }

bool GENDODT::operator ==(const GENDODT &other) const
    {
    return (passes == other.passes &&
    	    flags == other.flags &&
    	    red == other.red &&
    	    green == other.green &&
    	    blue == other.blue &&
    	    AlmostEqual(minWidth,other.minWidth,2) &&
    	    AlmostEqual(maxWidth,other.maxWidth,2) &&
    	    AlmostEqual(minHeight,other.minHeight,2) &&
    	    AlmostEqual(maxHeight,other.maxHeight,2) &&
    	    AlmostEqual(depth,other.depth,2) &&
    	    AlmostEqual(shininess,other.shininess,2) &&
    	    AlmostEqual(scale,other.scale,2));
    }

bool GENDODT::operator !=(const GENDODT &other) const
    {
    return !(*this == other);
    }

bool GENDODT::IsParallax()
    {
    return (flags & fIsParallax) != 0;
    }

void GENDODT::IsParallax(bool value)
    {
    if(value)
        flags |= fIsParallax;
    else
        flags &= ~fIsParallax;
    }

bool GENDODT::IsAlphaBlending()
    {
    return (flags & fIsAlphaBlending) != 0;
    }

void GENDODT::IsAlphaBlending(bool value)
    {
    if(value)
        flags |= fIsAlphaBlending;
    else
        flags &= ~fIsAlphaBlending;
    }

bool GENDODT::IsAlphaTesting()
    {
    return (flags & fIsAlphaTesting) != 0;
    }

void GENDODT::IsAlphaTesting(bool value)
    {
    if(value)
        flags |= fIsAlphaTesting;
    else
        flags &= ~fIsAlphaTesting;
    }

bool GENDODT::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(Exact)
        return (flags & Mask) == Mask;
    else
        return (flags & Mask) != 0;
    }

void GENDODT::SetFlagMask(UINT8 Mask)
    {
    flags = Mask;
    }