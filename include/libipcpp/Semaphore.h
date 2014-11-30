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

#ifndef LIBIPC_SEMAPHORE_H
#define LIBIPC_SEMAPHORE_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Exception/SemaphoreException.h"

namespace ipc {
    /*!
     * A semaphore provides an interface for critical section locking. The
     * class encapsulates a system resource also named semaphore.
     */
    class LIBIPC_API Semaphore : public ReferenceType
    {
    public:
        //! Creates a new semaphore object.
        Semaphore(); // TODO: Count angeben?
        //! Frees all allocated resources.
        virtual ~Semaphore();

        /*!
         * This operation locks the semaphore. If the semaphore is not already
         * locked, the execution continous immediately. If the semaphore is
         * alreayd locked by another process or thread, than the execution
         * blocks until the semphore is unlocked from the owner.
         *
         * If two or more processes or threads are blocked by this method and
         * the owner unlocks it. Than the order for the next owner is not
         * specified.
         */
        void Lock() throw(SemaphoreException);

        /*!
         * Tries to lock the semaphore. The executing thread or process gets
         * ownership of the semaphore if it is not already locked. In that case
         * this method returns TRUE. Otherwise if the semaphore is alraedy
         * locked, than this method returns FALSE. In general this is a non
         * blocking method.
         *
         * \returns TRUE if locked successful, in any other case FALSE.
         */
        bool TryLock() throw(SemaphoreException);

        /*!
         * Unlocks the semaphore. This method should be only called by the
         * owning thread or process. If this method gets called from an non
         * owning thread or process, than the behavior is undefined.
         *
         * This method is non blocking and returns immediately.
         */
        void Unlock() throw(SemaphoreException);

    private:

        IpcHandle mHandle = INVALID_HANDLE;
    };
}

#endif
