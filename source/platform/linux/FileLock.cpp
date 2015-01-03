#include "../../../include/libipcpp/FileLock.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>

ipc::FileLock::FileLock(const IpcHandle fileHandle) throw(FileLockException)
{
    struct flock fl = {F_WRLCK, SEEK_SET, 0, 0, 0};
    fl.l_pid = getpid();
    mFlock = fl;
    mHandle = fileHandle;
}

ipc::FileLock::~FileLock()
{
}

void ipc::FileLock::Lock() throw(FileLockException)
{
    mFlock.l_type = F_WRLCK;
    int rv = fcntl(mHandle, F_SETLK, &mFlock);
    if (rv == -1)
        throw FileLockException(std::string("Could not lock the file!"));
}

void ipc::FileLock::Unlock() throw(FileLockException)
{
    mFlock.l_type = F_UNLCK;
    int rv = fcntl(mHandle, F_SETLK, &mFlock);
    if (rv == -1)
        throw FileLockException(std::string("Could not unlock the file!"));
}

