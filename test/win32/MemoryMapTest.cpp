#include <gtest\gtest.h>
#include <libipcpp\MemoryMap.h>
#include <libipcpp\Utility.h>
#include <fstream>
#include "Globals.h"

using namespace ipc;
template <typename T>
using vector = std::vector < T >;
using string = std::string;

static std::fstream gLog;

class MemoryMapTest : public ::testing::Test
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

TEST_F(MemoryMapTest, ConstructorString_Length)
{
    try {
        // Arrange
        char buffer[1024];
        DWORD n = 0;
        memset(buffer, 0, sizeof(buffer));
        auto file = CreateFileA("tmp", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL , CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        WriteFile(file, buffer, 1024, &n, NULL);
        CloseHandle(file);

        // Act
        MemoryMap m("tmp");

        // Assert
        ASSERT_EQ(1024, m.Length());
    } catch (MemoryMapException& e) {
        gLog << "MemoryMap: ERROR: " << e.what();
        std::remove("tmp");
        ASSERT_FALSE(true);
    }

    std::remove("tmp");
}

TEST_F(MemoryMapTest, ConstructorByteCount_Length)
{
    try {
        // Arrange
        MemoryMap m(1024);

        // Act

        // Assert
        ASSERT_EQ(1024, m.Length());
    } catch (MemoryMapException& e) {
        gLog << "MemoryMap: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(MemoryMapTest, GetSetPosition)
{
    try {
        // Arrange
        MemoryMap m(1024);

        // Act
        m.Position(42);

        // Assert
        ASSERT_EQ(42, m.Position());
    } catch (MemoryMapException& e) {
        gLog << "MemoryMap: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}
