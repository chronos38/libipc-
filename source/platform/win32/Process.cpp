#ifdef _MSC_VER
#include "../../../include/libipcpp/Process.h"
#include <Psapi.h>

using string = std::string;
template <typename T>
using vector = std::vector < T > ;
template <typename T>
using shared_ptr = std::shared_ptr < T > ;

namespace ipc {
    ProcessInfo::ProcessInfo(ProcessInfo&& info) :
        mId(info.mId), mHandle(info.mHandle), mName(info.mName)
    {
        info.mId = 0;
        info.mName = "";
        info.mHandle = PROCESS_INVALID_HANDLE;
    }

    Process::Process(const string& fileName, const vector<string>& args)
    {
        string str = fileName;

        for (const string& arg : args) {
            str += " " + arg;
        }

        Process::Process(fileName, args);
    }

    Process::Process(const string& fileName, const string& args)
    {
        LPSTR cmdl = new CHAR[args.size() + 1];
        STARTUPINFO startupInfo;
        PROCESS_INFORMATION processInformation;
        memset(&startupInfo, 0, sizeof(startupInfo));
        memset(cmdl, 0, args.size() + 1);
        memcpy(cmdl, args.data(), args.size());

        startupInfo.cb = sizeof(startupInfo);

        BOOL result = CreateProcessA(fileName.c_str(), cmdl, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
        delete cmdl;

        if (!result) {
            // TODO: Systeminformation abrufen und als Argument übergeben.
            throw ProcessException("");
        } else {
            CHAR szProcessName[MAX_PATH] = "<unknown>";
            HMODULE hMod;
            DWORD cbNeeded;
            mIsOwner = true;
            mProcessInfo.mHandle = processInformation.hProcess;
            mProcessInfo.mId = GetProcessId(processInformation.hProcess);
            mThread = processInformation.hThread;

            if (EnumProcessModules(mProcessInfo.mHandle, &hMod, sizeof(hMod), &cbNeeded)) {
                GetModuleBaseNameA(mProcessInfo.mHandle, hMod, szProcessName, sizeof(szProcessName) / sizeof(CHAR));
                mProcessInfo.mName = szProcessName;
            }

        }
    }

    Process::Process(const ProcessInfo& info) :
        mProcessInfo(info)
    {
    }

    Process::Process(Process&& p) :
        mIsOwner(p.mIsOwner), mProcessInfo(p.mProcessInfo), mThread(p.mThread)
    {
        p.mIsOwner = false;
        p.mThread = PROCESS_INVALID_HANDLE;
    }

    Process::~Process()
    {
        try {
            if (mProcessInfo.mHandle != PROCESS_INVALID_HANDLE) {
                if (mIsOwner) {
                    Kill();
                } else {
                    CloseHandle(mProcessInfo.mHandle);
                    CloseHandle(mThread);
                    mProcessInfo.mHandle = PROCESS_INVALID_HANDLE;
                    mThread = PROCESS_INVALID_HANDLE;
                }
            }
        } catch (ProcessException&) {
            // Do nothing
        }
    }

    ProcessState Process::GetState() const
    {
        if (mProcessInfo.mHandle != PROCESS_INVALID_HANDLE) {
            DWORD result = WaitForSingleObject(mProcessInfo.mHandle, 0);
            return (result == WAIT_TIMEOUT) ? ProcessState::IsRunning : ProcessState::NotRunning;
        } else {
            return ProcessState::Invalid;
        }
    }

    int32_t Process::ExitCode() const
    {
        if (mProcessInfo.mHandle != PROCESS_INVALID_HANDLE) {
            DWORD exitCode = ~0;

            if (!GetExitCodeProcess(mProcessInfo.mHandle, &exitCode)) {
                // TODO: Systeminformation abrufen und als Argument übergeben.
                throw ProcessException("");
            } else {
                return static_cast<int32_t>(exitCode);
            }
        } else {
            throw ProcessException("Invalid process handle");
        }
    }

    void Process::Kill()
    {
        if (mProcessInfo.mHandle != PROCESS_INVALID_HANDLE) {
            if (GetState() == ProcessState::IsRunning) {
                // TODO: Bestimmter ExitCode?
                BOOL result = TerminateProcess(mProcessInfo.mHandle, ~0);

                if (!result) {
                    // TODO: Systeminformation abrufen und als Argument übergeben.
                    throw ProcessException("");
                } else {
                    CloseHandle(mProcessInfo.mHandle);
                    CloseHandle(mThread);
                    mProcessInfo.mHandle = PROCESS_INVALID_HANDLE;
                    mThread = PROCESS_INVALID_HANDLE;
                }
            }
        } else {
            throw ProcessException("Invalid process handle");
        }
    }

    Process& Process::Wait()
    {
        if (mProcessInfo.mHandle != PROCESS_INVALID_HANDLE) {
            if (WaitForSingleObject(mProcessInfo.mHandle, INFINITE) == WAIT_FAILED) {
                // TODO: Systeminformation abrufen und als Argument übergeben.
                throw ProcessException("");
            } else {
                CloseHandle(mProcessInfo.mHandle);
                CloseHandle(mThread);
                mProcessInfo.mHandle = PROCESS_INVALID_HANDLE;
                mThread = PROCESS_INVALID_HANDLE;
            }
        } else {
            throw ProcessException("Invalid process handle");
        }
    }

    ProcessInfo Process::GetProcessInfo()
    {
        return mProcessInfo;
    }

    vector<ProcessInfo> Process::GetProcessByName(const string& name)
    {
        vector<ProcessInfo> result;
        DWORD aProcesses[8192];
        DWORD cbNeeded;
        DWORD cProcesses;

        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
            // TODO: Systeminformation abrufen und als Argument übergeben.
            throw ProcessException("");
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
                            ProcessInfo info;
                            info.mHandle = hProcess;
                            info.mId = static_cast<int64_t>(aProcesses[i]);
                            info.mName = szProcessName;
                            result.push_back(info);
                        } else {
                            CloseHandle(hProcess);
                        }
                    } else {
                        CloseHandle(hProcess);
                    }
                }
            }
        }

        return result;
    }

    vector<ProcessInfo> Process::GetProcesses()
    {
        vector<ProcessInfo> result;
        DWORD aProcesses[8192];
        DWORD cbNeeded;
        DWORD cProcesses;

        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
            // TODO: Systeminformation abrufen und als Argument übergeben.
            throw ProcessException("");
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
                        ProcessInfo info;
                        info.mHandle = hProcess;
                        info.mId = static_cast<int64_t>(aProcesses[i]);
                        info.mName = szProcessName;
                        result.push_back(info);
                    } else {
                        CloseHandle(hProcess);
                    }
                }
            }
        }

        return result;
    }
}
#endif
