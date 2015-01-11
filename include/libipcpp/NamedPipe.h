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

#ifndef LIBIPC_NAMEDPIPE_H
#define LIBIPC_NAMEDPIPE_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"
#include "IOBase.h"
#include "Utility.h"
#include "exception/NamedPipeException.h"
#include <iterator>
#include <algorithm>
#include <cstring>


namespace ipc {
    enum class NamedPipeIo {
        Read,
        Write
    };

    class LIBIPC_API NamedPipe : public IOBase, public ReferenceType
    {
    public:
        NamedPipe(const std::string& name, NamedPipeIo flag) throw(NamedPipeException);
        virtual ~NamedPipe();

        /*!
         * Initializes the named pipe instance. This methods blocks until a
         * second pipe connects to this instance.
         */
        void Initialize() throw(NamedPipeException);

        /*!
         *  Writes a block of data to the pipe.
         *
         * \param[in] in The vector containing the data to be written to the pipe
         * \param[in] offset The position at which to start reading from the vector
         * \param[in] size The amount of data to be written to the pipe
         * \returns The number of bytes written is returned
         */
        virtual ByteCount Write(const char* in, size_t size) const override;

        /*!
         *  Reads a block of data from the pipe
         * 
         * \param[out] out The vector that accepts data from the pipe
         * \param[in] offset The position at which to start writing data to the vector
         * \param[in] size The amount of data to be read from the pipe
         */
        virtual ByteCount Read(char* out, size_t size) const override;
        
        /*!
         *  Writes a block of data to the pipe.
         * 
         * \param[in] InputIt must meet the requirements of InputIterator
         * \param[in] first,last The range of elements to examine
         * \returns The number of bytes written is returned
         */
        template <typename InputIt>
        ByteCount Write(InputIt first, InputIt end) const;
        
        /*!
         *  Reads a block of data from the pipe.
         * 
         * \tparam InputIt must meet the requirements of InputIterator
         * \param[in] first,last The range of elements to examine
         * \returns The number of bytes written is returned
         */
        template <typename OutputIt>
        ByteCount Read(OutputIt first, OutputIt end) const;

        /*!
         * Writes a single byte to the pipe.
         * 
         * \param[in] c The byte to be written to the Pipe
         * \returns The number of written bytes
         */
        virtual ByteCount WriteByte(char c) const override;
        
        /*!
         * Reads a single byte from the pipe.
         * 
         * \returns The read byte or -1 in case of error.
         */
        virtual int ReadByte() const override;
        
        /*!
         * Closes the Pipe.
         */
        void Close();
        
        /*!
         * \returns Returns true if the Pipe is Open 
         */
        bool IsOpen() const;

        /*!
         * \returns IO configuration from this pipe.
         */
        NamedPipeIo GetConfiguration() const;

    private:
        NamedPipeIo mConfig;
        bool mIsOpen;

#ifdef _MSC_VER
        const std::string mName = "";
#endif
        IpcHandle mHandle = INVALID_HANDLE;
    };
}

#ifdef _MSC_VER
#include "platform/win32/NamedPipe.inl"
#else
#include "platform/linux/NamedPipe.inl"
#endif

#endif
