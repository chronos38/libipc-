#ifdef _MSC_VER

#include "libipcpp\Semaphore.h"
#include "libipcpp\Utility.h"

namespace ipc {
    Semaphore::Semaphore()
    {
        SECURITY_ATTRIBUTES attr;
        attr.bInheritHandle = TRUE;
        attr.nLength = sizeof(SECURITY_ATTRIBUTES);
        attr.lpSecurityDescriptor = NULL;

        if ((mHandle = CreateSemaphore(&attr, 1, 1, NULL)) == NULL) {
            throw SemaphoreException(GetLastErrorString());
        }
    }

    Semaphore::~Semaphore()
    {
        if (mHandle != NULL) {
            BOOL success = CloseHandle(mHandle);
            mHandle = NULL;

            if (!success) {
                fprintf(stderr, "Silent throw in semaphore: %s\n", GetLastErrorString().c_str());
            }
        }
    }

    void Semaphore::Lock()
    {
        if (mHandle != NULL) {
            if (WaitForSingleObject(mHandle, INFINITE) == WAIT_FAILED) {
                throw SemaphoreException(GetLastErrorString());
            }
        } else {
            throw SemaphoreException("Invalid semaphore handle.");
        }
    }

    bool Semaphore::TryLock()
    {
        if (mHandle != NULL) {
            switch (WaitForSingleObject(mHandle, 0)) {
            case WAIT_OBJECT_0:
                return true;

            case WAIT_ABANDONED:
            case WAIT_TIMEOUT:
                return false;

            case WAIT_FAILED:
                throw SemaphoreException(GetLastErrorString());
            }
        } else {
            throw SemaphoreException("Invalid semaphore handle.");
        }
    }

    void Semaphore::Unlock()
    {
        if (mHandle != NULL) {
            if (!ReleaseSemaphore(mHandle, 1, NULL)) {
                throw SemaphoreException(GetLastErrorString());
            }
        } else {
            throw SemaphoreException("Invalid semaphore handle.");
        }
    }
}

#endif
