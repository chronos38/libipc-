#include "gtest/gtest.h"
#include "../../include/libipcpp/Process.h"
#include "../../include/libipcpp/exception/ProcessException.h"
#include <memory>
#include <fstream>
#include <thread>
#include <chrono>
#include "Globals.h"

static std::fstream gLog;
static const std::string NAME = "./data/testprocess";
static const std::string NAME1 = "./data/testprocess1";

class ProcessTest : public testing::Test
{
protected:
    virtual void SetUp()
    {
        gLog.open(LOGFILE, std::fstream::out | std::fstream::app);
        try {
            
            mProcess = std::unique_ptr<ipc::Process>(new ipc::Process(NAME1, ""));
        } catch (ipc::IpcException ex) {
            gLog << ex.what();
            ASSERT_TRUE(false) << "Critical Failure";
        }
        
        
    }
    
    virtual void TearDown()
    {
        gLog.close();
        try {
            mProcess->Kill();
            
        } catch (ipc::ProcessException ex) {
            ASSERT_TRUE(false) << ex.what();
        }
    }
    
    std::unique_ptr<ipc::Process> mProcess;
};

TEST_F(ProcessTest, GetProcessByName_ReturnsCorrect_ProcessInfo)
{
   auto list =  ipc::Process::GetProcessByName("testprocess");
   if (list.size() == 0)
       ASSERT_TRUE(false) << "Testprocess not found.";
   
   ASSERT_TRUE(list.front().GetName() == "testprocess");
   ASSERT_TRUE(list.front().GetHandle() == mProcess->GetProcessInfo().GetHandle());
}

TEST_F(ProcessTest, GetProcessByName_ReturnsEmptyListOnNonExistingName)
{
    auto list = ipc::Process::GetProcessByName("InternetExplorer 4.0");
    ASSERT_TRUE(list.size() == 0);
}

TEST_F(ProcessTest, Ctor_CreatedProcessIsValid)
{
    ASSERT_TRUE(mProcess->IsValid()) << "Testprocess not Valid";
}


TEST_F(ProcessTest, CtorVectorArgumentList_CreatesValidProcess)
{
    ipc::Process process(NAME, {"a", "b", "c"});
    ASSERT_TRUE(process.GetProcessInfo().GetHandle() > 0);
    ASSERT_TRUE(process.IsValid());
}

TEST_F(ProcessTest, CtorStringArgumentList_CreatesValidProcess)
{
    ipc::Process process(NAME, "a b c");
    ASSERT_TRUE(process.GetProcessInfo().GetHandle() > 0);
    ASSERT_TRUE(process.IsValid());
}

TEST_F(ProcessTest, CtorFromProcessInfo_CreatesValidProcess)
{
    ipc::Process process(NAME, "a b c");
    ipc::Process process2(process.GetProcessInfo());
    
    ASSERT_TRUE(process2.IsValid());
    process.Kill();
    ASSERT_FALSE(process.IsValid());
    ASSERT_FALSE(process2.IsValid());
    
}

TEST_F(ProcessTest, ExitCode_ReturnsExpected_Value)
{
    
    ipc::Process process("./data/testprocess_returns_2", "");
    process.Wait();
    auto rv = process.ExitCode();
    ASSERT_EQ(2, rv);
}