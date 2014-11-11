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

#ifndef LIBIPC_SHAREDMEMORY_EXCEPTION
#define LIBIPC_SHAREDMEMORY_EXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#include "IpcException.h"
#include <string>
#include <exception>

namespace ipc
{
    class LIBIPC_API SharedMemoryException : public IpcException
    {
    public:
        SharedMemoryException(const std::string& );
        SharedMemoryException(const std::string& , const exception& ex);
        virtual ~SharedMemoryException() = default;
    };

}


#endif //SHAREDMEMORY_EXCEPTION
