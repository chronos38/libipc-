/*  This file is part of libipc++
 *
 *  Copyright (C) 2014 David Wolf, Leonhardt Schwarz
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifndef LIBIPC_IOBASE_H
#define LIBIPC_IOBASE_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"

namespace ipc {
    class LIBIPC_API IOBase
    {
    public:
        virtual ~IOBase() = default;
        virtual ByteCount Write(const char* buffer, size_t size) const = 0;
        virtual ByteCount WriteByte(char byte) const = 0;
        virtual ByteCount Read(char* buffer, size_t size) const = 0;
        virtual int ReadByte() const = 0;
    };
}

#endif
