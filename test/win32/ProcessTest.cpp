#ifdef _MSC_VER
#include <gtest\gtest.h>
#include <libipcpp\Process.h>
#include <libipcpp\Utility.h>
#include <Psapi.h>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include "Globals.h"

using namespace ipc;
template <typename T>
using vector = std::vector < T > ;
using string = std::string;

static const string NAME = ".\\ProcessTest.exe";
static const string CMPNAME = "ProcessTest.exe";
static std::fstream gLog;

class ProcessTest : public ::testing::Test
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

TEST_F(ProcessTest, Constructor_Vector)
{
    try {
        // Arrange
        Process p(NAME, { "60", "", "" });
        vector<string> result;
        DWORD aProcesses[8192];
        DWORD cbNeeded;
        DWORD cProcesses;

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Slepp one second

        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
            throw ProcessException(GetLastErrorString());
        }

        cProcesses = cbNeeded / sizeof(DWORD);

        for (DWORD i = 0; i < cProcesses; i++) {
            if (aProcesses[i] != 0) {
                CHAR szProcessName[MAX_PATH] = "<unknown>";
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);

                if (hProcess) {
                    HMODULE hMod;
                    DWORD cbNeeded;

                    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                        GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(CHAR));

                        if (szProcessName == CMPNAME) {
                            result.push_back(szProcessName);
                        } else {
                            CloseHandle(hProcess);
                        }
                    } else {
                        CloseHandle(hProcess);
                    }
                }
            }
        }

        // Assert
        ASSERT_TRUE(result.size() > 0);
        ASSERT_EQ(CMPNAME, result[0]);
        ASSERT_EQ(p.GetProcessInfo().GetName(), result[0]);
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Constructor_String)
{
    try {
        // Arrange
        Process p(NAME, "60");
        vector<string> result;
        DWORD aProcesses[8192];
        DWORD cbNeeded;
        DWORD cProcesses;

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Slepp one second

        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
            throw ProcessException(GetLastErrorString());
        }

        cProcesses = cbNeeded / sizeof(DWORD);

        for (DWORD i = 0; i < cProcesses; i++) {
            if (aProcesses[i] != 0) {
                CHAR szProcessName[MAX_PATH] = "<unknown>";
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);

                if (hProcess) {
                    HMODULE hMod;
                    DWORD cbNeeded;

                    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                        GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(CHAR));

                        if (szProcessName == CMPNAME) {
                            result.push_back(szProcessName);
                        } else {
                            CloseHandle(hProcess);
                        }
                    } else {
                        CloseHandle(hProcess);
                    }
                }
            }
        }

        // Assert
        ASSERT_TRUE(result.size() > 0);
        ASSERT_EQ(CMPNAME, result[0]);
        ASSERT_EQ(CMPNAME, p.GetProcessInfo().GetName());
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, GetProcessByName_ValidName)
{
    try {
        // Arrange
        Process p(NAME, "3");

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Slepp one second
        auto v = Process::GetProcessByName(CMPNAME);

        // Assert
        ASSERT_TRUE(v.size() > 0);
        ASSERT_EQ(CMPNAME, v[0].GetName());
        ASSERT_EQ(CMPNAME, p.GetProcessInfo().GetName());
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, GetProcessByName_InvalidName)
{
    try {
        // Arrange
        vector<ProcessInfo> v;

        // Act
        v = Process::GetProcessByName("this-is-absolutely-not-a-valid-name.exe");

        // Assert
        ASSERT_TRUE(v.size() == 0);
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, GetProcesses_Exist)
{
    try {
        // Arrange
        bool exist = false;
        Process p(NAME, "");

        // Act
        auto v = Process::GetProcesses();
        std::for_each(std::begin(v), std::end(v), [&] (const ProcessInfo& info) {
            !exist ? (exist = (info.GetName() == CMPNAME)) : (true);
        });

        // Assert
        ASSERT_TRUE(v.size() > 0);
        ASSERT_TRUE(exist);
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, ExitCode_Default)
{
    try {
        // Arrange
        Process p(NAME, "1");

        // Act

        // Assert
        ASSERT_EQ(~0, p.ExitCode());
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, ExitCode_42)
{
    try {
        // Arrange
        Process p(NAME, "1 42");

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Assert
        ASSERT_EQ(42, p.ExitCode());
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, ExitCode_Negative42)
{
    try {
        // Arrange
        Process p(NAME, "1 -42");

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Assert
        ASSERT_EQ(-42, p.ExitCode());
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, GetState_IsRunning)
{
    try {
        // Arrange
        Process p(NAME, "3");

        // Act
        auto state = p.GetState();

        // Assert
        ASSERT_EQ(ProcessState::IsRunning, state);
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, GetState_NotRunning)
{
    try {
        // Arrange
        Process p(NAME, "1");

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto state = p.GetState();

        // Assert
        ASSERT_EQ(ProcessState::NotRunning, state);
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, GetState_Invalid)
{
    try {
        // Arrange
        Process p(NAME, "1");

        // Act
        p.Kill();
        auto state = p.GetState();

        // Assert
        ASSERT_EQ(ProcessState::Invalid, state);
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Kill_BeforeExit)
{
    try {
        // Arrange
        Process p(NAME, "");

        // Act
        p.Kill();
        auto v = Process::GetProcessByName(NAME);

        // Assert
        ASSERT_TRUE(v.size() == 0);
        ASSERT_EQ(ProcessState::Invalid, p.GetState());
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Kill_AfterExit)
{
    try {
        // Arrange
        Process p(NAME, "1");

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(3));
        p.Kill();
        auto v = Process::GetProcessByName(NAME);

        // Assert
        ASSERT_TRUE(v.size() == 0);
        ASSERT_EQ(ProcessState::Invalid, p.GetState());
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Wait_Valid)
{
    try {
        // Arrange
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        Process p(NAME, "3");

        // Act
        p.Wait();
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;

        // Assert
        ASSERT_TRUE(elapsed_seconds.count() > 3.0);
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, WaitFor_Sufficient)
{
    try {
        // Arrange
        Process p(NAME, "1");

        // Act
        auto stateBefore = p.GetState();
        p.WaitFor(std::chrono::seconds(3));
        auto stateAfter = p.GetState();

        // Assert
        ASSERT_EQ(ProcessState::IsRunning, stateBefore);
        ASSERT_EQ(ProcessState::NotRunning, stateAfter);
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, WaitFor_NotSufficient)
{
    try {
        // Arrange
        Process p(NAME, "3");

        // Act
        auto stateBefore = p.GetState();
        p.WaitFor(std::chrono::seconds(1));
        auto stateAfter = p.GetState();

        // Assert
        ASSERT_EQ(ProcessState::IsRunning, stateBefore);
        ASSERT_EQ(ProcessState::IsRunning, stateAfter);
    } catch (ProcessException& e) {
        gLog << "ProcessTest: ERROR: " << e.what();
        ASSERT_FALSE(true);
    }
}

#endif
