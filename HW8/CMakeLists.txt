cmake_minimum_required(VERSION 3.27)
project(HW8)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW8 main.cpp
        Expr.cpp
        parse.cpp
        tests.cpp
        val.cpp
        cmdline.cpp)
