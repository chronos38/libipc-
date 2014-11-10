set(SOURCES
    MessageQueue.cpp
    Pipe.cpp
    Process.cpp
    Semaphore.cpp
    SharedMemory.cpp
    Utility.cpp
    
    PARENT_SCOPE
)

set(HEADERS
    ../include/libipcpp/Definitions.h
    ../include/libipcpp/FileLock.h
    ../include/libipcpp/IOBase.h
    ../include/libipcpp/libipcpp.h
    ../include/libipcpp/LockGuard.h
    ../include/libipcpp/MemoryMap.h
    ../include/libipcpp/MessageQueue.h
    ../include/libipcpp/Pipe.h
    ../include/libipcpp/Process.h
    ../include/libipcpp/Semaphore.h
    ../include/libipcpp/SharedMemory.h
    ../include/libipcpp/Utility.h
    
    ../include/libipcpp/exception/FileLockException.h
    ../include/libipcpp/exception/IpcException.h
    ../include/libipcpp/exception/MemoryMapException.h
    ../include/libipcpp/exception/MessageQueueException.h
    ../include/libipcpp/exception/NamedPipeException.h
    ../include/libipcpp/exception/PipeException.h
    ../include/libipcpp/exception/ProcessException.h
    ../include/libipcpp/exception/SemaphoreException.h
    ../include/libipcpp/exception/SharedMemoryException.h
)

optional_source(LINUX
    SOURCES
        platform/linux/Process.cpp
    HEADERS
        ../include/libipcpp/platform/linux/Process.inl

)

optional_source(WIN32
    SOURCES
        platform/win32/Process.cpp
        platform/win32/Definitions.cpp
    HEADERS
        ../include/libipcpp/platform/win32/Process.inl
)

add_library(${PROJECT_NAME_STR} SHARED ${SOURCES} ${HEADERS})