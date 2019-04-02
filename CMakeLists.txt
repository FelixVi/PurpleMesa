cmake_minimum_required(VERSION 3.13)
project(PurpleMesa)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(VhdlParser src/vhdl_parser/vhdl_parser.y ${CMAKE_CURRENT_BINARY_DIR}/vhdl_parser.cpp)
FLEX_TARGET(VhdlLexer src/vhdl_parser/vhdl_lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/vhdl_lexer.cpp)

add_subdirectory(external/googletest/googletest)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        src/driver
        src/ast
        src/ast/AstNodes
        external/googletest/googletest/include
        )

add_executable(PurpleMesa
        src/main.cpp
        ${FLEX_VhdlLexer_OUTPUTS}
        ${BISON_VhdlParser_OUTPUTS}
        src/driver/vhdl_parser_driver.cpp
        )

add_executable(tests
        tests/tests.cpp

        ${FLEX_VhdlLexer_OUTPUTS}
        ${BISON_VhdlParser_OUTPUTS}
        src/driver/vhdl_parser_driver.cpp
        )

target_link_libraries(tests
        gtest
        gtest_main
        )