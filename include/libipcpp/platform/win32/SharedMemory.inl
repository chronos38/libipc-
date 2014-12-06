#ifdef _MSC_VER

namespace ipc {
    template <typename InputIt>
    ByteCount SharedMemory::Write(InputIt first, InputIt last) const
    {
        auto buffer = vector<typename std::iterator_traits<InputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<InputIt>::value_type);
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        CopyMemory((char*)mBuffer + mPosition, buffer.data(), count);
        mPosition += count;
        return count;
    }

    template <typename OutputIt>
    ByteCount SharedMemory::Read(OutputIt first, OutputIt last) const
    {
        auto buffer = vector<typename std::iterator_traits<OutputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<OutputIt>::value_type);
        ByteCount count = size > Length() - mPosition ? Length() - mPosition : size;
        if (count == 0) return 0;
        CopyMemory(buffer.data(), (char*)mBuffer + mPosition, count);
        std::copy(std::begin(buffer), std::end(buffer), first);
        mPosition += count;
        return count;
    }
}

#endif
