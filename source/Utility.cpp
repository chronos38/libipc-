#include "../include/libipcpp/Utility.h"
#include <algorithm>


namespace ipc {

    bool IsNumber(const std::string& input)
    {
        return !input.empty() && std::find_if(input.begin(), input.end(),
            [](char c) {return !std::isdigit(c); }) == input.end();
    }

    bool IsValidFileName(std::string& fileName)
    {

    }

    void SplitString(const std::string& str,
                          const std::string& delimiters,
                          std::vector< std::string >& tokens)
    {
        std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            lastPos = str.find_first_not_of(delimiters, pos);
            pos = str.find_first_of(delimiters, lastPos);
        }
    }

}