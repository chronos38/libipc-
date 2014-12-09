#include "gtest/gtest.h"
#include "Globals.h"
#include "../../include/libipcpp/MemoryMap.h"
#include "../../include/libipcpp/exception/MemoryMapException.h"
#include <fstream>
#include <vector>


static std::fstream gLog;

class MemoryMapTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        gLog.open(LOGFILE, std::fstream::out | std::fstream::app);
        
        std::vector<char> buffer(1024, 0);
        std::ofstream out("tmp", std::ostream::binary);
        out.write(buffer.data(), buffer.size());
        mSize = buffer.size();
    }

    virtual void TearDown()
    {
        std::remove("tmp");
        gLog.close();
    }
    
    size_t mSize;
};

TEST_F(MemoryMapTest, ConstructorString_Length)
{
    try {
        // Arrange
        // Act
        ipc::MemoryMap m("tmp");

        // Assert
        ASSERT_EQ(mSize, m.Length());
    } catch (ipc::MemoryMapException& e) {
        gLog << "MemoryMap: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }

    std::remove("tmp");
}

TEST_F(MemoryMapTest, GetSetPosition)
{
    try {
        // Arrange
        ipc::MemoryMap m("tmp");

        // Act
        m.Position(42);

        // Assert
        ASSERT_EQ(42, m.Position());
    } catch (ipc::MemoryMapException& e) {
        gLog << "MemoryMap: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(MemoryMapTest, ReadWriteData)
{
    try {
        // Arrange
        ipc::MemoryMap p("tmp");
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
    } catch (ipc::MemoryMapException& e) {
        gLog << "MemoryMapTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(MemoryMapTest, ReadWriteByte)
{
    try {
        // Arrange
        ipc::MemoryMap p("tmp");
        char b;

        // Act
        auto n = p.WriteByte((char)255);
        p.Position(0);
        auto r = p.ReadByte();

        // Assert
        ASSERT_EQ(1, n);
        ASSERT_EQ(255, r);
    } catch (ipc::MemoryMapException& e) {
        gLog << "MemoryMapTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(MemoryMapTest, ReadWriteFullRange)
{
    try {
        // Arrange
        ipc::MemoryMap p("tmp");
        std::vector<char> write = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::vector<char> read(write.size(), 0);

        // Act
        p.Write(std::begin(write), std::end(write));
        p.Position(0);
        p.Read(std::begin(read), std::end(read));

        // Assert
        for (int i = 0; i < read.size(); i++) {
            ASSERT_EQ(i, read[i]);
        }
    } catch (ipc::MemoryMapException& e) {
        gLog << "MemoryMapTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(MemoryMapTest, ReadWriteSpecificRange)
{
    try {
        // Arrange
        ipc::MemoryMap p("tmp");
        std::vector<char> write = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::vector<char> read(write.size(), 0);

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
    } catch (ipc::MemoryMapException& e) {
        gLog << "MemoryMapTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(MemoryMapTest, ReadWriteSpecificRangeInteger)
{
    try {
        // Arrange
        ipc::MemoryMap p("tmp");
        std::vector<int> write = { -1000, -1001, -1002, -1003, -1004, -1005, -1006, -1007, -1008, -1009 };
        std::vector<int> read(write.size(), 0);

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
    } catch (ipc::MemoryMapException& e) {
        gLog << "MemoryMapTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(MemoryMapTest, ReadWriteSpecificRangeULong)
{
    try {
        // Arrange
        ipc::MemoryMap p("tmp");
        std::vector<unsigned long long> write = { 1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009 };
        std::vector<unsigned long long> read(write.size(), 0);

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
    } catch (ipc::MemoryMapException& e) {
        gLog << "MemoryMapTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}
