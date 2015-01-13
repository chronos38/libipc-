#ifdef _MSC_VER
#include "libipcpp\NamedPipe.h"

using string = std::string;

namespace ipc {
    NamedPipe::NamedPipe(const string& name, NamedPipeIo io) :
        mName("\\\\.\\pipe\\" + name), mConfig(io)
    {
        if (!IsValidFileName(name)) {
            throw NamedPipeException("Name ist invalid. \\ and / are not allowed.");
        }
    }

    NamedPipe::~NamedPipe()
    {
        Close();
    }

    void NamedPipe::Initialize()
    {
        SECURITY_ATTRIBUTES attr;
        attr.bInheritHandle = TRUE;
        attr.nLength = sizeof(SECURITY_ATTRIBUTES);
        attr.lpSecurityDescriptor = NULL;

        mHandle = CreateFileA(
            mName.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            &attr,
            OPEN_EXISTING,
            0,
            NULL);

        if (mHandle == INVALID_HANDLE) {
            mHandle = CreateNamedPipeA(
                mName.c_str(),
                PIPE_ACCESS_DUPLEX,
                PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
                PIPE_UNLIMITED_INSTANCES,
                65536,
                65536,
                NMPWAIT_WAIT_FOREVER,
                &attr);

            if (mHandle == INVALID_HANDLE) {
                throw NamedPipeException(GetLastErrorString());
            } else if (!ConnectNamedPipe(mHandle, NULL) && GetLastError() != ERROR_PIPE_CONNECTED) {
                throw NamedPipeException(GetLastErrorString());
            }
        }
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
        CloseHandle(mHandle);
        mHandle = INVALID_HANDLE;
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
