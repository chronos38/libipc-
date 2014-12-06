#include <libipcpp\SharedMemory.h>
#include <libipcpp\Utility.h>

namespace ipc {
    SharedMemory::SharedMemory(ByteCount byteCount) :
        mLength(byteCount)
    {
        SECURITY_ATTRIBUTES attr;

        memset(&attr, 0, sizeof(attr));
        attr.nLength = sizeof(attr);
        attr.bInheritHandle = TRUE;

        mHandle = CreateFileMapping(INVALID_HANDLE_VALUE, &attr, PAGE_READWRITE | SEC_COMMIT, 0, byteCount, NULL);

        if (!mHandle) {
            throw SharedMemoryException(GetLastErrorString());
        }

        mBuffer = MapViewOfFile(mHandle, FILE_MAP_ALL_ACCESS, 0, 0, byteCount);

        if (mBuffer == NULL) {
            throw SharedMemoryException(GetLastErrorString());
        }
    }

    SharedMemory::~SharedMemory()
    {
        UnmapViewOfFile(mBuffer);
        CloseHandle(mHandle);
        mBuffer = nullptr;
        mHandle = INVALID_HANDLE;
    }

    ByteCount SharedMemory::Length() const
    {
        return mLength;
    }

    char& SharedMemory::operator[](size_t index)
    {
        if (index >= Length()) {
            throw std::out_of_range("index");
        } else {
            return *((char*)mBuffer + index);
        }
    }

    const char& SharedMemory::operator[](size_t index) const
    {
        if (index >= Length()) {
            throw std::out_of_range("index");
        } else {
            return *((char*)mBuffer + index);
        }
    }

    ByteCount SharedMemory::Position() const
    {
        return mPosition;
    }

    void SharedMemory::Position(ByteCount position)
    {
        if (position >= Length()) {
            throw std::out_of_range("position");
        } else {
            mPosition = position;
        }
    }

    ByteCount SharedMemory::Write(const char* buffer, size_t size) const
    {
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        CopyMemory((char*)mBuffer + mPosition, buffer, count);
        mPosition += count;
        return count;
    }

    ByteCount SharedMemory::WriteByte(char byte) const
    {
        if (mPosition == Length()) return 0;
        *((char*)mBuffer + mPosition++) = byte;
        return 1;
    }

    ByteCount SharedMemory::Read(char* buffer, size_t size) const
    {
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        CopyMemory(buffer, (char*)mBuffer + mPosition, count);
        mPosition += count;
        return count;
    }

    int SharedMemory::ReadByte() const
    {
        if (mPosition == Length()) return -1;
        return *((unsigned char*)mBuffer + mPosition++);
    }
}
