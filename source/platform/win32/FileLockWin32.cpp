#include <libipcpp\FileLock.h>
#include <libipcpp\Utility.h>

using string = std::string;

namespace ipc {
    FileLock::FileLock(const string& path)
    {
        SECURITY_ATTRIBUTES attr;

        memset(&attr, 0, sizeof(attr));
        attr.nLength = sizeof(attr);
        attr.bInheritHandle = TRUE;

        mHandle = CreateFileA(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &attr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (mHandle == INVALID_HANDLE_VALUE) {
            throw FileLockException(GetLastErrorString());
        }
    }

    FileLock::~FileLock()
    {
        CloseHandle(mHandle);
        mHandle = INVALID_HANDLE;
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
