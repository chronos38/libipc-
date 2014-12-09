namespace ipc {
    template <typename InputIt>
    ByteCount MemoryMap::Write(InputIt first, InputIt last) const throw(IpcException)
    {
        auto buffer = std::vector<typename std::iterator_traits<InputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<InputIt>::value_type);
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        memcpy((char*)mBuffer + mPosition, buffer.data(), count);
        mPosition += count;
        return count;
    }

    template <typename OutputIt>
    ByteCount MemoryMap::Read(OutputIt first, OutputIt last) const throw(IpcException)
    {
        auto buffer = std::vector<typename std::iterator_traits<OutputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<OutputIt>::value_type);
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        memcpy(buffer.data(), (char*)mBuffer + mPosition, count);
        std::copy(std::begin(buffer), std::end(buffer), first);
        mPosition += count;
        return count;
    }
}