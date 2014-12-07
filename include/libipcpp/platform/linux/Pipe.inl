namespace ipc {
    template <typename InputIt>
    ByteCount Pipe::Write(InputIt first, InputIt last) const
    {
        auto buffer = std::vector<typename std::iterator_traits<InputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<InputIt>::value_type);
        
        int rv = write(mHandles[1], buffer.data(), size);
        if(rv < 0) {
            throw PipeException(std::string("Writing the Pipe failed: ") + strerror(errno));
        }
        return rv;
    
    }
    
    template <typename OutputIt>
    ByteCount Pipe::Read(OutputIt first, OutputIt last) const
    {
        auto buffer = std::vector<typename std::iterator_traits<OutputIt>::value_type>(first, last);
        auto size = std::distance(first, last) * sizeof(typename std::iterator_traits<OutputIt>::value_type);
        
        int rv = read(mHandles[0], buffer.data(), size);
        if(rv < 0) {
            throw PipeException(std::string("Reading the Pipe failed: ") + strerror(errno));
        }
        std::copy(std::begin(buffer), std::end(buffer), first);
        return rv;
    
    }
}