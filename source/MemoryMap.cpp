#include "../include/libipcpp/MemoryMap.h"
#include <cstring>

namespace ipc {
    
    ByteCount MemoryMap::Length() const NOEXCEPT
    {
        return mLength;
    }

    ByteCount MemoryMap::Position() const NOEXCEPT
    {
        return mPosition;
    }

    void MemoryMap::Position(ByteCount position) const throw(std::out_of_range)
    {
        if (position >= Length()) {
            throw std::out_of_range("position");
        } else {
            mPosition = position;
        }
    }

    ByteCount MemoryMap::Write(const char* buffer, size_t size) const throw(MemoryMapException)
    {
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        memcpy((char*)mBuffer + mPosition, buffer, count);
        mPosition += count;
        return count;
    }

    ByteCount MemoryMap::WriteByte(char byte) const NOEXCEPT
    {
        if (mPosition == Length()) return 0;
        *((char*)mBuffer + mPosition++) = byte;
        return 1;
    }

    ByteCount MemoryMap::Read(char* buffer, size_t size) const throw(MemoryMapException) 
    {
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        memcpy(buffer, (char*)mBuffer + mPosition, count);
        mPosition += count;
        return count;
    }

    int MemoryMap::ReadByte() const NOEXCEPT
    {
        if (mPosition == Length()) return -1;
        return *((unsigned char*)mBuffer + mPosition++);
    }
}