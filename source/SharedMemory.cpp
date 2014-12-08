#include "../include/libipcpp/SharedMemory.h"
#include <cstring>

namespace ipc {
    
    ByteCount SharedMemory::Length() const NOEXCEPT
    {
        return mLength;
    }

    char& SharedMemory::operator[](size_t index) throw(SharedMemoryException, std::out_of_range)
    {
        if (index >= Length()) {
            throw std::out_of_range("index");
        } else {
            return *((char*)mBuffer + index);
        }
    }

    const char& SharedMemory::operator[](size_t index) const throw(SharedMemoryException, std::out_of_range)
    {
        if (index >= Length()) {
            throw std::out_of_range("index");
        } else {
            return *((char*)mBuffer + index);
        }
    }

    ByteCount SharedMemory::Position() const NOEXCEPT
    {
        return mPosition;
    }

    void SharedMemory::Position(ByteCount position) throw(std::out_of_range)
    {
        if (position >= Length()) {
            throw std::out_of_range("position");
        } else {
            mPosition = position;
        }
    }

    ByteCount SharedMemory::Write(const char* buffer, size_t size) const throw(SharedMemoryException) 
    {
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        
        memcpy((char*)mBuffer + mPosition, buffer, count);
        mPosition += count;
        return count;
    }

    ByteCount SharedMemory::WriteByte(char byte) const NOEXCEPT
    {
        if (mPosition == Length()) return 0;
        *((char*)mBuffer + mPosition++) = byte;
        return 1;
    }

    ByteCount SharedMemory::Read(char* buffer, size_t size) const throw(SharedMemoryException)
    {
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        memcpy(buffer, (char*)mBuffer + mPosition, count);
        mPosition += count;
        return count;
    }

    int SharedMemory::ReadByte() const NOEXCEPT
    {
        if (mPosition == Length()) return -1;
        return *((unsigned char*)mBuffer + mPosition++);
    }
}