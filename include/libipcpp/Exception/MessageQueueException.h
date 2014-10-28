#ifndef MESSAGEQUEUE_EXCEPTION
#define MESSAGEQUEUE_EXCEPTION

#include "IpcException.h"
#include <string>
#include <exception>

namespace ipc
{
    class LIBIPC_API MessageQueueException : public IpcException
    {
    MessageQueueException ( const std::string& );
    MessageQueueException ( const std::string , const exception& ex );
    virtual ~MessageQueueException();
    virtual const char* what() const;
    };

}

#endif
