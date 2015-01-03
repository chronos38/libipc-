cmake_minimum_required(VERSION 2.8)

include(cmake/OptionalSource.cmake)
include(cmake/ParseArguments.cmake)

# Variablen
set(PROJECT_NAME_STR libipc++)
project(${PROJECT_NAME_STR})

set(CMAKE_SHARED_LIBRARY_PREFIX "") # Entfernt automatischen "lib" Prefix
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECT_DIR ${PROJECT_SOURCE_DIR}/ext)
set(OTHER_SOURCES)

if(UNIX AND NOT APPLE)
    set(LINUX 1)
endif()



# Compiler Flags
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Setting GCC flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -Wno-variadic-macros -Wuninitialized -Wcast-align -Wredundant-decls \
        -Wno-unknown-pragmas -fdata-sections -ffunction-sections -pedantic \
        -Wextra -Wold-style-cast -Wstrict-overflow -Woverloaded-virtual \
        -Wsign-promo -Wabi -Wmissing-declarations -Wall -std=c++1y -fpermissive")

else()
    message(STATUS "Setting MSVC flags")
    set(CMAKE_CXX_FLAGS "") # MSVC Definitionen hier einfügen
endif() 




# Subdirectories
add_subdirectory(${PROJECT_SOURCE_DIR}/source)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${EXT_PROJECT_DIR}/gtest)


enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)

include_directories(${GTEST_INCLUDE_DIRS} 
    ${COMMON_INCLUDES}
    
)


file(GLOB TEST_COMMON_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

if(NOT WIN32)
    
    add_subdirectory(${PROJECT_SOURCE_DIR}/test/linux)
    
    #file(GLOB TEST_LINUX_SRC_FILES ${PROJECT_SOURCE_DIR}/test/linux/*.cpp)
    
    set(TEST_LINUX_SRC_FILES
        ${PROJECT_SOURCE_DIR}/test/linux/ProcessTest.cpp
        ${PROJECT_SOURCE_DIR}/test/linux/PipeTest.cpp
        ${PROJECT_SOURCE_DIR}/test/linux/SemaphoreTest.cpp
        ${PROJECT_SOURCE_DIR}/test/linux/SharedMemoryTest.cpp
        ${PROJECT_SOURCE_DIR}/test/linux/MemoryMapTest.cpp
        ${PROJECT_SOURCE_DIR}/test/linux/FileLockTest.cpp
        ${PROJECT_SOURCE_DIR}/test/linux/NamedPipeTest.cpp
    )
    
    add_executable(${PROJECT_TEST_NAME} ${TEST_COMMON_SRC_FILES} ${TEST_LINUX_SRC_FILES})
    add_dependencies(${PROJECT_TEST_NAME} googletest ${PROJECT_NAME_STR})
        
    target_link_libraries(${PROJECT_TEST_NAME}
                    ${PROJECT_NAME_STR}
                    ${GTEST_LIBS_DIR}/libgtest.a
                    ${GTEST_LIBS_DIR}/libgtest_main.a
                    pthread
            )
else()
    file(GLOB TEST_WIN_SRC_FILES ${PROJECT_SOURCE_DIR}/test/win32/*.cpp)
    add_executable(${PROJECT_TEST_NAME} ${TEST_COMMON_SRC_FILES} ${TEST_LINUX_WIN_FILES})
    add_dependencies(${PROJECT_TEST_NAME} googletest)
    
    target_link_libraries(${PROJECT_TEST_NAME}
            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
    )
    target_link_libraries(${PROJECT_TEST_NAME}
            debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
            optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
    )
endif()

add_test(test1 ${PROJECT_TEST_NAME})
