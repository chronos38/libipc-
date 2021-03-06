#include <libipcpp\Pipe.h>

#define PIPE_SIZE 65536

namespace ipc {
    Pipe::Pipe()
    {
        if (!CreatePipe(&mHandles[1], &mHandles[0], NULL, PIPE_SIZE)) {
            throw PipeException(GetLastErrorString());
        }
    }

    Pipe::Pipe(Pipe&& p)
    {
        mHandles[0] = p.mHandles[0];
        mHandles[1] = p.mHandles[1];
        p.mHandles[0] = INVALID_HANDLE;
        p.mHandles[1] = INVALID_HANDLE;
    }

    Pipe::~Pipe()
    {
        try {
            Close();
        } catch (PipeException& e) {
            fprintf(stderr, "Silent throw in pipe: %s\n", e.what());
        }
    }

    ByteCount Pipe::Write(const char* in, size_t size) const
    {
        DWORD n = 0;

        if (!WriteFile(mHandles[0], in, size, &n, NULL)) {
            throw PipeException(GetLastErrorString());
        }

        return n;
    }

    ByteCount Pipe::Read(char* out, size_t size) const
    {
        DWORD n = 0;

        if (!ReadFile(mHandles[1], out, size, &n, NULL)) {
            throw PipeException(GetLastErrorString());
        }

        return n;
    }

    ByteCount Pipe::WriteByte(char c) const
    {
        DWORD n = 0;
        unsigned char b = (unsigned char)c;

        if (!WriteFile(mHandles[0], &b, 1, &n, NULL)) {
            return 0;
        }

        return n;
    }

    int Pipe::ReadByte() const
    {
        DWORD n = 0;
        int result = -1;

        if (!ReadFile(mHandles[1], &result, 1, &n, NULL) || n == 0) {
            return -1;
        }

        return (unsigned char)result;
    }

    void Pipe::Close()
    {
        BOOL success = FALSE;

        if (mHandles[0] != INVALID_HANDLE) {
            success = CloseHandle(mHandles[0]);
            mHandles[0] = INVALID_HANDLE;
        }

        if (mHandles[1] != INVALID_HANDLE) {
            if (success) {
                CloseHandle(mHandles[1]);
            } else {
                success = CloseHandle(mHandles[1]);
            }

            mHandles[1] = INVALID_HANDLE;
        }

        if (!success) {
            throw PipeException(GetLastErrorString());
        }
    }

    bool Pipe::IsOpen() const
    {
        return (mHandles[0] != INVALID_HANDLE && mHandles[1] != INVALID_HANDLE);
    }
}
