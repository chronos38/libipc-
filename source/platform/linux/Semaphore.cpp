#include "../../../include/libipcpp/Semaphore.h"
#include <fcntl.h>
#include <sys/ipc.h>
#include <string>
#include <cstring>

namespace ipc
{
    Semaphore::Semaphore()
    {
        
        mHandle = ftok("/proc/self/exe", 7);
        std::string semaphoreName("Semaphore_");
        semaphoreName.append(std::to_string(mHandle));
        
        mSem = sem_open(semaphoreName.c_str(), O_CREAT | O_EXCL, 0644 , 1);
        sem_unlink(semaphoreName.c_str());
        
        
    }

    Semaphore::~Semaphore()
    {
        int rv = sem_destroy(mSem);
        if (rv < 0) {
                fprintf(stderr, "Silent throw in semaphore: %s\n", strerror(errno));
        }
    }

    void Semaphore::Lock() throw(SemaphoreException)
    {
        int rv =sem_wait(mSem);
        if (rv < 0)
        {
            char * err =  strerror(errno);
            throw SemaphoreException(std::string("Failed to lock Semaphore: ") + err);
        }
    }
    
    bool Semaphore::TryLock() throw(SemaphoreException)
    {
        int rv =sem_trywait(mSem);
        if (rv < 0)
        {
            if (errno == EAGAIN)
                return false;
            
            char * err =  strerror(errno);
            throw SemaphoreException(std::string("Failed to lock Semaphore: ") + err);
        }
        return true;
    }
    
    void Semaphore::Unlock() throw(SemaphoreException)
    {
        int rv = sem_post(mSem);
        if (rv < 0)
        {
            char * err =  strerror(errno);
            throw SemaphoreException(std::string("Failed to lock Semaphore: ") + err);
        }
    }
 
}