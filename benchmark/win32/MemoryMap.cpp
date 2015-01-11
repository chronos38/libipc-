#include "../Header.h"

std::chrono::duration<double, std::ratio<1, 1000>> CallNativeMemoryMap(unsigned dataSize, unsigned iterations, CallMethod method)
{
    auto handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_COMMIT, 0, dataSize * iterations, NULL);
    auto sharedBuffer = MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    char* buffer = new char[dataSize];
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    switch (method) {
    case Read:
        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < iterations; i++) {
            CopyMemory(buffer, (char*)sharedBuffer, dataSize);
        }
        end = std::chrono::high_resolution_clock::now();
        break;
    case Write:
        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < iterations; i++) {
            CopyMemory((char*)sharedBuffer, buffer, dataSize);
        }
        end = std::chrono::high_resolution_clock::now();
        break;
    case ReadWrite:
        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < iterations; i++) {
            CopyMemory((char*)sharedBuffer, buffer, dataSize);
            CopyMemory(buffer, (char*)sharedBuffer, dataSize);
        }
        end = std::chrono::high_resolution_clock::now();
        break;
    }

    delete buffer;
    UnmapViewOfFile(sharedBuffer);
    CloseHandle(handle);
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start);
}
