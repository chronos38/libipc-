#include "../include/libipcpp/Process.h"

using string = std::string;

namespace ipc {
    int64_t ProcessInfo::GetId() const NOEXCEPT
    {
        return mId;
    }

    string ProcessInfo::GetName() const NOEXCEPT
    {
        return mName;
    }

    ProcessHandle ProcessInfo::GetHandle() const NOEXCEPT
    {
        return mHandle;
    }

    ProcessInfo Process::GetProcessInfo() const NOEXCEPT
    {
        return mProcessInfo;
    }
}
