#include "gtest/gtest.h"
#include "../../include/libipcpp/Process.h"

TEST(ProcessTest, Ctor_Returns_Process)
{
   auto list =  ipc::Process::GetProcessByName("firefox");
    
}
