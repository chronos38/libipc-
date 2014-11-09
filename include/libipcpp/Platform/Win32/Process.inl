#ifdef _MSC_VER

namespace ipc {
    template <typename Rep, typename Period>
    bool Process::WaitFor(const std::chrono::duration<Rep, Period>& timeoutDuration) throw(ProcessException)
    {
        if (WaitForSingleObject(mProcess, static_cast<DWORD>(std::chrono::duration_cast<std::chrono::milliseconds>(timeoutDuration).count())) == WAIT_FAILED) {
            // TODO: Systeminformation abrufen und als Argument übergeben.
            throw ProcessException("");
        } else {
            mProcess = PROCESS_INVALID_HANDLE;
            mState = ProcessState::Invalid;
        }
    }

    template <typename Clock, typename Duration>
    bool Process::WaitUntil(const std::chrono::time_point<Clock, Duration>& timeoutTime) throw(ProcessException)
    {
        // TODO: Win32 Code implementieren.
    }
}

#endif
