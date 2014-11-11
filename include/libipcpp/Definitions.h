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

#ifndef LIBIPC_DEFINITIONS_H
#define LIBIPC_DEFINITIONS_H

#ifdef _MSC_VER
#pragma once
#include <Windows.h>
#pragma warning(disable: 4290)
#define NOEXCEPT throw()

#ifdef LIBIPC_EXPORT
#define LIBIPC_API __declspec(dllexport)
#else
#define LIBIPC_API __declspec(dllimport)
#endif

namespace ipc {
    //! Global OS handle
    typedef HANDLE IpcHandle;
    //! Native OS null handle
    static const IpcHandle INVALID_HANDLE = nullptr;
    //! Native process handle
    typedef HANDLE ProcessHandle;
    //! Native process null handle
    static const ProcessHandle PROCESS_INVALID_HANDLE = nullptr;
    //! Native byte count type
    typedef DWORD ByteCount;
}

#else
#define NOEXCEPT noexcept
#include <sys/types.h>

#ifdef LIBIPC_EXPORT

#ifdef __CYGWIN__
#define LIBIPC_API __attribute__ ((dllexport))
#else
#define LIBIPC_API __attribute__ ((visibility ("default")))
#endif

#else

#ifdef __CYGWIN__
#define LIBIPC_API __attribute__ ((dllimport))
#else
#define LIBIPC_API __attribute__ ((visibility ("default")))
#endif

#endif
namespace ipc {
    //! Global OS handle
    typedef int IpcHandle;
    //! Native OS null handle
    static const IpcHandle INVALID_HANDLE = -1;
    //! Native process handle
    typedef pid_t ProcessHandle;
    //! Native process null handle
    static const ProcessHandle PROCESS_INVALID_HANDLE = -1;
    //! Native byte count type
    typedef ssize_t ByteCount;
}
#endif

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <functional>
#include <exception>

namespace ipc {
    //! Type is not copyable
    class LIBIPC_API ReferenceType
    {
    public:
        //! Default constructor
        ReferenceType() = default;
        //! Default destructor
        virtual ~ReferenceType() = default;

#ifdef _MSC_VER
        //! Explicit implemenation for Win32
        ReferenceType(ReferenceType&&);
        //! Explicit implemenation for Win32
        ReferenceType& operator=(ReferenceType&&);
#else
        //! Default move constructor
        ReferenceType(ReferenceType&&) = default;
        //! Default move assignment operator
        ReferenceType& operator=(ReferenceType&&) = default;
#endif
    private:
        ReferenceType(const ReferenceType&) = delete;
        ReferenceType& operator=(const ReferenceType&) = delete;
    };

}

#endif
