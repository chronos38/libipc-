#ifdef _MSC_VER

#include "libipcpp\Utility.h"

namespace ipc {
    bool IsValidFileName(std::string& fileName)
    {
        return false;
    }

    bool IsNumber(const std::string& input)
    {
        return false;
    }

    void SplitString(const std::string& str, const std::string& delimiters, std::vector<std::string>& tokens)
    {

    }

    std::string GetLastErrorString()
    {
        // Retrieve the system error message for the last-error code
        CHAR buffer[1024];
        DWORD dw = GetLastError();
        memset(buffer, 0, 1024);

        FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            buffer,
            1023, NULL);

        return buffer;
    }
}

#endif
