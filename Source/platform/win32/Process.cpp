#ifdef _MSC_VER
#include "../../../include/libipcpp/Process.h"

using namespace std;

namespace ipc {
    Process::Process(const string& fileName, const vector<string>& args)
    {
    }
    Process::Process(const string& fileName, const string& args)
    {
        LPSTR cmdl = new CHAR[args.size()];
        STARTUPINFO startupInfo;
        PROCESS_INFORMATION processInformation;
        memset(&startupInfo, 0, sizeof(startupInfo));
        memcpy(cmdl, args.data(), args.size());

        BOOL result = CreateProcessA(fileName.c_str(), args, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
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
