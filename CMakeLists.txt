cmake_minimum_required(VERSION 3.0)
project(ger VERSION 0.1 LANGUAGES CXX C)

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
set(TPL_LIBRARY "tpllib")
set(TPL_BINARY "tpl")

#########################################################################################
# Dependencies
#########################################################################################
include_directories(third-party/enum_t/include)

#########################################################################################
# Project
#########################################################################################
include_directories(${TPL_INCLUDE_DIR})
add_executable(${TPL_BINARY}
    src/lexer.cc
)
