cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#########################################################################################
# Scanner
#########################################################################################
set(TPL_LEXER_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/scanner.ll)
set(TPL_LEXER_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc)
add_custom_command(
    OUTPUT ${TPL_LEXER_OUTPUT}
    COMMAND flex++ -o ${TPL_LEXER_OUTPUT} ${TPL_LEXER_INPUT}
    DEPENDS ${TPL_LEXER_INPUT}
    COMMENT "Generating FLEX Scanner")
add_custom_target(tpl-lexer-generate-files DEPENDS ${TPL_LEXER_OUTPUT} ${TPL_LEXER_INPUT})
set_source_files_properties(${TPL_LEXER_OUTPUT} PROPERTIES GENERATED TRUE)
add_library(tpl-lexer ${TPL_LEXER_OUTPUT})
add_dependencies(tpl-lexer tpl-lexer-generate-files tpl-parser)

#########################################################################################
# Parser
#########################################################################################
set(TPL_PARSER_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/parser.yy)
set(TPL_PARSER_OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
    ${CMAKE_CURRENT_BINARY_DIR}/parser.h
    ${CMAKE_CURRENT_BINARY_DIR}/position.hh
    ${CMAKE_CURRENT_BINARY_DIR}/location.hh
    ${CMAKE_CURRENT_BINARY_DIR}/stack.hh
)
add_custom_command(
    OUTPUT ${TPL_PARSER_OUTPUT}
    COMMAND bison
        -o ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
        --defines=${CMAKE_CURRENT_BINARY_DIR}/parser.h
        ${TPL_PARSER_INPUT}
        DEPENDS ${TPL_PARSER_INPUT}
    COMMENT "Generating BISON Parser")
add_custom_target(tpl-parser-generate-files DEPENDS ${TPL_PARSER_OUTPUT} ${TPL_PARSER_INPUT})
set_source_files_properties(${TPL_PARSER_OUTPUT} PROPERTIES GENERATED TRUE)
add_library(tpl-parser ${TPL_PARSER_OUTPUT})
add_dependencies(tpl-parser tpl-parser-generate-files)

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
    driver.cc
)

target_link_libraries(${TPL_BINARY} tpl-lexer tpl-parser)
