#ifndef LIBIPC_PIPE_H
#define LIBIPC_PIPE_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Definitions.h"

namespace ipc {

    class LIBIPC_API Pipe
    {
        Pipe() = default;
        Pipe(const Pipe&) = default;
        ~Pipe() = default;

#ifdef _MSC_VER
        Pipe(Pipe&&);
#else
        Pipe(Pipe&&) = default;
#endif
    public:
        /*!
         *  Writes a block of data to the pipe.
         *
         * \params[in] buf The buffer containing the data to be written to the pipe
         * \params[in] size The buffers size
         * \returns The number of bytes written is returned
         */
        uint32_t Write(char * buf, uint32_t size);
        uint32_t Read(char * buf, uint32_t size);
        bool WriteByte(unsigned char);
        bool ReadByte(unsigned char);
        void Close();
        bool isOpen();
    };
}
#endif