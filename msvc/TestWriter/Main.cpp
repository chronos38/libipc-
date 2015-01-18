#include "../../include/libipcpp/NamedPipe.h"
#include <cstdio>
#include <string>

int main()
{
    std::string str = "Hello World!";
    auto pipe = ipc::NamedPipe("IpcExample", ipc::NamedPipeIo::Write);


    pipe.Initialize();
    auto n = pipe.Write(str.c_str(), str.size());

    printf("Written: %d\n", n);
    return 0;
}
