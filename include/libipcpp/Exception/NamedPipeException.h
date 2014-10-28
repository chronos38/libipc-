#ifndef NAMEDPIPE_EXCEPTION
#define NAMEDPIPE_EXCEPTION

#include "IpcException.h"
#include <string>
#include <exception>

namespace ipc
{
    class LIBIPC_API NamedPipeException : public IpcException
    {
        NamedPipeException(const std::string);
        NamedPipeException(const std::string, const std::exception&);
        virtual ~NamedPipeException() = default;
    };

}

#endif
