#ifdef _MSC_VER
#include <gtest\gtest.h>
#include <libipcpp\SharedMemory.h>
#include <libipcpp\Utility.h>
#include <fstream>
#include "Globals.h"

using namespace ipc;
template <typename T>
using vector = std::vector < T >;
using string = std::string;

static std::fstream gLog;

class SharedMemoryTest : public ::testing::Test
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

TEST_F(SharedMemoryTest, ConstructorByteCount_Length)
{
    try {
        // Arrange
        SharedMemory m(1024);

        // Act

        // Assert
        ASSERT_EQ(1024, m.Length());
    } catch (SharedMemoryException& e) {
        gLog << "SharedMemory: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(SharedMemoryTest, operatorBracket)
{
    EXPECT_NO_THROW({
        // Arrange
        SharedMemory m(1024);

        // Act
        m[0] = 127;
        m[1] = (char)255;

        // Assert
        ASSERT_EQ(127, m[0]);
        ASSERT_EQ((char)255, m[1]);
    });
}

TEST_F(SharedMemoryTest, GetSetPosition)
{
    try {
        // Arrange
        SharedMemory m(1024);

        // Act
        m.Position(42);

        // Assert
        ASSERT_EQ(42, m.Position());
    } catch (SharedMemoryException& e) {
        gLog << "SharedMemory: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(SharedMemoryTest, ReadWriteData)
{
    try {
        // Arrange
        SharedMemory p(1024);
        char read[4];

        // Act
        memset(read, 0, sizeof(read));
        auto n = p.Write("abc", sizeof("abc"));
        p.Position(0);
        auto m = p.Read(read, sizeof("abc"));

        // Assert
        ASSERT_EQ(4, n);
        ASSERT_EQ(4, m);
        ASSERT_TRUE(strcmp("abc", read) == 0);
    } catch (SharedMemoryException& e) {
        gLog << "SharedMemoryTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(SharedMemoryTest, ReadWriteByte)
{
    try {
        // Arrange
        SharedMemory p(1024);
        char b;

        // Act
        auto n = p.WriteByte((char)255);
        p.Position(0);
        auto r = p.ReadByte();

        // Assert
        ASSERT_EQ(1, n);
        ASSERT_EQ(255, r);
    } catch (SharedMemoryException& e) {
        gLog << "SharedMemoryTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(SharedMemoryTest, ReadWriteFullRange)
{
    try {
        // Arrange
        SharedMemory p(1024);
        vector<char> write = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<char> read(write.size(), 0);

        // Act
        p.Write(std::begin(write), std::end(write));
        p.Position(0);
        p.Read(std::begin(read), std::end(read));

        // Assert
        for (int i = 0; i < read.size(); i++) {
            ASSERT_EQ(i, read[i]);
        }
    } catch (SharedMemoryException& e) {
        gLog << "SharedMemoryTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(SharedMemoryTest, ReadWriteSpecificRange)
{
    try {
        // Arrange
        SharedMemory p(1024);
        vector<char> write = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<char> read(write.size(), 0);

        auto wfirst = std::begin(write);
        std::advance(wfirst, 2);
        auto wlast = std::begin(write);
        std::advance(wlast, 5);

        auto rfirst = std::begin(read);
        std::advance(rfirst, 3);
        auto rlast = std::begin(read);
        std::advance(rlast, 6);

        // Act
        auto n = p.Write(wfirst, wlast);
        p.Position(0);
        auto m = p.Read(rfirst, rlast);

        // Assert
        ASSERT_EQ(3, n);
        ASSERT_EQ(3, m);
        for (int i = 0; i < read.size(); i++) {
            if (i >= 3 && i < 6) {
                ASSERT_EQ(i - 1, read[i]);
            } else {
                ASSERT_EQ(0, read[i]);
            }
        }
    } catch (SharedMemoryException& e) {
        gLog << "SharedMemoryTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(SharedMemoryTest, ReadWriteSpecificRangeInteger)
{
    try {
        // Arrange
        SharedMemory p(1024);
        vector<int> write = { -1000, -1001, -1002, -1003, -1004, -1005, -1006, -1007, -1008, -1009 };
        vector<int> read(write.size(), 0);

        auto wfirst = std::begin(write);
        std::advance(wfirst, 2);
        auto wlast = std::begin(write);
        std::advance(wlast, 5);

        auto rfirst = std::begin(read);
        std::advance(rfirst, 3);
        auto rlast = std::begin(read);
        std::advance(rlast, 6);

        // Act
        auto n = p.Write(wfirst, wlast);
        p.Position(0);
        auto m = p.Read(rfirst, rlast);

        // Assert
        ASSERT_EQ(sizeof(int) * 3, n);
        ASSERT_EQ(sizeof(int) * 3, m);
        for (int i = 0; i < read.size(); i++) {
            if (i >= 3 && i < 6) {
                ASSERT_EQ(-1000 - (i - 1), read[i]);
            } else {
                ASSERT_EQ(0, read[i]);
            }
        }
    } catch (SharedMemoryException& e) {
        gLog << "SharedMemoryTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(SharedMemoryTest, ReadWriteSpecificRangeULong)
{
    try {
        // Arrange
        SharedMemory p(1024);
        vector<unsigned long long> write = { 1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009 };
        vector<unsigned long long> read(write.size(), 0);

        auto wfirst = std::begin(write);
        std::advance(wfirst, 2);
        auto wlast = std::begin(write);
        std::advance(wlast, 5);

        auto rfirst = std::begin(read);
        std::advance(rfirst, 3);
        auto rlast = std::begin(read);
        std::advance(rlast, 6);

        // Act
        auto n = p.Write(wfirst, wlast);
        p.Position(0);
        auto m = p.Read(rfirst, rlast);

        // Assert
        ASSERT_EQ(sizeof(unsigned long long) * 3, n);
        ASSERT_EQ(sizeof(unsigned long long) * 3, m);
        for (int i = 0; i < read.size(); i++) {
            if (i >= 3 && i < 6) {
                ASSERT_EQ(1000 + i - 1, read[i]);
            } else {
                ASSERT_EQ(0, read[i]);
            }
        }
    } catch (SharedMemoryException& e) {
        gLog << "SharedMemoryTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

#endif
