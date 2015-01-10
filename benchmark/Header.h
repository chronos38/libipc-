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
 *
 * ReadWrite = write and read cycles
 * Read = only read cycles
 * Write = only write cycles
 */

/*
 */
std::chrono::duration<double, std::ratio<1, 1000>> CallIpcType(ipc::IOBase& iobase, unsigned dataSize, unsigned iterations, CallMethod method);
std::chrono::duration<double, std::ratio<1, 1000>> CallNativePipe(unsigned dataSize, unsigned iterations, CallMethod method);
std::chrono::duration<double, std::ratio<1, 1000>> CallNativeMemoryMap(unsigned dataSize, unsigned iterations, CallMethod method);
std::chrono::duration<double, std::ratio<1, 1000>> CallNativeSharedMemory(unsigned dataSize, unsigned iterations, CallMethod method);

/*
 * Lock/Unlock cycles.
 */
std::chrono::duration<double, std::ratio<1, 1000>> CallIpcFileLock(unsigned iterations);
std::chrono::duration<double, std::ratio<1, 1000>> CallNativeFileLock(unsigned iterations);

#endif
