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
}
