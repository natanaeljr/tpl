cmake_minimum_required(VERSION 3.0)
project(tpl VERSION 0.1 LANGUAGES CXX C)

#########################################################################################
# Configs
#########################################################################################
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wconversion -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

#########################################################################################
# Global Defines
#########################################################################################
set(TPL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TPL_LIBRARY "tpl")
set(TPL_BINARY "tplc")
set(TPL_TEST "tpl-test")

#########################################################################################
# Dependencies
#########################################################################################
# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include_directories(${CONAN_INCLUDE_DIRS})
add_definitions(${CONAN_DEFINES})
link_libraries(${CONAN_LIBS})
# njr::enum_t
include_directories(third-party/enum_t/include)

#########################################################################################
# Project
#########################################################################################
include_directories(${TPL_INCLUDE_DIR})
add_subdirectory(src)

#########################################################################################
# Testing
#########################################################################################
if(BUILD_TESTING)
    add_subdirectory(test)
endif()
