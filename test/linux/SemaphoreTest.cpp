#include "gtest/gtest.h"
#include "Globals.h"
#include "../../include/libipcpp/Semaphore.h"
#include "../../include/libipcpp/exception/SemaphoreException.h"
#include <fstream>

static std::fstream gLog;

class SemaphoreTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        gLog.open(LOGFILE, std::fstream::out | std::fstream::app);
    }

    virtual void TearDown()
    {
        gLog.close();
    }
};

TEST_F(SemaphoreTest, Semaphore_IsLockableAndUnLockable)
{
    try {
        ipc::Semaphore sp; 
        
        sp.Lock();
        if(!fork()) {
            ASSERT_FALSE(sp.TryLock());
            exit(0);
            
        } else {
            wait(nullptr);
            sp.Unlock();
        }
        
    } catch (ipc::SemaphoreException ex) {
        ASSERT_TRUE(false) << ex.what();
    }
    
}