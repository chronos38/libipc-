#include <libipcpp\MemoryMap.h>
#include <libipcpp\Utility.h>

using string = std::string;

#define GetFilePointer(handle) SetFilePointer(handle, 0, NULL, FILE_CURRENT)

namespace ipc {
    MemoryMap::MemoryMap(const string& fileName)
    {
        SECURITY_ATTRIBUTES attr;

        memset(&attr, 0, sizeof(attr));
        attr.nLength = sizeof(attr);
        attr.bInheritHandle = TRUE;

        auto hFile = CreateFileA(fileName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &attr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (hFile == INVALID_HANDLE_VALUE) {
            throw MemoryMapException(GetLastErrorString());
        }

        mHandle = CreateFileMappingA(hFile, &attr, PAGE_READWRITE, 0, 0, fileName.c_str());
        CloseHandle(hFile);

        if (!mHandle) {
            throw MemoryMapException(GetLastErrorString());
        }
    }

    MemoryMap::MemoryMap(ByteCount byteCount)
    {
        SECURITY_ATTRIBUTES attr;

        memset(&attr, 0, sizeof(attr));
        attr.nLength = sizeof(attr);
        attr.bInheritHandle = TRUE;

        mHandle = CreateFileMappingA(INVALID_HANDLE_VALUE, &attr, PAGE_READWRITE | SEC_COMMIT, 0, byteCount, NULL);

        if (!mHandle) {
            throw MemoryMapException(GetLastErrorString());
        }
    }

    MemoryMap::~MemoryMap()
    {
        CloseHandle(mHandle);
        mHandle = INVALID_HANDLE;
    }

    ByteCount MemoryMap::Length() const
    {
        return GetFileSize(mHandle, NULL);
    }

    ByteCount MemoryMap::Position() const
    {
        return GetFilePointer(mHandle);
    }

    void MemoryMap::Position(ByteCount position) const
    {
        if (SetFilePointer(mHandle, position, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
            throw MemoryMapException(GetLastErrorString());
        }
    }

    ByteCount MemoryMap::Write(const char* buffer, size_t size) const
    {
        ByteCount count = 0;

        if (!WriteFile(mHandle, buffer, size, &count, NULL)) {
            throw MemoryMapException(GetLastErrorString());
        }

        return count;
    }

    ByteCount MemoryMap::WriteByte(char byte) const
    {
        ByteCount count = 0;

        if (!WriteFile(mHandle, &byte, 1, &count, NULL)) {
            return 0;
        }

        return count;
    }

    ByteCount MemoryMap::Read(char* buffer, size_t size) const
    {
        ByteCount count = 0;

        if (!ReadFile(mHandle, buffer, size, &count, NULL)) {
            throw MemoryMapException(GetLastErrorString());
        }

        return count;
    }

    int MemoryMap::ReadByte() const
    {
        ByteCount count = 0;
        unsigned char result = 0;

        if (!ReadFile(mHandle, &result, 1, &count, NULL) || count != 1) {
            return -1;
        }

        return result;
    }
}
