cmake_minimum_required(VERSION 3.13)
project(PurpleMesa)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(VhdlParser src/vhdl_parser/vhdl_parser.y ${CMAKE_CURRENT_BINARY_DIR}/vhdl_parser.cpp)
FLEX_TARGET(VhdlLexer src/vhdl_parser/vhdl_lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/vhdl_lexer.cpp)

add_subdirectory(external/googletest/googletest)

SET (SRCS src/PurpleMesa.cpp

        src/vhdl_parser/vhdl_parser_driver.cpp

        src/AST/Passes/BindArchPass.cpp

        src/AST/Visitors/AstVisitor.cpp
        src/AST/Visitors/AstPrintVisitor.cpp
        src/AST/Visitors/RTIL/RTILVisitor.cpp

        src/AST/Nodes/AstNode.cpp
        )

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        src/AST
        src/AST/Nodes
        src
        external/googletest/googletest/include
        )

add_executable(PurpleMesa
        src/main.cpp
        ${SRCS}
        ${FLEX_VhdlLexer_OUTPUTS}
        ${BISON_VhdlParser_OUTPUTS}
        )

add_executable(tests
        tests/tests.cpp
        ${SRCS}
        ${FLEX_VhdlLexer_OUTPUTS}
        ${BISON_VhdlParser_OUTPUTS}
        )

target_link_libraries(tests
        gtest
        gtest_main
        )