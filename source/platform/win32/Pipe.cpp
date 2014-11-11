#include "../../../include/libipcpp/Pipe.h"

namespace ipc {
    ByteCount Pipe::Write(const std::vector<uint8_t>& in, size_t size, size_t offset)
    {
        return 0;
    }

    ByteCount Pipe::Read(std::vector<uint8_t>& out, size_t size, size_t offset)
    {
        return 0;
    }

    ByteCount Pipe::WriteByte(uint8_t c)
    {
        return 0;
    }

    int Pipe::ReadByte()
    {
        return -1;
    }
}
