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

#ifndef UTILITY_H
#define UTILITY_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"

namespace ipc {

    /*!
     * Checks if a filename is compatible with Windows
     *
     * \params[in] fileName The filename that should be checked
     * \returns TRUE if the filename was OK, else FALSE
     */
    LIBIPC_API bool IsValidFileName(std::string& fileName);
    /*!
     * Checks wether a string is solely composed of numbers.
     * 
     * \param[in] input The string to be checked.
     * 
     * \returns Returns True if the string is only containing numbers.
     */
    LIBIPC_API bool IsNumber(const std::string& input);
    /*!
     * Splits a string into tokens using the passed delimiters
     * 
     * \param[in] str The string to be split into tokens
     * \param[in] delimiters The delimiters used to split the string
     * \param[out] tokens The resulting tokens
     */
    LIBIPC_API void SplitString(const std::string& str,
                        const std::string& delimiters,
                        std::vector<std::string>& tokens);

#ifdef _MSC_VER
    /*!
     * Get last system error string from Win32.
     *
     * \returns Last system error string.
     */
	LIBIPC_API std::string GetLastErrorString();
#endif

}
#endif
