#ifdef _MSC_VER
#include <gtest\gtest.h>
#include <libipcpp\NamedPipe.h>
#include <libipcpp\Utility.h>
#include <fstream>
#include <thread>
#include <chrono>
#include "Globals.h"

using namespace ipc;
template <typename T>
using vector = std::vector < T >;
using string = std::string;

static std::fstream gLog;

class NamedPipeTest : public ::testing::Test
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

TEST_F(NamedPipeTest, Constructor)
{
    try {
        // Arrange
        NamedPipe p("Test", NamedPipeIo::Read);

        // Act

        // Assert
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, Destructor)
{
    try {
        // Arrange
        NamedPipe* p = new NamedPipe("Test", NamedPipeIo::Read);

        // Act
        p->~NamedPipe();
        delete p;

        // Assert
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, IsOpenFalse)
{
    try {
        // Arrange
        NamedPipe p("Test", NamedPipeIo::Read);

        // Act

        // Assert
        ASSERT_FALSE(p.IsOpen());
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, IsOpenTrue)
{
    try {
        // Arrange
        NamedPipe server("Test", NamedPipeIo::Write);
        NamedPipe client("Test", NamedPipeIo::Read);
        auto t = std::thread([&] () {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            client.Initialize();
        });
        server.Initialize();

        // Act

        // Assert
        ASSERT_TRUE(server.IsOpen());
        t.join();
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, Close)
{
    try {
        // Arrange
        NamedPipe server("Test", NamedPipeIo::Write);
        NamedPipe client("Test", NamedPipeIo::Read);
        auto t = std::thread([&] () {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            client.Initialize();
        });
        server.Initialize();

        // Act
        server.Close();

        // Assert
        ASSERT_FALSE(server.IsOpen());
        t.join();
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, ReadWriteData)
{
    try {
        // Arrange
        ByteCount n, m;
        char read[4];
        NamedPipe server("Test", NamedPipeIo::Write);
        NamedPipe client("Test", NamedPipeIo::Read);
        auto t = std::thread([&] () {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            client.Initialize();
            m = client.Read(read, sizeof("abc"));
        });
        server.Initialize();

        // Act
        memset(read, 0, sizeof(read));
        n = server.Write("abc", sizeof("abc"));
        t.join();

        // Assert
        ASSERT_EQ(4, n);
        ASSERT_EQ(4, m);
        ASSERT_TRUE(strcmp("abc", read) == 0);
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, ReadWriteByte)
{
    try {
        // Arrange
        int n, m;
        char b;
        NamedPipe server("Test", NamedPipeIo::Write);
        NamedPipe client("Test", NamedPipeIo::Read);
        auto t = std::thread([&] () {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            client.Initialize();
            m = client.ReadByte();
        });
        server.Initialize();

        // Act
        n = server.WriteByte((char)255);
        t.join();

        // Assert
        ASSERT_EQ(1, n);
        ASSERT_EQ(255, m);
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, ReadWriteFullRange)
{
    try {
        // Arrange
        ByteCount n, m;
        vector<char> write = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<char> read(write.size(), 0);
        NamedPipe server("Test", NamedPipeIo::Write);
        NamedPipe client("Test", NamedPipeIo::Read);
        auto t = std::thread([&] () {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            client.Initialize();
            m = client.Read(std::begin(read), std::end(read));
        });
        server.Initialize();

        // Act
        n = server.Write(std::begin(write), std::end(write));
        t.join();

        // Assert
        for (int i = 0; i < read.size(); i++) {
            ASSERT_EQ(i, read[i]);
        }
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, ReadWriteSpecificRange)
{
    try {
        // Arrange
        ByteCount n, m;
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

        NamedPipe server("Test", NamedPipeIo::Write);
        NamedPipe client("Test", NamedPipeIo::Read);
        auto t = std::thread([&] () {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            client.Initialize();
            m = client.Read(rfirst, rlast);
        });
        server.Initialize();

        // Act
        n = server.Write(wfirst, wlast);
        t.join();

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
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, ReadWriteSpecificRangeInteger)
{
    try {
        // Arrange
        ByteCount n, m;
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

        NamedPipe server("Test", NamedPipeIo::Write);
        NamedPipe client("Test", NamedPipeIo::Read);
        auto t = std::thread([&] () {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            client.Initialize();
            m = client.Read(rfirst, rlast);
        });
        server.Initialize();

        // Act
        n = server.Write(wfirst, wlast);
        t.join();

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
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(NamedPipeTest, ReadWriteSpecificRangeULong)
{
    try {
        // Arrange
        ByteCount n, m;
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

        NamedPipe server("Test", NamedPipeIo::Write);
        NamedPipe client("Test", NamedPipeIo::Read);
        auto t = std::thread([&] () {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            client.Initialize();
            m = client.Read(rfirst, rlast);
        });
        server.Initialize();

        // Act
        n = server.Write(wfirst, wlast);
        t.join();

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
    } catch (NamedPipeException& e) {
        gLog << "NamedPipeTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

#endif
