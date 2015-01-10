#include "../Header.h"
#include "../../include/libipcpp/FileLock.h"

std::chrono::duration<double> CallIpcFileLock(unsigned iterations)
{
    auto file = CreateFileA(".\\BenchmarkFileLock.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    auto lock = ipc::FileLock(file);
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    start = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < iterations; i++) {
        lock.Lock();
        lock.Unlock();
    }
    end = std::chrono::high_resolution_clock::now();

    CloseHandle(file);
    std::remove(".\\BenchmarkFileLock.txt");
    return std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
}

std::chrono::duration<double> CallNativeFileLock(unsigned iterations)
{
    auto file = CreateFileA(".\\BenchmarkFileLock.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    DWORD high = 0;

    start = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < iterations; i++) {
        LockFile(file, 0, 0, GetFileSize(file, &high), high);
        UnlockFile(file, 0, 0, GetFileSize(file, &high), high);
    }
    end = std::chrono::high_resolution_clock::now();

    CloseHandle(file);
    std::remove(".\\BenchmarkFileLock.txt");
    return std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
}
