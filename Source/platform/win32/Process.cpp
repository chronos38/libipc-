#ifdef _MSC_VER
#include "../../../include/libipcpp/Process.h"

using string = std::string;
template <typename T>
using vector = std::vector < T > ;
template <typename T>
using shared_ptr = std::shared_ptr < T > ;

namespace ipc {
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

        BOOL result = CreateProcessA(fileName.c_str(), cmdl, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
        delete cmdl;

        if (!result) {
            // TODO: Systeminformation abrufen und als Argument übergeben.
            throw ProcessException("");
        } else {
            mIsOwner = true;
            mProcess = processInformation.hProcess;
            mState = ProcessState::IsRunning;
        }
    }

    Process::Process(Process&& p) :
        mIsOwner(p.mIsOwner), mProcess(p.mProcess), mState(p.mState)
    {
        p.mIsOwner = false;
        p.mProcess = PROCESS_INVALID_HANDLE;
        p.mState = ProcessState::Invalid;
    }

    Process::~Process()
    {

    }

    int32_t Process::ExitCode() const
    {

    }

    void Process::Kill()
    {

    }

    Process& Process::Wait()
    {

    }

    vector<shared_ptr<Process>> Process::GetProcessByName(const string& name)
    {

    }

    vector<ProcessInfo> Process::GetProcesses()
    {

    }
}
#endif
