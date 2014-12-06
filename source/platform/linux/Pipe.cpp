#include "../../../include/libipcpp/Pipe.h"
#include <unistd.h>
#include <cstring>

namespace ipc {
    
    Pipe::Pipe() :
        mOpen(false)
    {
        if(pipe(mHandles) == -1) {
            throw PipeException("Pipe creation failed.");
        }
        mOpen = true;
        
        
    }
    
    Pipe::Pipe(ipc::Pipe&& p)
    {
        mHandles[0] = p.mHandles[0];
        mHandles[1] = p.mHandles[1];
        p.mOpen = mOpen;
        p.mHandles[0] = INVALID_HANDLE;
        p.mHandles[1] = INVALID_HANDLE;
        p.mOpen = false;
        
    }
    
    Pipe::~Pipe()
    {
        if(mOpen)
            Close();
    }

    void Pipe::Close()
    {
        mOpen = false;
        close(mHandles[0]);
        close(mHandles[1]);
    }

    bool Pipe::IsOpen() const
    {
        return mOpen;
    }
    
    ByteCount Pipe::Read(char* out, size_t size) const
    {
        int rv = read(mHandles[0], out, size);
        if(rv < 0) {
            throw PipeException(std::string("Reading the Pipe failed: ") + strerror(errno));
        }
        return rv;
    }
    
    int Pipe::ReadByte() const
    {
        char c = 0;
        int rv = read(mHandles[0], &c, 1);
        if(rv < 0) {
            throw PipeException(std::string("Reading the Pipe failed: ") + strerror(errno));
        }
        return c;

    }

    ByteCount Pipe::Write(const char* in, size_t size) const
    {
        int rv = write(mHandles[1], in, size);
        if(rv < 0) {
            throw PipeException(std::string("Writing the Pipe failed: ") + strerror(errno));
        }
        return rv;
    }


    ByteCount Pipe::WriteByte(char c) const
    {
        int rv = write(mHandles[1], &c, 1);
        if(rv < 0) {
            throw PipeException(std::string("Writing the Pipe failed: ") + strerror(errno));
        }
        return rv;

    }

}