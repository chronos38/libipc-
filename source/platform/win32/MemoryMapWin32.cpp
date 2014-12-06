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

        mLength = GetFileSize(hFile, NULL);
        mHandle = CreateFileMappingA(hFile, &attr, PAGE_READWRITE, 0, 0, fileName.c_str());

        if (!mHandle) {
            throw MemoryMapException(GetLastErrorString());
        }

        mBuffer = MapViewOfFile(mHandle, FILE_MAP_ALL_ACCESS, 0, 0, mLength);

        if (mBuffer == NULL) {
            throw MemoryMapException(GetLastErrorString());
        }
    }

    MemoryMap::MemoryMap(ByteCount byteCount) :
        mLength(byteCount)
    {
        SECURITY_ATTRIBUTES attr;

        memset(&attr, 0, sizeof(attr));
        attr.nLength = sizeof(attr);
        attr.bInheritHandle = TRUE;

        mHandle = CreateFileMapping(INVALID_HANDLE_VALUE, &attr, PAGE_READWRITE | SEC_COMMIT, 0, byteCount, NULL);

        if (!mHandle) {
            throw MemoryMapException(GetLastErrorString());
        }

        mBuffer = MapViewOfFile(mHandle, FILE_MAP_ALL_ACCESS, 0, 0, byteCount);

        if (mBuffer == NULL) {
            throw MemoryMapException(GetLastErrorString());
        }
    }

    MemoryMap::~MemoryMap()
    {
        UnmapViewOfFile(mBuffer);
        CloseHandle(mHandle);
        mBuffer = nullptr;
        mHandle = INVALID_HANDLE;
    }

    ByteCount MemoryMap::Length() const
    {
        return mLength;
    }

    ByteCount MemoryMap::Position() const
    {
        return mPosition;
    }

    void MemoryMap::Position(ByteCount position) const
    {
        if (position >= Length()) {
            throw std::out_of_range("position");
        } else {
            mPosition = position;
        }
    }

    ByteCount MemoryMap::Write(const char* buffer, size_t size) const
    {
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        CopyMemory((char*)mBuffer + mPosition, buffer, count);
        mPosition += count;
        return count;
    }

    ByteCount MemoryMap::WriteByte(char byte) const
    {
        if (mPosition == Length()) return 0;
        *((char*)mBuffer + mPosition++) = byte;
        return 1;
    }

    ByteCount MemoryMap::Read(char* buffer, size_t size) const
    {
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        CopyMemory(buffer, (char*)mBuffer + mPosition, count);
        mPosition += count;
        return count;
    }

    int MemoryMap::ReadByte() const
    {
        if (mPosition == Length()) return -1;
        return *((unsigned char*)mBuffer + mPosition++);
    }
}
