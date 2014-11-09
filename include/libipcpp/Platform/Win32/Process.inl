#ifdef _MSC_VER

namespace ipc {
    template <typename Rep, typename Period>
    bool Process::WaitFor(const std::chrono::duration<Rep, Period>& timeoutDuration) throw(ProcessException)
    {
        // TODO: Win32 Code implementieren.
    }

    template <typename Clock, typename Duration>
    bool Process::WaitUntil(const std::chrono::time_point<Clock, Duration>& timeoutTime) throw(ProcessException)
    {
        // TODO: Win32 Code implementieren.
    }
}

#endif
