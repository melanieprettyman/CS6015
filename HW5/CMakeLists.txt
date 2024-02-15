cmake_minimum_required(VERSION 3.27)
project(HW6)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW6 main.cpp
        cmdline.cpp
        Expr.cpp
        parse.cpp
        tests.cpp)
