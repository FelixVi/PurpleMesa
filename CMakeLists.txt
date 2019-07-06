cmake_minimum_required(VERSION 3.13)
project(PurpleMesa)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(VhdlParser src/vhdl_parser/vhdl_parser.y ${CMAKE_CURRENT_BINARY_DIR}/vhdl/vhdl_parser.cpp)
FLEX_TARGET(VhdlLexer src/vhdl_parser/vhdl_lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/vhdl/vhdl_lexer.cpp COMPILE_FLAGS)

BISON_TARGET(PurpleMesaParser src/kernel/PurpleMesa_parser.y ${CMAKE_CURRENT_BINARY_DIR}/pm/PurpleMesa_parser.cpp)
FLEX_TARGET(PurpleMesaLexer src/kernel/PurpleMesa_lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/pm/PurpleMesa_lexer.cpp COMPILE_FLAGS "-P yypm")

add_subdirectory(external/googletest/googletest)

SET (SRCS src/kernel/PurpleMesa.cpp

        src/vhdl_parser/vhdl_parser_driver.cpp

        src/kernel/PurpleMesa_parser_driver.cpp

        src/AST/Passes/BindArchPass.cpp

        src/AST/Visitors/AstVisitor.cpp
        src/AST/Visitors/AstPrintVisitor.cpp
        src/AST/Visitors/RTIL/RTILVisitor.cpp

        src/AST/Nodes/AstNode.cpp

        ${FLEX_VhdlLexer_OUTPUTS}
        ${BISON_VhdlParser_OUTPUTS}

        ${FLEX_PurpleMesaLexer_OUTPUTS}
        ${BISON_PurpleMesaParser_OUTPUTS}
        )

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/pm
        ${CMAKE_CURRENT_BINARY_DIR}/vhdl
        src/AST
        src/AST/Nodes
        src/kernel
        src
        src/vhdl_parser
        external/googletest/googletest/include
        )

add_executable(PurpleMesa
        src/main.cpp
        ${SRCS}
        )

add_executable(tests
        tests/tests.cpp
        ${SRCS}
        )

target_link_libraries(tests
        gtest
        gtest_main
        )

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pm)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vhdl)