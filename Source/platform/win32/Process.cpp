#ifdef _MSC_VER
#include "../../../include/libipcpp/Process.h"

using string = std::string;
template <typename T>
using vector = std::vector < T > ;

namespace ipc {
    Process::Process(const string& fileName, const vector<string>& args)
    {
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
        }
    }

    Process::Process(Process&& p)
    {

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
