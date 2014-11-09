#ifdef _MSC_VER
#include "../../../include/libipcpp/Process.h"

using namespace std;

namespace ipc {
    Process::Process(const string& fileName, const vector<string>& args)
    {

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
