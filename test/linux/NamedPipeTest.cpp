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

/*
TEST_F(NamedPipeTest, NamedPipe_ChildWritingSingleByte_IsReadableByParentProcess)
{
}

TEST_F(NamedPipeTest, NamedPipe_ParentWritingSingleByte_IsReadableByChildProcess)
{
}

TEST_F(NamedPipeTest, NamedPipe_ChildWritingMultipleBytes_IsReadAbleByParentProcess)
{
}


TEST_F(NamedPipeTest, NamedPipe_ParentWritingMultipleBytes_IsReadAbleByChildProcess)
{
}

TEST_F(NamedPipeTest, NamedPipe_ChildWritingVector_IsReadAbleByParentProcess)
{
}


TEST_F(NamedPipeTest, NamedPipe_ParentWritingVector_IsReadAbleByChildProcess)
{
}
*/