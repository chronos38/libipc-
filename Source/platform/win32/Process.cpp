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

    ProcessInfo::~ProcessInfo()
    {
        if (mHandle != PROCESS_INVALID_HANDLE) {
            CloseHandle(mHandle);
            mHandle = PROCESS_INVALID_HANDLE;
        }
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
            mIsOwner = true;
            mProcess = processInformation.hProcess; // TODO: hThread speichern.
        }
    }

    Process::Process(const ProcessInfo& info) :
        mProcess(info.mHandle)
    {
    }

    Process::Process(Process&& p) :
        mIsOwner(p.mIsOwner), mProcess(p.mProcess)
    {
        p.mIsOwner = false;
        p.mProcess = PROCESS_INVALID_HANDLE;
    }

    Process::~Process()
    {
        if (mProcess != PROCESS_INVALID_HANDLE) {
            if (mIsOwner) {
                Kill();
            } else {
                CloseHandle(mProcess);
                mProcess = PROCESS_INVALID_HANDLE;

                // TODO: mThread schließen.
            }
        }
    }

    ProcessState Process::GetState() const
    {
        if (mProcess != PROCESS_INVALID_HANDLE) {
            DWORD ret = WaitForSingleObject(mProcess, 0);
            return (ret == WAIT_TIMEOUT) ? ProcessState::IsRunning : ProcessState::NotRunning;
        } else {
            return ProcessState::Invalid;
        }
    }

    int32_t Process::ExitCode() const
    {
        DWORD exitCode = ~0;
        
        if (!GetExitCodeProcess(mProcess, &exitCode)) {
            // TODO: Systeminformation abrufen und als Argument übergeben.
            throw ProcessException("");
        } else {
            return static_cast<int32_t>(exitCode);
        }
    }

    void Process::Kill()
    {
        if (GetState() == ProcessState::IsRunning) {
            // TODO: Bestimmter ExitCode?
            BOOL result = TerminateProcess(mProcess, ~0);

            if (!result) {
                // TODO: Systeminformation abrufen und als Argument übergeben.
                throw ProcessException("");
            } else {
                CloseHandle(mProcess);
                mProcess = PROCESS_INVALID_HANDLE;
            }

            // TODO: mThread terminieren.
        }
    }

    Process& Process::Wait()
    {
        if (WaitForSingleObject(mProcess, INFINITE) == WAIT_FAILED) {
            // TODO: Systeminformation abrufen und als Argument übergeben.
            throw ProcessException("");
        } else {
            CloseHandle(mProcess);
            mProcess = PROCESS_INVALID_HANDLE;

            // TODO: mThread schließen.
        }
    }

    vector<ProcessInfo> Process::GetProcessByName(const string& name)
    {
        vector<ProcessInfo> result;
        DWORD aProcesses[1024];
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
        DWORD aProcesses[1024];
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
