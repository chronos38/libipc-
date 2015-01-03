#ifdef _MSC_VER
#include "libipcpp\NamedPipe.h"

using string = std::string;

namespace ipc {
    NamedPipe::NamedPipe(const string& name, NamedPipeIo io)
    {
        DWORD config = GENERIC_READ | GENERIC_WRITE;
        auto pipeName = "\\\\.\\pipe\\" + name;
        SECURITY_ATTRIBUTES attr;
        attr.bInheritHandle = TRUE;
        attr.nLength = sizeof(SECURITY_ATTRIBUTES);
        attr.lpSecurityDescriptor = NULL;

        switch (io) {
        case NamedPipeIo::Read: config = GENERIC_READ;
        case NamedPipeIo::Write: config = GENERIC_WRITE;
        }

        mHandle = CreateFileA(
            pipeName.c_str(), 
            config,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            &attr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        
        if (mHandle == INVALID_HANDLE) {
            auto hPipe = CreateNamedPipeA(
                pipeName.c_str(),
                PIPE_ACCESS_DUPLEX,
                0,
                PIPE_UNLIMITED_INSTANCES,
                65536,
                65536,
                PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
                &attr);

            if (hPipe == INVALID_HANDLE) {
                throw NamedPipeException(GetLastErrorString());
            }

            mHandle = CreateFileA(
                pipeName.c_str(),
                config,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                &attr,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);

            CloseHandle(hPipe);
        }

        if (mHandle == INVALID_HANDLE) {
            throw NamedPipeException(GetLastErrorString());
        }
    }

    NamedPipe::~NamedPipe()
    {
        CloseHandle(mHandle);
    }

    ByteCount NamedPipe::Write(const char* in, size_t size) const
    {
        DWORD n = 0;

        if (!WriteFile(mHandle, in, size, &n, NULL)) {
            throw NamedPipeException(GetLastErrorString());
        }

        return n;
    }

    ByteCount NamedPipe::Read(char* out, size_t size) const
    {
        DWORD n = 0;

        if (!ReadFile(mHandle, out, size, &n, NULL)) {
            throw NamedPipeException(GetLastErrorString());
        }

        return n;
    }

    ByteCount NamedPipe::WriteByte(char c) const
    {
        DWORD n = 0;
        unsigned char b = (unsigned char)c;

        if (!WriteFile(mHandle, &b, 1, &n, NULL)) {
            return 0;
        }

        return n;
    }

    int NamedPipe::ReadByte() const
    {
        DWORD n = 0;
        int result = -1;

        if (!ReadFile(mHandle, &result, 1, &n, NULL) || n == 0) {
            return -1;
        }

        return (unsigned char)result;
    }

    void NamedPipe::Close()
    {

    }

    bool NamedPipe::IsOpen() const
    {
        return mHandle != INVALID_HANDLE;
    }

    NamedPipeIo NamedPipe::GetConfiguration() const
    {
        return mConfig;
    }
}

#endif
