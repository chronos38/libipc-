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
    result << "Pipe_8_10000_readwrite: " << CallIpcType(pipe, 8, 10000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_20000_readwrite: " << CallIpcType(pipe, 8, 20000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_30000_readwrite: " << CallIpcType(pipe, 8, 30000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_40000_readwrite: " << CallIpcType(pipe, 8, 40000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_50000_readwrite: " << CallIpcType(pipe, 8, 50000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_60000_readwrite: " << CallIpcType(pipe, 8, 60000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_70000_readwrite: " << CallIpcType(pipe, 8, 70000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_80000_readwrite: " << CallIpcType(pipe, 8, 80000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_90000_readwrite: " << CallIpcType(pipe, 8, 90000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_100000_readwrite: " << CallIpcType(pipe, 8, 100000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_10000_readwrite: " << CallIpcType(pipe, 128, 10000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_20000_readwrite: " << CallIpcType(pipe, 128, 20000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_30000_readwrite: " << CallIpcType(pipe, 128, 30000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_40000_readwrite: " << CallIpcType(pipe, 128, 40000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_50000_readwrite: " << CallIpcType(pipe, 128, 50000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_60000_readwrite: " << CallIpcType(pipe, 128, 60000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_70000_readwrite: " << CallIpcType(pipe, 128, 70000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_80000_readwrite: " << CallIpcType(pipe, 128, 80000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_90000_readwrite: " << CallIpcType(pipe, 128, 90000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_100000_readwrite: " << CallIpcType(pipe, 128, 100000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_10000_readwrite: " << CallIpcType(pipe, 4096, 10000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_20000_readwrite: " << CallIpcType(pipe, 4096, 20000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_30000_readwrite: " << CallIpcType(pipe, 4096, 30000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_40000_readwrite: " << CallIpcType(pipe, 4096, 40000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_50000_readwrite: " << CallIpcType(pipe, 4096, 50000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_60000_readwrite: " << CallIpcType(pipe, 4096, 60000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_70000_readwrite: " << CallIpcType(pipe, 4096, 70000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_80000_readwrite: " << CallIpcType(pipe, 4096, 80000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_90000_readwrite: " << CallIpcType(pipe, 4096, 90000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_100000_readwrite: " << CallIpcType(pipe, 4096, 100000, ReadWrite).count() << "ms\n\n";

    ///////////////////////////////////////////////////////////////////////////
    /// SharedMemory
    ///////////////////////////////////////////////////////////////////////////
    result << "SharedMemory_8_10000_readwrite: " << CallIpcType(sharedMemory, 8, 10000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_20000_readwrite: " << CallIpcType(sharedMemory, 8, 20000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_30000_readwrite: " << CallIpcType(sharedMemory, 8, 30000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_40000_readwrite: " << CallIpcType(sharedMemory, 8, 40000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_50000_readwrite: " << CallIpcType(sharedMemory, 8, 50000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_60000_readwrite: " << CallIpcType(sharedMemory, 8, 60000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_70000_readwrite: " << CallIpcType(sharedMemory, 8, 70000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_80000_readwrite: " << CallIpcType(sharedMemory, 8, 80000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_90000_readwrite: " << CallIpcType(sharedMemory, 8, 90000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_100000_readwrite: " << CallIpcType(sharedMemory, 8, 100000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_10000_readwrite: " << CallIpcType(sharedMemory, 128, 10000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_20000_readwrite: " << CallIpcType(sharedMemory, 128, 20000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_30000_readwrite: " << CallIpcType(sharedMemory, 128, 30000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_40000_readwrite: " << CallIpcType(sharedMemory, 128, 40000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_50000_readwrite: " << CallIpcType(sharedMemory, 128, 50000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_60000_readwrite: " << CallIpcType(sharedMemory, 128, 60000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_70000_readwrite: " << CallIpcType(sharedMemory, 128, 70000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_80000_readwrite: " << CallIpcType(sharedMemory, 128, 80000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_90000_readwrite: " << CallIpcType(sharedMemory, 128, 90000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_100000_readwrite: " << CallIpcType(sharedMemory, 128, 100000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_10000_readwrite: " << CallIpcType(sharedMemory, 4096, 10000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_20000_readwrite: " << CallIpcType(sharedMemory, 4096, 20000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_30000_readwrite: " << CallIpcType(sharedMemory, 4096, 30000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_40000_readwrite: " << CallIpcType(sharedMemory, 4096, 40000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_50000_readwrite: " << CallIpcType(sharedMemory, 4096, 50000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_60000_readwrite: " << CallIpcType(sharedMemory, 4096, 60000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_70000_readwrite: " << CallIpcType(sharedMemory, 4096, 70000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_80000_readwrite: " << CallIpcType(sharedMemory, 4096, 80000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_90000_readwrite: " << CallIpcType(sharedMemory, 4096, 90000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_100000_readwrite: " << CallIpcType(sharedMemory, 4096, 100000, ReadWrite).count() << "ms\n\n";

    ///////////////////////////////////////////////////////////////////////////
    /// MemoryMap
    ///////////////////////////////////////////////////////////////////////////
    result << "MemoryMap_8_10000_readwrite: " << CallIpcType(memoryMap, 8, 10000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_20000_readwrite: " << CallIpcType(memoryMap, 8, 20000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_30000_readwrite: " << CallIpcType(memoryMap, 8, 30000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_40000_readwrite: " << CallIpcType(memoryMap, 8, 40000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_50000_readwrite: " << CallIpcType(memoryMap, 8, 50000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_60000_readwrite: " << CallIpcType(memoryMap, 8, 60000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_70000_readwrite: " << CallIpcType(memoryMap, 8, 70000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_80000_readwrite: " << CallIpcType(memoryMap, 8, 80000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_90000_readwrite: " << CallIpcType(memoryMap, 8, 90000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_100000_readwrite: " << CallIpcType(memoryMap, 8, 100000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_10000_readwrite: " << CallIpcType(memoryMap, 128, 10000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_20000_readwrite: " << CallIpcType(memoryMap, 128, 20000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_30000_readwrite: " << CallIpcType(memoryMap, 128, 30000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_40000_readwrite: " << CallIpcType(memoryMap, 128, 40000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_50000_readwrite: " << CallIpcType(memoryMap, 128, 50000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_60000_readwrite: " << CallIpcType(memoryMap, 128, 60000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_70000_readwrite: " << CallIpcType(memoryMap, 128, 70000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_80000_readwrite: " << CallIpcType(memoryMap, 128, 80000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_90000_readwrite: " << CallIpcType(memoryMap, 128, 90000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_100000_readwrite: " << CallIpcType(memoryMap, 128, 100000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_10000_readwrite: " << CallIpcType(memoryMap, 4096, 10000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_20000_readwrite: " << CallIpcType(memoryMap, 4096, 20000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_30000_readwrite: " << CallIpcType(memoryMap, 4096, 30000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_40000_readwrite: " << CallIpcType(memoryMap, 4096, 40000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_50000_readwrite: " << CallIpcType(memoryMap, 4096, 50000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_60000_readwrite: " << CallIpcType(memoryMap, 4096, 60000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_70000_readwrite: " << CallIpcType(memoryMap, 4096, 70000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_80000_readwrite: " << CallIpcType(memoryMap, 4096, 80000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_90000_readwrite: " << CallIpcType(memoryMap, 4096, 90000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_100000_readwrite: " << CallIpcType(memoryMap, 4096, 100000, ReadWrite).count() << "ms\n\n";

    ///////////////////////////////////////////////////////////////////////////
    /// FileLock
    ///////////////////////////////////////////////////////////////////////////
    result << "IpcFileLock_10000: " << CallIpcFileLock(10000).count() << "ms\n";
    result << "IpcFileLock_20000: " << CallIpcFileLock(20000).count() << "ms\n";
    result << "IpcFileLock_30000: " << CallIpcFileLock(30000).count() << "ms\n";
    result << "IpcFileLock_40000: " << CallIpcFileLock(40000).count() << "ms\n";
    result << "IpcFileLock_50000: " << CallIpcFileLock(50000).count() << "ms\n";
    result << "IpcFileLock_60000: " << CallIpcFileLock(60000).count() << "ms\n";
    result << "IpcFileLock_70000: " << CallIpcFileLock(70000).count() << "ms\n";
    result << "IpcFileLock_80000: " << CallIpcFileLock(80000).count() << "ms\n";
    result << "IpcFileLock_90000: " << CallIpcFileLock(90000).count() << "ms\n";
    result << "IpcFileLock_100000: " << CallIpcFileLock(100000).count() << "ms\n\n";
    result << " -- Native Code -- \n\n";

    ///////////////////////////////////////////////////////////////////////////
    /// Native Code
    /// Pipe
    ///////////////////////////////////////////////////////////////////////////
    result << "Pipe_8_10000_readwrite: " << CallNativePipe(8, 10000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_20000_readwrite: " << CallNativePipe(8, 10000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_30000_readwrite: " << CallNativePipe(8, 30000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_40000_readwrite: " << CallNativePipe(8, 40000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_50000_readwrite: " << CallNativePipe(8, 50000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_60000_readwrite: " << CallNativePipe(8, 60000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_70000_readwrite: " << CallNativePipe(8, 70000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_80000_readwrite: " << CallNativePipe(8, 80000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_90000_readwrite: " << CallNativePipe(8, 90000, ReadWrite).count() << "ms\n";
    result << "Pipe_8_100000_readwrite: " << CallNativePipe(8, 100000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_10000_readwrite: " << CallNativePipe(128, 10000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_20000_readwrite: " << CallNativePipe(128, 20000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_30000_readwrite: " << CallNativePipe(128, 30000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_40000_readwrite: " << CallNativePipe(128, 40000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_50000_readwrite: " << CallNativePipe(128, 50000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_60000_readwrite: " << CallNativePipe(128, 60000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_70000_readwrite: " << CallNativePipe(128, 70000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_80000_readwrite: " << CallNativePipe(128, 80000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_90000_readwrite: " << CallNativePipe(128, 90000, ReadWrite).count() << "ms\n";
    result << "Pipe_128_100000_readwrite: " << CallNativePipe(128, 100000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_10000_readwrite: " << CallNativePipe(4096, 10000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_20000_readwrite: " << CallNativePipe(4096, 20000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_30000_readwrite: " << CallNativePipe(4096, 30000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_40000_readwrite: " << CallNativePipe(4096, 40000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_50000_readwrite: " << CallNativePipe(4096, 50000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_60000_readwrite: " << CallNativePipe(4096, 60000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_70000_readwrite: " << CallNativePipe(4096, 70000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_80000_readwrite: " << CallNativePipe(4096, 80000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_90000_readwrite: " << CallNativePipe(4096, 90000, ReadWrite).count() << "ms\n";
    result << "Pipe_4096_100000_readwrite: " << CallNativePipe(4096, 100000, ReadWrite).count() << "ms\n\n";

    ///////////////////////////////////////////////////////////////////////////
    /// SharedMemory
    ///////////////////////////////////////////////////////////////////////////
    result << "SharedMemory_8_10000_readwrite: " << CallNativeSharedMemory(8, 10000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_20000_readwrite: " << CallNativeSharedMemory(8, 20000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_30000_readwrite: " << CallNativeSharedMemory(8, 30000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_40000_readwrite: " << CallNativeSharedMemory(8, 40000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_50000_readwrite: " << CallNativeSharedMemory(8, 50000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_60000_readwrite: " << CallNativeSharedMemory(8, 60000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_70000_readwrite: " << CallNativeSharedMemory(8, 70000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_80000_readwrite: " << CallNativeSharedMemory(8, 80000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_90000_readwrite: " << CallNativeSharedMemory(8, 90000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_8_100000_readwrite: " << CallNativeSharedMemory(8, 100000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_10000_readwrite: " << CallNativeSharedMemory(128, 10000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_20000_readwrite: " << CallNativeSharedMemory(128, 20000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_30000_readwrite: " << CallNativeSharedMemory(128, 30000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_40000_readwrite: " << CallNativeSharedMemory(128, 40000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_50000_readwrite: " << CallNativeSharedMemory(128, 50000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_60000_readwrite: " << CallNativeSharedMemory(128, 60000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_70000_readwrite: " << CallNativeSharedMemory(128, 70000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_80000_readwrite: " << CallNativeSharedMemory(128, 80000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_90000_readwrite: " << CallNativeSharedMemory(128, 90000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_128_100000_readwrite: " << CallNativeSharedMemory(128, 100000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_10000_readwrite: " << CallNativeSharedMemory(4096, 10000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_20000_readwrite: " << CallNativeSharedMemory(4096, 20000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_30000_readwrite: " << CallNativeSharedMemory(4096, 30000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_40000_readwrite: " << CallNativeSharedMemory(4096, 40000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_50000_readwrite: " << CallNativeSharedMemory(4096, 50000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_60000_readwrite: " << CallNativeSharedMemory(4096, 60000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_70000_readwrite: " << CallNativeSharedMemory(4096, 70000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_80000_readwrite: " << CallNativeSharedMemory(4096, 80000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_90000_readwrite: " << CallNativeSharedMemory(4096, 90000, ReadWrite).count() << "ms\n";
    result << "SharedMemory_4096_100000_readwrite: " << CallNativeSharedMemory(4096, 100000, ReadWrite).count() << "ms\n\n";

    ///////////////////////////////////////////////////////////////////////////
    /// MemoryMap
    ///////////////////////////////////////////////////////////////////////////
    result << "MemoryMap_8_10000_readwrite: " << CallNativeMemoryMap(8, 10000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_20000_readwrite: " << CallNativeMemoryMap(8, 20000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_30000_readwrite: " << CallNativeMemoryMap(8, 30000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_40000_readwrite: " << CallNativeMemoryMap(8, 40000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_50000_readwrite: " << CallNativeMemoryMap(8, 50000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_60000_readwrite: " << CallNativeMemoryMap(8, 60000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_70000_readwrite: " << CallNativeMemoryMap(8, 70000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_80000_readwrite: " << CallNativeMemoryMap(8, 80000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_90000_readwrite: " << CallNativeMemoryMap(8, 90000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_8_100000_readwrite: " << CallNativeMemoryMap(8, 100000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_10000_readwrite: " << CallNativeMemoryMap(128, 10000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_20000_readwrite: " << CallNativeMemoryMap(128, 20000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_30000_readwrite: " << CallNativeMemoryMap(128, 30000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_40000_readwrite: " << CallNativeMemoryMap(128, 40000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_50000_readwrite: " << CallNativeMemoryMap(128, 50000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_60000_readwrite: " << CallNativeMemoryMap(128, 60000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_70000_readwrite: " << CallNativeMemoryMap(128, 70000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_80000_readwrite: " << CallNativeMemoryMap(128, 80000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_90000_readwrite: " << CallNativeMemoryMap(128, 90000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_128_100000_readwrite: " << CallNativeMemoryMap(128, 100000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_10000_readwrite: " << CallNativeMemoryMap(4096, 10000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_20000_readwrite: " << CallNativeMemoryMap(4096, 20000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_30000_readwrite: " << CallNativeMemoryMap(4096, 30000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_40000_readwrite: " << CallNativeMemoryMap(4096, 40000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_50000_readwrite: " << CallNativeMemoryMap(4096, 50000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_60000_readwrite: " << CallNativeMemoryMap(4096, 60000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_70000_readwrite: " << CallNativeMemoryMap(4096, 70000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_80000_readwrite: " << CallNativeMemoryMap(4096, 80000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_90000_readwrite: " << CallNativeMemoryMap(4096, 90000, ReadWrite).count() << "ms\n";
    result << "MemoryMap_4096_100000_readwrite: " << CallNativeMemoryMap(4096, 100000, ReadWrite).count() << "ms\n\n";

    ///////////////////////////////////////////////////////////////////////////
    /// FileLock
    ///////////////////////////////////////////////////////////////////////////
    result << "NativeFileLock_10000: " << CallNativeFileLock(10000).count() << "ms\n";
    result << "NativeFileLock_20000: " << CallNativeFileLock(20000).count() << "ms\n";
    result << "NativeFileLock_30000: " << CallNativeFileLock(30000).count() << "ms\n";
    result << "NativeFileLock_40000: " << CallNativeFileLock(40000).count() << "ms\n";
    result << "NativeFileLock_50000: " << CallNativeFileLock(50000).count() << "ms\n";
    result << "NativeFileLock_60000: " << CallNativeFileLock(60000).count() << "ms\n";
    result << "NativeFileLock_70000: " << CallNativeFileLock(70000).count() << "ms\n";
    result << "NativeFileLock_80000: " << CallNativeFileLock(80000).count() << "ms\n";
    result << "NativeFileLock_90000: " << CallNativeFileLock(90000).count() << "ms\n";
    result << "NativeFileLock_100000: " << CallNativeFileLock(100000).count() << "ms\n\n";

    auto file = fopen("./Benchmark.txt", "w");
    auto str = result.str();
    fwrite(str.c_str(), 1, str.length(), file);
    fclose(file);
    return 0;
}
