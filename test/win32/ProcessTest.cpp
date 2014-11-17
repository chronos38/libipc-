#ifdef _MSC_VER
#include <gtest\gtest.h>
#include <libipcpp\Process.h>
#include <libipcpp\Utility.h>
#include <Psapi.h>

using namespace ipc;
template <typename T>
using vector = std::vector < T > ;
using string = std::string;

class ProcessTest : ::testing::Test
{
protected:
    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
};

TEST(ProcessTest, Process_Constructor_Vector)
{
    // Arrange
    string name = ".\ProcessTest.exe";
    Process p(name, { "arg1", "arg2", "arg3" });
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

                    if (szProcessName == name.c_str()) {
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
    ASSERT_EQ(name, result[0]);
    ASSERT_EQ(p.GetProcessInfo().GetName(), result[0]);
}

TEST(ProcessTest, Process_Constructor_String)
{
    // Arrange
    string name = ".\ProcessTest.exe";
    Process p(name, "arg1 arg2 arg3");
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

                    if (szProcessName == name.c_str()) {
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
    ASSERT_EQ(name, result[0]);
    ASSERT_EQ(p.GetProcessInfo().GetName(), result[0]);
}

#endif
