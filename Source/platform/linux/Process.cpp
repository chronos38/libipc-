
#include "../../../include/libipcpp/Utility.h"
#include "../../../include/libipcpp/Process.h"
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <algorithm>

namespace ipc {
    
   
    Process::Process(const std::string& fileName, const std::vector<std::string>& args)
    {
        std::string str();
        for(const std::string& arg : args) {
            str += " " + arg;
        }
        Process(fileName, args);
    }
    
    Process::Process(const std::string& fileName, const std::string& args)
    {
        pid_t pid = fork();
        switch(pid) {
            case -1:
                throw ProcessException("Process could not be created.");
                break;
            case 0:
                execv(fileName, static_cast<char *[]>{fileName, args, NULL});
            default:
                mProcess = pid;
                mState = ProcessState::IsRunning;
        }
    }
    
    Process::Process(const ProcessHandle& handle)
    {
        mProcess = handle;
        if (!IsValid()) {
            throw ProcessException("Process handle is not valid.");
        }
    }

    Process::Process(Process&& p)
    {

    }

    Process::~Process()
    {
        if(!mIsOwner);
            return;
            
        int rv = kill(mProcess, SIGKILL);
        if (rv == EPERM)
            throw ProcessException("Process could not be killed");
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

    std::vector<shared_ptr<Process>> Process::GetProcessByName(const std::string& name)
    {
        DIR *directory = opendir("/proc");
        std::vector<Process> results;
        if(directory) {
            struct dirent *dirEntry;
            while ((dirEntry = readdir(directory)))
            {
                if(!IsNumber(dirEntry->d_name))
                continue;

                int nextPid = std::stoi(dirEntry->d_name);

                std::string path = std::string("/proc/") + dirEntry->d_name + "/cmdline";
                std::ifstream file(path);
                std::string line;
                std::getline(file, line, '\0');
                if(line.empty())
                continue;
                std::vector< std::string > tokens;
                SplitString(line, "/", tokens);

                std::string processCandidate = tokens.back();
                auto it = std::search(processCandidate.begin(), processCandidate.end(), name.begin(), name.end());
                if(it != processCandidate.end())
                results.push_back(nextPid);
            }
            return;

        }
    }

    std::vector<ProcessInfo> Process::GetProcesses()
    {

    }
    
    
    Process::ValidateProcessHandle(ProcessHandle& handle) {
        int rv = kill(mProcess, 0);
        if(rv == EPERM) {
            mIsOwner = false;
            mState = ProcessState::IsRunning;
        } else if(rv < 0) {
            mState = ProcessState::Invalid;
        }
        
        return true;
    }

}