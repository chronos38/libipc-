set(PROJECT_NAME_STR libipc++)
project(${PROJECT_NAME_STR})

cmake_minimum_required(VERSION 2.8)

set(CMAKE_SHARED_LIBRARY_PREFIX "") #Entfernt automatischen "lib" Prefix

if(CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(
                -Wno-variadic-macros -Wuninitialized -Wcast-align -Wredundant-decls 
                -Wno-unknown-pragmas -fdata-sections -ffunction-sections -pedantic 
                -Wextra -Wold-style-cast -Wstrict-overflow -Woverloaded-virtual 
                -Wsign-promo -Wabi -Wmissing-declarations -Wall -std=c++11) 
endif()

if(MSVC)
        set(MSVC_COMPILER_DEFS "") #MSVC Definitionen hier einfügen
endif() 



set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECT_DIR ${PROJECT_SOURCE_DIR}/ext)

add_subdirectory(${PROJECT_SOURCE_DIR}/source)

add_subdirectory(${EXT_PROJECT_DIR}/gtest)
add_definitions(${MSVC_COMPILER_DEFS})

enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)

include_directories(${GTEST_INCLUDE_DIRS} 
    ${COMMON_INCLUDES}
    
)

file(GLOB TEST_COMMON_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

if(NOT WIN32)
    file(GLOB TEST_LINUX_SRC_FILES ${PROJECT_SOURCE_DIR}/test/linux/*.cpp)
    add_executable(${PROJECT_TEST_NAME} ${TEST_COMMON_SRC_FILES} ${TEST_LINUX_SRC_FILES})
    add_dependencies(${PROJECT_TEST_NAME} googletest)
        
    target_link_libraries(${PROJECT_TEST_NAME}
                    ${GTEST_LIBS_DIR}/libgtest.a
                    ${GTEST_LIBS_DIR}/libgtest_main.a
                    pthread
            )
else()
    file(GLOB TEST_LINUX_SRC_FILES ${PROJECT_SOURCE_DIR}/test/win32/*.cpp)
    add_executable(${PROJECT_TEST_NAME} ${TEST_COMMON_SRC_FILES} ${TEST_LINUX_SRC_FILES})
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

#add_executable(libipc++_test main.cpp)
#add_library(libipc++ SHARED Process.cpp)
add_subdirectory(test/linux)
