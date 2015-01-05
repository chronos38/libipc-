libipc++
=======

libipc++ is a Crossplatfrom IPC Library for C++. It supports Windows and Linux systems and allows for easy use of processes,pipes, 
semaphores and more. This library was created as part of a student project at the University Of Applied Science Technikum Wien.

Installation
------------
In order to use this library you have to build it first using the CMake build system.

    ccmake . 
    make 

Usage
-----
After building the shared library simply include libipcpp.h in order to use the whole library
or use only a subset by including the respective header file.
For example a new process can be started like this:

    #include <libipc.h>
    #inlcude <stdio>
   
    int main() 
    {
       try {
         ipc::Process p("programm.exe", "someArguments");
         p.Wait();
         auto rv = p.ExitCode();
         std::cout << "Exit Code was:" << rv << std::endl;
       } catch(ipc::ProcessException e)
       {
         //ErrorHandling
       }
       return 0;
    }
