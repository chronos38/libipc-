#include "../../include/libipcpp/NamedPipe.h"
#include <cstdio>

int main()
{
    char buffer[1024];
    auto pipe = ipc::NamedPipe("IpcExample", ipc::NamedPipeIo::Read);

    memset(buffer, 0, sizeof(buffer));
    pipe.Initialize();
    pipe.Read(buffer, 1024);

    printf("Read: %s\n", buffer);
    return 0;
}
