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

#ifndef LIBIPC_SHAREDMEMORY_H
#define LIBIPC_SHAREDMEMORY_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Exception/SharedMemoryException.h"

namespace ipc {
    // TODO: IO Interface implementieren.
    //! A shared memory for different threads and processes.
    class MemoryMap : public ReferenceType
    {
    public:
        /*!
         * 
         */
        MemoryMap(); // INFO: Leerer Konstruktor richtig?
        virtual ~MemoryMap();

        /*!
         * Gets read and write access for the byte on the given index. If the
         * index is out of range than the particular exception is thrown.
         *
         * \param[in]   index   The 0 based index for access.
         * \returns Byte on given index.
         */
        uint8_t& operator[](size_t index) throw(SharedMemoryException, std::out_of_range);

        /*!
         * Gets read only access for the byte on the given index. If the index
         * is out of range than the particular exception is thrown.
         *
         * \param[in]   index   The 0 based index for access.
         * \returns Byte on given index.
         */
        const uint8_t& operator[](size_t index) const throw(SharedMemoryException, std::out_of_range);

        /*!
         * Gets the length for this shared memory.
         * \returns Length in bytes for this shared memory.
         */
        size_t Length() const NOEXCEPT;

        /*!
         * Writes a buffer to this shared memory. This method is not safe for
         * concurrent execution. It needs an external lock mechanism to be
         * considered safe. If two write operations happen at the same time,
         * than the behavior is undefined.
         *
         * If the offset is greater than or equal the buffer size, than an
         * out_of_range exception is thrown.
         *
         * If the size minus offset is greate than the buffer size, than an
         * out_of_range exception is thrown.
         *
         * For the remaining errors an IpcException is thrown.
         *
         * \param[in]   buffer  The byte buffer to write to the shared memory.
         * \param[in]   offset  The offest for the given byte buffer.
         * \param[in]   size    The actual size to write.
         * \returns Count of written bytes to the shared memory.
         */
        ByteCount Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(SharedMemoryException, std::out_of_range);

        /*!
         * This method allows range based writing. It expects sequential
         * iterators. It also allows only primitive types. For any other custom type
         * an seperate serialize method must be implemented.
         *
         * If the iterator is invalid or out of bound, than the behavior of
         * this method is undefined.
         *
         * \param[in]   first   Iterator that points to the beginning.
         * \param[in]   last    Iterator that points to the ending.
         * \returns Count of written elements to the shared memory.
         */
        template <typename InputIt>
        size_t Write(InputIt first, InputIt last) throw(IpcException)
        {
            // TODO: implementieren
        }

        /*!
         * Writes a single byte to the shared memory. If this method fails it does
         * not throw an exception, but instead it returns zero (0).
         *
         * \returns Either 1 or 0.
         */
        ByteCount WriteByte(uint8_t byte) NOEXCEPT;

        /*!
         * This method reads from the shared memory. All read bytes are written
         * into the given byte buffer. It is possible to define an offset
         * and read size for this method. So the range is customizable.
         *
         * If the offset is greater than or equal the buffer size, than an
         * out_of_range exception is thrown.
         *
         * If the size minus offset is greate than the buffer size, than an
         * out_of_range exception is thrown.
         *
         * For the remaining errors an IpcException is thrown.
         *
         * \param[in,out]   buffer  Target buffer for this operation.
         * \param[in]   offset  The offest for the given byte buffer.
         * \param[in]   size    The actual size to write.
         * \returns Count of read bytes from the shared memory.
         */
        ByteCount Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(SharedMemoryException, std::out_of_range);

        /*!
         * This method allows range based reading. It expects sequential
         * iterators. It also allows only byte or integer types. For any other
         * this method has undefined behavior.
         *
         * If the iterator is invalid or out of bound, than the behavior of
         * this method is undefined.
         *
         * \param[in]   first   Iterator that points to the beginning.
         * \param[in]   last    Iterator that points to the ending.
         * \returns Count of written elements to the shared memory.
         */
        template <typename OutputIt>
        size_t Read(OutputIt first, OutputIt last) throw(IpcException)
        {
            // TODO: implementieren
        }

        /*!
         * This method reads a single byte from the shared memory. If any error
         * happens, than this method returns -1.
         * If this method succeeds, than it returns a value between 0 and 255.
         *
         * \returns Byte value or -1
         */
        int ReadByte() NOEXCEPT;
    };
}

#endif
