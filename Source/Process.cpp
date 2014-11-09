#include "../include/libipcpp/Process.h"

using namespace std;

namespace ipc {
    int64_t ProcessInfo::GetId() const
    {
        return mId;
    }

    string ProcessInfo::GetName() const
    {
        return mName;
    }

    ProcessHandle ProcessInfo::GetHandle() const
    {
        return mHandle;
    }

    bool Process::IsValid() const
    {
        return (mProcess != PROCESS_INVALID_HANDLE && mState != ProcessState::Invalid);
    }

    ProcessState Process::GetState() const
    {
        return mState;
    }
}
