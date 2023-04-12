cmake_minimum_required(VERSION 3.21)
project(untitled3)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled3 main.cpp VM.cpp VM.h Commands.h Registers.h CommandsRepr.h Assembler.cpp Assembler.h Commands.cpp Registers.cpp CommandsRepr.cpp)
