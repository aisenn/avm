cmake_minimum_required(VERSION 3.13)
project(avm)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -lreadline")

add_executable(avm
        main.cpp
        IOperand.hpp
        OperandsFactory.cpp
        OperandsFactory.hpp
        Operand.hpp
        Stack.cpp
        Stack.hpp
        Parser.cpp
        Parser.hpp
        Operand.cpp AvmExceptions.cpp AvmExceptions.hpp Lexer.cpp Lexer.hpp)