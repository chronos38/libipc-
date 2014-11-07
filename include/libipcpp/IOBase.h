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
        virtual size_t Length() const = 0;
        virtual size_t Position() const = 0;
        virtual void Position(size_t position) = 0;
        virtual ByteCount Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) = 0;
        virtual ByteCount WriteByte(uint8_t byte) = 0;
        virtual ByteCount Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) = 0;
        virtual int ReadByte() = 0;
    };
}

#endif
