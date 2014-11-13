#include "gtest/gtest.h"
#include "../../include/libipcpp/Process.h"
#include "../../include/libipcpp/exception/ProcessException.h"


class ProcessTest : public testing::Test
{
protected:
    virtual void SetUp()
    {
        mProcess = new ipc::Process("./data/testprocess", "");
    }
    
    virtual void TearDown()
    {
        try {
            mProcess->Kill();
            
        } catch (ipc::ProcessException ex) {
            ASSERT_TRUE(false) << ex.what();
        }
        delete mProcess;
    }
    
    ipc::Process* mProcess;
};

TEST_F(ProcessTest, GetProcessByName_ReturnsCorrect_ProcessInfo)
{
   auto list =  ipc::Process::GetProcessByName("testprocess");
   if (list.size() == 0)
       ASSERT_TRUE(false) << "Testprocess not found.";
   
   ASSERT_TRUE(list.front().GetName() == "testprocess");
   ASSERT_TRUE(list.front().GetHandle() == mProcess->GetProcessInfo().GetHandle());
}

TEST_F(ProcessTest, Ctor_CreatedProcessIsValid)
{
    ASSERT_TRUE(mProcess->IsValid()) << "Testprocess not Valid";
}