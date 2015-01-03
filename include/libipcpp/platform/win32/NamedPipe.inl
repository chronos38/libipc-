namespace ipc {

    template <typename InputIt>
    ByteCount NamedPipe::Write(InputIt first, InputIt last) const
    {
        auto buffer = vector<typename std::iterator_traits<InputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<InputIt>::value_type);
        DWORD n = 0;

        if (!WriteFile(mHandle, buffer.data(), size, &n, NULL)) {
            throw NamedPipeException(GetLastErrorString());
        }

        return n;
    }

    template <typename OutputIt>
    ByteCount NamedPipe::Read(OutputIt first, OutputIt last) const
    {
        auto buffer = vector<typename std::iterator_traits<OutputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<OutputIt>::value_type);
        DWORD n = 0;

        if (!ReadFile(mHandle, buffer.data(), size, &n, NULL)) {
            throw NamedPipeException(GetLastErrorString());
        } else {
            std::copy(std::begin(buffer), std::end(buffer), first);
        }

        return n;
    }
}
