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

class ProcessTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
};

TEST_F(ProcessTest, Process_Constructor_Vector)
{
    try {
        // Arrange
        Process p(NAME, { "", "", "" });
        vector<string> result;
        DWORD aProcesses[8192];
        DWORD cbNeeded;
        DWORD cProcesses;

        // Act
        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
            // TODO: Systeminformation abrufen und als Argument übergeben.
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

                        if (szProcessName == NAME.c_str()) {
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
        ASSERT_EQ(NAME, result[0]);
        ASSERT_EQ(p.GetProcessInfo().GetName(), result[0]);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_Constructor_String)
{
    try {
        // Arrange
        Process p(NAME, "");
        vector<string> result;
        DWORD aProcesses[8192];
        DWORD cbNeeded;
        DWORD cProcesses;

        // Act
        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
            // TODO: Systeminformation abrufen und als Argument übergeben.
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

                        if (szProcessName == NAME.c_str()) {
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
        ASSERT_EQ(NAME, result[0]);
        ASSERT_EQ(p.GetProcessInfo().GetName(), result[0]);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_Constructor_ProcessInfo)
{
    Process p(ProcessInfo());
    // ?!
}

TEST_F(ProcessTest, Process_GetProcessByName_ValidName)
{
    try {
        // Arrange
        Process p(NAME, "");

        // Act
        auto v = Process::GetProcessByName(NAME);

        // Assert
        ASSERT_TRUE(v.size() == 1);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_GetProcessByName_InvalidName)
{
    try {
        // Arrange
        vector<ProcessInfo> v;

        // Act
        v = Process::GetProcessByName("this-is-absolutely-not-a-valid-name.exe");

        // Assert
        ASSERT_TRUE(v.size() == 0);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_GetProcesses_Exist)
{
    try {
        // Arrange
        bool exist = false;
        Process p(NAME, "");

        // Act
        auto v = Process::GetProcesses();
        std::for_each(std::begin(v), std::end(v), [&] (const ProcessInfo& info) {
            !exist ? (exist = (info.GetName() == NAME)) : (true);
        });

        // Assert
        ASSERT_TRUE(v.size() > 0);
        ASSERT_TRUE(exist);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_ExitCode_Default)
{
    try {
        // Arrange
        Process p(NAME, "1");

        // Act

        // Assert
        ASSERT_EQ(p.ExitCode(), ~0);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_ExitCode_42)
{
    try {
        // Arrange
        Process p(NAME, "1 42");

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Assert
        ASSERT_EQ(p.ExitCode(), 42);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_ExitCode_neg42)
{
    try {
        // Arrange
        Process p(NAME, "1 -42");

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Assert
        ASSERT_EQ(p.ExitCode(), -42);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_GetState_IsRunning)
{
    try {
        // Arrange
        Process p(NAME, "3");

        // Act
        auto state = p.GetState();

        // Assert
        ASSERT_EQ(state, ProcessState::IsRunning);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_GetState_NotRunning)
{
    try {
        // Arrange
        Process p(NAME, "1");

        // Act
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto state = p.GetState();

        // Assert
        ASSERT_EQ(state, ProcessState::NotRunning);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_GetState_Invalid)
{
    try {
        // Arrange
        Process p(NAME, "1");

        // Act
        p.Kill();
        auto state = p.GetState();

        // Assert
        ASSERT_EQ(state, ProcessState::Invalid);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_Kill_BeforeExit)
{
    try {
        // Arrange
        Process p(NAME, "");

        // Act
        p.Kill();
        auto v = Process::GetProcessByName(NAME);

        // Assert
        ASSERT_TRUE(v.size() == 0);
        ASSERT_EQ(p.GetState(), ProcessState::Invalid);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_Kill_AfterExit)
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
        ASSERT_EQ(p.GetState(), ProcessState::Invalid);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_Wait_Valid)
{
    try {
        // Arrange
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        Process p(NAME, "3 many arguments for the hope of a minor delay");

        // Act
        p.Wait();
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;

        // Assert
        ASSERT_TRUE(elapsed_seconds.count() > 3.0);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_WaitFor_Sufficient)
{
    try {
        // Arrange
        Process p(NAME, "1 many arguments for the hope of a minor delay");

        // Act
        auto stateBefore = p.GetState();
        p.WaitFor(std::chrono::seconds(3));
        auto stateAfter = p.GetState();

        // Assert
        ASSERT_EQ(stateBefore, ProcessState::IsRunning);
        ASSERT_EQ(stateAfter, ProcessState::NotRunning);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

TEST_F(ProcessTest, Process_WaitFor_NotSufficient)
{
    try {
        // Arrange
        Process p(NAME, "3 many arguments for the hope of a minor delay");

        // Act
        auto stateBefore = p.GetState();
        p.WaitFor(std::chrono::seconds(1));
        auto stateAfter = p.GetState();

        // Assert
        ASSERT_EQ(stateBefore, ProcessState::IsRunning);
        ASSERT_EQ(stateAfter, ProcessState::IsRunning);
    } catch (ProcessException& e) {
        std::fstream log;
        log.open(LOGFILE, std::fstream::out | std::fstream::app);
        log << "ProcessTest: " << e.what();
        log.close();
        ASSERT_FALSE(true);
    }
}

#endif
