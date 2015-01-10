#include "Header.h"
#include <cstdint>

std::chrono::duration<double, std::ratio<1, 1000>> CallIpcType(ipc::IOBase& iobase, unsigned dataSize, unsigned iterations, CallMethod method)
{
    char* buffer = new char[dataSize];
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    switch (method) {
    case Read:
        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < iterations; i++) {
            iobase.Read(buffer, dataSize);
        }
        end = std::chrono::high_resolution_clock::now();
        break;
    case Write:
        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < iterations; i++) {
            iobase.Write(buffer, dataSize);
        }
        end = std::chrono::high_resolution_clock::now();
        break;
    case ReadWrite:
        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < iterations; i++) {
            iobase.Write(buffer, dataSize);
            iobase.Read(buffer, dataSize);
        }
        end = std::chrono::high_resolution_clock::now();
        break;
    }

    delete buffer;
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start);
}
