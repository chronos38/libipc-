#ifndef LIBIPC_HEADER_H
#define LIBIPC_HEADER_H

#include "../include/libipcpp/IOBase.h"
#include <chrono>
std::chrono::microseconds CallIpcProcess(unsigned count, const char* procName);
std::chrono::microseconds CallNativeProcess(unsigned count, const char* procName);

enum CallMethod {
    Read,
    Write,
    ReadWrite
};

/*
 * Good test values are:
 * - dataSize:   8 Byte, 128 Byte, 4096 Byte
 * - iterations: 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000
 */

/*
 */
std::chrono::duration<double> CallIpcType(ipc::IOBase& iobase, unsigned dataSize, unsigned iterations, CallMethod method);
std::chrono::duration<double> CallNativePipe(unsigned dataSize, unsigned iterations);
std::chrono::duration<double> CallNativeNamedPipe(unsigned dataSize, unsigned iterations);
std::chrono::duration<double> CallNativeMemoryMap(unsigned dataSize, unsigned iterations);
std::chrono::duration<double> CallNativeSharedMemory(unsigned dataSize, unsigned iterations);

/*
 * Lock/Unlock cycles.
 */
std::chrono::duration<double> CallIpcFileLock(unsigned iterations);
std::chrono::duration<double> CallNativeFileLock(unsigned iterations);

#endif
