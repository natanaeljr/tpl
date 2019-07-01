cmake_minimum_required(VERSION 3.0)

add_executable(${TPL_TEST}
    test_lexer.cc
)

target_link_libraries(${TPL_TEST} ${TPL_LIBRARY})