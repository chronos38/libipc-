#include "../../../include/libipcpp/Process.h"

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
}
