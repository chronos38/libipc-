namespace ipc {
    template <typename InputIt>
    ByteCount NamedPipe::Write(InputIt first, InputIt last) const
    {
        auto buffer = std::vector<typename std::iterator_traits<InputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<InputIt>::value_type);
        
        int rv = write(mHandle, buffer.data(), size);
        if(rv < 0) {
            throw NamedPipeException(std::string("Writing the Pipe failed: ") + strerror(errno));
        }
        return rv;
    
    }
    
    template <typename OutputIt>
    ByteCount NamedPipe::Read(OutputIt first, OutputIt last) const
    {
        auto buffer = std::vector<typename std::iterator_traits<OutputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<OutputIt>::value_type);
        
        int rv = read(mHandle, buffer.data(), size);
        if(rv < 0) {
            throw NamedPipeException(std::string("Reading the Pipe failed: ") + strerror(errno));
        }
        std::copy(std::begin(buffer), std::end(buffer), first);
        return rv;
    }
}