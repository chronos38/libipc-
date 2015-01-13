#include "gtest/gtest.h"
#include "Globals.h"
#include "../../include/libipcpp/NamedPipe.h"
#include "../../include/libipcpp/exception/NamedPipeException.h"
#include <fstream>

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

TEST_F(NamedPipeTest, NamedPipe_OpensAndCloses_WithoutError)
{
    if(!fork()) {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Write);
        ASSERT_TRUE(pipe.IsOpen());
        pipe.Close();
        ASSERT_FALSE(pipe.IsOpen());
        exit(0);
    } else {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Read);
        ASSERT_TRUE(pipe.IsOpen());
        pipe.Close();
        ASSERT_FALSE(pipe.IsOpen());
        wait(nullptr);
        
    }
}

TEST_F(NamedPipeTest, NamedPipe_ChildWritingSingleByte_IsReadableByParentProcess)
{
    if(!fork()) {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Write);
        pipe.WriteByte('a');
        pipe.Close();
        exit(0);
    } else {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Read);
        ASSERT_EQ('a',pipe.ReadByte());
        pipe.Close();
        wait(nullptr);
    }
}

TEST_F(NamedPipeTest, NamedPipe_ParentWritingSingleByte_IsReadableByChildProcess)
{
    if(!fork()) {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Read);
        ASSERT_EQ('a',pipe.ReadByte());
        exit(0);
    } else {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Write);
        pipe.WriteByte('a');
        wait(nullptr);
    }
}

TEST_F(NamedPipeTest, NamedPipe_ChildWritingMultipleBytes_IsReadAbleByParentProcess)
{
    char buf[30] = {0};
    if(!fork()) {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Write);
        pipe.Write("0123456789", 10);
        exit(0);
    } else {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Read);
        pipe.Read(buf,10);
        ASSERT_STREQ("0123456789",buf);
        wait(nullptr);
    }
}


TEST_F(NamedPipeTest, NamedPipe_ParentWritingMultipleBytes_IsReadAbleByChildProcess)
{
    char buf[30] = {0};
    if(!fork()) {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Read);
        pipe.Read(buf,10);
        ASSERT_STREQ("0123456789",buf);
        exit(0);
    } else {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Write);
        pipe.Write("0123456789", 10);
        wait(nullptr);
    }
}

TEST_F(NamedPipeTest, NamedPipe_ChildWritingVector_IsReadAbleByParentProcess)
{
    const char * str = "0123456789";
    std::vector<char> buf(str, str + 11);
    std::vector<char> bufRead(buf.size(), 0);
    
    if(!fork()) {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Write);
        pipe.Write(buf.begin(),buf.end());
        exit(0);
    } else {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Read);
        pipe.Read(bufRead.begin(),bufRead.end());
        for(int i = 0; i < bufRead.size(); i++) {
            ASSERT_EQ(buf[i], bufRead[i]);
        }
        wait(nullptr);
    }
}


TEST_F(NamedPipeTest, NamedPipe_ParentWritingVector_IsReadAbleByChildProcess)
{

    const char * str = "0123456789";
    std::vector<char> buf(str, str + 11);
    std::vector<char> bufRead(buf.size(), 0);
    
    if(!fork()) {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Read);
        pipe.Read(bufRead.begin(),bufRead.end());
        for(int i = 0; i < bufRead.size(); i++) {
            ASSERT_EQ(buf[i], bufRead[i]);
        }
        exit(0);
    } else {
        ipc::NamedPipe pipe("Testpipe", ipc::NamedPipeIo::Write);
        pipe.Write(buf.begin(),buf.end());
        wait(nullptr);
    }
}