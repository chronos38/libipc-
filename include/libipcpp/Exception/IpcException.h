#ifndef IPC_EXCEPTION
#define IPC_EXCEPTION

#include "../Definitions.h"
#include <exception>

namespace ipc {
    class LIBIPC_API IpcException : public std::exception
    {
    public:
        IpcException(const std::string&);
        IpcException(const std::string, const std::exception& ex);
        ~IpcException() = default;
        const char* what() const override;
    private:
        std::string mMsg = "";
        std::exception mInnerException;
    };

}
#endif
