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

#ifndef LIBIPC_FILELOCK_H
#define LIBIPC_FILELOCK_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"
#include "exception/FileLockException.h"

namespace ipc {
    //! Locks a specified file for a critical section or memory editing
    class LIBIPC_API FileLock : public ReferenceType
    {
    public:
        /*!
         * Creates a new lock for the specified file provided in the argument
         * path. If the file has already an lock, than this operation blocks
         * until the file gets unlocked again.
         *
         * If two or more attempted locks are queued. Than the order for the
         * next lock is not specified.
         */
        FileLock(const std::string& path) throw(FileLockException);

        /*!
         * Frees all allocated resources and unlocks the file if not already
         * unlocked.
         */
        virtual ~FileLock();

        /*!
         * This method locks the file for exclusive use. If the file is already
         * locked, than this method blocks until the file gets unlocked.
         *
         * If this method gets called multiple times by the same process, than 
         * the behavior is undefined.
         */
        void Lock() throw(FileLockException);

        /*!
         * Unlocks the file manually. The destructor will not attempt to unlock
         * the file. If the file is already unlocked, than this method does
         * nothing.
         *
         * This is a non blocking method and it returns immediately after it is
         * called.
         *
         * If this method gets called by a non owning process, than the
         * behavior is undefined.
         */
        void Unlock() throw(FileLockException);

    private:
        //! No default constructor.
        FileLock() = delete;

#ifdef _MSC_VER
        IpcHandle mHandle;
#endif
    };
}

#endif
