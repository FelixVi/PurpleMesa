cmake_minimum_required(VERSION 3.13)
project(PurpleMesa)

set(CMAKE_CXX_STANDARD 14)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(VhdlParser vhdl_parser/vhdl_parser.y ${CMAKE_CURRENT_BINARY_DIR}/vhdl_parser.cpp)
FLEX_TARGET(VhdlLexer vhdl_parser/vhdl_lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/vhdl_lexer.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR} driver)

add_executable(PurpleMesa
        main.cpp
        ${FLEX_VhdlLexer_OUTPUTS}
        ${BISON_VhdlParser_OUTPUTS}
        driver/vhdl_parser_driver.cpp)