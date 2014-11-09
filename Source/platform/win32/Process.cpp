#ifdef _MSC_VER
#include "../../../include/libipcpp/Process.h"

using namespace std;

namespace ipc {
    Process::Process()
    {

    }

    Process::Process(Process&& p)
    {

    }

    Process::~Process()
    {

    }

    bool Process::IsValid() const
    {

    }

    int32_t Process::ExitCode() const
    {

    }

    ProcessState Process::GetState() const
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
