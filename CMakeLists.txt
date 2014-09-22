project(libipc++)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_SHARED_LIBRARY_PREFIX "") #Entfernt automatischen "lib" Prefix

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-Wno-variadic-macros -Wuninitialized -Wcast-align -Wredundant-decls -Wno-unknown-pragmas -fdata-sections -ffunction-sections -pedantic -Wextra -Wold-style-cast -Wstrict-overflow -Woverloaded-virtual -Wsign-promo -Wabi -Wmissing-declarations -Wall -std=c++11") 
endif()

add_executable(libipc++_tests main.cpp)
#add_library(libipc++ SHARED Process.cpp)