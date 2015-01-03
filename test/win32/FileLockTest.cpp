#include <gtest\gtest.h>
#include <libipcpp\FileLock.h>
#include <libipcpp\Utility.h>
#include <fstream>
#include "Globals.h"

using namespace ipc;
template <typename T>
using vector = std::vector < T >;
using string = std::string;

static std::fstream gLog;

class FileLockTest : public ::testing::Test
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

TEST_F(FileLockTest, ConstructorString_Length)
{
    // Arrange
    char buffer[1024];
    DWORD n = 0;
    memset(buffer, 0, sizeof(buffer));
    auto file = CreateFileA("tmp", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(file, buffer, 1024, &n, NULL);

    // Act
    FileLock* m = new FileLock(file);
    m->Lock();
    m->Unlock();
    m->~FileLock();
    delete m;
    CloseHandle(file);

    std::remove("tmp");
}
