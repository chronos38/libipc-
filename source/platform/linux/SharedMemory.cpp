#include "../../../include/libipcpp/SharedMemory.h"
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cstring>

namespace ipc {
    SharedMemory::SharedMemory(ByteCount byteCount) throw(SharedMemoryException) :
        mLength(byteCount)
    {
        //TODO: Key muss kontrollierbar sein
        key_t shmkey = ftok("dev/null/", 123);
        mHandle = shmget(shmkey, byteCount, 0664 | IPC_CREAT);
        if (mHandle < 0) {
            char * err = strerror(errno);
            throw SharedMemoryException(std::string("Failed to aquire shared memory: ")+  err);
        }
        
        mBuffer = shmat(mHandle, NULL, 0);
        if (mHandle == (void*) -1) {
            char * err = strerror(errno);
            throw SharedMemoryException(std::string("Failed to aquire shared memory: ")+  err);
        }
        
        
        
    }

    SharedMemory::~SharedMemory()
    {
        shmdt(mBuffer);
        shmctl (mHandle, IPC_RMID, 0);
        
        mBuffer = nullptr;
        mHandle = INVALID_HANDLE;
    }
}
