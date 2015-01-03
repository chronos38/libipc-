#include "../../../include/libipcpp/NamedPipe.h"
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>

ipc::NamedPipe::NamedPipe(const std::string& name, ipc::NamedPipeIo flag) throw(NamedPipeException) :
    mIsOpen(false)
{
    struct stat info;
    if (lstat(name.c_str(), &info) != 0) {
        if (errno == ENOENT) {
            mknod(name.c_str(), S_IFIFO | 0666, 0);
        } 
    }
    
    if (!S_ISFIFO(info.st_mode)) {
        throw NamedPipeException("File exists and is not a named pipe!");
    }
    
    
    if (flag == NamedPipeIo::Read)
        mHandle = open(name.c_str(), O_RDONLY);
    else if (flag == NamedPipeIo::Write)
        mHandle = open(name.c_str(), O_WRONLY);
    
    if (mHandle != -1)
        mIsOpen = true;
    
    mConfig = flag;
    
}

ipc::NamedPipe::~NamedPipe()
{
    Close();
}

void ipc::NamedPipe::Close()
{
    close(mHandle);
    mIsOpen = false;
}

ipc::NamedPipeIo ipc::NamedPipe::GetConfiguration() const
{
    return mConfig;
}

bool ipc::NamedPipe::IsOpen() const
{
    return mIsOpen;
}

ipc::ByteCount ipc::NamedPipe::Read(char* out, size_t size) const
{
    int rv = read(mHandle, out, size);
    if(rv < 0) {
        throw NamedPipeException(std::string("Reading the Pipe failed: ") + strerror(errno));
    }
    return rv;
}

int ipc::NamedPipe::ReadByte() const
{
    char c = 0;
    int rv = read(mHandle, &c, 1);
    if(rv < 0) {
        throw NamedPipeException(std::string("Reading the Pipe failed: ") + strerror(errno));
    }
    return c;

}

ipc::ByteCount ipc::NamedPipe::Write(const char* in, size_t size) const
{
    int rv = write(mHandle, in, size);
    if(rv < 0) {
        throw NamedPipeException(std::string("Writing the Pipe failed: ") + strerror(errno));
    }
    return rv;
}

ipc::ByteCount ipc::NamedPipe::WriteByte(char c) const
{

    int rv = write(mHandle, &c, 1);
    if(rv < 0) {
        throw NamedPipeException(std::string("Writing the Pipe failed: ") + strerror(errno));
    }
    return rv;
}

