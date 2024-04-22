cmake_minimum_required(VERSION 3.27)
project(HW10)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW10 main.cpp
        cmdline.cpp
        Expr.cpp
        parse.cpp
        tests.cpp
        val.cpp)
