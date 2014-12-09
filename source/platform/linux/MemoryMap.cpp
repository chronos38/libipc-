#include "../../../include/libipcpp/MemoryMap.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string>
#include <cstring>

namespace ipc {
    MemoryMap::MemoryMap(const std::string& fileName) throw(MemoryMapException)
    {
        int fd = open(fileName.c_str(), O_RDWR);
        if (fd < 0) {
            char * err = strerror(errno);
            throw MemoryMapException(std::string("Failed to map file to memory: ") + err);
        }
        
        struct stat fileInfo;
        int rv = stat(fileName.c_str(), &fileInfo);
        if (rv < 0) {
            char * err = strerror(errno);
            throw MemoryMapException(std::string("Failed to map file to memory: ") + err);
            
        }
        mLength = fileInfo.st_size;
        
        mBuffer = mmap(nullptr, fileInfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if(mBuffer == (caddr_t)-1) {
            char * err = strerror(errno);
            throw MemoryMapException(std::string("Failed to map file to memory: ") + err);
        }
        
        //File is no longer needed.
        close(fd);
        
        
    }

    MemoryMap::MemoryMap(ByteCount byteCount) :
        mLength(byteCount)
    {
        
    }

    MemoryMap::~MemoryMap()
    {
        int rv = munmap(mBuffer, mLength);
        if(rv < 0) {
            fprintf(stderr, "WARNING: Failed to unmap file: %s", strerror(errno));
        }
    }
}