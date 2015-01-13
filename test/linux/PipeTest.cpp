#include "gtest/gtest.h"
#include "Globals.h"
#include "../../include/libipcpp/Pipe.h"
#include "../../include/libipcpp/exception/PipeException.h"
#include <fstream>

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

TEST_F(PipeTest, Pipe_OpensAndCloses_WithoutError)
{
    auto pipe = ipc::Pipe();
    ASSERT_TRUE(pipe.IsOpen());
    pipe.Close();
    ASSERT_FALSE(pipe.IsOpen());
}

TEST_F(PipeTest, Pipe_ChildWritingSingleByte_IsReadableByParentProcess)
{
    auto pipe = ipc::Pipe();
    if(!fork()) {
        pipe.WriteByte('a');
        exit(0);
    } else {
        ASSERT_EQ('a',pipe.ReadByte());
        wait(nullptr);
    }
}

TEST_F(PipeTest, Pipe_ParentWritingSingleByte_IsReadableByChildProcess)
{
    auto pipe = ipc::Pipe();
    if(!fork()) {
        ASSERT_EQ('a',pipe.ReadByte());
        exit(0);
    } else {
        pipe.WriteByte('a');
        wait(nullptr);
    }
}

TEST_F(PipeTest, Pipe_ChildWritingMultipleBytes_IsReadAbleByParentProcess)
{
    auto pipe = ipc::Pipe();
    char buf[30] = {0};
    if(!fork()) {
        pipe.Write("0123456789", 10);
        exit(0);
    } else {
        pipe.Read(buf,10);
        ASSERT_STREQ("0123456789",buf);
        wait(nullptr);
    }
    
}


TEST_F(PipeTest, Pipe_ParentWritingMultipleBytes_IsReadAbleByChildProcess)
{
    auto pipe = ipc::Pipe();
    char buf[30] = {0};
    if(!fork()) {
        pipe.Read(buf,10);
        ASSERT_STREQ("0123456789",buf);
        exit(0);
    } else {
        pipe.Write("0123456789", 10);
        wait(nullptr);
    }
    
}

TEST_F(PipeTest, Pipe_ChildWritingVector_IsReadAbleByParentProcess)
{
    auto pipe = ipc::Pipe();
    const char * str = "0123456789";
    std::vector<char> buf(str, str + 11);
    std::vector<char> bufRead(buf.size(), 0);
    
    if(!fork()) {
        pipe.Write(buf.begin(),buf.end());
        exit(0);
    } else {
        pipe.Read(bufRead.begin(),bufRead.end());
        for(int i = 0; i < bufRead.size(); i++) {
            ASSERT_EQ(buf[i], bufRead[i]);
        }
        wait(nullptr);
    }
    
}


TEST_F(PipeTest, Pipe_ParentWritingVector_IsReadAbleByChildProcess)
{
    auto pipe = ipc::Pipe();
    const char * str = "0123456789";
    std::vector<char> buf(str, str + 11);
    std::vector<char> bufRead(buf.size(), 0);
    
    if(!fork()) {
        pipe.Read(bufRead.begin(),bufRead.end());
        for(int i = 0; i < bufRead.size(); i++) {
            ASSERT_EQ(buf[i], bufRead[i]);
        }
        exit(0);
    } else {
        pipe.Write(buf.begin(),buf.end());
        wait(nullptr);
    }
    
}














