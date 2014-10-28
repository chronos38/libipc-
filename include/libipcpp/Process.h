#ifndef LIBIPC_PROCESS_H
#define LIBIPC_PROCESS_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"

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
        ProcessHandle mHandle = PROCESS_NULL_HANDLE;

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
         * \param[in,out] p The Process instance that should be moved to a new handle
         */
        Process(Process&& p);

        /*!
         * Creates a new process and immediately start the given function f.
         * The arguments for are provided through the variable argument list.
         *
         * \param[in]  f       Function to call as a main.
         * \param[in]  args    Argument list for the function.
         */
        template <class Function, class... Args>
        Process(Function&& f, Args&&... args) throw(IpcException)
        {
            // TODO: implementieren
        }

        /*!
         * The destructor is not exception safe and can throw an exception of 
         * the type IpcException. Exceptions occur when the process can not 
         * be killed.
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
         * Reads the exit code of the process. The value depends heavily on the
         * used operating systems.
         *
         * \returns The exit code of the process.
         */
        int32_t ExitCode() const NOEXCEPT;

        /*!
         * Gets the current process state. If the state equals
         * ProcessState::Invalid, than this class has an undefined state.
         *
         * \returns Current process state.
         */
        ProcessState GetState() const NOEXCEPT;

        /*!
         * Terminates the process and sets the instance state to "invalid".
         * A exception of the type IpcException is thrown on error.
         *
         */
        void Kill() throw(IpcException);

        /*!
         * Starts the execution with the specified function. This function
         * serves as a main function. The function itself could be a function
         * pointer, lambda expression or functional object.
         *
         * \param[in]  f       Function to call as a main function.
         * \param[in]  args    Variable argument list given as function
         *                      arguments.
         */
        template <class Function, class... Args>
        void Start(Function&& f, Args&&... args) throw(IpcException)
        {
            // TODO: implementieren
        }
        
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
         * \param[in]  timeoutDuration Maximum duration to wait for termination
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
         * \param[in]  timeoutTime Wait until this point for termination
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
         * \param[in]  main The function object to be executed
         * \param[in]  args The function parameters
         *
         * \returns Pointer to the new Process instance.
         */
        template <typename Function, typename... Args>
        static std::shared_ptr<Process> Create(Function&& main, Args&&... args) throw(IpcException)
        {
            // TODO: implementieren
        }

        /*!
         * Searches for a process by name and returns a pointer to the first match.
         * If no process is found a nullptr is returned
         *
         * \param[in]  name    Name to search for.
         * \returns Pointer to a process, nullptr if no match exists
         */
        static std::vector<std::shared_ptr<Process>> GetProcessByName(const std::string& name) NOEXCEPT;

        /*!
         * Returns a Vector of all currently running processes.
         *
         * \returns Vector of all running processes
         */
        static std::vector<ProcessInfo> GetProcesses() NOEXCEPT;

    private:

        Process(const Process&) = delete;
    };
}

#endif
