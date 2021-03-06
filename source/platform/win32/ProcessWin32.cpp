#ifdef _MSC_VER
#include <libipcpp\Process.h>
#include <Psapi.h>

using string = std::string;
template <typename T>
using vector = std::vector < T > ;

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
        string str;

        for (const string& arg : args) {
            if (!arg.empty()) {
                if (str.empty()) {
                    str += arg;
                } else {
                    str += " " + arg;
                }
            }
        }

        LPSTR cmdl = new CHAR[str.size() + 1];
        STARTUPINFO startupInfo;
        PROCESS_INFORMATION processInformation;
        memset(&startupInfo, 0, sizeof(startupInfo));
        memset(cmdl, 0, str.size() + 1);
        memcpy(cmdl, str.data(), str.size());

        startupInfo.cb = sizeof(startupInfo);

        BOOL result = CreateProcessA(fileName.c_str(), cmdl, NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInformation);
        delete cmdl;

        if (!result) {
            throw ProcessException(GetLastErrorString());
        } else {
            CHAR cFileName[MAX_PATH];
            CHAR cExt[MAX_PATH];
            mIsOwner = true;
            mProcessInfo.mHandle = processInformation.hProcess;
            mProcessInfo.mId = processInformation.dwProcessId;
            mThread = processInformation.hThread;
            memset(cFileName, 0, sizeof(cFileName));
            memset(cExt, 0, sizeof(cExt));
            _splitpath_s(fileName.c_str(), NULL, 0, NULL, 0, cFileName, sizeof(cFileName), cExt, sizeof(cExt));
            mProcessInfo.mName = string(cFileName) + string(cExt);
        }
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

        BOOL result = CreateProcessA(fileName.c_str(), cmdl, NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInformation);
        delete cmdl;

        if (!result) {
            throw ProcessException(GetLastErrorString());
        } else {
            CHAR cFileName[MAX_PATH];
            CHAR cExt[MAX_PATH];
            mIsOwner = true;
            mProcessInfo.mHandle = processInformation.hProcess;
            mProcessInfo.mId = processInformation.dwProcessId;
            mThread = processInformation.hThread;
            memset(cFileName, 0, sizeof(cFileName));
            memset(cExt, 0, sizeof(cExt));
            _splitpath_s(fileName.c_str(), NULL, 0, NULL, 0, cFileName, sizeof(cFileName), cExt, sizeof(cExt));
            mProcessInfo.mName = string(cFileName) + string(cExt);
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
        } catch (ProcessException& e) {
            fprintf(stderr, "Silent throw in process: %s\n", e.what());
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
                throw ProcessException(GetLastErrorString());
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
            auto state = GetState();

            if (state == ProcessState::IsRunning) {
                BOOL result = TerminateProcess(mProcessInfo.mHandle, ~0);

                if (!result) {
                    throw ProcessException(GetLastErrorString());
                } else {
                    CloseHandle(mProcessInfo.mHandle);
                    CloseHandle(mThread);
                    mProcessInfo.mHandle = PROCESS_INVALID_HANDLE;
                    mThread = PROCESS_INVALID_HANDLE;
                }
            } else if (state == ProcessState::NotRunning) {
                CloseHandle(mProcessInfo.mHandle);
                CloseHandle(mThread);
                mProcessInfo.mHandle = PROCESS_INVALID_HANDLE;
                mThread = PROCESS_INVALID_HANDLE;
            }
        } else {
            throw ProcessException("Invalid process handle");
        }
    }

    Process& Process::Wait()
    {
        if (mProcessInfo.mHandle != PROCESS_INVALID_HANDLE) {
            if (WaitForSingleObject(mProcessInfo.mHandle, INFINITE) == WAIT_FAILED) {
                throw ProcessException(GetLastErrorString());
            } else {
                CloseHandle(mProcessInfo.mHandle);
                CloseHandle(mThread);
                mProcessInfo.mHandle = PROCESS_INVALID_HANDLE;
                mThread = PROCESS_INVALID_HANDLE;
            }
        } else {
            throw ProcessException("Invalid process handle");
        }

        return *this;
    }

    vector<ProcessInfo> Process::GetProcessByName(const string& name)
    {
        vector<ProcessInfo> result;
        DWORD aProcesses[8192];
        DWORD cbNeeded;
        DWORD cProcesses;

        if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
            throw ProcessException(GetLastErrorString());
        }

        cProcesses = cbNeeded / sizeof(DWORD);

        for (DWORD i = 0; i < cProcesses; i++) {
            if (aProcesses[i] != 0) {
                CHAR szProcessName[MAX_PATH];
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
                memset(szProcessName, 0, sizeof(szProcessName));

                if (hProcess) {
                    HMODULE hMod;
                    DWORD cbNeeded;

                    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                        GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(CHAR));
                        
                        if (szProcessName == name) {
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
            throw ProcessException(GetLastErrorString());
        }

        cProcesses = cbNeeded / sizeof(DWORD);

        for (DWORD i = 0; i < cProcesses; i++) {
            if (aProcesses[i] != 0) {
                CHAR szProcessName[MAX_PATH];
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
                memset(szProcessName, 0, sizeof(szProcessName));

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

    Process& Process::operator=(Process&& p)
    {
        mIsOwner = p.mIsOwner;
        mProcessInfo = p.mProcessInfo;
        mThread = p.mThread;
        
        p.mIsOwner = false;
        p.mProcessInfo = ProcessInfo();
        p.mThread = PROCESS_INVALID_HANDLE;

        return *this;
    }
    
    bool Process::IsValid() NOEXCEPT
    {
        return (mProcessInfo.mHandle != PROCESS_INVALID_HANDLE && WaitForSingleObject(mProcessInfo.mHandle, 0) == WAIT_TIMEOUT);
    }
}
#endif
