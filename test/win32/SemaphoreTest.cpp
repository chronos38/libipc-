#ifdef _MSC_VER
#include <gtest\gtest.h>
#include <libipcpp\Semaphore.h>
#include <libipcpp\Utility.h>
#include <fstream>
#include "Globals.h"

using namespace ipc;
using string = std::string;

static std::fstream gLog;

class SemaphoreTest : public ::testing::Test
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

TEST_F(SemaphoreTest, Constructor)
{
    try {
        // Arrange
        Semaphore s;

        // Act

        // Assert
    } catch (SemaphoreException& e) {
        gLog << "SemaphoreTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(SemaphoreTest, Destructor)
{
    try {
        // Arrange
        Semaphore* s = new Semaphore();

        // Act
        s->~Semaphore();

        // Assert
        try {
            s->TryLock();
            delete s;
            ASSERT_TRUE(false);
        } catch (SemaphoreException& e) {
            delete s;
            ASSERT_TRUE(true);
        }
    } catch (SemaphoreException& e) {
        gLog << "SemaphoreTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

// TODO: Tests ausbauen.

#endif
