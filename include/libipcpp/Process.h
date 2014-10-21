#ifndef LIBIPC_PROCESS_H
#define LIBIPC_PROCESS_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"

namespace ipc {
    //! This class saves important process data
    class LIBIPC_API ProcessInfo
    {
    public:
        //! Creates a new class
        ProcessInfo() = default;
        //! Standard copy constructor
        ProcessInfo(const ProcessInfo&) = default;
        //! Standard destructor
        ~ProcessInfo() = default;

#ifdef _MSC_VER
        ProcessInfo(ProcessInfo&&);
#else
        ProcessInfo(ProcessInfo&&) = default;
#endif

        /*!
         * On success the process ID is returned.
         * On failure -1 is returned this might be caused by an invalid process
         *
         * \returns Process ID or -1 on failure
         */
        int32_t GetId() const NOEXCEPT;

        /*!
         * The name of the process is returned.
         * An empty string is returned in case the process is invalid
         *
         * \returns Process name
         */
        std::string GetName() const NOEXCEPT;

        /*!
         *
         * Allows access to the native process handle.
         *
         * \return Native process handle
         */
        ProcessHandle GetHandle() const NOEXCEPT;

    private:
        int32_t mId = 0;
        std::string mName = "";
        ProcessHandle mHandle = PROCESS_NULL_HANDLE;

        friend class Process;
    };

    class LIBIPC_API Process : public ReferenceType
    {
    public:
        //TODO: Add Start() method
        /*!
         * Creates a new Process instance.
         *
         * \b Exceptions:
         * - IpcException
         */
        Process() throw(IpcException);

        /*!
         * Move constructor
         *
         * \params[in,out] p The Process instance that should be moved to a new handle
         */
        Process(Process&& p);

        /*!
         * The destructor is not exception safe and can throw an exception of the type IpcException.
         * Exceptions occur when the process can not be killed.
         *
         */
        virtual ~Process() throw(IpcException);

        /*!
         * Checks if the process is in a valid state.
         * A Process in an invalid state can not be used.
         *
         * \returns TRUE when the Process is in a valid state, otherwise FALSE is returned.
         */
        bool IsValid() const NOEXCEPT;

        /*!
         * Reads the exit code of the process.
         * If the process has not exited yet one of the following codes is returned:
         *
         * \b States:
         * - PROCESS_NOT_STARTED
         * - PROCESS_STILL_RUNNING
         * - PROCESS_NOT_VALID
         *
         * \returns The exit code of the process.
         */
        int32_t ExitCode() const NOEXCEPT;
        //! The process has not been started.
        static const int32_t PROCESS_NOT_STARTED = 0x80000000;
        //! The process is running.
        static const int32_t PROCESS_STILL_RUNNING = 0x80000001;
        //! The process is in an invalid state.
        static const int32_t PROCESS_NOT_VALID = 0x80000002;

        /*!
         * Terminates the process and sets the instance state to "invalid".
         * A exception of the type IpcException is thrown on error.
         *
         */
         void Kill() throw(IpcException);
        
        /*!
         * Wait until the process has stopped execution.
         * Returns immediately if the process is not running or in an invalid state.
         * This method is blocking.
         *
         * \returns Reference to the process.
         */
        Process& Wait() NOEXCEPT;

        /*!
         * Equal behaviour to Wait but returns after a certain time.
         *
         * \params[in]  timeoutDuration Maximum duration to wait for termination
         * \returns TRUE if the process terminated, otherwise FALSE.
         */
        template <typename Rep, typename Period>
        bool WaitFor(const std::chrono::duration<Rep, Period>& timeoutDuration) const NOEXCEPT
        {
            // TODO: implementieren
        }

        /*!
         *  Similar to WaitFor but waits until a certain point in time is reached.
         *
         * \params[in]  timeoutTime Wait until this point for termination
         * \returns TRUE if the process terminated, otherwise FALSE.
         */
        template <typename Clock, typename Duration>
        bool WaitUntil(const std::chrono::time_point<Clock, Duration>& timeoutTime) const NOEXCEPT
        {
            // TODO: implementieren
        }

        /*!
         * Creates a new process and executes the passed function as main function.
         * Throws an IpcException on error.
         *
         * \b Exception:
         * - IpcException
         *
         * \params[in]  main    The function object to be executed
         * \params[in]  args... The function parameters
         *
         * \returns Pointer to the new Process instance.
         */
        template <typename Function, typename... Args>
        static std::shared_ptr<Process> Create(Function&& main, Args&&... args) throw(IpcException)
        {
            // TODO: implementieren
        }

        /*!
         *
         * Searches for a process by name and returns a pointer to the first match.
         * If no process is found a nullptr is returned
         *
         * \returns Pointer to a process, nullptr if no match exists
         */
        static std::shared_ptr<Process> GetProcessByName(const std::string&) NOEXCEPT;

        /*!
         * Returns a Vector of all currently running processes.
         *
         * \returns Vector of all running processes
         */
        static std::vector<ProcessInfo> GetProcesses() NOEXCEPT;

    protected:

    private:

        Process(const Process&) = delete;
    };
}

#endif
