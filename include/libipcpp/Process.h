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

#ifndef LIBIPC_PROCESS_H
#define LIBIPC_PROCESS_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"
#include "Utility.h"
#include "exception/ProcessException.h"

namespace ipc {
    //! This class saves important process data.
    class LIBIPC_API ProcessInfo
    {
    public:
        //! Creates a new class.
        ProcessInfo() = default;
        //! Standard copy constructor.
        ProcessInfo(const ProcessInfo&) = default;
        //! Standard destructor.
        ~ProcessInfo() = default;

#ifdef _MSC_VER
        //! Explicit implemenation for Win32
        ProcessInfo(ProcessInfo&&);
#else
        //! Default move constructor
        ProcessInfo(ProcessInfo&&) = default;
#endif
        
        ProcessInfo& operator=(const ProcessInfo&) = default;

        /*!
         * On success the process ID is returned.
         * On failure -1 is returned this might be caused by an invalid process.
         *
         * \returns Process ID or -1 on failure.
         */
        int64_t GetId() const NOEXCEPT;

        /*!
         * The name of the process is returned.
         * An empty string is returned in case the process is invalid
         *
         * \returns Name of the process.
         */
        std::string GetName() const NOEXCEPT;

        /*!
         *
         * Allows access to the native process handle.
         *
         * \return Native process handle.
         */
        ProcessHandle GetHandle() const NOEXCEPT;

    private:
        int64_t mId = 0;
        std::string mName = "";
        ProcessHandle mHandle = PROCESS_INVALID_HANDLE;

        friend class Process;
    };

    //! Process state enumeration.
    enum class ProcessState : uint8_t {
        NotRunning, //!< Process is not running.
        IsRunning, //!< Process is running.
        Invalid //!< Process has an invalid state.
    };

    //! Process class for multi processing.
    class LIBIPC_API Process : public ReferenceType
    {
    public:
        /*!
         * Creates a new Process instance.
         *
         * \b Exceptions:
         * - ProcessException
         *
         * \param[in] fileName The executable file for the new process.
         * \param[in] args Arguments for the new process.
         */
        Process(const std::string& fileName, const std::vector<std::string>& args) throw(ProcessException);

        /*!
         * Creates a new Process instance.
         *
         * \b Exceptions:
         * - ProcessException
         *
         * \param[in] fileName The executable file for the new process.
         * \param[in] args Arguments for the new process.
         */
        Process(const std::string& fileName, const std::string& args) throw(ProcessException);
        
       /*!
        * Creates a new Process instance. The process class does not take
        * ownership of this handle. Therefore if the process is still running,
        * the destructor does not kill it.
        * 
        * \b Exceptions:
        * - ProcessException
        * 
        * \param[in] info The ProcessHandle of the Process to be managed by the Instance.
        */ 
        Process(const ProcessInfo& info);

        /*!
         * Move constructor
         *
         * \param[in,out] p The Process instance that should be moved to a new handle
         */
        Process(Process&& p);

        /*!
         * The destructor is not exception safe and can throw an exception of 
         * the type ProcessException. Exceptions occur when the process can not 
         * be killed.
         *
         */
        virtual ~Process();

        /*!
         * Checks if the process is in a valid state.
         * A Process in an invalid state can not be used.
         *
         * \returns TRUE when the Process is in a valid state, otherwise FALSE is returned.
         */
        bool IsValid() NOEXCEPT;

        /*!
         * Reads the exit code of the process. The value depends heavily on the
         * used operating systems.
         *
         * If the process is still running, than the return value is undefined.
         *
         * \returns The exit code of the process.
         */
        int32_t ExitCode() const throw(ProcessException);

        /*!
         * Gets the current process state. If the state equals
         * ProcessState::Invalid, than this class has an undefined state.
         *
         * \returns Current process state.
         */
        ProcessState GetState() const NOEXCEPT;

        /*!
         * Terminates the process and sets the instance state to "invalid".
         * A exception of the type ProcessException is thrown on error.
         */
        void Kill() throw(ProcessException);
        
        /*!
         * Wait until the process has stopped execution.
         * Returns immediately if the process is not running or in an invalid state.
         * This method is blocking.
         *
         * \returns Reference to the process.
         */
        Process& Wait() throw(ProcessException);

        /*!
         * Equal behaviour to Wait but returns after a certain time.
         *
         * \param[in]  timeoutDuration Maximum duration to wait for termination
         * \returns TRUE if the process terminated, otherwise FALSE.
         */
        template <typename Rep, typename Period>
        bool WaitFor(const std::chrono::duration<Rep, Period>& timeoutDuration) throw(ProcessException);

        /*!
         *  Similar to WaitFor but waits until a certain point in time is reached.
         *
         * \param[in]  timeoutTime Wait until this point for termination
         * \returns TRUE if the process terminated, otherwise FALSE.
         */
        template <typename Clock, typename Duration>
        bool WaitUntil(const std::chrono::time_point<Clock, Duration>& timeoutTime) throw(ProcessException);

        /*!
         * Searches for a process by name and returns a pointer to the first match.
         * If no process is found a nullptr is returned
         *
         * \param[in]  name    Name to search for.
         * \returns Pointer to a process, nullptr if no match exists
         */
        static std::vector<ProcessInfo> GetProcessByName(const std::string& name) throw(ProcessException);

        /*!
         * Returns a Vector of all currently running processes.
         *
         * \returns Vector of all running processes
         */
        static std::vector<ProcessInfo> GetProcesses() throw(ProcessException);
        
        /*!
         * 
         * \returns This getter returns a copy of the ProcessInfo object.
         */
        ProcessInfo GetProcessInfo() const NOEXCEPT;
        
#ifdef _MSC_VER
        Process& operator=(Process&&);
#else
        Process& operator=(Process&&) = default;
#endif
        
    private:

        Process() = delete;
        Process(const Process&) = delete;

        bool mIsOwner = false;
        ProcessInfo mProcessInfo;
#ifdef _MSC_VER
        ProcessHandle mThread = PROCESS_INVALID_HANDLE;
#else
        void ValidateProcessHandle();
        
        int32_t mStatus;
#endif
    };
}

#include "platform/linux/Process.inl"
#include "platform/win32/Process.inl"

#endif
