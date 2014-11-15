#ifndef _MSC_VER
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

    bool Process::IsValid() const NOEXCEPT
    {
        return (mProcessInfo.mHandle != PROCESS_INVALID_HANDLE);
    }
    
    ProcessInfo Process::GetProcessInfo() const NOEXCEPT
    {
        return mProcessInfo;
    }
}
#endif
