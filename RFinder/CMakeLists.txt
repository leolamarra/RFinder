cmake_minimum_required(VERSION 3.31)
project(RFinder)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(RFinder 
        src/main.cpp
        src/Lexer.cpp
        src/Parser.cpp
        src/AST.cpp
)
