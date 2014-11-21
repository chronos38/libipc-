namespace ipc {
    template <typename InputIt>
    ByteCount Pipe::Write(InputIt first, InputIt last) const
    {
        return Write(std::vector<char>(first, last).data(), std::distance(first, last));
    }

    template <typename OutputIt>
    ByteCount Pipe::Read(OutputIt first, OutputIt end) const
    {
        OutputIt it = first;
        for (; it != end; std::advance(it, 1)) {
            int byte = ReadByte();

            if (byte != -1) {
                *it = static_cast<char>(byte);
            }
        }

        return static_cast<ByteCount>(std::distance(first, it));
    }
}
