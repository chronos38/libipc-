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

#ifndef LIBIPC_LOCKGUARD_H
#define LIBIPC_LOCKGUARD_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"

namespace ipc {
    //! High level locking class to lock in scope.
    template <typename T>
    class LIBIPC_API LockGuard
    {
    public:
        //! Locks given lockable object.
        LockGuard(T& t) :
            mT(t)
        {
            mT.Lock();
        }

        //! Unlocks object
        ~LockGuard()
        {
            mT.Unlock();
        }

        LockGuard() = delete;
        LockGuard(const LockGuard&) = delete;
        LockGuard(LockGuard&&) = delete;

        LockGuard& operator=(const LockGuard&) = delete;
        LockGuard& operator=(LockGuard&&) = delete;

    private:

        T& mT;
    };
}

#endif
