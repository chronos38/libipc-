#ifdef _MSC_VER
#include "libipcpp\NamedPipe.h"

using string = std::string;

namespace ipc {
    NamedPipe::NamedPipe(const string& name, NamedPipeIo io)
    {

    }

    NamedPipe::~NamedPipe()
    {

    }

    ByteCount NamedPipe::Write(const char* in, size_t size) const
    {
        return 0;
    }

    ByteCount NamedPipe::Read(char* out, size_t size) const
    {
        return 0;
    }

    ByteCount NamedPipe::WriteByte(char c) const
    {
        return 0;
    }

    int NamedPipe::ReadByte() const
    {
        return 0;
    }

    void NamedPipe::Close()
    {

    }

    bool NamedPipe::IsOpen() const
    {
        return false;
    }

    NamedPipeIo NamedPipe::GetConfiguration() const
    {
        return mConfig;
    }
}

#endif
