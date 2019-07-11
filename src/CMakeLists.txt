cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#########################################################################################
# Lexer
#########################################################################################
set(TPL_LEX_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/lex.l)
set(TPL_LEX_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc)
add_custom_command(
    OUTPUT ${TPL_LEX_OUTPUT}
    COMMAND flex++ ${TPL_LEX_INPUT}
    DEPENDS ${TPL_LEX_INPUT}
    COMMENT "Generating FLEX Scanner")
add_custom_target(tpl-lex-generate-files DEPENDS ${TPL_LEX_OUTPUT} ${TPL_LEX_INPUT})
set_source_files_properties(${TPL_LEX_OUTPUT} PROPERTIES GENERATED TRUE)
add_library(tpl-lex ${TPL_LEX_OUTPUT})
add_dependencies(tpl-lex tpl-lex-generate-files tpl-parse)

#########################################################################################
# Parser
#########################################################################################
set(TPL_PARSE_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/parse.y)
set(TPL_PARSE_OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/parse.tab.cc
    ${CMAKE_CURRENT_BINARY_DIR}/parse.tab.hh
    ${CMAKE_CURRENT_BINARY_DIR}/stack.hh
    ${CMAKE_CURRENT_BINARY_DIR}/position.hh
    ${CMAKE_CURRENT_BINARY_DIR}/location.hh
)
add_custom_command(
    OUTPUT ${TPL_PARSE_OUTPUT}
    COMMAND bison -d ${TPL_PARSE_INPUT}
    DEPENDS ${TPL_PARSE_INPUT}
    COMMENT "Generating BISON Parser")
add_custom_target(tpl-parse-generate-files DEPENDS ${TPL_PARSE_OUTPUT} ${TPL_PARSE_INPUT})
set_source_files_properties(${TPL_PARSE_OUTPUT} PROPERTIES GENERATED TRUE)
add_library(tpl-parse ${TPL_PARSE_OUTPUT})
add_dependencies(tpl-parse tpl-parse-generate-files)

#########################################################################################
# Main Library
#########################################################################################
# add_library(${TPL_LIBRARY}
#     src/lexer.cc
# )

# target_link_libraries(${TPL_LIBRARY}
#     tpl-lex
# )

# add_dependencies(${TPL_LIBRARY}
#     tpl-lex
# )

#########################################################################################
# Main Executable
#########################################################################################
add_executable(${TPL_BINARY}
    main.cc
)

target_link_libraries(${TPL_BINARY} tpl-lex tpl-parse)
