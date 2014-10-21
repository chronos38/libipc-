#ifndef UTILITY_H
#define UTILITY_H

#include <string>

namespace ipc {
    class Utility {

        /*!
         * Checks if a filename is compatible with Windows
         *
         * \params[in] fileName The filename that should be checked
         * \returns TRUE if the filename was OK, else FALSE
         */
        static bool isValidFileName(std::string& fileName);
    };

}
#endif