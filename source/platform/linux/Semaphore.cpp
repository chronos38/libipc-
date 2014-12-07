#include "../../../include/libipcpp/Semaphore.h"
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <cstring>

namespace ipc
{
    
    union semun {
       int              val;    /* Value for SETVAL */
       struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
       unsigned short  *array;  /* Array for GETALL, SETALL */
       struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
    };

    Semaphore::Semaphore()
    {
        // Using the executable of the running program as key
        //key_t key = ftok("/proc/self/exe", 7);
        key_t key = ftok("Makefile", 7);
        mHandle = semget(key, 1, IPC_CREAT |  0660);
        
        if (mHandle < 0) {
            char * tmp = strerror(errno);
            throw new SemaphoreException(std::string("Semaphore creation failed: ") + strerror(errno));
        }
        
        union semun arg;
        arg.val = 1;
        semctl(mHandle, 0, SETVAL, arg);
    }

    Semaphore::~Semaphore()
    {
        
        int rv =semctl(mHandle, 0, IPC_RMID, 0);
        if (rv < 0) {
            fprintf(stderr, "Silent throw in semaphore: %s\n", strerror(errno));
        }
        mHandle = INVALID_HANDLE;
    }

    void Semaphore::Lock() throw(SemaphoreException)
    {
        struct sembuf sb;
        sb.sem_num = 0;
        sb.sem_op = -1;
        sb.sem_flg = 0;

        int rv = semop(mHandle, &sb, 1);
        if (rv < 0) {
            throw SemaphoreException(std::string("Failed to aquire lock.") + strerror(errno));
        }
    }
    
    bool Semaphore::TryLock() throw(SemaphoreException)
    {
        struct sembuf sb;
        sb.sem_num = 0;
        sb.sem_op = -1;
        sb.sem_flg = IPC_NOWAIT;
        
        
        int rv = semop(mHandle, &sb, 1);
        if (rv == EAGAIN) {
            return false;
        } else if(rv < 0) {
            throw SemaphoreException(std::string("Failed to aquire lock.") + strerror(errno));
        }
        return true;
    }
    
    void Semaphore::Unlock() throw(SemaphoreException)
    {
        struct sembuf sb;
        sb.sem_num = 0;
        sb.sem_op = 1;
        sb.sem_flg = 0;
        
        int rv = semop(mHandle, &sb, 1);
        if (rv < 0) {
            throw SemaphoreException(std::string("Failed to unlock.") + strerror(errno));
        }

    }
 
}