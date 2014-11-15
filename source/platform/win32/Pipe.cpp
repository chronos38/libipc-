#include "../../../include/libipcpp/Pipe.h"

using out_of_range = std::out_of_range;

namespace ipc {
    Pipe::Pipe(Pipe&& p)
    {
        // INFO: Größe bestimmen?
        if (!CreatePipe(&mHandles[1], &mHandles[0], NULL, 65536)) {
            // TODO: Information auslesen.
            throw PipeException("");
        }
    }

    Pipe::~Pipe()
    {
        try {
            Close();
        } catch (PipeException&) {
            // Do nothing
        }
    }

    ByteCount Pipe::Write(const char* in, size_t size) const
    {
        DWORD n = 0;

        if (!WriteFile(mHandles[0], in, size, &n, NULL)) {
            // TODO: Information auslesen.
            throw PipeException("");
        }

        return n;
    }

    ByteCount Pipe::Read(char* out, size_t size) const
    {
        DWORD n = 0;

        if (!ReadFile(mHandles[1], out, size, &n, NULL)) {
            // TODO: Information auslesen.
            throw PipeException("");
        }

        return n;
    }

    ByteCount Pipe::WriteByte(char c) const
    {
        DWORD n = 0;

        if (!WriteFile(mHandles[0], &c, 1, &n, NULL)) {
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

        return result;
    }

    void Pipe::Close()
    {
        BOOL error = FALSE;

        if (mHandles[0] != INVALID_HANDLE) {
            error = CloseHandle(mHandles[0]);
            mHandles[0] = INVALID_HANDLE;
        }

        if (mHandles[1] != INVALID_HANDLE) {
            if (!error) {
                error = CloseHandle(mHandles[1]);
            } else {
                CloseHandle(mHandles[1]);
            }

            mHandles[1] = INVALID_HANDLE;
        }

        if (error) {
            // TODO: Information auslesen.
            throw PipeException("");
        }
    }

    bool Pipe::IsOpen() const
    {
        return (mHandles[0] != INVALID_HANDLE && mHandles[1] != INVALID_HANDLE);
    }
}
