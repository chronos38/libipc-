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

#ifndef LIBIPC_PIPE_H
#define LIBIPC_PIPE_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"

namespace ipc {

    class LIBIPC_API Pipe
    {
        Pipe() = default;
        Pipe(const Pipe&) = default;
        ~Pipe() = default;

#ifdef _MSC_VER
        Pipe(Pipe&&);
#else
        Pipe(Pipe&&) = default;
#endif
    public:
        /*!
         *  Writes a block of data to the pipe.
         *
         * \params[in] buf The buffer containing the data to be written to the pipe
         * \params[in] size The buffers size
         * \returns The number of bytes written is returned
         */
        uint32_t Write(char * buf, uint32_t size);
        uint32_t Read(char * buf, uint32_t size);
        bool WriteByte(unsigned char);
        bool ReadByte(unsigned char);
        void Close();
        bool isOpen();
    };
}
#endif