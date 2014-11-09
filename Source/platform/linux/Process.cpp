#ifdef __linux__
#include "../../../include/libipcpp/Utility.h"
#include "../../../include/libipcpp/Process.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
    
    Process::Process(const ProcessInfo& info)
    {
        mProcess = info.GetHandle();
        ValidateProcessHandle();
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
            
        Kill();
    }

    int32_t Process::ExitCode() const
    {
        
    }

    void Process::Kill()
    {
        int rv = kill(mProcess, SIGKILL);
        if(rv < 0)
            throw ProcessException("Process could not be killed.");
    }

    Process& Process::Wait()
    {
    }

    std::vector<ProcessInfo> Process::GetProcessByName(const std::string& name)
    {
        DIR *directory = opendir("/proc");
        std::vector<ProcessInfo> results;
        
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
                if(it != processCandidate.end()) {
                    ProcessInfo tmp; 
                    tmp.mId = nextPid;
                    tmp.mHandle = nextPid;
                    tmp.mName = name;
                    results.push_back(tmp);
                }
                    
            }
            return results;

        }
    }

    std::vector<ProcessInfo> Process::GetProcesses()
    {

    }
    
    
    Process::ValidateProcessHandle(ProcessHandle& handle) {
        int rv = kill(mProcess, 0);
        if (rv == 0) {
            mIsOwner = true;
            mState = ProcessState::IsRunning;
        }
        else if(rv == EPERM) {
            mIsOwner = false;
            mState = ProcessState::IsRunning;
        } else if(rv < 0) {
            mState = ProcessState::Invalid;
        }
        
        return true;
    }

}
#endif