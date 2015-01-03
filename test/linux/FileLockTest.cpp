#include "gtest/gtest.h"
#include "Globals.h"
#include "../../include/libipcpp/FileLock.h"
#include "../../include/libipcpp/exception/FileLockException.h"
#include <fstream>

static std::fstream gLog;
static const std::string NAME1 = "./data/testfile";

class FileLockTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        mFd = open(NAME1.c_str(), O_CREAT | 0666);
        gLog.open(LOGFILE, std::fstream::out | std::fstream::app);
    }

    virtual void TearDown()
    {
        close(mFd);
        unlink(NAME1.c_str());
        gLog.close();
    }
    int mFd;
};

TEST_F(FileLockTest, FileLock_FileIsLockable)
{
    
    ipc::FileLock lock(mFd);
    lock.Lock();
    
    int fd2 = open(NAME1.c_str(), 0666);
    ASSERT_TRUE(fd2 == -1);
}