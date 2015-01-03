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

#ifndef LIBIPC_MEMORYMAP_H
#define LIBIPC_MEMORYMAP_H

#ifdef _MSC_VER
#pragma once
#endif

#include "exception/MemoryMapException.h"
#include "IOBase.h"

namespace ipc {
    //! A memory map references a file memory in the RAM.
    class LIBIPC_API MemoryMap : public IOBase, public ReferenceType
    {
    public:
        /*!
         * Creates a new memory map with given file. All memory from the file
         * is loaded and referenced in the RAM. If an error occurs while
         * creating this object, than the thrown exception provides the
         * necessary information.
         *
         * \param[in]   fileName    File name for creating the memory map.
         */
        MemoryMap(const std::string& fileName) throw(MemoryMapException);

        /*!
         * Creates a new memory map with at leas the given byte size. If there
         * is not enough memory available or any other error happens while
         * trying to create the memory map, than the thrown exceptions provides
         * the necessary information.
         *
         * \param[in]   byteCount   The size in bytes for this memory map.
         */
        MemoryMap(ByteCount byteCount);
        virtual ~MemoryMap();

        /*!
         * Gets the length for this shared memory.
         * \returns Length in bytes for this shared memory.
         */
        virtual ByteCount Length() const NOEXCEPT;

        /*!
         * Gets the current zero based position within this memory.
         * \returns Position in this map.
         */
        virtual ByteCount Position() const NOEXCEPT;

        /*!
         * Sets the position within this memory. If the position is out of
         * range, than the particular exception is raised. A value of zero sets
         * the position on the beginning of this map.
         */
        virtual void Position(ByteCount position) const throw(std::out_of_range);

        /*!
         * Writes a buffer to this shared memory. This method is not safe for
         * concurrent execution. It needs an external lock mechanism to be
         * considered safe. If two write operations happen at the same time,
         * than the behavior is undefined.
         *
         * For the remaining errors an IpcException is thrown.
         *
         * \param[in]   buffer  The byte buffer to write to the shared memory.
         * \param[in]   size    The actual size to write.
         * \returns Count of written bytes to the shared memory.
         */
        virtual ByteCount Write(const char* buffer, size_t size) const throw(MemoryMapException) override;

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
        ByteCount Write(InputIt first, InputIt last) const throw(IpcException);

        /*!
         * Writes a single byte to the shared memory. If this method fails it does
         * not throw an exception, but instead it returns zero (0).
         *
         * \returns Either 1 or 0.
         */
        virtual ByteCount WriteByte(char byte) const NOEXCEPT override;

        /*!
         * This method reads from the shared memory. All read bytes are written
         * into the given byte buffer. It is possible to define an offset
         * and read size for this method. So the range is customizable.
         *
         * For the remaining errors an IpcException is thrown.
         *
         * \param[in,out]   buffer  Target buffer for this operation.
         * \param[in]   size    The actual size to write.
         * \returns Count of read bytes from the shared memory.
         */
        virtual ByteCount Read(char* buffer, size_t size) const throw(MemoryMapException) override;

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
        ByteCount Read(OutputIt first, OutputIt last) const throw(IpcException);

        /*!
         * This method reads a single byte from the shared memory. If any error
         * happens, than this method returns -1.
         * If this method succeeds, than it returns a value between 0 and 255.
         *
         * \returns Byte value or -1
         */
        virtual int ReadByte() const NOEXCEPT override;

    private:

        IpcHandle mHandle = INVALID_HANDLE;
        mutable void* mBuffer = nullptr;
        mutable ByteCount mPosition = 0;
        ByteCount mLength = 0;
    };
}

#ifdef _MSC_VER
#include "platform/win32/MemoryMap.inl"
#else
#include "platform/linux/MemoryMap.inl"
#endif

#endif
