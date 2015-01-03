#include <libipcpp\FileLock.h>
#include <libipcpp\Utility.h>

using string = std::string;

namespace ipc {
    FileLock::FileLock(const IpcHandle fileHandle)
    {
        SECURITY_ATTRIBUTES attr;

        memset(&attr, 0, sizeof(attr));
        attr.nLength = sizeof(attr);
        attr.bInheritHandle = TRUE;

        mHandle = fileHandle;

        if (mHandle == INVALID_HANDLE_VALUE) {
            throw FileLockException(GetLastErrorString());
        }
    }

    FileLock::~FileLock()
    {
    }

    void FileLock::Lock()
    {
        DWORD high = 0;

        if (!LockFile(mHandle, 0, 0, GetFileSize(mHandle, &high), high)) {
            throw FileLockException(GetLastErrorString());
        }
    }

    void FileLock::Unlock()
    {
        DWORD high = 0;

        if (!UnlockFile(mHandle, 0, 0, GetFileSize(mHandle, &high), high)) {
            throw FileLockException(GetLastErrorString());
        }
    }
}
