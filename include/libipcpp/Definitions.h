#ifndef LIBIPC_DEFINITIONS_H
#define LIBIPC_DEFINITIONS_H

#ifdef _MSC_VER
#pragma once
#include <Windows.h>
#pragma warning(disable: 4290)
#define NOEXCEPT throw()

#ifdef LIBIPC_EXPORT
#define LIBIPC_API __declspec(dllexport)
#else
#define LIBIPC_API __declspec(dllimport)
#endif

namespace ipc {
    typedef HANDLE ProcessHandle;
    static const ProcessHandle PROCESS_NULL_HANDLE = nullptr;
}

#else
#define NOEXCEPT noexcept

#ifdef LIBIPC_EXPORT

#ifdef __CYGWIN__
#define LIBIPC_API __attribute__ ((dllexport))
#else
#define LIBIPC_API __attribute__ ((visibility ("default")))
#endif

#else

#ifdef __CYGWIN__
#define LIBIPC_API __attribute__ ((dllimport))
#else
#define LIBIPC_API __attribute__ ((visibility ("default")))
#endif

#endif
#endif

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <functional>
#include <exception>

namespace ipc {
    class LIBIPC_API ReferenceType
    {
    public:
        ReferenceType() = default;
        virtual ~ReferenceType() = default;

#ifdef _MSC_VER
        ReferenceType(ReferenceType&&);
        ReferenceType& operator=(ReferenceType&&);
#else
        ReferenceType(ReferenceType&&) = default;
        ReferenceType& operator=(ReferenceType&&) = default;
#endif
    private:
        ReferenceType(const ReferenceType&) = delete;
        ReferenceType& operator=(const ReferenceType&) = delete;
    };

    class LIBIPC_API IpcException : public std::exception
    {
    public:
        IpcException(const std::string&);
        ~IpcException() = default;
        const char* what() const override;
    private:
        std::string mMsg = "";
    };
}

#endif
