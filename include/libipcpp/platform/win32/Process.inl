#ifdef _MSC_VER

namespace ipc {
    template <typename Rep, typename Period>
    bool Process::WaitFor(const std::chrono::duration<Rep, Period>& timeoutDuration) throw(ProcessException)
    {
        if (mProcess != PROCESS_INVALID_HANDLE) {
            DWORD result = WaitForSingleObject(mProcess, static_cast<DWORD>(std::chrono::duration_cast<std::chrono::milliseconds>(timeoutDuration).count()));

            switch (result) {
            case WAIT_FAILED:
                // TODO: Systeminformation abrufen und als Argument übergeben.
                throw ProcessException("");

            case WAIT_TIMEOUT:
                return false;

            default:
                return true;
            }
        } else {
            throw ProcessException("Invalid process handle");
        }
    }

    template <typename Clock, typename Duration>
    bool Process::WaitUntil(const std::chrono::time_point<Clock, Duration>& timeoutTime) throw(ProcessException)
    {
        if (mProcess != PROCESS_INVALID_HANDLE) {
            auto timeoutDuration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - timeoutTime);

            if (timeoutDuration.count() > 0) {
                DWORD result = WaitForSingleObject(mProcess, static_cast<DWORD>(timeoutDuration.count()));

                switch (result) {
                case WAIT_FAILED:
                    // TODO: Systeminformation abrufen und als Argument übergeben.
                    throw ProcessException("");

                case WAIT_TIMEOUT:
                    return false;

                default:
                    return true;
                }
            }
        } else {
            throw ProcessException("Invalid process handle");
        }
    }
}

#endif
