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
    // Arrange

    // Act

    // Assert
}

#endif
