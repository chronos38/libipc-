#include "../Header.h"

std::chrono::duration<double, std::ratio<1, 1000>> CallNativePipe(unsigned dataSize, unsigned iterations, CallMethod method)
{
    HANDLE write, read;
    CreatePipe(&read, &write, NULL, 65536);
    char* buffer = new char[dataSize];
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    DWORD n = 0;

    switch (method) {
    case Read:
        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < iterations; i++) {
            ReadFile(read, buffer, dataSize, &n, NULL);
        }
        end = std::chrono::high_resolution_clock::now();
        break;
    case Write:
        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < iterations; i++) {
            WriteFile(write, buffer, dataSize, &n, NULL);
        }
        end = std::chrono::high_resolution_clock::now();
        break;
    case ReadWrite:
        start = std::chrono::high_resolution_clock::now();
        for (unsigned i = 0; i < iterations; i++) {
            WriteFile(write, buffer, dataSize, &n, NULL);
            ReadFile(read, buffer, dataSize, &n, NULL);
        }
        end = std::chrono::high_resolution_clock::now();
        break;
    }

    delete buffer;
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>(end - start);
}
