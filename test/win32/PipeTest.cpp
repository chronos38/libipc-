#ifdef _MSC_VER
#include <gtest\gtest.h>
#include <libipcpp\Pipe.h>
#include <libipcpp\Utility.h>
#include <Psapi.h>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include "Globals.h"

using namespace ipc;
template <typename T>
using vector = std::vector < T >;
using string = std::string;

static std::fstream gLog;

class PipeTest : public ::testing::Test
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

TEST_F(PipeTest, Constructor)
{
    try {
        // Arrange
        Pipe p;

        // Act

        // Assert
        ASSERT_TRUE(p.IsOpen());
    } catch (PipeException& e) {
        gLog << "PipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(PipeTest, IsOpen)
{
    try {
        // Arrange
        Pipe p;

        // Act

        // Assert
        ASSERT_TRUE(p.IsOpen());
    } catch (PipeException& e) {
        gLog << "PipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(PipeTest, Close)
{
    try {
        // Arrange
        Pipe p;

        // Act
        p.Close();

        // Assert
        ASSERT_FALSE(p.IsOpen());
    } catch (PipeException& e) {
        gLog << "PipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(PipeTest, ReadWriteData)
{
    try {
        // Arrange
        Pipe p;
        char read[4];

        // Act
        memset(read, 0, sizeof(read));
        auto n = p.Write("abc", sizeof("abc"));
        auto m = p.Read(read, sizeof("abc"));

        // Assert
        ASSERT_EQ(4, n);
        ASSERT_EQ(4, m);
        ASSERT_TRUE(strcmp("abc", read) == 0);
    } catch (PipeException& e) {
        gLog << "PipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(PipeTest, ReadWriteByte)
{
    try {
        // Arrange
        Pipe p;
        char b;

        // Act
        auto n = p.WriteByte((char)255);
        auto r = p.ReadByte();

        // Assert
        ASSERT_EQ(1, n);
        ASSERT_EQ(255, r);
    } catch (PipeException& e) {
        gLog << "PipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(PipeTest, ReadWriteFullRange)
{
    try {
        // Arrange
        Pipe p;
        vector<char> write = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<char> read(write.size(), 0);

        // Act
        p.Write(std::begin(write), std::end(write));
        p.Read(std::begin(read), std::end(read));

        // Assert
        for (int i = 0; i < read.size(); i++) {
            ASSERT_EQ(i, read[i]);
        }
    } catch (PipeException& e) {
        gLog << "PipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(PipeTest, ReadWriteSpecificRange)
{
    try {
        // Arrange
        Pipe p;
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
    } catch (PipeException& e) {
        gLog << "PipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(PipeTest, ReadWriteSpecificRangeInteger)
{
    try {
        // Arrange
        Pipe p;
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
    } catch (PipeException& e) {
        gLog << "PipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(PipeTest, ReadWriteSpecificRangeULong)
{
    try {
        // Arrange
        Pipe p;
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
    } catch (PipeException& e) {
        gLog << "PipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

#endif
