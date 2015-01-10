#include "Header.h"
#include "../include/libipcpp/Pipe.h"
#include "../include/libipcpp/MemoryMap.h"
#include "../include/libipcpp/SharedMemory.h"
#include "../include/libipcpp/FileLock.h"
#include <cstdio>
#include <sstream>

#define KB 1024

#ifdef max
#undef max
#endif

// Variable names: <ipc-type>_<data-size>_<iterations>_<method>

int main()
{
    auto result = std::stringstream();
    auto pipe = ipc::Pipe();
    auto memoryMap = ipc::MemoryMap(409600000);
    auto sharedMemory = ipc::SharedMemory(409600000);

    ///////////////////////////////////////////////////////////////////////////
    /// Pipe
    ///////////////////////////////////////////////////////////////////////////
    result << "Pipe_8_10000_readwrite: " << CallIpcType(pipe, 8, 10000, ReadWrite).count() << "s\n";
    result << "Pipe_8_20000_readwrite: " << CallIpcType(pipe, 8, 20000, ReadWrite).count() << "s\n";
    result << "Pipe_8_30000_readwrite: " << CallIpcType(pipe, 8, 30000, ReadWrite).count() << "s\n";
    result << "Pipe_8_40000_readwrite: " << CallIpcType(pipe, 8, 40000, ReadWrite).count() << "s\n";
    result << "Pipe_8_50000_readwrite: " << CallIpcType(pipe, 8, 50000, ReadWrite).count() << "s\n";
    result << "Pipe_8_60000_readwrite: " << CallIpcType(pipe, 8, 60000, ReadWrite).count() << "s\n";
    result << "Pipe_8_70000_readwrite: " << CallIpcType(pipe, 8, 70000, ReadWrite).count() << "s\n";
    result << "Pipe_8_80000_readwrite: " << CallIpcType(pipe, 8, 80000, ReadWrite).count() << "s\n";
    result << "Pipe_8_90000_readwrite: " << CallIpcType(pipe, 8, 90000, ReadWrite).count() << "s\n";
    result << "Pipe_8_100000_readwrite: " << CallIpcType(pipe, 8, 100000, ReadWrite).count() << "s\n";
    result << "Pipe_128_10000_readwrite: " << CallIpcType(pipe, 128, 10000, ReadWrite).count() << "s\n";
    result << "Pipe_128_20000_readwrite: " << CallIpcType(pipe, 128, 20000, ReadWrite).count() << "s\n";
    result << "Pipe_128_30000_readwrite: " << CallIpcType(pipe, 128, 30000, ReadWrite).count() << "s\n";
    result << "Pipe_128_40000_readwrite: " << CallIpcType(pipe, 128, 40000, ReadWrite).count() << "s\n";
    result << "Pipe_128_50000_readwrite: " << CallIpcType(pipe, 128, 50000, ReadWrite).count() << "s\n";
    result << "Pipe_128_60000_readwrite: " << CallIpcType(pipe, 128, 60000, ReadWrite).count() << "s\n";
    result << "Pipe_128_70000_readwrite: " << CallIpcType(pipe, 128, 70000, ReadWrite).count() << "s\n";
    result << "Pipe_128_80000_readwrite: " << CallIpcType(pipe, 128, 80000, ReadWrite).count() << "s\n";
    result << "Pipe_128_90000_readwrite: " << CallIpcType(pipe, 128, 90000, ReadWrite).count() << "s\n";
    result << "Pipe_128_100000_readwrite: " << CallIpcType(pipe, 128, 100000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_10000_readwrite: " << CallIpcType(pipe, 4096, 10000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_20000_readwrite: " << CallIpcType(pipe, 4096, 20000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_30000_readwrite: " << CallIpcType(pipe, 4096, 30000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_40000_readwrite: " << CallIpcType(pipe, 4096, 40000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_50000_readwrite: " << CallIpcType(pipe, 4096, 50000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_60000_readwrite: " << CallIpcType(pipe, 4096, 60000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_70000_readwrite: " << CallIpcType(pipe, 4096, 70000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_80000_readwrite: " << CallIpcType(pipe, 4096, 80000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_90000_readwrite: " << CallIpcType(pipe, 4096, 90000, ReadWrite).count() << "s\n";
    result << "Pipe_4096_100000_readwrite: " << CallIpcType(pipe, 4096, 100000, ReadWrite).count() << "s\n\n";

    ///////////////////////////////////////////////////////////////////////////
    /// SharedMemory
    ///////////////////////////////////////////////////////////////////////////
    result << "SharedMemory_8_10000_readwrite: " << CallIpcType(sharedMemory, 8, 10000, ReadWrite).count() << "s\n";
    result << "SharedMemory_8_20000_readwrite: " << CallIpcType(sharedMemory, 8, 20000, ReadWrite).count() << "s\n";
    result << "SharedMemory_8_30000_readwrite: " << CallIpcType(sharedMemory, 8, 30000, ReadWrite).count() << "s\n";
    result << "SharedMemory_8_40000_readwrite: " << CallIpcType(sharedMemory, 8, 40000, ReadWrite).count() << "s\n";
    result << "SharedMemory_8_50000_readwrite: " << CallIpcType(sharedMemory, 8, 50000, ReadWrite).count() << "s\n";
    result << "SharedMemory_8_60000_readwrite: " << CallIpcType(sharedMemory, 8, 60000, ReadWrite).count() << "s\n";
    result << "SharedMemory_8_70000_readwrite: " << CallIpcType(sharedMemory, 8, 70000, ReadWrite).count() << "s\n";
    result << "SharedMemory_8_80000_readwrite: " << CallIpcType(sharedMemory, 8, 80000, ReadWrite).count() << "s\n";
    result << "SharedMemory_8_90000_readwrite: " << CallIpcType(sharedMemory, 8, 90000, ReadWrite).count() << "s\n";
    result << "SharedMemory_8_100000_readwrite: " << CallIpcType(sharedMemory, 8, 100000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_10000_readwrite: " << CallIpcType(sharedMemory, 128, 10000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_20000_readwrite: " << CallIpcType(sharedMemory, 128, 20000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_30000_readwrite: " << CallIpcType(sharedMemory, 128, 30000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_40000_readwrite: " << CallIpcType(sharedMemory, 128, 40000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_50000_readwrite: " << CallIpcType(sharedMemory, 128, 50000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_60000_readwrite: " << CallIpcType(sharedMemory, 128, 60000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_70000_readwrite: " << CallIpcType(sharedMemory, 128, 70000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_80000_readwrite: " << CallIpcType(sharedMemory, 128, 80000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_90000_readwrite: " << CallIpcType(sharedMemory, 128, 90000, ReadWrite).count() << "s\n";
    result << "SharedMemory_128_100000_readwrite: " << CallIpcType(sharedMemory, 128, 100000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_10000_readwrite: " << CallIpcType(sharedMemory, 4096, 10000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_20000_readwrite: " << CallIpcType(sharedMemory, 4096, 20000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_30000_readwrite: " << CallIpcType(sharedMemory, 4096, 30000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_40000_readwrite: " << CallIpcType(sharedMemory, 4096, 40000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_50000_readwrite: " << CallIpcType(sharedMemory, 4096, 50000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_60000_readwrite: " << CallIpcType(sharedMemory, 4096, 60000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_70000_readwrite: " << CallIpcType(sharedMemory, 4096, 70000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_80000_readwrite: " << CallIpcType(sharedMemory, 4096, 80000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_90000_readwrite: " << CallIpcType(sharedMemory, 4096, 90000, ReadWrite).count() << "s\n";
    result << "SharedMemory_4096_100000_readwrite: " << CallIpcType(sharedMemory, 4096, 100000, ReadWrite).count() << "s\n\n";

    ///////////////////////////////////////////////////////////////////////////
    /// MemoryMap
    ///////////////////////////////////////////////////////////////////////////
    result << "MemoryMap_8_10000_readwrite: " << CallIpcType(memoryMap, 8, 10000, ReadWrite).count() << "s\n";
    result << "MemoryMap_8_20000_readwrite: " << CallIpcType(memoryMap, 8, 20000, ReadWrite).count() << "s\n";
    result << "MemoryMap_8_30000_readwrite: " << CallIpcType(memoryMap, 8, 30000, ReadWrite).count() << "s\n";
    result << "MemoryMap_8_40000_readwrite: " << CallIpcType(memoryMap, 8, 40000, ReadWrite).count() << "s\n";
    result << "MemoryMap_8_50000_readwrite: " << CallIpcType(memoryMap, 8, 50000, ReadWrite).count() << "s\n";
    result << "MemoryMap_8_60000_readwrite: " << CallIpcType(memoryMap, 8, 60000, ReadWrite).count() << "s\n";
    result << "MemoryMap_8_70000_readwrite: " << CallIpcType(memoryMap, 8, 70000, ReadWrite).count() << "s\n";
    result << "MemoryMap_8_80000_readwrite: " << CallIpcType(memoryMap, 8, 80000, ReadWrite).count() << "s\n";
    result << "MemoryMap_8_90000_readwrite: " << CallIpcType(memoryMap, 8, 90000, ReadWrite).count() << "s\n";
    result << "MemoryMap_8_100000_readwrite: " << CallIpcType(memoryMap, 8, 100000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_10000_readwrite: " << CallIpcType(memoryMap, 128, 10000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_20000_readwrite: " << CallIpcType(memoryMap, 128, 20000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_30000_readwrite: " << CallIpcType(memoryMap, 128, 30000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_40000_readwrite: " << CallIpcType(memoryMap, 128, 40000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_50000_readwrite: " << CallIpcType(memoryMap, 128, 50000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_60000_readwrite: " << CallIpcType(memoryMap, 128, 60000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_70000_readwrite: " << CallIpcType(memoryMap, 128, 70000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_80000_readwrite: " << CallIpcType(memoryMap, 128, 80000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_90000_readwrite: " << CallIpcType(memoryMap, 128, 90000, ReadWrite).count() << "s\n";
    result << "MemoryMap_128_100000_readwrite: " << CallIpcType(memoryMap, 128, 100000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_10000_readwrite: " << CallIpcType(memoryMap, 4096, 10000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_20000_readwrite: " << CallIpcType(memoryMap, 4096, 20000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_30000_readwrite: " << CallIpcType(memoryMap, 4096, 30000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_40000_readwrite: " << CallIpcType(memoryMap, 4096, 40000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_50000_readwrite: " << CallIpcType(memoryMap, 4096, 50000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_60000_readwrite: " << CallIpcType(memoryMap, 4096, 60000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_70000_readwrite: " << CallIpcType(memoryMap, 4096, 70000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_80000_readwrite: " << CallIpcType(memoryMap, 4096, 80000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_90000_readwrite: " << CallIpcType(memoryMap, 4096, 90000, ReadWrite).count() << "s\n";
    result << "MemoryMap_4096_100000_readwrite: " << CallIpcType(memoryMap, 4096, 100000, ReadWrite).count() << "s\n\n";

    auto file = fopen("./Benchmark.txt", "w");
    auto str = result.str();
    fwrite(str.c_str(), 1, str.length(), file);
    fclose(file);
    return 0;
}
