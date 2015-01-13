#ifdef _MSC_VER

#include "libipcpp\Utility.h"

namespace ipc {
    /*bool IsValidFileName(const std::string& fileName)
    {
        return (fileName.find_first_of("\\/") == fileName.npos);
    }

    bool IsNumber(const std::string& input)
    {
        int64_t i = 0;
        return (std::sscanf(input.c_str(), "%lld", &i) == 1);
    }

    void SplitString(const std::string& str, const std::string& delimiters, std::vector<std::string>& tokens)
    {
        for (size_t n = str.find_first_of(delimiters), pn = 0; n != str.npos; pn = n + 1, n = str.find_first_of(delimiters, n + 1)) {
            if (pn == n) {
                tokens.push_back("");
            } else {
                tokens.push_back(str.substr(pn, n - pn));
            }
        }
    }*/

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
