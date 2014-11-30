#ifdef _MSC_VER
namespace ipc {
    template <typename InputIt>
    ByteCount Pipe::Write(InputIt first, InputIt last) const
    {
        auto buffer = vector<typename std::iterator_traits<InputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<InputIt>::value_type);
        DWORD n = 0;

        if (!WriteFile(mHandles[0], buffer.data(), size, &n, NULL)) {
            throw PipeException(GetLastErrorString());
        }

        return n;
    }

    template <typename OutputIt>
    ByteCount Pipe::Read(OutputIt first, OutputIt last) const
    {
        auto buffer = vector<typename std::iterator_traits<OutputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<OutputIt>::value_type);
        DWORD n = 0;

        if (!ReadFile(mHandles[1], buffer.data(), size, &n, NULL)) {
            throw PipeException(GetLastErrorString());
        } else {
            std::copy(std::begin(buffer), std::end(buffer), first);
        }

        return n;
    }
}
#endif
